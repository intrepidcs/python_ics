![](IntrepidCS.png)

![](https://github.com/intrepidcs/python_ics/actions/workflows/wheels.yml/badge.svg)

# Description

Python wrapper for interfacing to IntrepidCS Hardware.

# Installing

- `pip install python_ics`

## Platform specific Installation notes

### Windows

- Windows requires icsneo40.dll to be installed in the PATH. This can be obtained through vspy3 or our hardware installation kit found here: https://cdn.intrepidcs.net/updates/files/RP1210KitInstall.zip

### Linux

- Linux builds use [libicsneo](https://github.com/intrepidcs/libicsneo) and are built against [manylinux](https://github.com/pypa/manylinux) using cibuildwheel.
- libicsneolegacy.so is bundled with the wheel and python_ics will automatically use it.

### MacOS

- Mac builds use [libicsneo](https://github.com/intrepidcs/libicsneo) and are built using cibuildwheel
- libicsneolegacy.dylib is bundled with the wheel and python_ics will automatically use it.

# Documentation

http://python-ics.readthedocs.io/


# Building from source

- Building from source requires clang and clang-format to be present on the build machine.

# License - MIT

Copyright (c) Intrepid Control Systems, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
