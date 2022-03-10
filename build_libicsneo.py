import subprocess
import multiprocessing
import os
import shutil
import sys

LIBICSNEO_COMMIT = '6cd821be2c79190cdd45d9e0bf28bdb19aee84b9'
LIBUSB_COMMIT = '4622bfcf44db373c53502e3fe873bd611e8332f6'
CPUS = str(multiprocessing.cpu_count())


def checkout():
    if not os.path.isdir('libicsneo'):
        subprocess.check_output(
            ['git', 'clone', 'https://github.com/intrepidcs/libicsneo.git'])
    subprocess.check_output(
        ['git', 'checkout', LIBICSNEO_COMMIT], cwd='libicsneo')

    if not os.path.isdir('libusb'):
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


def _build_icsneo():
    subprocess.check_output(['git', 'clean', '-xdf'], cwd='libicsneo')
    subprocess.check_output(['mkdir', '-p', 'libicsneo/build'])

    subprocess.check_output(['cmake', '..', '-DCMAKE_BUILD_TYPE=RelWithDebInfo', '-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64',
                            '-DLIBICSNEO_BUILD_ICSNEOLEGACY=ON', '-DCMAKE_OSX_DEPLOYMENT_TARGET=10.13',
                            '-DLIBUSB_LIBRARIES=/tmp/libusb/lib/libusb-1.0.0.dylib',
                            '-DLIBUSB_INCLUDE_DIR=/tmp/libusb/include/libusb-1.0'], cwd='libicsneo/build')

    subprocess.check_output(['cmake', '--build', '.', '--target',
                            'icsneolegacy', '--parallel', CPUS], cwd='libicsneo/build')
    subprocess.check_output(['install_name_tool', '-change', '/tmp/libusb/lib/libusb-1.0.0.dylib',
                            '@loader_path/libusb-1.0.0.dylib', 'libicsneolegacy.dylib'], cwd='libicsneo/build')


def build():
    _build_libusb()
    _build_icsneo()


def copy():
    shutil.copyfile('/tmp/libusb/lib/libusb-1.0.0.dylib',
                    'ics/libusb-1.0.0.dylib')
    shutil.copyfile('libicsneo/build/libicsneolegacy.dylib',
                    'ics/libicsneolegacy.dylib')


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
