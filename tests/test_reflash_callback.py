"""Hardware-free callback tests; each case owns an isolated native-library registration."""

import os
from pathlib import Path
import shutil
import subprocess
import sys

import pytest


@pytest.fixture(scope="module")
def callback_libraries(tmp_path_factory):
    directory = tmp_path_factory.mktemp("reflash_callback")
    source = directory / "callback.c"
    source.write_text(r"""
#ifdef _WIN32
#define API __declspec(dllexport)
#define CALL __stdcall
typedef unsigned short wchar_t;
#else
#include <stddef.h>
#define API __attribute__((visibility("default")))
#define CALL
#endif
typedef void (*callback_t)(const wchar_t*, unsigned long);
static callback_t callback;
static int fire_on_registration;
API void fire_callback(void);
API void set_fire_on_registration(int value) { fire_on_registration = value; }
#ifndef OMIT_SETTER
API void CALL icsneoSetReflashCallback(callback_t value) {
    callback = value;
    if (fire_on_registration) fire_callback();
}
#endif
API void fire_callback(void) {
    static const wchar_t message[] = { 'p', 'r', 'o', 'g', 'r', 'e', 's', 's', 0x2713, 0 };
    if (callback) callback(message, 42);
}
""")
    libraries = []
    for missing in (False, True):
        name = "missing" if missing else "callback"
        if sys.platform == "win32":
            compiler = shutil.which("clang-cl")
            linker = shutil.which("lld-link")
            if not compiler or not linker:
                pytest.skip("callback mock requires clang-cl and lld-link")
            library = directory / (name + ".dll")
            obj = directory / (name + ".obj")
            target = "i686-pc-windows-msvc" if sys.maxsize <= 2**32 else "x86_64-pc-windows-msvc"
            command = [compiler, "--target=" + target, "/nologo", "/c", "/GS-", "/Zl", str(source), "/Fo" + str(obj)]
            if missing:
                command.append("/DOMIT_SETTER")
            subprocess.run(command, check=True, capture_output=True)
            exports = (
                ["/export:fire_callback=_fire_callback", "/export:set_fire_on_registration=_set_fire_on_registration"]
                if sys.maxsize <= 2**32
                else []
            )
            if sys.maxsize <= 2**32 and not missing:
                exports.append("/export:icsneoSetReflashCallback=_icsneoSetReflashCallback@4")
            subprocess.run(
                [linker, "/dll", "/noentry", "/nodefaultlib", "/out:" + str(library), str(obj), *exports],
                check=True,
                capture_output=True,
            )
        else:
            compiler = shutil.which("cc")
            if not compiler:
                pytest.skip("callback mock requires a C compiler")
            library = directory / (name + (".dylib" if sys.platform == "darwin" else ".so"))
            command = [
                compiler,
                "-dynamiclib" if sys.platform == "darwin" else "-shared",
                "-fPIC",
                str(source),
                "-o",
                str(library),
            ]
            if missing:
                command.append("-DOMIT_SETTER")
            subprocess.run(command, check=True, capture_output=True)
        libraries.append(library)
    return libraries


PREAMBLE = """
import ctypes, gc, sys, weakref
import ics
ics.override_library_name(sys.argv[1])
native = ctypes.CDLL(sys.argv[1])
native.fire_callback.argtypes = []
native.fire_callback.restype = None
events = []
class Handler:
    def __call__(self, message, progress):
        events.append((message, progress))
def collect():
    gc.collect()
"""


CASES = {
    "lifetime": """
handler = Handler()
ref = weakref.ref(handler)
ics.set_reflash_callback(handler)
del handler
collect()
assert ref() is not None, 'registered callback was collected'
native.fire_callback()
assert events == [('progress\\u2713', 42)]
ics.set_reflash_callback(None)
collect()
assert ref() is None
native.fire_callback()
assert len(events) == 1
""",
    "replacement": """
first, second = Handler(), Handler()
old, new = weakref.ref(first), weakref.ref(second)
ics.set_reflash_callback(first)
ics.set_reflash_callback(first)
del first
ics.set_reflash_callback(second)
del second
collect()
assert old() is None and new() is not None
ics.set_reflash_callback(None)
collect()
assert new() is None
""",
    "method": """
class MethodHandler:
    def reflash_callback(self, message, progress):
        events.append((message, progress))
handler = MethodHandler()
ref = weakref.ref(handler)
ics.set_reflash_callback(handler)
del handler
collect()
assert ref() is not None
native.fire_callback()
assert events == [('progress\\u2713', 42)]
ics.set_reflash_callback(None)
collect()
assert ref() is None
""",
    "invalid": """
handler = Handler()
ics.set_reflash_callback(handler)
class Invalid:
    reflash_callback = 1
for value in (123, object(), Invalid()):
    try:
        ics.set_reflash_callback(value)
    except TypeError:
        pass
    else:
        raise AssertionError('accepted invalid callback')
native.fire_callback()
assert len(events) == 1
ics.set_reflash_callback(None)
""",
    "return_value": """
refs = []
def callback(message, progress):
    result = Handler()
    refs.append(weakref.ref(result))
    return result
ics.set_reflash_callback(callback)
for _ in range(10):
    native.fire_callback()
collect()
assert all(ref() is None for ref in refs)
ics.set_reflash_callback(None)
""",
    "exception": """
errors = []
sys.unraisablehook = lambda error: errors.append((error.exc_type, str(error.exc_value)))
def callback(message, progress):
    raise ValueError('callback failed')
ics.set_reflash_callback(callback)
native.fire_callback()
native.fire_callback()
assert errors == [(ValueError, 'callback failed')] * 2
ics.set_reflash_callback(Handler())
native.fire_callback()
assert len(events) == 1
ics.set_reflash_callback(None)
""",
    "reentrant": """
refs = []
errors = []
sys.unraisablehook = lambda error: errors.append(error.exc_type)
class Reentrant:
    def __call__(self, message, progress):
        ics.set_reflash_callback(None)
        collect()
        assert refs[0]() is self
        raise ValueError('after unregister')
handler = Reentrant()
refs.append(weakref.ref(handler))
ics.set_reflash_callback(handler)
del handler
native.fire_callback()
collect()
assert errors == [ValueError]
assert refs[0]() is None
""",
    "stdout": """
import contextlib, io
handler = Handler()
ref = weakref.ref(handler)
ics.set_reflash_callback(handler)
del handler
ics.set_reflash_callback()
collect()
assert ref() is None
output = io.StringIO()
with contextlib.redirect_stdout(output):
    native.fire_callback()
assert output.getvalue() == 'progress\\u2713 -42\\n'
ics.set_reflash_callback(None)
""",
    "missing_symbol": """
handler = Handler()
ref = weakref.ref(handler)
ics.set_reflash_callback(handler)
del handler
ics.override_library_name(sys.argv[2])
candidate = Handler()
candidate_ref = weakref.ref(candidate)
try:
    ics.set_reflash_callback(candidate)
except ics.RuntimeError:
    pass
else:
    raise AssertionError('missing symbol accepted')
del candidate
collect()
assert ref() is not None and candidate_ref() is None
native.fire_callback()
assert len(events) == 1
ics.override_library_name(sys.argv[1])
ics.set_reflash_callback(None)
collect()
assert ref() is None
""",
    "attribute_error": """
class Broken:
    @property
    def reflash_callback(self):
        raise ValueError('attribute failed')
ics.set_reflash_callback(Handler())
try:
    ics.set_reflash_callback(Broken())
except ValueError as error:
    assert str(error) == 'attribute failed'
else:
    raise AssertionError('attribute error suppressed')
native.fire_callback()
assert len(events) == 1
ics.set_reflash_callback(None)
""",
    "thread": """
import threading
ics.set_reflash_callback(Handler())
worker = threading.Thread(target=native.fire_callback)
worker.start()
worker.join(timeout=5)
assert not worker.is_alive()
assert events == [('progress\\u2713', 42)]
ics.set_reflash_callback(None)
""",
    "immediate": """
native.set_fire_on_registration.argtypes = [ctypes.c_int]
native.set_fire_on_registration.restype = None
native.set_fire_on_registration(1)
ics.set_reflash_callback(Handler())
assert events == [('progress\\u2713', 42)]
ics.set_reflash_callback(None)
assert len(events) == 1
""",
}


@pytest.mark.parametrize("case", CASES)
def test_reflash_callback(callback_libraries, case):
    env = os.environ.copy()
    # Preserve the selected checkout/build when launching an isolated interpreter.
    env["PYTHONPATH"] = os.pathsep.join(str(Path(path).resolve()) for path in sys.path)
    result = subprocess.run(
        [sys.executable, "-c", PREAMBLE + CASES[case], *map(str, callback_libraries)],
        env=env,
        capture_output=True,
        text=True,
        timeout=30,
    )
    assert result.returncode == 0, result.stdout + result.stderr
