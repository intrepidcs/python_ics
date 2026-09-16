"""Run in a subprocess by test_reference_leaks.py with a mock native library."""
import ctypes
import importlib
import os
import sys

import ics
import pytest


@pytest.fixture(autouse=True, scope="module")
def mock_library():
    ics.override_library_name(os.environ["ICS_REFERENCE_MOCK"])


@pytest.fixture
def device():
    device = ics.PyNeoDeviceEx()
    device._auto_handle_close = False
    return device


def assert_stable(target, action):
    for _ in range(50):
        action()
    before = sys.getrefcount(target)
    for _ in range(1000):
        action()
    assert sys.getrefcount(target) == before


def expect_error(action, error):
    with pytest.raises(error):
        action()


def test_handle_creation_and_clear(device):
    for _ in range(50):
        assert ics.open_device(device) is device
        capsule = device._handle
        assert sys.getrefcount(capsule) == 3  # local, device, getrefcount argument
        assert device._Handle == 0x1234
        assert ics.close_device(device) == 0
        assert device._handle is None
        assert sys.getrefcount(capsule) == 2


@pytest.mark.parametrize("kind", ["capsule", "noncapsule", "named_capsule"])
def test_handle_lookup(device, kind):
    if kind == "noncapsule":
        handle = object()
    else:
        new = ctypes.pythonapi.PyCapsule_New
        new.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_void_p]
        new.restype = ctypes.py_object
        handle = new(0x1234, b"wrong_name" if kind == "named_capsule" else None, None)
    device._handle = handle
    if kind == "named_capsule":
        action = lambda: expect_error(lambda: ics.get_device_status(device), ValueError)
    else:
        action = lambda: ics.get_device_status(device)
    assert_stable(handle, action)


@pytest.mark.parametrize("failure", ["missing", "raises"])
def test_handle_attribute_failure(device, monkeypatch, failure):
    if failure == "missing":
        monkeypatch.delattr(ics.PyNeoDeviceEx, "_handle")
        expect_error(lambda: ics.get_device_status(device), AttributeError)
    else:
        rejected = []

        def reject(self, value):
            rejected.append(value)
            raise ValueError("reject handle assignment")
        monkeypatch.setattr(ics.PyNeoDeviceEx, "_handle", property(lambda self: sentinel, reject))
        sentinel = object()
        assert_stable(sentinel, lambda: expect_error(lambda: ics.open_device(device), ValueError))
        # A failing setter never stole the helper's newly created reference.
        for capsule in rejected:
            assert sys.getrefcount(capsule) == 3  # list, loop local, getrefcount


@pytest.mark.parametrize("helper", ["construct", "isinstance"])
@pytest.mark.parametrize("case", ["success", "missing", "raises", "not_module"])
def test_module_references(device, monkeypatch, helper, case):
    name = "ics_device_status" if helper == "construct" else "st_cm_iso157652_rx_message"
    module_name = "ics.structures." + name
    module = importlib.import_module(module_name)
    cls = getattr(module, name)
    message = cls()
    action = (lambda: ics.get_device_status(device)) if helper == "construct" else (
        lambda: ics.iso15765_receive_message(device, 0, message)
    )
    if case == "missing":
        monkeypatch.delattr(module, name)
    elif case == "raises":
        if helper == "construct":
            def raises():
                raise ValueError("constructor failed")
            replacement = raises
        else:
            class Meta(type):
                def __instancecheck__(self, instance):
                    raise ValueError("instance check failed")
            replacement = Meta("FailingClass", (), {})
        monkeypatch.setattr(module, name, replacement)
    elif case == "not_module":
        module = object()
        monkeypatch.setitem(sys.modules, module_name, module)
    if case != "success":
        original_action = action
        error = ValueError if helper == "isinstance" and case == "raises" else ics.RuntimeError
        action = lambda: expect_error(original_action, error)
    assert_stable(module, action)
