"""Hardware-free transmit validation using a native call-counting stub."""

import os
from pathlib import Path
import shutil
import subprocess
import sys

import pytest


@pytest.fixture(scope="module")
def transmit_library(tmp_path_factory):
    directory = tmp_path_factory.mktemp("transmit-library")
    source = directory / "mock.c"
    source.write_text(
        """
#ifdef _WIN32
#define API __declspec(dllexport)
#define CALL __stdcall
#else
#define API
#define CALL
#endif
static int calls;
static int network;
static int result = 1;
API int CALL icsneoTxMessages(void* handle, void* message, int net, int count) {
    ++calls;
    network = net;
    return result;
}
API int review_calls(void) { return calls; }
API int review_network(void) { return network; }
API void review_result(int value) { result = value; }
"""
    )
    if sys.platform == "win32":
        compiler = shutil.which("clang-cl")
        linker = shutil.which("lld-link")
        if not compiler or not linker:
            pytest.skip("Native transmit tests require clang-cl and lld-link")
        library = directory / "mock.dll"
        obj = directory / "mock.obj"
        bits = 64 if sys.maxsize > 2**32 else 32
        subprocess.run(
            [compiler, f"-m{bits}", "/nologo", "/c", "/GS-", "/Zl", str(source), f"/Fo{obj}"], check=True
        )
        command = [linker, "/dll", "/noentry", "/nodefaultlib", f"/out:{library}", str(obj)]
        if bits == 32:
            command.append("/export:icsneoTxMessages=_icsneoTxMessages@16")
        subprocess.run(command, check=True)
    else:
        compiler = shutil.which("cc")
        if not compiler:
            pytest.skip("Native transmit tests require a C compiler")
        library = directory / ("mock.dylib" if sys.platform == "darwin" else "mock.so")
        subprocess.run([compiler, "-shared", "-fPIC", str(source), "-o", str(library)], check=True)
    return library


def test_transmit_message_types(transmit_library):
    # Isolate the process-global library override from other tests. No real
    # device is opened and the mock never dereferences a message pointer.
    script = r'''
import ctypes
import sys
import ics

ics.override_library_name(sys.argv[1])
library = ctypes.CDLL(sys.argv[1])
device = ics.PyNeoDeviceEx()
device._auto_handle_close = False
invalid_device = ics.PyNeoDeviceEx()
invalid_device._auto_handle_close = False

for invalid in (None, 42, object(), "message", [], {}, invalid_device):
    for argument in (invalid, (invalid,), (ics.SpyMessage(), invalid),
                     (invalid, ics.SpyMessageJ1850()),
                     (ics.SpyMessage(), invalid, ics.SpyMessageJ1850())):
        before = library.review_calls()
        refs = sys.getrefcount(invalid)
        try:
            ics.transmit_messages(device, argument)
        except TypeError as error:
            assert "SpyMessage" in str(error)
        else:
            raise AssertionError(f"accepted invalid input: {argument!r}")
        assert library.review_calls() == before, "partially transmitted invalid batch"
        assert sys.getrefcount(invalid) == refs, "invalid input leaked a reference"

standard = ics.SpyMessage()
j1850 = ics.SpyMessageJ1850()
standard.NetworkID = 0x34
standard.NetworkID2 = 0x12
j1850.NetworkID = 0x78
j1850.NetworkID2 = 0x56
for argument, count, network in ((standard, 1, 0x1234), (j1850, 1, 0x5678),
                                 ((standard, j1850), 2, 0x5678), ((), 0, 0x5678)):
    before = library.review_calls()
    assert ics.transmit_messages(device, argument) is None
    assert library.review_calls() == before + count
    assert library.review_network() == network

library.review_result(0)
before = library.review_calls()
try:
    ics.transmit_messages(device, (standard, j1850))
except ics.RuntimeError:
    pass
else:
    raise AssertionError("native transmit failure was ignored")
assert library.review_calls() == before + 1
'''
    # Pass the actual imported package location even when pytest was launched
    # with an adjusted sys.path instead of an installed wheel.
    import ics

    environment = os.environ.copy()
    environment["PYTHONPATH"] = os.pathsep.join([str(Path(ics.__file__).resolve().parent.parent), *sys.path])
    subprocess.run([sys.executable, "-c", script, str(transmit_library)], env=environment, check=True)
