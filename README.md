# python_ics

Python C Code module for interfacing to the icsneo40 dynamic library. Code tries to respect PEP 8 (https://www.python.org/dev/peps/pep-0008/). Function naming convention does not follow the tradition c style icsneo40 naming convention as the python_ics module name acts as the namespace (icsneo portion of the function) and function names are suppose to be lowercase with underscores instead of mixedCase like icsneo API.

# Installing

- `pip install python_ics`

- Placing icsneo40.dll in the system path as the api uses this DLL extensively.

# How to use

#### Documentation

http://python-ics.readthedocs.io/

#### C API can be mimiced almost identically by doing the following:

    >>> import ics as icsneo
    >>> devices = icsneo.FindNeoDevices()
    >>> for device in devices:
    ...     print(device.Name, device.SerialNumber)
    ...
    neoVI FIRE 59886
    
#### Recommended Python way by doing the following:

    >>> import ics
    >>> devices = ics.find_devices()
    >>> for device in devices:
    ...     print(device.Name, device.SerialNumber)
    ...
    neoVI FIRE 59886

It should be noted that `ics.NeoDevice` is used a little bit differently than the C API. `ics.NeoDevice` contains two extra members:

`ics.NeoDevice.AutoHandleClose` and `ics.NeoDevice._Handle`
The handle normally returned from `icsneoOpenNeoDevice()` is stored inside `_Handle` and setting `AutoHandleClose` to `True` (Default) will automatically close the handle when the `ics.NeoDevice` goes out of scope.

# License - MIT

Copyright (c) 2017 Intrepid Control Systems, Inc.

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
