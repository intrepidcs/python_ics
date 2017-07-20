#!/usr/bin/env python3
from setuptools import setup, Extension
from distutils.command import build as build_module
import os
import platform

MAJOR_VERSION = 2
MINOR_VERSION = 6

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

# Set compiler flags here
if 'LINUX' in platform.system().upper():
	compile_args = [
		'-fpermissive', 
		'-Wno-unused-variable',
		'-Wno-unused-function',
		'-Wno-write-strings'
	]
else:
	compile_args = []

module = Extension('ics',
  define_macros = [('MAJOR_VERSION', MAJOR_VERSION), ('MINOR_VERSION', MINOR_VERSION)],
  include_dirs=['include', 'include/ics', 'include/ice'],
  libraries = [],
  library_dirs = ['/usr/local/lib'],
  sources = source_files,
  extra_compile_args=compile_args)

setup (name = 'python_ics',
       version = '%d.%d' % (MAJOR_VERSION, MINOR_VERSION),
       description = 'Intrepidcs icsneo40 Python 3 API/Wrapper',
       long_description = 
       """Python C Code module for interfacing to the icsneo40 dynamic library. Code tries 
to respect PEP 8 (https://www.python.org/dev/peps/pep-0008/). Function naming convention does 
not follow the tradition c style icsneo40 naming convention as the python_ics module 
name acts as the namespace (icsneo portion of the function) and function names 
are suppose to be lowercase with underscores instead of mixedCase like icsneo API.""",
       license = "MIT",
       author = 'David Rebbe',
       author_email='drebbe@intrepidcs.com',
       maintainer = 'David Rebbe',
       maintainer_email='drebbe@intrepidcs.com',
       url='https://github.com/intrepidcs/python_ics/',
       cmdclass = { 'build': build, },
       download_url = 'https://github.com/intrepidcs/python_ics/releases',
       ext_modules = [module],
       classifiers = [
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        ],)
