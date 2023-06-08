import subprocess
import multiprocessing
import os
import shutil
import sys

LIBICSNEO_COMMIT = '63c81b1c3d13bb96371611d7e2573d6e4adcb6e2'
LIBUSB_COMMIT = '4239bc3a50014b8e6a5a2a59df1fff3b7469543b'
CPUS = str(multiprocessing.cpu_count())


def checkout():
    if not os.path.isdir('libicsneo'):
        subprocess.check_output(
            ['git', 'clone', 'https://github.com/intrepidcs/libicsneo.git'])
    subprocess.check_output(
        ['git', 'checkout', LIBICSNEO_COMMIT], cwd='libicsneo')

    if not os.path.isdir('libusb') and sys.platform == 'darwin':
        subprocess.check_output(
            ['git', 'clone', 'https://github.com/libusb/libusb.git'])
        subprocess.check_output(['git', 'checkout', LIBUSB_COMMIT], cwd='libusb')


def _build_libusb():
    subprocess.check_output(['git', 'clean', '-xdf'], cwd='libusb')

    subprocess.check_output(['./bootstrap.sh'], cwd='libusb')

    env = os.environ.copy()
    env['CFLAGS'] = '-arch x86_64 -arch arm64 -mmacosx-version-min=10.13'
    env['CXXFLAGS'] = '-arch x86_64 -arch arm64 -mmacosx-version-min=10.13'
    subprocess.check_output(
        ['./configure', '--disable-static', '--prefix=/tmp/libusb'], cwd='libusb', env=env)

    subprocess.check_output(['make', '-j' + CPUS], cwd='libusb')
    subprocess.check_output(['make', 'install'], cwd='libusb')


def _build_icsneo_linux():
    subprocess.check_output(['git', 'clean', '-xdf'], cwd='libicsneo')
    subprocess.check_output(['mkdir', '-p', 'libicsneo/build'])

    subprocess.check_output(['cmake', '..', '-DCMAKE_BUILD_TYPE=Release', '-DLIBICSNEO_BUILD_ICSNEOLEGACY=ON'], cwd='libicsneo/build')
    subprocess.check_output(['cmake', '--build', '.', '--target',
                            'icsneolegacy', '--parallel', CPUS], cwd='libicsneo/build')

def _build_icsneo_macos():
    subprocess.check_output(['git', 'clean', '-xdf'], cwd='libicsneo')
    subprocess.check_output(['mkdir', '-p', 'libicsneo/build'])

    subprocess.check_output(['cmake', '..', '-DCMAKE_BUILD_TYPE=Release', '-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64',
                            '-DLIBICSNEO_BUILD_ICSNEOLEGACY=ON', '-DCMAKE_OSX_DEPLOYMENT_TARGET=10.13',
                            '-DLIBUSB_LIBRARIES=/tmp/libusb/lib/libusb-1.0.0.dylib',
                            '-DLIBUSB_INCLUDE_DIR=/tmp/libusb/include/libusb-1.0'], cwd='libicsneo/build')

    subprocess.check_output(['cmake', '--build', '.', '--target',
                            'icsneolegacy', '--parallel', CPUS], cwd='libicsneo/build')
    subprocess.check_output(['install_name_tool', '-change', '/tmp/libusb/lib/libusb-1.0.0.dylib',
                            '@loader_path/libusb-1.0.0.dylib', 'libicsneolegacy.dylib'], cwd='libicsneo/build')


def build():
    print("Building libicsneo...")
    if sys.platform == 'darwin':
        _build_libusb()
        _build_icsneo_macos()
    elif sys.platform == 'linux':
        _build_icsneo_linux()


def copy():
    if sys.platform == 'darwin':
        shutil.copyfile('/tmp/libusb/lib/libusb-1.0.0.dylib',
                        'ics/libusb-1.0.0.dylib')
        shutil.copyfile('libicsneo/build/libicsneolegacy.dylib',
                        'ics/libicsneolegacy.dylib')
    elif sys.platform == 'linux':
        shutil.copyfile('libicsneo/build/libicsneolegacy.so',
                        'ics/libicsneolegacy.so')


def clean():
    shutil.rmtree('libicsneo')
    shutil.rmtree('libusb')
    shutil.rmtree('/tmp/libusb')


if __name__ == '__main__':
    if '--clean' in sys.argv:
        clean()
        exit(0)
    checkout()
    build()
    copy()
