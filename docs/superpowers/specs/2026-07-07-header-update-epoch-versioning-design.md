# Design: icsnVC40.h 3.26.3.9 update + PEP 440 epoch versioning

Date: 2026-07-07
Status: approved

## Problem

1. python_ics headers are at the v923-era icsnVC40.h; Vehicle Spy 3.26.3.9
   (`C:\dev\vspy3\Core\Hardware\`) ships a newer header with renamed
   deprecated devices, removed legacy settings structs, and new/grown
   structures.
2. The project's versioning scheme changed from `923.11` (icsneo40 DLL
   era) to `26.3.9` (Vspy-aligned). PEP 440 orders `923.11 > 26.3.9`, so a
   plain `26.3.9` upload would never be selected by pip: fresh installs
   would keep resolving 923.11 and existing users would never see
   upgrades. Nothing 26.x has been published to PyPI (verified 2026-07-07;
   latest is 923.11), so the fix can land before anything breaks.

## Decisions (made with maintainer)

- **Version scheme:** PEP 440 epoch — release as `1!26.3.9`.
- **Legacy names:** mirror the new header as-is; no Python-side compat
  aliases for `NEODEVICE_BLUE`/`_FIRE`/`_VCAN3`/... (now `*_DEPRECATED`)
  or the deleted `SRedSettings`/`SFireSettings`/... structs. The epoch
  bump is the breaking-change signal; legacy-device users stay on 923.11.
- **Local header patch:** drop `include/ics/icsnVC40.h.patch`. Upstream
  3.26.3.9 carries its own `pack(4)` (around the `icsDeviceStatus` union
  only). Matching the exact header the 3.26.3.9 icsneo40.dll was built
  against is the ABI-safe choice.

## 1. Versioning migration

Versions come from git tags via dunamai (`ics_utility.get_pkg_version`).
dunamai's default tag pattern already parses epochs (verified:
`v1!26.3.9` → `1!26.3.9`), so no version-machinery code changes.

- Tag releases `v1!<vspy-version>`: first one is `v1!26.3.9`.
- Dry-run before tagging: build sdist+wheel locally, confirm wheel
  filename and METADATA carry `1!26.3.9`, and confirm pip resolves the
  local wheel as an upgrade over an installed 923.11.
- README: short section explaining the epoch — why `1!` exists, that
  `pip install -U python_ics` moves 923.11 users to `1!26.3.9`, and that
  exact pins must be `==1!26.3.9`.
- Release-process note: all future tags keep the `1!` prefix
  (`v1!26.4.0`, ...). A bare `v26.4.0` tag would silently sort below
  923.11 again.
- No PyPI yanking required.

## 2. Header import

- Copy `C:\dev\vspy3\Core\Hardware\icsnVC40.h` and `cicsSpyStatusBits.h`
  verbatim into `include/ics/`.
- Delete `include/ics/icsnVC40.h.patch`.
- Sanity-diff old vs new header; expected changes: deprecated renames,
  legacy settings structs removed, RADComet3 / RADGigastar2 / CMP
  structures added, grown structs (SRADGalaxy2Settings 960→1204,
  SRADComet3Settings 918, SRADGigastar2Settings 2400).
- Verify `descIdType` is still `int16_t` (generator carries a hand-coded
  override in generate_icsneo40_structs.py).

## 3. Regeneration and build

- Work off `master` (PR #233 is merged as d6e0abf) — its generator fixes
  (unsigned 32-bit enum handling, descIdType) are prerequisites for a
  clean regen.
- Rerun extract_icsneo40_defines.py / generate_icsneo40_structs.py
  pipeline; regenerate setup_module_auto_defines.cpp and ctypes structs.
- Rebuild the extension; fix any C++ references to renamed NEODEVICE_*
  constants surfaced by the compiler.
- Validate generated ctypes struct sizes against the header's `*_SIZE`
  macros (same method as the June 2026 audit), with attention to the
  grown/new structs.
- Out of scope: binding any new 3.26 DLL APIs. Header, regen, and
  versioning only.

## 4. Testing and hardware verification

- Full pytest suite passes (26 tests; test_defines constants still exist
  under the new header).
- FIRE3 bench: find/open, Ethernet tx/rx roundtrip (procedure from the
  PR #233 verification), and get_device_status() — currently failing,
  may be fixed by the matched header layout. Check the installed
  icsneo40.dll version first; if older than 3.26.3.9, note the
  limitation instead of blocking.

## Risks

- Extractor's clang preprocess step may trip on new header constructs —
  caught at regen time.
- Bench DLL older than 3.26.3.9 leaves get_device_status unverified.
- Removed legacy names break old scripts by design; communicated via the
  epoch bump and README note.
