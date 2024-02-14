#!/usr/bin/env python3
from setuptools import setup, Extension

from distutils.command import build as build_module
import os
import platform
import sys
import unittest
import shutil

MAJOR_VERSION = 914
MINOR_VERSION = 14
POST_VERSION = None

if POST_VERSION:
    VERSION_STRING = "%d.%d-%d" % (MAJOR_VERSION, MINOR_VERSION, POST_VERSION)
else:
    VERSION_STRING = "%d.%d" % (MAJOR_VERSION, MINOR_VERSION)


def _run_tests():
    directory = os.path.abspath(os.path.dirname(sys.modules["__main__"].__file__))
    loader = unittest.defaultTestLoader
    runner = unittest.TextTestRunner()
    suite = loader.discover(os.path.join(directory, "test"))
    runner.run(suite)


try:
    from setuptools.command.test import test

    class UnitTests(test):
        def finalize_options(self):
            test.finalize_options(self)
            self.test_args = []
            self.test_suite = True

        def run_tests(self):
            _run_tests()

except ImportError:
    from distutils.core import Command

    class UnitTests(Command):
        user_options = []

        def initialize_options(self):
            pass

        def finalize_options(self):
            pass

        def run(self):
            _run_tests()


class build(build_module.build):
    def run(self):
        import extract_icsneo40_defines
        import generate_icsneo40_structs

        extract_icsneo40_defines.extract()
        generate_icsneo40_structs.generate_all_files()
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


def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()


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
    version=VERSION_STRING,
    description="Library for interfacing with Intrepid devices in Python",
    long_description=read("README.md"),
    long_description_content_type="text/markdown",
    license="MIT",
    author="David Rebbe",
    author_email="drebbe@intrepidcs.com",
    maintainer="David Rebbe",
    maintainer_email="drebbe@intrepidcs.com",
    url="https://github.com/intrepidcs/python_ics/",
    cmdclass={
        "build": build,
        "test": UnitTests,
    },
    download_url="https://github.com/intrepidcs/python_ics/releases",
    packages=["ics", "ics.structures"],
    package_data=package_data,
    include_package_data=True,
    ext_modules=[ics_extension],
    classifiers=[
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
        "Programming Language :: Python :: 3.12",
    ],
)
