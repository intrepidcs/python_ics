"""Reference ownership regressions; native calls run only against a mock library."""
import os
from pathlib import Path
import shutil
import struct
import subprocess
import sys

import ics
import pytest


@pytest.mark.parametrize("message_type", [ics.SpyMessage, ics.SpyMessageJ1850])
@pytest.mark.parametrize("attribute", ["StatusBitField", "Data", "AckBytes", "Header", "ExtraDataPtr", "missing_attribute"])
def test_attribute_name_reference_count(message_type, attribute):
    message = message_type()
    name = "".join([attribute[:-1], attribute[-1:]])

    def read():
        try:
            getattr(message, name)
        except AttributeError:
            assert attribute == "missing_attribute"

    for _ in range(50):
        read()
    before = sys.getrefcount(name)
    for _ in range(1000):
        read()
    assert sys.getrefcount(name) == before


def test_native_helper_reference_counts(tmp_path):
    clang = shutil.which("clang")
    if not clang:
        pytest.skip("clang is required to build the hardware-free mock library")
    source = Path(__file__).with_name("reference_mock.c")
    library = tmp_path / ("reference_mock.dll" if sys.platform == "win32" else "reference_mock.so")
    if sys.platform == "win32":
        linker = shutil.which("lld-link")
        if not linker:
            pytest.skip("lld-link is required to link the hardware-free mock library")
        target = "x86_64-pc-windows-msvc" if struct.calcsize("P") == 8 else "i686-pc-windows-msvc"
        obj = tmp_path / "reference_mock.obj"
        subprocess.run([clang, "-target", target, "-c", str(source), "-o", str(obj)], check=True)
        exports = []
        if struct.calcsize("P") == 4:
            # ice looks up undecorated names; i686 stdcall exports include stack sizes.
            exports = [
                f"/export:{name}=_{name}@{size}"
                for name, size in [
                    ("icsneoOpenDevice", 28),
                    ("icsneoClosePort", 8),
                    ("icsneoFreeObject", 4),
                    ("icsneoGetDeviceStatus", 12),
                    ("icsneoISO15765_ReceiveMessage", 12),
                ]
            ]
        subprocess.run(
            [linker, "/dll", "/noentry", "/nodefaultlib", str(obj), f"/out:{library}", *exports], check=True
        )
    else:
        subprocess.run([clang, "-shared", "-fPIC", str(source), "-o", str(library)], check=True)
    # Isolate the global library override and module monkeypatches from the suite.
    env = os.environ.copy()
    env["ICS_REFERENCE_MOCK"] = str(library)
    result = subprocess.run(
        [sys.executable, "-m", "pytest", "-q", str(Path(__file__).with_name("_reference_helpers.py"))],
        env=env, capture_output=True, text=True, timeout=120,
    )
    assert result.returncode == 0, result.stdout + result.stderr
