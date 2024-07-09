#!/usr/bin/env python3
from setuptools import setup, Extension
from setuptools.command.build import build
from setuptools.command.build_clib import build_clib
from setuptools.command.egg_info import egg_info
from setuptools.command.develop import develop
from setuptools.command.install import install

import os
import sys
import platform
import shutil
import os.path
import extract_icsneo40_defines
import generate_icsneo40_structs
from ics_utility import get_pkg_version, create_version_py, GEN_DIR, get_module_name
import pathlib
from typing import List

MODULE_NAME = get_module_name()

# Check for clang stuff here, read the docs doesn't have this so use what is in the repo
if not os.getenv("READTHEDOCS"):
    if not shutil.which("clang"):
        raise RuntimeError(f"clang is required for building {MODULE_NAME}.")
    if not shutil.which("clang-format"):
        raise RuntimeError(f"clang-format is required for building {MODULE_NAME}.")

def get_version():
    major = int(get_pkg_version().split(".")[0])
    minor = int(get_pkg_version().split(".")[1])
    return major, minor

def prepare_python_source_files():
    print("Copy python source files over to gen...")
    src_path = pathlib.Path("./src/")
    gen_path = GEN_DIR
    struct_path = GEN_DIR / "structures"

    shutil.rmtree(gen_path, ignore_errors=True)
    struct_path.mkdir(parents=True, exist_ok=True)
    for dirpath, dirnames, filenames in os.walk(src_path):
        dirpath = pathlib.Path(dirpath)
        for name in filenames:
            if pathlib.Path(name).suffix == ".py" and 'icsdebug' not in name:
                src = (dirpath / name)
                dest = (gen_path / dirpath.relative_to(src_path) / name)
                dest.parent.mkdir(parents=True, exist_ok=True)
                print(f"Copying {src} to {dest}")
                shutil.copy(src, dest)

    create_version_py()
    generate_icsneo40_structs.generate_all_files()
    print("Generating python defines from icsnVC40.h...")
    extract_icsneo40_defines.extract()


###############################################################################
# Custom Command class begins here
#
#
# python setup.py build calls in this order (on windows):
# running build
# running build_py
# running egg_info
# running build_ext
#
#
# python setup.py install calls in this order (on windows):
# running install
# running build
# running build_py
# running egg_info
# running build_ext
# running install_lib
# running install_egg_info
# running install_scripts
#
# python -m build . calls in this order (on windows):
# running egg_info
# running sdist
# running egg_info
# running check
# running egg_info
# running bdist_wheel
# running build
# running build_py
# running egg_info
# running build_ext
# running install
# running install_lib
# running install_egg_info
# running install_scripts
#
# C:\python\python313\python -m pip install . -v calls in this order (on windows):
# running egg_info
# running dist_info
# running bdist_wheel
# running build
# running build_py
# running egg_info
# running build_ext
# running install
# running build_libicsneo
# running install_lib
# running install_egg_info
# running install_scripts
#
###############################################################################

class _build_libicsneo(build_clib):
    def run(self):
        # checkout and build libicsneo
        if platform.system().upper() in ("DARWIN", "LINUX"):
            import build_libicsneo
            print("Checking out libicsneo...")
            build_libicsneo.checkout()
            print("Building libicsneo...")
            build_libicsneo.build()
            print("Copying libicsneo...")
            build_libicsneo.copy()
        elif platform.system().upper() == "WINDOWS":
            print("Windows uses icsneo40.dll instead of libicsneo.dll, skipping build")
        else:
            raise NotImplementedError("Unsupported platform: ", platform.system())
        super().run()


class _build(build):
    def run(self):
        #print(f"DEBUG: {self.__class__.__name__}")
        prepare_python_source_files()
        super().run()
        
class _egg_info(egg_info):
    def run(self):
        #print(f"DEBUG: {self.__class__.__name__}")
        prepare_python_source_files()
        super().run()

class _develop(develop):
    def run(self):
        #print(f"DEBUG: {self.__class__.__name__}")
        prepare_python_source_files()
        super().run()

class _install(install):
    def run(self):
        #print(f"DEBUG: {self.__class__.__name__}")
        self.run_command("build_libicsneo")
        super().run()

def get_ics_extension_compiler_arguments() -> List[str]:
    """Return a list of compiler arguments to append for compiling the ics extension module"""
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
    return compile_args

c_extension = Extension(
    f"{MODULE_NAME}.c_mod",
    define_macros=[("MAJOR_VERSION", get_version()[0]), ("MINOR_VERSION", get_version()[1]), ("EXTERNAL_PROJECT", 1)],
    include_dirs=["include", "include/ics", "src/ice/include", "src/ice/include/ice"],
    libraries=[],
    library_dirs=["/usr/local/lib"],
    sources=[
        "src/object_spy_message.cpp",
        "src/defines.cpp",
        "src/exceptions.cpp",
        "src/dll.cpp",
        "src/setup_module_auto_defines.cpp",
        "src/main.cpp",
        "src/methods.cpp",
        "src/ice/src/ice_library_manager.cpp",
        "src/ice/src/ice_library_name.cpp",
        "src/ice/src/ice_library.cpp",
    ],
    extra_compile_args=get_ics_extension_compiler_arguments(),
)

package_data = {}
if "DARWIN" in platform.system().upper():
    package_data[""] = ["*.dylib"]
elif "LINUX" in platform.system().upper():
    package_data[""] = ["*.so"]

setup(
    name=MODULE_NAME,
    version=get_pkg_version(),
    cmdclass={
        "build": _build,
        "build_libicsneo": _build_libicsneo,
        "egg_info": _egg_info,
        "develop": _develop,
        "install": _install,
    },
    download_url="https://github.com/intrepidcs/python_ics/releases",
    packages=[MODULE_NAME, f"{MODULE_NAME}.structures"],
    package_dir={MODULE_NAME: "gen", f"{MODULE_NAME}.structures": "gen/structures"},
    package_data=package_data,
    include_package_data=True,
    ext_modules=[c_extension],
)
