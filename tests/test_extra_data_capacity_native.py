"""Exercise DLL-owned payloads in a subprocess; never load a hardware library."""
import os
from pathlib import Path
import subprocess
import sys

import pytest


def test_received_payload_capacity_and_native_transmit(tmp_path):
    # setuptools supplies portable compiler discovery, including MSVC. This
    # integration test needs the same native toolchain as the extension build.
    pytest.importorskip("setuptools")
    from setuptools._distutils.ccompiler import new_compiler
    from setuptools._distutils.sysconfig import customize_compiler

    compiler = new_compiler()
    customize_compiler(compiler)
    root = Path(__file__).resolve().parents[1]
    objects = compiler.compile(
        [str(root / "tests" / "extra_data_capacity_mock.cpp")],
        output_dir=str(tmp_path),
        include_dirs=[str(root / "include" / "ics")],
        macros=[("EXTERNAL_PROJECT", "1")],
    )
    library = tmp_path / ("capacity_mock.dll" if os.name == "nt" else "capacity_mock.so")
    extra_args = []
    if os.name == "nt" and sys.maxsize <= 2**32:
        # stdcall exports are decorated on x86, but the runtime resolves the
        # vendor API by its undecorated names.
        exports = {"icsneoGetDLLVersion": 0, "icsneoWaitForRxMessagesWithTimeOut": 8,
                   "icsneoGetMessages": 16, "icsneoScriptReadTxMessage": 12,
                   "icsneoScriptReadRxMessage": 16, "icsneoTxMessages": 16, "capacity_mock_calls": 0}
        extra_args = [f"/EXPORT:{name}=_{name}@{size}" for name, size in exports.items()]
    compiler.link_shared_object(objects, str(library), target_lang="c++", extra_postargs=extra_args)
    script = r'''
import ctypes
import gc
import sys
import ics

ics.override_library_name(sys.argv[1])
dll = (ctypes.WinDLL if sys.platform == "win32" else ctypes.CDLL)(sys.argv[1])
device = ics.PyNeoDeviceEx()
device._auto_handle_close = False
payload = tuple(i & 255 for i in range(300))
for j1850 in (False, True):
    for source in ("receive", "script", "rx_message", "rx_mask"):
        if source == "receive":
            messages, errors = ics.get_messages(device, j1850, 0)
            assert errors == 0
            msg = messages[0]
        elif source == "script":
            msg = ics.coremini_read_tx_message(device, 0, j1850)
        else:
            pair = ics.coremini_read_rx_message(device, 0, j1850)
            assert all(m.ExtraDataPtr == payload for m in pair)
            msg = pair[source == "rx_mask"]
        assert msg.ExtraDataPtr == payload
        assert msg.noExtraDataPtrCleanup
        msg.NumberBytesHeader = 0
        assert msg.ExtraDataPtr == payload[:44]
        msg.NumberBytesHeader = 1
        try:
            msg.NumberBytesData = 45
        except ValueError:
            pass
        else:
            raise AssertionError("received capacity was enlarged")
        before = dll.capacity_mock_calls()
        ics.transmit_messages(device, msg)
        assert dll.capacity_mock_calls() == before + 1
        type(msg).NumberBytesHeader.__set__(msg, 2)
        for operation in (lambda: msg.ExtraDataPtr, lambda: ics.transmit_messages(device, msg)):
            try:
                operation()
            except ValueError:
                pass
            else:
                raise AssertionError("descriptor bypass exposed native payload")
        assert dll.capacity_mock_calls() == before + 1
        # Replacement must not delete the DLL's static buffer, and must set a
        # new bound independent of the received length.
        msg.ExtraDataPtr = (9,)
        assert msg.ExtraDataPtr == (9,)
        assert not msg.noExtraDataPtrCleanup
        del msg
        gc.collect()
print("mock receive, script read, replacement and transmit bounds passed")
'''
    result = subprocess.run([sys.executable, "-c", script, str(library)], text=True, capture_output=True)
    assert result.returncode == 0, result.stdout + result.stderr
