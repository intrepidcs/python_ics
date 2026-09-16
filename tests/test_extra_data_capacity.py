"""Payload bounds must not depend on mutable wire-format length fields."""
import ctypes
import os
import subprocess
import sys

import ics
import pytest


MESSAGE_TYPES = [ics.SpyMessage, ics.SpyMessageJ1850]
PACKED_PROTOCOLS = [ics.SPY_PROTOCOL_ETHERNET, ics.SPY_PROTOCOL_A2B, ics.SPY_PROTOCOL_SPI, ics.SPY_PROTOCOL_WBMS]


@pytest.mark.parametrize("message_type", MESSAGE_TYPES)
@pytest.mark.parametrize("attribute", ["NumberBytesData", "NumberBytesHeader", "Protocol"])
def test_subclass_descriptors_cannot_replace_payload_during_rollback(message_type, attribute):
    script = r'''
import ics
import sys

base = getattr(ics, sys.argv[1])
attribute = sys.argv[2]
calls = []
def replace_payload(self, value):
    calls.append(True)
    self.ExtraDataPtr = (2, 3)
    getattr(base, attribute).__set__(self, value)
def delete_payload(self):
    self.ExtraDataPtr = (2, 3)
    # A deletion callback may leave inconsistent fields; the getter must reject
    # them, but rollback must never resurrect the freed original payload.
    base.NumberBytesData.__set__(self, 3)
message_type = type("Message", (base,), {attribute: property(fset=replace_payload, fdel=delete_payload)})
msg = message_type()
base.Protocol.__set__(msg, ics.SPY_PROTOCOL_SPI)
if attribute == "Protocol":
    base.Protocol.__set__(msg, ics.SPY_PROTOCOL_CANFD)
    base.NumberBytesHeader.__set__(msg, 1)
msg.ExtraDataPtr = (17,)
value = {"NumberBytesData": 3, "NumberBytesHeader": 1, "Protocol": ics.SPY_PROTOCOL_ETHERNET}[attribute]
try:
    setattr(msg, attribute, value)
except ValueError:
    pass
else:
    raise AssertionError("unsafe native field accepted")
assert calls == []
assert msg.ExtraDataPtr == (17,)
delattr(msg, attribute)
try:
    msg.ExtraDataPtr
except ValueError:
    pass
else:
    raise AssertionError("inconsistent deletion result accepted")
base.NumberBytesData.__set__(msg, 2)
assert msg.ExtraDataPtr == (2, 3)
del msg
'''
    env = os.environ.copy()
    env["PYTHONPATH"] = os.pathsep.join(str(path) for path in sys.path)
    result = subprocess.run([sys.executable, "-c", script, message_type.__name__, attribute],
                            env=env, capture_output=True, text=True, timeout=30)
    assert result.returncode == 0, result.stdout + result.stderr


@pytest.mark.parametrize("message_type", MESSAGE_TYPES)
@pytest.mark.parametrize("protocol", [ics.SPY_PROTOCOL_CANFD] + PACKED_PROTOCOLS)
def test_payload_length_cannot_exceed_allocation(message_type, protocol):
    msg = message_type()
    msg.Protocol = protocol
    msg.ExtraDataPtr = (17,)
    with pytest.raises(ValueError, match="capacity"):
        msg.NumberBytesData = 64
    assert msg.NumberBytesData == 1
    assert msg.ExtraDataPtr == (17,)
    if protocol in PACKED_PROTOCOLS:
        with pytest.raises(ValueError, match="capacity"):
            msg.NumberBytesHeader = 1
        assert msg.NumberBytesHeader == 0


@pytest.mark.parametrize("message_type", MESSAGE_TYPES)
@pytest.mark.parametrize("protocol", PACKED_PROTOCOLS)
def test_protocol_change_cannot_reinterpret_header_as_extra_capacity(message_type, protocol):
    msg = message_type()
    msg.Protocol = ics.SPY_PROTOCOL_CANFD
    msg.NumberBytesHeader = 1
    msg.ExtraDataPtr = (17,)
    with pytest.raises(ValueError, match="capacity"):
        msg.Protocol = protocol
    assert msg.Protocol == ics.SPY_PROTOCOL_CANFD
    assert msg.ExtraDataPtrEnabled == 1
    assert msg.ExtraDataPtr == (17,)


@pytest.mark.parametrize("message_type", MESSAGE_TYPES)
def test_data_and_header_updates_are_atomic(message_type):
    msg = message_type()
    msg.Protocol = ics.SPY_PROTOCOL_SPI
    msg.ExtraDataPtr = (17,)
    with pytest.raises(ValueError, match="capacity"):
        msg.Data = (1, 2)
    assert msg.Data == (0,)
    if message_type is ics.SpyMessageJ1850:
        with pytest.raises(ValueError, match="capacity"):
            msg.Header = (1,)
        assert msg.Header == ()
    assert msg.ExtraDataPtr == (17,)


@pytest.mark.parametrize("message_type", MESSAGE_TYPES)
def test_capacity_survives_shrink_replacement_and_cleanup_flag(message_type):
    msg = message_type()
    msg.Protocol = ics.SPY_PROTOCOL_SPI
    payload = tuple(i & 255 for i in range(300))
    msg.ExtraDataPtr = payload
    msg.NumberBytesHeader = 0
    assert msg.ExtraDataPtr == payload[:44]
    msg.NumberBytesHeader = 1
    assert msg.ExtraDataPtr == payload
    msg.ExtraDataPtr = (2, 3)
    msg.noExtraDataPtrCleanup = True
    try:
        with pytest.raises(ValueError, match="capacity"):
            msg.NumberBytesData = 3
    finally:
        msg.noExtraDataPtrCleanup = False
    with pytest.raises(TypeError):
        msg.ExtraDataPtr = (1, "bad")
    assert msg.ExtraDataPtr == (2, 3)
    msg.ExtraDataPtr = ()
    with pytest.raises(ValueError, match="capacity"):
        msg.NumberBytesData = 1
    assert msg.ExtraDataPtr is None


@pytest.mark.parametrize("message_type", MESSAGE_TYPES)
def test_direct_descriptor_write_still_cannot_read_past_payload(message_type):
    msg = message_type()
    msg.ExtraDataPtr = (17,)
    # Member descriptors bypass tp_setattro; the getter must defend itself too.
    message_type.NumberBytesData.__set__(msg, 64)
    with pytest.raises(ValueError, match="capacity"):
        _ = msg.ExtraDataPtr


@pytest.mark.parametrize("attribute", ["NumberBytesData", "Data", "Header", "Protocol"])
def test_reentrant_integer_conversion_preserves_replacement_payload(attribute):
    msg = ics.SpyMessageJ1850()
    msg.Protocol = ics.SPY_PROTOCOL_CANFD
    msg.ExtraDataPtr = (17,)

    class ReplacePayload:
        def __index__(self):
            msg.ExtraDataPtr = (2, 3)
            if attribute == "Header":
                msg.Protocol = ics.SPY_PROTOCOL_SPI
            if attribute == "Protocol":
                msg.NumberBytesHeader = 1
                return ics.SPY_PROTOCOL_SPI
            return 3

    value = ReplacePayload()
    if attribute == "Data":
        value = (value, 4, 5)
    elif attribute == "Header":
        value = (value,)
    with pytest.raises(ValueError, match="capacity"):
        setattr(msg, attribute, value)
    assert msg.ExtraDataPtr == (2, 3)
    assert msg.NumberBytesData == 2


@pytest.mark.parametrize("attribute", ["NumberBytesData", "NumberBytesHeader", "Protocol"])
@pytest.mark.parametrize("value", [-1, 259])
def test_out_of_range_scalar_does_not_call_warning_hook(attribute, value, monkeypatch):
    import warnings

    msg = ics.SpyMessage()
    msg.ExtraDataPtr = (17,)
    calls = []

    def replace_payload(*args, **kwargs):
        calls.append(True)
        msg.ExtraDataPtr = (2, 3)

    monkeypatch.setattr(warnings, "showwarning", replace_payload)
    with warnings.catch_warnings():
        warnings.simplefilter("always")
        with pytest.raises(ValueError, match="0..255"):
            setattr(msg, attribute, value)
    assert calls == []
    assert msg.ExtraDataPtr == (17,)


@pytest.mark.parametrize("message_type", MESSAGE_TYPES)
@pytest.mark.parametrize("operation", ["transmit", "tx_script", "rx_script", "rx_mask"])
def test_invalid_payload_is_rejected_before_native_library_lookup(message_type, operation):
    device = ics.PyNeoDeviceEx()
    device._auto_handle_close = False
    # No device or native library is opened. The sentinel capsule only passes
    # handle extraction; validation must reject the message before native use.
    capsule_new = ctypes.pythonapi.PyCapsule_New
    capsule_new.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_void_p]
    capsule_new.restype = ctypes.py_object
    device._handle = capsule_new(1, None, None)
    msg = message_type()
    msg.ExtraDataPtr = (17,)
    message_type.NumberBytesData.__set__(msg, 64)
    j1850 = message_type is ics.SpyMessageJ1850
    with pytest.raises(ValueError, match="capacity"):
        if operation == "transmit":
            ics.transmit_messages(device, (message_type(), msg))
        elif operation == "tx_script":
            ics.coremini_write_tx_message(device, 0, msg, j1850)
        elif operation == "rx_script":
            ics.coremini_write_rx_message(device, 0, msg, message_type(), j1850)
        else:
            ics.coremini_write_rx_message(device, 0, message_type(), msg, j1850)
