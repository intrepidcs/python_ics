"""Hardware-free script loading tests; each mock runs in a separate process."""

import os
from pathlib import Path
import shutil
import subprocess
import sys

import ics
import pytest


@pytest.fixture(scope="module")
def script_library(tmp_path_factory):
    root = tmp_path_factory.mktemp("script-library")
    source = root / "mock.c"
    source.write_text(r"""
#ifdef _WIN32
#define API __declspec(dllexport)
#define CALL __stdcall
#else
#define API __attribute__((visibility("default")))
#define CALL
#endif
API int CALL icsneoScriptLoad(void* h, const unsigned char* data, unsigned long size, int location) {
    unsigned long i;
    if (location == -1) return 0;
    for (i = 0; i < size; ++i) if (data[i] != (unsigned char)i) return 0;
    return 1;
}
API int CALL icsneoScriptLoadReadBin(void* h, const unsigned char* data, unsigned long size, int location) {
    return icsneoScriptLoad(h, data, size, location);
}
""")
    if sys.platform == "win32":
        compiler, linker = shutil.which("clang-cl"), shutil.which("lld-link")
        if not compiler or not linker:
            pytest.skip("LLVM is required for the mock DLL")
        library = root / "mock.dll"
        subprocess.run([compiler, "/nologo", "/c", "/GS-", "/Zl", str(source),
                        f"/Fo{root / 'mock.obj'}"], check=True, capture_output=True)
        subprocess.run([linker, "/dll", "/noentry", "/nodefaultlib", f"/out:{library}",
                        str(root / "mock.obj")], check=True, capture_output=True)
    else:
        compiler = shutil.which("cc")
        if not compiler:
            pytest.skip("C compiler is required for the mock library")
        library = root / "mock.so"
        subprocess.run([compiler, "-shared", "-fPIC", str(source), "-o", str(library)], check=True)
    return library


@pytest.mark.parametrize("loader", ["coremini_load", "load_readbin"])
@pytest.mark.parametrize("kind", ["file", "tuple"])
@pytest.mark.parametrize("failure", [False, True])
def test_script_load(script_library, tmp_path, loader, kind, failure):
    if not hasattr(ics, loader):
        pytest.skip("load_readbin requires the internal header build")
    # Preserve the exact extension under test without changing the parent process's DLL.
    env = os.environ.copy()
    env["PYTHONPATH"] = str(Path(ics.__file__).resolve().parent.parent)
    script = r'''
import ctypes
import sys
from pathlib import Path
import ics

library, loader, kind, failure, root = sys.argv[1:]
ics.override_library_name(library)
load = getattr(ics, loader)
device = ics.PyNeoDeviceEx()
device._auto_handle_close = False
payload = bytes(range(256)) * 4096
path = Path(root) / "payload.bin"
path.write_bytes(payload)
data = str(path) if kind == "file" else tuple(payload)

def call():
    if failure == "True":
        try:
            load(device, data, -1)
        except ics.RuntimeError:
            pass
        else:
            raise AssertionError("native failure was ignored")
    else:
        assert load(device, data, 0) is None

def private_bytes():
    # Windows private commit includes malloc storage even when it is not resident.
    class Counters(ctypes.Structure):
        _fields_ = [("cb", ctypes.c_ulong), ("PageFaultCount", ctypes.c_ulong)] + [
            (name, ctypes.c_size_t) for name in (
                "PeakWorkingSetSize", "WorkingSetSize", "QuotaPeakPagedPoolUsage",
                "QuotaPagedPoolUsage", "QuotaPeakNonPagedPoolUsage", "QuotaNonPagedPoolUsage",
                "PagefileUsage", "PeakPagefileUsage", "PrivateUsage")]
    counters = Counters()
    kernel = ctypes.WinDLL("kernel32", use_last_error=True)
    kernel.GetCurrentProcess.restype = ctypes.c_void_p
    psapi = ctypes.WinDLL("psapi", use_last_error=True)
    psapi.GetProcessMemoryInfo.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_ulong]
    assert psapi.GetProcessMemoryInfo(kernel.GetCurrentProcess(), ctypes.byref(counters), ctypes.sizeof(counters))
    return counters.PrivateUsage

for _ in range(4):
    call()
before = private_bytes() if sys.platform == "win32" else None
for _ in range(32):
    call()
if before is not None:
    growth = private_bytes() - before
    print("private byte growth:", growth)
    assert growth < 8 * 1024 * 1024, growth

# Failed conversions must preserve their exception and never call the native API.
for value, error in [(object(), ics.RuntimeError), (1 << 100, OverflowError)]:
    try:
        load(device, (0, value), 0)
    except error:
        pass
    else:
        raise AssertionError("invalid tuple accepted")
empty = Path(root) / "empty.bin"
empty.write_bytes(b"")
assert load(device, str(empty), 0) is None
assert load(device, (), 0) is None
try:
    load(device, str(Path(root) / "missing.bin"), 0)
except ics.RuntimeError:
    pass
else:
    raise AssertionError("missing file accepted")
'''
    result = subprocess.run([sys.executable, "-c", script, str(script_library), loader, kind,
                             str(failure), str(tmp_path)], env=env, capture_output=True, text=True)
    assert result.returncode == 0, result.stdout + result.stderr
