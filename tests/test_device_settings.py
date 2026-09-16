"""Hardware-free checks of the settings type passed across the native ABI."""

import os
from pathlib import Path
import shutil
import subprocess
import sys

import pytest


@pytest.fixture(scope="module")
def settings_library(tmp_path_factory):
    directory = tmp_path_factory.mktemp("settings-library")
    source = directory / "settings.c"
    source.write_text(r"""
#ifdef _WIN32
#define API __declspec(dllexport)
#define CALL __stdcall
#else
#define API
#define CALL
#endif
static int received = -99, discoveries, requests, slot, size;
API int CALL icsneoGetDeviceSettingsType(void* handle, int vnet, int* type) {
    ++discoveries;
    slot = vnet;
    *type = 27;
    return vnet != 98;
}
API int CALL icsneoGetDeviceSettings(void* handle, int* settings, int bytes, int vnet) {
    ++requests;
    received = *settings;
    slot = vnet;
    size = bytes;
    return vnet != 99;
}
API int observed(int field) {
    switch (field) {
    case 0: return received;
    case 1: return discoveries;
    case 2: return requests;
    case 3: return slot;
    default: return size;
    }
}
""")
    if sys.platform == "win32":
        compiler = shutil.which("clang-cl")
        linker = shutil.which("lld-link")
        if not compiler or not linker:
            pytest.skip("LLVM clang-cl and lld-link are required for the mock DLL")
        library = directory / "settings.dll"
        obj = directory / "settings.obj"
        target = "i686" if sys.maxsize <= 2**32 else "x86_64"
        subprocess.run([compiler, f"--target={target}-pc-windows-msvc", "/nologo", "/c", "/GS-", "/Zl",
                        str(source), f"/Fo{obj}"], check=True, capture_output=True, timeout=60)
        # The wrapper resolves undecorated API names, also on 32-bit Windows.
        exports = [] if target == "x86_64" else [
            "/export:icsneoGetDeviceSettings=_icsneoGetDeviceSettings@16",
            "/export:icsneoGetDeviceSettingsType=_icsneoGetDeviceSettingsType@12",
        ]
        subprocess.run([linker, "/dll", "/noentry", "/nodefaultlib", f"/out:{library}", str(obj), *exports],
                       check=True, capture_output=True, timeout=60)
    else:
        compiler = shutil.which("cc")
        if not compiler:
            pytest.skip("A C compiler is required for the mock library")
        library = directory / ("settings.dylib" if sys.platform == "darwin" else "settings.so")
        subprocess.run([compiler, "-dynamiclib" if sys.platform == "darwin" else "-shared", "-fPIC",
                        str(source), "-o", str(library)], check=True, capture_output=True, timeout=60)
    return library


@pytest.mark.parametrize("scenario", ["override", "first", "last", "discovery", "sentinel",
                                     "invalid", "overflow", "discovery_failure", "settings_failure"])
def test_device_settings_type(settings_library, scenario):
    # Isolate the process-global library override from all other tests.
    script = r"""
import ctypes
import sys
import ics

library, scenario = sys.argv[1:]
ics.override_library_name(library)
mock = ctypes.CDLL(library)
mock.observed.argtypes = [ctypes.c_int]
mock.observed.restype = ctypes.c_int
device = ics.PyNeoDeviceEx()
device._auto_handle_close = False
if scenario in ('invalid', 'overflow'):
    values = (-2, ics.DeviceSettingsTypeMax, ics.DeviceSettingsTypeMax + 1, 0xFFFFFFFF)
    if scenario == 'overflow':
        values = (2**100, -(2**100))
    for value in values:
        try:
            ics.get_device_settings(device, value)
        except (ValueError, OverflowError):
            pass
        else:
            raise AssertionError(f'accepted invalid override {value}')
    assert mock.observed(1) == mock.observed(2) == 0
elif scenario in ('discovery_failure', 'settings_failure'):
    discovery = scenario == 'discovery_failure'
    name = 'icsneoGetDeviceSettingsType()' if discovery else 'icsneoGetDeviceSettings()'
    try:
        ics.get_device_settings(device, -1 if discovery else ics.DeviceFire3SettingsType,
                                98 if discovery else 99)
    except ics.RuntimeError as error:
        assert name in str(error)
    else:
        raise AssertionError('native failure was ignored')
    assert mock.observed(1) == int(discovery)
    assert mock.observed(2) == int(not discovery)
else:
    expected = {'override': ics.DeviceFire3SettingsType, 'first': 0,
                'last': ics.DeviceSettingsTypeMax - 1}.get(scenario, ics.DeviceRADJupiterSettingsType)
    if scenario == 'discovery':
        result = ics.get_device_settings(device)
    else:
        result = ics.get_device_settings(device, -1 if scenario == 'sentinel' else expected, 2)
    assert mock.observed(0) == expected
    assert result.DeviceSettingType == expected
    assert mock.observed(1) == int(scenario in ('discovery', 'sentinel'))
    assert mock.observed(2) == 1
    assert mock.observed(3) == (ics.PlasmaIonVnetChannelMain if scenario == 'discovery' else 2)
    assert mock.observed(4) == ctypes.sizeof(result)
"""
    env = os.environ.copy()
    env["PYTHONPATH"] = os.pathsep.join(str(Path(path).resolve()) for path in sys.path)
    result = subprocess.run([sys.executable, "-c", script, str(settings_library), scenario],
                            env=env, capture_output=True, text=True, timeout=30)
    assert result.returncode == 0, result.stdout + result.stderr
