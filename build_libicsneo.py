import subprocess
import multiprocessing
import os
import shutil
import sys
from pathlib import Path

ROOT = Path.cwd()
CPUS = str(multiprocessing.cpu_count())

LIBUSB_VERSION = "1.0.27"
LIBUSB_ROOT = f"{ROOT}/libusb/{LIBUSB_VERSION}"
LIBUSB_SOURCE = f"{LIBUSB_ROOT}/source"
LIBUSB_BUILD = f"{LIBUSB_ROOT}/build"
LIBUSB_INSTALL = f"{LIBUSB_ROOT}/install"

# NOTE: this pin's vendored icsnVC40.h still predates Vspy 3.26.3.9
# (SRADGalaxy2Settings 840 vs 1204, no Comet3/Gigastar2), so Linux/macOS
# wheels lag the Windows ABI until upstream syncs the header; bump again
# when it does. libicsneo requires icspb (protobuf) as of 2026: its
# codegen needs the Ninja generator (protobuf_generate never creates
# PROTOC_OUT_DIR; Make doesn't pre-create declared output dirs, Ninja
# does), and it bootstraps protobuf from source at configure time — see
# ICSPB_BOOTSTRAP_DIR below.
LIBICSNEO_VERSION = "4ed29b4"
LIBICSNEO_ROOT = f"{ROOT}/libicsneo/{LIBICSNEO_VERSION}"
LIBICSNEO_SOURCE = f"{LIBICSNEO_ROOT}/source"
LIBICSNEO_BUILD = f"{LIBICSNEO_ROOT}/build"
LIBICSNEO_INSTALL = f"{LIBICSNEO_ROOT}/install"
print(f"LIBICSNEO PATH: {LIBICSNEO_ROOT}")

# icspb bootstraps protobuf from source at configure time. Keep the
# bootstrap OUTSIDE the libicsneo build dir so it survives the per-python
# `git clean` in _build_libicsneo_linux and is reused across all
# cibuildwheel builds in a job (it self-partitions by <system>-<processor>,
# so sharing one root across archs is safe). Building protobuf once per
# arch instead of once per python matters most under QEMU aarch64.
ICSPB_BOOTSTRAP_DIR = f"{ROOT}/icspb_bootstrap"

LIBPCAP_VERSION = "1.10.4"
LIBPCAP_ROOT = f"{ROOT}/libpcap/{LIBPCAP_VERSION}"
LIBPCAP_SOURCE = f"{LIBPCAP_ROOT}/source"
LIBPCAP_BUILD = f"{LIBPCAP_ROOT}/build"
LIBPCAP_INSTALL = f"{LIBPCAP_ROOT}/install"

def checkout():
    if not os.path.isdir(LIBICSNEO_SOURCE):
        os.makedirs(LIBICSNEO_ROOT, exist_ok=True)
        subprocess.check_output(["git", "clone", "https://github.com/intrepidcs/libicsneo.git", LIBICSNEO_SOURCE], cwd=LIBICSNEO_ROOT)
        subprocess.check_output(["git", "checkout", LIBICSNEO_VERSION], cwd=LIBICSNEO_SOURCE)
    
    if not os.path.isdir(LIBUSB_SOURCE):
        os.makedirs(LIBUSB_ROOT, exist_ok=True)
        subprocess.check_output(["curl", "-LO", f"https://github.com/libusb/libusb/releases/download/v{LIBUSB_VERSION}/libusb-{LIBUSB_VERSION}.tar.bz2"], cwd=LIBUSB_ROOT)
        subprocess.check_output(["tar", "-xf", f"libusb-{LIBUSB_VERSION}.tar.bz2"], cwd=LIBUSB_ROOT)
        subprocess.check_output(["mv", f"libusb-{LIBUSB_VERSION}", "source"], cwd=LIBUSB_ROOT)
        subprocess.check_output(["rm", f"libusb-{LIBUSB_VERSION}.tar.bz2"], cwd=LIBUSB_ROOT)

    if not os.path.isdir(LIBPCAP_SOURCE):
        os.makedirs(LIBPCAP_ROOT, exist_ok=True)
        subprocess.check_output(["curl", "-LO", f"https://www.tcpdump.org/release/libpcap-{LIBPCAP_VERSION}.tar.gz"], cwd=LIBPCAP_ROOT)
        subprocess.check_output(["tar", "-xf", f"libpcap-{LIBPCAP_VERSION}.tar.gz"], cwd=LIBPCAP_ROOT)
        subprocess.check_output(["mv", f"libpcap-{LIBPCAP_VERSION}", "source"], cwd=LIBPCAP_ROOT)
        subprocess.check_output(["rm", f"libpcap-{LIBPCAP_VERSION}.tar.gz"], cwd=LIBPCAP_ROOT)

def _build_libusb():
    os.makedirs(LIBUSB_BUILD, exist_ok=True)
    env = os.environ.copy()
    if sys.platform == "darwin":
        env["CFLAGS"] = "-arch x86_64 -arch arm64 -mmacosx-version-min=10.13"
        env["CXXFLAGS"] = "-arch x86_64 -arch arm64 -mmacosx-version-min=10.13"
    else:
        env["CFLAGS"] = "-fPIC"
        env["CXXFLAGS"] = "-fPIC"
    subprocess.check_output([
        f"{LIBUSB_SOURCE}/configure",
        "--disable-shared",
        "--enable-static",
        f"--prefix={LIBUSB_INSTALL}",
        "--disable-udev"
    ], cwd=LIBUSB_BUILD, env=env)

    subprocess.check_output(["make", "-j" + CPUS], cwd=LIBUSB_BUILD)
    subprocess.check_output(["make", "install"], cwd=LIBUSB_BUILD)

def _build_libpcap():
    os.makedirs(LIBPCAP_BUILD, exist_ok=True)
    env = os.environ.copy()
    if sys.platform == "darwin":
        env["CFLAGS"] = "-arch x86_64 -arch arm64 -mmacosx-version-min=10.13"
        env["CXXFLAGS"] = "-arch x86_64 -arch arm64 -mmacosx-version-min=10.13"
    else:
        env["CFLAGS"] = "-fPIC"
        env["CXXFLAGS"] = "-fPIC"
    subprocess.check_output([
        f"{LIBPCAP_SOURCE}/configure",
        "--disable-shared",
        "--disable-usb",
        "--disable-netmap",
        "--disable-bluetooth",
        "--disable-dbus",
        "--disable-rdma",
        "--without-dag",
        "--without-septel",
        "--without-snf",
        "--without-turbocap",
        "--without-dpdk",
        "--without-libnl",
        f"--prefix={LIBPCAP_INSTALL}",
    ], cwd=LIBPCAP_BUILD, env=env)

    subprocess.check_output(["make", "-j" + CPUS], cwd=LIBPCAP_BUILD)
    subprocess.check_output(["make", "install"], cwd=LIBPCAP_BUILD)

def _cmake_ninja_args():
    # pip's ninja lives inside each isolated build env, and cibuildwheel
    # deletes that env between python versions. A reused CMake build dir
    # caches the old (now dead) path in CMAKE_MAKE_PROGRAM and fails at
    # the next configure, so always override with the current ninja.
    ninja = shutil.which("ninja")
    args = ["-G", "Ninja"]
    if ninja:
        args.append(f"-DCMAKE_MAKE_PROGRAM={ninja}")
    return args


def _build_libicsneo_linux():
    print("Cleaning libicsneo...")
    subprocess.check_output(["git", "clean", "-xdf"], cwd="libicsneo")
    subprocess.check_output(["mkdir", "-p", "libicsneo/build"])

    print("cmake libicsneo...")
    subprocess.check_output(
        [
            "cmake",
            # Ninja is required: icspb's protobuf_generate never creates its
            # output dir, and only Ninja pre-creates declared output dirs.
            *_cmake_ninja_args(),
            "-DCMAKE_BUILD_TYPE=Release",
            "-DLIBICSNEO_BUILD_ICSNEOLEGACY=ON",
            f"-DCMAKE_PREFIX_PATH={LIBUSB_INSTALL};{LIBPCAP_INSTALL}",
            f"-DICSPB_BOOTSTRAP_DIR={ICSPB_BOOTSTRAP_DIR}",
            "-S", LIBICSNEO_SOURCE,
            "-B", LIBICSNEO_BUILD,
            "-Wno-dev",
        ]
    )
    print("cmake build libicsneo...")
    subprocess.check_output(
        ["cmake", "--build", LIBICSNEO_BUILD, "--target", "icsneolegacy", "--parallel", CPUS]
    )

def _build_libicsneo_macos():
    env = os.environ.copy()
    # Set as env vars (not only -D flags) so icspb's nested protobuf
    # bootstrap — a separate cmake invocation via execute_process, which
    # inherits the environment but not our -D cache entries — also builds
    # universal2 static libs instead of arm64-only ones.
    env["CMAKE_OSX_ARCHITECTURES"] = "arm64;x86_64"
    env["CMAKE_OSX_DEPLOYMENT_TARGET"] = "10.13"
    subprocess.check_output(
        [
            "cmake",
            # Ninja is required: icspb's protobuf_generate never creates its
            # output dir, and only Ninja pre-creates declared output dirs.
            *_cmake_ninja_args(),
            "-DCMAKE_BUILD_TYPE=Release",
            "-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64",
            "-DLIBICSNEO_BUILD_ICSNEOLEGACY=ON",
            "-DCMAKE_OSX_DEPLOYMENT_TARGET=10.13",
            f"-DCMAKE_PREFIX_PATH={LIBUSB_INSTALL};{LIBPCAP_INSTALL}",
            f"-DICSPB_BOOTSTRAP_DIR={ICSPB_BOOTSTRAP_DIR}",
            "-S", LIBICSNEO_SOURCE,
            "-B", LIBICSNEO_BUILD
        ],
        env=env,
    )

    subprocess.check_output(
        ["cmake", "--build", LIBICSNEO_BUILD, "--target", "icsneolegacy", "--parallel", CPUS]
    )

def build():
    print("Building libusb...")
    _build_libusb()
    print("Building libpcap...")
    _build_libpcap()
    if sys.platform == "darwin":
        _build_libicsneo_macos()
    elif sys.platform == "linux":
        _build_libicsneo_linux()

def copy():
    if sys.platform == "darwin":
        shutil.copyfile(f"{LIBICSNEO_BUILD}/libicsneolegacy.dylib", "gen/ics/libicsneolegacy.dylib")
    elif sys.platform == "linux":
        shutil.copyfile(f"{LIBICSNEO_BUILD}/libicsneolegacy.so", "gen/ics/libicsneolegacy.so")


def clean():
    shutil.rmtree("libicsneo")
    shutil.rmtree("libusb")
    shutil.rmtree("libpcap")

if __name__ == "__main__":
    if "--clean" in sys.argv:
        clean()
        exit(0)
    
    print("Checking out libicsneo...")
    checkout()
    print("Building libicsneo...")
    build()
    print("Copy libicsneo...")
    copy()
