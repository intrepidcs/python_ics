"""Hardware-independent radio message parsing regressions.

Run each call in a child process so native parser crashes become test failures.
"""

import os
import subprocess
import sys

import pytest


@pytest.mark.parametrize(
    "code",
    [
        "assert ics.create_neovi_radio_message() == (0, 0, 0, 0, 0)",
        """assert ics.create_neovi_radio_message(
            Relay1=1, Relay2=0, Relay3=2, Relay4=0, Relay5=255,
            LED5=0, LED6=1, MSB_report_rate=0x123, LSB_report_rate=0x45,
            analog_change_report_rate=0x67, relay_timeout=0x89,
        ) == (0x55, 0x23, 0x45, 0x67, 0x89)""",
        "assert ics.create_neovi_radio_message(0, 1, 0, 1, 0, 1, 0, 255, 128, 1, 2) == (0x2A, 255, 128, 1, 2)",
        "assert ics.create_neovi_radio_message(relay_timeout=255) == (0, 0, 0, 0, 255)",
        """try:
    ics.create_neovi_radio_message(unknown=1)
except TypeError:
    pass
else:
    raise AssertionError('unknown keyword was accepted')""",
        *[
            f"""try:
    ics.create_neovi_radio_message(**{{{name!r}: {value!r}}})
except {error}:
    pass
else:
    raise AssertionError('invalid argument was accepted')"""
            for name in ("Relay1", "Relay2", "Relay3", "Relay4", "Relay5", "LED5", "LED6")
            for value, error in ((-1, "OverflowError"), (256, "OverflowError"), ("bad", "TypeError"))
        ],
    ],
    ids=["defaults", "all-keywords", "positional", "last-keyword", "unknown-keyword"]
    + [
        f"{name}-{case}"
        for name in ("Relay1", "Relay2", "Relay3", "Relay4", "Relay5", "LED5", "LED6")
        for case in ("negative", "overflow", "non-integer")
    ],
)
def test_create_neovi_radio_message_subprocess(code):
    env = os.environ.copy()
    # Preserve the test runner's import path, including an in-place extension.
    env["PYTHONPATH"] = os.pathsep.join(sys.path)
    prelude = "import ics\n"
    if sys.platform == "win32":
        # Suppress Windows Error Reporting dialogs when testing a broken build.
        prelude = "import ctypes\nctypes.windll.kernel32.SetErrorMode(3)\n" + prelude
    result = subprocess.run(
        [sys.executable, "-c", prelude + code],
        env=env,
        capture_output=True,
        text=True,
        timeout=30,
    )
    assert result.returncode == 0, (
        f"child exited with {result.returncode}\nstdout: {result.stdout}\nstderr: {result.stderr}"
    )
