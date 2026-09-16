"""Exercise native buffer ownership in subprocesses using a hardware-free library."""

import os
from pathlib import Path
import shutil
import subprocess
import sys
import textwrap

import pytest


@pytest.fixture(scope="module")
def mock_libraries(tmp_path_factory):
    directory = tmp_path_factory.mktemp("buffer_exports")
    source = Path(__file__).with_name("buffer_exports_mock.c")
    libraries = []
    for missing in (False, True):
        name = "missing" if missing else "mock"
        defines = ["-DOMIT_BUFFER_APIS"] if missing else []
        if sys.platform == "win32":
            compiler = shutil.which("clang-cl")
            linker = shutil.which("lld-link")
            if not compiler or not linker:
                pytest.skip("LLVM clang-cl and lld-link are required for the mock DLL")
            library = directory / (name + ".dll")
            obj = directory / (name + ".obj")
            subprocess.run([compiler, "/nologo", "/c", "/GS-", "/Zl", *defines,
                            str(source), "/Fo" + str(obj)], check=True, capture_output=True)
            subprocess.run([linker, "/dll", "/noentry", "/nodefaultlib",
                            "/out:" + str(library), str(obj)], check=True, capture_output=True)
        else:
            compiler = shutil.which("cc")
            if not compiler:
                pytest.skip("A C compiler is required for the mock library")
            library = directory / (name + (".dylib" if sys.platform == "darwin" else ".so"))
            subprocess.run([compiler, "-shared", "-fPIC", *defines, str(source), "-o", str(library)],
                           check=True, capture_output=True)
        libraries.append(library)
    return libraries


def run_case(library, code):
    # Keep the process-global library override out of other tests. Use the same
    # import paths as pytest, including a locally built extension when selected.
    env = dict(os.environ, PYTHONPATH=os.pathsep.join(map(str, sys.path)))
    setup = f"""
import ctypes, gc, importlib, weakref
import ics
library = {str(library)!r}
mock = ctypes.CDLL(library)
mock.set_mode.argtypes = [ctypes.c_int]
mock.set_mode.restype = None
ics.override_library_name(library)
device = ics.PyNeoDeviceEx()
device._auto_handle_close = False
"""
    result = subprocess.run([sys.executable, "-c", setup + textwrap.dedent(code)],
                            env=env, capture_output=True, text=True, timeout=30)
    assert result.returncode == 0, result.stdout + result.stderr


@pytest.mark.parametrize("method,prefix,expected", [
    ("uart_write", "device, 0", 3),
    ("generic_api_send_command", "device, 0, 0, 0", 7),
    ("flash_accessory_firmware", "device", 1),
])
@pytest.mark.parametrize("path", ["success", "failure", "missing", "invalid_device"])
def test_input_exports_released(mock_libraries, method, prefix, expected, path):
    library = mock_libraries[path == "missing"]
    if path == "invalid_device":
        prefix = prefix.replace("device", "None")
    run_case(library, f"""
        mock.set_mode({int(path == 'failure')})
        data = bytearray(b'abc')
        try:
            result = ics.{method}({prefix}, data)
        except ics.RuntimeError:
            assert {path != 'success'!r}
        else:
            assert {path == 'success'!r}
            assert result == {expected}
        data.extend(b'd')
        assert data == b'abcd'
    """)


@pytest.mark.parametrize("method,args", [
    ("uart_write", "device, 0, data"),
    ("flash_accessory_firmware", "device, data"),
])
def test_checked_error_releases_input(mock_libraries, method, args):
    run_case(mock_libraries[0], f"""
        mock.set_mode(2)
        data = bytearray(b'abc')
        try:
            ics.{method}({args})
        except ics.RuntimeError:
            pass
        else:
            raise AssertionError('expected checked error')
        data.extend(b'd')
    """)


@pytest.mark.parametrize("method,module_name", [
    ("get_device_status", "ics_device_status"),
    ("get_hw_firmware_info", "st_api_firmware_info"),
    ("get_dll_firmware_info", "st_api_firmware_info"),
])
@pytest.mark.parametrize("path", ["success", "failure", "missing", "no_buffer"])
def test_result_objects_collectable(mock_libraries, method, module_name, path):
    run_case(mock_libraries[path == "missing"], f"""
        module = importlib.import_module('ics.structures.{module_name}')
        original = module.{module_name}
        refs = []
        class NoBuffer:
            pass
        def create():
            obj = NoBuffer() if {path == 'no_buffer'!r} else original()
            refs.append(weakref.ref(obj))
            return obj
        module.{module_name} = create
        mock.set_mode({int(path == 'failure')})
        try:
            result = ics.{method}(device)
        except (ics.RuntimeError, TypeError):
            assert {path != 'success'!r}
        else:
            assert {path == 'success'!r}
            assert isinstance(result, original)
            del result
        gc.collect()
        assert all(ref() is None for ref in refs)
        if {path != 'missing'!r}:
            assert len(refs) == 1
    """)


def test_status_size_mismatch_collectable(mock_libraries):
    run_case(mock_libraries[0], """
        module = importlib.import_module('ics.structures.ics_device_status')
        original = module.ics_device_status
        refs = []
        def create():
            obj = original()
            refs.append(weakref.ref(obj))
            return obj
        module.ics_device_status = create
        mock.set_mode(2)
        try:
            ics.get_device_status(device, True)
        except ics.RuntimeError:
            pass
        else:
            raise AssertionError('expected size mismatch')
        gc.collect()
        assert refs[0]() is None
    """)


def test_accessory_buffer_acquisition_failure(mock_libraries):
    run_case(mock_libraries[0], """
        try:
            ics.flash_accessory_firmware(device, object())
        except TypeError:
            pass
        else:
            raise AssertionError('expected buffer acquisition failure')
    """)


def test_uart_late_parse_failure_releases_once(mock_libraries):
    run_case(mock_libraries[0], """
        data = bytearray(b'abc')
        try:
            ics.uart_write(device, 0, data, object())
        except TypeError:
            pass
        else:
            raise AssertionError('expected argument conversion failure')
        data.extend(b'd')
    """)

