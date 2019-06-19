
#include <Python.h>
#include <datetime.h>
#include "defines.h"
#include "setup_module_auto_defines.h"
#include "methods.h"
#include "exceptions.h"
#include "object_spy_message.h"
#include "object_neo_device.h"

#define _DOC_ICS_MODULE \
    "Python C Code module for interfacing to the icsneo40 dynamic library. Code tries\n" \
    "to respect PEP 8 (http://python.org/dev/peps/pep-0008). Function naming convention does\n" \
    "not follow the tradition c style icsneo40 naming convention as pyics module\n" \
    "name acts as the namespace (icsneo portion of the function) and function names\n" \
    "are suppose to be lowercase with underscores instead of mixedCase like icsneo API.\n" \
    "\n" \
    "C API can be mimiced almost identically by doing the following:\n" \
    "\t>>> import ics as icsneo\n" \
    "\t>>> devices = icsneo.FindNeoDevices()\n" \
    "\t>>> for device in devices:\n" \
    "\t...     print(device.Name, device.SerialNumber)\n" \
    "\t...\n" \
    "\tneoVI FIRE 59886\n" \
    "\n" \
    "Recommended `Python` way by doing the following:\n" \
    "\t>>> import ics\n" \
    "\t>>> devices = ics.find_devices()\n" \
    "\t>>> for device in devices:\n" \
    "\t...     print(device.Name, device.SerialNumber)\n" \
    "\t...\n" \
    "\tneoVI FIRE 59886\n" \
    "\n" \
    "It should be noted that :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "` is used a little bit differently than the C API.\n" \
    ":class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "` contains two extra members:\n" \
    "\t:class:`" MODULE_NAME"." NEO_DEVICE_OBJECT_NAME ".AutoHandleClose` and :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "._Handle`\n" \
    "The handle normally returned from `icsneoOpenNeoDevice()` is stored inside _Handle and setting AutoHandleClose to True (Default)\n" \
    "will automatically close the handle when the :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "` goes out of scope.\n" \
    "\n" \
    "\n" \
    "Installation:\n" \
    "\n" \
    "\tpip install python_ics\n" \
    "\n" \
    "https://pypi.python.org/pypi/python-ics\n"


#if PY_MAJOR_VERSION >= 3
static PyModuleDef IcsModule = {
    PyModuleDef_HEAD_INIT,
    MODULE_NAME,
    _DOC_ICS_MODULE,
    -1,
    IcsMethods,
    NULL,
    NULL,
    NULL,
    NULL
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_ics(void)
#else
void initics(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject* module = PyModule_Create(&IcsModule);
#else
    PyObject* module = Py_InitModule3(MODULE_NAME, IcsMethods, _DOC_ICS_MODULE);
#endif
    if (!module) {
#if PY_MAJOR_VERSION >= 3
        return module;
#else
        return;
#endif
    }
    PyDateTime_IMPORT;

    // Add build constant variables
    setup_module_defines(module);
    setup_module_auto_defines(module);

    initialize_exceptions(module);

    // These were a WIP, as you get towards the bottom the code structure is simplier.
    setup_neo_device_object(module);
    setup_spy_message_object(module);

#if PY_MAJOR_VERSION >= 3
    return module;
#else
    return;
#endif
}

#ifdef __cplusplus
}
#endif
