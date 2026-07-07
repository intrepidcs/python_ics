"""Validate generated ctypes struct sizes against the header's *_SIZE macros.

Every `#define <Name>_SIZE (N)` in icsnVC40.h is exported as a module
constant; the matching generated ctypes struct must have the same
ctypes.sizeof. Catches header/generator layout drift on header updates.
"""
import ctypes
import importlib
import inspect
import pkgutil

import pytest
import ics
import ics.structures

# Upstream header bugs: macro value disagrees with the actual struct.
# Keep entries here only with a comment explaining the discrepancy.
KNOWN_STALE_MACROS = {
    # Upstream never updated the macro after the struct grew to 56 bytes
    # (still 40 in vspy 3.26.3.9). Reported to header owners.
    "RAD_GPTP_AND_TAP_SETTINGS_SIZE",
}

# Macros whose name doesn't map to a generated struct class (nested/typedef
# variants). Count is asserted so silent growth gets investigated.
EXPECTED_UNMATCHED = 11


def _struct_registry():
    registry = {}
    for info in pkgutil.iter_modules(ics.structures.__path__):
        mod = importlib.import_module(f"ics.structures.{info.name}")
        for name, obj in inspect.getmembers(mod, inspect.isclass):
            if (
                issubclass(obj, (ctypes.Structure, ctypes.Union))
                and obj.__module__ == mod.__name__
            ):
                registry["".join(c for c in name.lower() if c.isalnum())] = obj
    return registry


def test_generated_struct_sizes_match_header_macros():
    registry = _struct_registry()
    mismatches = []
    unmatched = []
    matched = 0
    for macro in (n for n in dir(ics) if n.endswith("_SIZE")):
        key = "".join(c for c in macro[:-5].lower() if c.isalnum())
        cls = registry.get(key)
        if cls is None:
            unmatched.append(macro)
            continue
        expected = getattr(ics, macro)
        actual = ctypes.sizeof(cls)
        if actual == expected:
            matched += 1
        elif macro not in KNOWN_STALE_MACROS:
            mismatches.append(f"{macro}: header says {expected}, ctypes says {actual}")
    assert not mismatches, "\n".join(mismatches)
    # 3.26.3.9 removed 5 legacy settings structs (SRedSettings, SFireSettings,
    # SVCAN3Settings, SECUSettings, SPendantSettings) and their *_SIZE macros
    # together, dropping the matched baseline from 77 to 72. That is a clean
    # removal, not a mapping regression: both sides disappeared in lockstep.
    assert matched >= 72, f"only {matched} macros matched a struct; mapping regressed"
    assert len(unmatched) <= EXPECTED_UNMATCHED, f"unmatched grew: {sorted(unmatched)}"
