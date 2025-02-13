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

LIBICSNEO_VERSION = "02b5daf"
LIBICSNEO_ROOT = f"{ROOT}/libicsneo/{LIBICSNEO_VERSION}"
LIBICSNEO_SOURCE = f"{LIBICSNEO_ROOT}/source"
LIBICSNEO_BUILD = f"{LIBICSNEO_ROOT}/build"
LIBICSNEO_INSTALL = f"{LIBICSNEO_ROOT}/install"
print(f"LIBICSNEO PATH: {LIBICSNEO_ROOT}")

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

def _build_libicsneo_linux():
    print("Cleaning libicsneo...")
    subprocess.check_output(["git", "clean", "-xdf"], cwd="libicsneo")
    subprocess.check_output(["mkdir", "-p", "libicsneo/build"])

    print("cmake libicsneo...")
    subprocess.check_output(
        [
            "cmake",
            "-DCMAKE_BUILD_TYPE=Release",
            "-DLIBICSNEO_BUILD_ICSNEOLEGACY=ON",
            f"-DCMAKE_PREFIX_PATH={LIBUSB_INSTALL};{LIBPCAP_INSTALL}",
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
    subprocess.check_output(
        [
            "cmake",
            "-DCMAKE_BUILD_TYPE=Release",
            "-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64",
            "-DLIBICSNEO_BUILD_ICSNEOLEGACY=ON",
            "-DCMAKE_OSX_DEPLOYMENT_TARGET=10.13",
            f"-DCMAKE_PREFIX_PATH={LIBUSB_INSTALL};{LIBPCAP_INSTALL}",
            "-S", LIBICSNEO_SOURCE,
            "-B", LIBICSNEO_BUILD
        ]
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
