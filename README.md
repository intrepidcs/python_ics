![](https://github.com/intrepidcs/python_ics/blob/master/IntrepidCS.png?raw=true)

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
- python_ics has submodules, please be sure to initial all submodules also.
```powershell
PS > git clone git@github.com:intrepidcs/python_ics.git

PS > cd python_ics

PS > git submodule update --init

PS > clang --version
clang version 11.1.0
Target: x86_64-pc-windows-msvc
Thread model: posix
InstalledDir: C:\Program Files\LLVM\bin

PS > clang-format --version
clang-format version 11.1.0

PS > python -m pip install .
```

# Debugging on Windows with Visual Studio Code

- Build and install python_ics for debug. When installing python choose the following:
    - Customize Installation -> Advanced Options
        - Check Download debugging symbols
        - Check Download debug binaries
- Build python with debug:
    - Install Visual Studio 2019 build tools(NOTE: As of 2/5/24, it looks like MSVC 2022 does not build correctly with setuptools and debug configurations). You should be able to build from source already.
    - Create virtual environment and activate it (powershell):
        - `python -m venv .venv`
        - `.\.venv\Scripts\Activate.ps1`
    - Install dependencies:
        - `python -m pip install -r requirements.txt`
    - Build in debug (`-g` flag):
        - `python setup.py build -g`
    - Install into our virtual environment:
        - `python setup.py install --force`
    - Inside visual studio code:
        - Open the root python_ics directory
            - `code C:\Path\To\python_ics`
        - Make sure the python extension is installed (ctrl+shift+x)
            - [Python](https://marketplace.visualstudio.com/items?itemName=ms-python.python])
            - [Python Debugger](https://marketplace.visualstudio.com/items?itemName=ms-python.debugpy)
        - Select the python interpreter from our virtual environment.
        - Open and place a breakpoint in `src/icsdebug.py`
        - launch "Python: Debug icsdebug.py"
            - Note the PID that is outputted to terminal (Can also add `os.getpid()` to watch window)
        - Place a breakpoint inside the function you'd like to debug in `methods.cpp`
        - launch "Debugger Attach" (`launch.json`) and enter the pid when prompted.
        - enjoy!

*

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
