"""Hardware-free handle ownership tests, isolated from the process-wide DLL override."""

import os
from pathlib import Path
import shutil
import subprocess
import sys

import pytest


@pytest.fixture(scope="module")
def handle_library(tmp_path_factory):
    root = tmp_path_factory.mktemp("handle-library")
    source = root / "mock.c"
    source.write_text(
        r"""
#ifdef _WIN32
#define API __declspec(dllexport)
#define CALL __stdcall
#else
#define API __attribute__((visibility("default")))
#define CALL
#endif
static int opens, closes, frees, fail_open, fail_close;
static char handles[16];
API int CALL icsneoOpenDevice(void* device, void** handle, unsigned char* networks,
                             int config, int options, void* extra, unsigned long reserved) {
    ++opens;
    if (fail_open) return 0;
    *handle = &handles[opens % 16];
    return 1;
}
API int CALL icsneoClosePort(void* handle, int* errors) { ++closes; *errors = 0; return !fail_close; }
API void CALL icsneoFreeObject(void* handle) { ++frees; }
API int counts(int which) { return which == 0 ? opens : which == 1 ? closes : frees; }
API void failures(int opening, int closing) { fail_open = opening; fail_close = closing; }
"""
    )
    if sys.platform == "win32":
        compiler = shutil.which("clang-cl")
        linker = shutil.which("lld-link")
        if not compiler or not linker:
            pytest.skip("handle mock requires clang-cl and lld-link")
        library = root / "mock.dll"
        obj = root / "mock.obj"
        bits = 64 if sys.maxsize > 2**32 else 32
        subprocess.run(
            [compiler, f"-m{bits}", "/nologo", "/c", "/GS-", "/Zl", str(source), f"/Fo{obj}"],
            check=True, timeout=60,
        )
        command = [linker, "/dll", "/noentry", "/nodefaultlib", f"/out:{library}", str(obj)]
        if bits == 32:
            # ice loads undecorated names; x86 stdcall exports are decorated.
            command.extend([
                "/export:icsneoOpenDevice=_icsneoOpenDevice@28",
                "/export:icsneoClosePort=_icsneoClosePort@8",
                "/export:icsneoFreeObject=_icsneoFreeObject@4",
            ])
        subprocess.run(command, check=True, timeout=60)
    else:
        compiler = shutil.which("cc")
        if not compiler:
            pytest.skip("handle mock requires a C compiler")
        library = root / ("mock.dylib" if sys.platform == "darwin" else "mock.so")
        subprocess.run([compiler, "-shared", "-fPIC", str(source), "-o", str(library)], check=True, timeout=60)
    return library


def run_case(library, code):
    import ics

    env = os.environ.copy()
    env["PYTHONPATH"] = str(Path(ics.__file__).resolve().parent.parent)
    result = subprocess.run(
        [sys.executable, "-c", """
import ctypes
import ics
import sys
import pytest
ics.override_library_name(sys.argv[1])
mock = ctypes.CDLL(sys.argv[1])
mock.counts.argtypes = [ctypes.c_int]
mock.counts.restype = ctypes.c_int
mock.failures.argtypes = [ctypes.c_int, ctypes.c_int]
mock.failures.restype = None
device = ics.PyNeoDeviceEx()
device._auto_handle_close = False
def counts():
    return tuple(mock.counts(i) for i in range(3))
""" + code, str(library)],
        env=env, capture_output=True, text=True, timeout=30,
    )
    assert result.returncode == 0, result.stdout + result.stderr


def test_reopen_rejected_without_native_open_and_close_allows_reopen(handle_library):
    run_case(handle_library, """
assert ics.open_device(device) is device
capsule = device._handle
handle = device._Handle
with pytest.raises(ics.RuntimeError, match="already open"):
    ics.open_device(device)
assert counts() == (1, 0, 0)
assert device._handle is capsule and device._Handle == handle
assert ics.close_device(device) == 0
assert device._handle is None
assert counts() == (1, 1, 1)
assert ics.open_device(device) is device
assert device._Handle != handle
assert ics.close_device(device) == 0
assert ics.close_device(device) == 0
assert counts() == (2, 2, 2)
""")


@pytest.mark.parametrize("fail_close", [0, 1])
def test_failed_python_assignment_releases_new_handle(handle_library, fail_close):
    run_case(handle_library, f"mock.failures(0, {fail_close})\n" + """
def reject_handle(self, value):
    raise MemoryError("injected handle assignment failure")
ics.PyNeoDeviceEx._handle = property(lambda self: None, reject_handle)
with pytest.raises(MemoryError, match="injected handle assignment failure"):
    ics.open_device(device)
assert device._handle is None
assert counts() == (1, 1, 1)
""")


def test_native_open_failure_does_not_publish_or_close_handle(handle_library):
    run_case(handle_library, r"""
mock.failures(1, 0)
with pytest.raises(ics.RuntimeError, match=r"icsneoOpenDevice\(\) Failed"):
    ics.open_device(device)
assert device._handle is None
assert counts() == (1, 0, 0)
mock.failures(0, 0)
assert ics.open_device(device) is device
assert ics.close_device(device) == 0
assert counts() == (2, 1, 1)
""")

