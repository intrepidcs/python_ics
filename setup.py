#!/usr/bin/env python3
import sys
sys.settrace
from setuptools import setup, Extension

from distutils.command import build as build_module
import os
import platform
import sys
import unittest
import shutil
from pathlib import Path
import codecs
import os.path
import extract_icsneo40_defines
import generate_icsneo40_structs
from create_version import get_pkg_version, create_version_py
import shutil
import pathlib

# force this to happen every single time, fixes sync issues.
extract_icsneo40_defines.extract()
generate_icsneo40_structs.generate_all_files()

create_version_py()


src_path = pathlib.Path("./src/")
gen_path = pathlib.Path("./gen/")

print("Copy python source files over to gen...")
for dirpath, dirnames, filenames in os.walk(src_path):
    dirpath = pathlib.Path(dirpath)
    for name in filenames:
        if pathlib.Path(name).suffix == ".py" and not 'icsdebug' in name:
            src = (dirpath / name)
            dest = (gen_path / dirpath.relative_to(src_path) / name)
            print(f"Copying {src} to {dest}")
            shutil.copy(src, dest)

MAJOR_VERSION = int(get_pkg_version().split(".")[0])
MINOR_VERSION = int(get_pkg_version().split(".")[1])

class build(build_module.build):
    def run(self):
        if platform.system().upper() in ("DARWIN", "LINUX"):
            import build_libicsneo

            build_libicsneo.checkout()
            build_libicsneo.build()
            build_libicsneo.copy()
        build_module.build.run(self)


source_files = [
    "src/object_spy_message.cpp",
    "src/defines.cpp",
    "src/exceptions.cpp",
    "src/dll.cpp",
    "src/setup_module_auto_defines.cpp",
    "src/main.cpp",
    "src/object_neo_device.cpp",
    "src/methods.cpp",
    "src/ice/src/ice_library_manager.cpp",
    "src/ice/src/ice_library_name.cpp",
    "src/ice/src/ice_library.cpp",
]

# gcc and clang arguments
GCC_COMPILE_ARGS = [
    "-fpermissive",
    "-Wno-unused-variable",
    "-Wno-unused-function",
    "-Wno-write-strings",
]

# Set compiler flags here
if "WINDOWS" in platform.system().upper():
    compile_args = []
    # mingw and clang python builds won't have MSC in the version string
    if "MSC" not in sys.version:
        compile_args = GCC_COMPILE_ARGS
elif "LINUX" in platform.system().upper():
    compile_args = GCC_COMPILE_ARGS
elif "DARWIN" in platform.system().upper():
    # Mac doesn't respect the compiler args, but will append with ARCHFLAGS environment variable
    os.environ["ARCHFLAGS"] += " -std=c++17"
    compile_args = []
else:
    compile_args = []

# Check for clang stuff here, read the docs doesn't have this so use what is in the repo
if not os.getenv("READTHEDOCS"):
    if not shutil.which("clang"):
        raise RuntimeError("clang is required for building python_ics.")
    if not shutil.which("clang-format"):
        raise RuntimeError("clang-format is required for building python_ics.")

ics_extension = Extension(
    "ics.ics",
    define_macros=[("MAJOR_VERSION", MAJOR_VERSION), ("MINOR_VERSION", MINOR_VERSION), ("EXTERNAL_PROJECT", 1)],
    include_dirs=["include", "include/ics", "src/ice/include", "src/ice/include/ice"],
    libraries=[],
    library_dirs=["/usr/local/lib"],
    sources=source_files,
    extra_compile_args=compile_args,
)

package_data = {}
if "DARWIN" in platform.system().upper():
    package_data["ics"] = ["*.dylib"]
elif "LINUX" in platform.system().upper():
    package_data[""] = ["*.so"]

setup(
    name="python_ics",
    version=get_pkg_version(),
    cmdclass={
        "build": build,
    },
    download_url="https://github.com/intrepidcs/python_ics/releases",
    packages=["ics", "ics.structures"],
    package_dir={"ics": "gen/ics", "ics.structures": "gen/ics/structures"},
    package_data=package_data,
    include_package_data=True,
    ext_modules=[ics_extension],
)
