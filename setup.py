#!/usr/bin/env python3
from distutils.core import setup, Extension
from distutils.command import build as build_module
import os

MAJOR_VERSION = 1
MINOR_VERSION = 0

class build(build_module.build):
    def run(self):
        import extract_icsneo40_defines # this is ghetto...
        build_module.build.run(self)

home_path = os.path.expanduser('~')
# Grab all the source files
source_files = []
for root, dirs, files in os.walk('src'):
    for file in files:
        if file.endswith('.cpp') or file.endswith('.c'):
            source_files.append(os.path.join(root, file))

module = Extension('ics',
  define_macros = [('MAJOR_VERSION', MAJOR_VERSION), ('MINOR_VERSION', MINOR_VERSION)],
  include_dirs=['include', 'include/ics', 'include/ice'],
  libraries = [],
  library_dirs = ['/usr/local/lib'],
  sources = source_files,
  extra_compile_args=['-fpermissive'])

setup (name = 'python_ics',
       version = '%d.%d' % (MAJOR_VERSION, MINOR_VERSION),
       description = 'Intrepidcs icsneo40 Python 3 API/Wrapper',
       author = 'David Rebbe',
       author_email='drebbe@intrepidcs.com',
       url='http://www.intrepidcs.com',
       cmdclass = { 'build': build, },
       download_url = 'https://github.com/ic3man5/python_ics/archive/1.0.tar.gz',
       ext_modules = [module])
