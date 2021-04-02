#!/usr/bin/env python3
from setuptools import setup, Extension

from distutils.command import build as build_module
import os
import platform
import sys
import unittest

MAJOR_VERSION = 903
MINOR_VERSION = 17

def _run_tests():
    directory = os.path.abspath(os.path.dirname(sys.modules['__main__'].__file__))
    loader = unittest.defaultTestLoader
    runner = unittest.TextTestRunner()
    suite = loader.discover(os.path.join(directory, 'test'))
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
        import extract_icsneo40_defines # there should be a better way to do this...
        import generate_icsneo40_structs
        generate_icsneo40_structs.generate()
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

    
def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()
    
ics_extension = Extension('ics.ics',
  define_macros = [('MAJOR_VERSION', MAJOR_VERSION), ('MINOR_VERSION', MINOR_VERSION), ('EXTERNAL_PROJECT', 1)],
  include_dirs=['include', 'include/ics', 'include/ice'],
  libraries = [],
  library_dirs = ['/usr/local/lib'],
  sources = source_files,
  extra_compile_args=compile_args)

setup (name = 'python_ics',
       version = '%d.%d' % (MAJOR_VERSION, MINOR_VERSION),
       description = 'Library for interfacing with Intrepid devices in Python',
       long_description = read('README.md'),
       license = "MIT",
       author = 'David Rebbe',
       author_email='drebbe@intrepidcs.com',
       maintainer = 'David Rebbe',
       maintainer_email='drebbe@intrepidcs.com',
       url='https://github.com/intrepidcs/python_ics/',
       cmdclass = { 'build': build, 'test': UnitTests, },
       download_url = 'https://github.com/intrepidcs/python_ics/releases',
       packages = ['ics', 'ics.structures'], # 'ics.structures', 'ics.main'],
       #package_dir = {'ics.structures': 'ics',},
       ext_modules = [ics_extension],
       #package_dir = {'ics.structures': 'python/ics'},
       
       classifiers = [
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        ],)
