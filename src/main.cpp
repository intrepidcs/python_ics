#include <ice/ice.h>
#include <Python.h>
#include <datetime.h>
#include "defines.h"
#include "setup_module_auto_defines.h"
#include "methods.h"
#include "exceptions.h"
#include "object_spy_message.h"

#define _DOC_ICS_MODULE                                                                                                \
    "Python C Code module for interfacing to the icsneo40 dynamic library. Code tries\n"                               \
    "to respect PEP 8 (http://python.org/dev/peps/pep-0008). Function naming convention does\n"                        \
    "not follow the tradition c style icsneo40 naming convention as the python_ics module\n"                           \
    "name acts as the namespace (icsneo portion of the function) and function names\n"                                 \
    "are suppose to be lowercase with underscores instead of mixedCase like the icsneo API.\n"                         \
    "\n"                                                                                                               \
    "C API can be mimiced almost identically by doing the following:\n"                                                \
    "\t>>> import ics as icsneo\n"                                                                                     \
    "\t>>> devices = icsneo.FindNeoDevices()\n"                                                                        \
    "\t>>> for device in devices:\n"                                                                                   \
    "\t...     print(device)\n"                                                                                        \
    "\t...\n"                                                                                                          \
    "\tneoVI FIRE 59886\n"                                                                                             \
    "\n"                                                                                                               \
    "Recommended `Python` way by doing the following:\n"                                                               \
    "\t>>> import ics\n"                                                                                               \
    "\t>>> devices = ics.find_devices()\n"                                                                             \
    "\t>>> for device in devices:\n"                                                                                   \
    "\t...     print(device)\n"                                                                                        \
    "\t...\n"                                                                                                          \
    "\tneoVI FIRE 59886\n"                                                                                             \
    "\n"                                                                                                               \
    "It should be noted that :class:`" MODULE_NAME ".PyNeoDeviceEx`"                                                   \
    " is used a little bit differently than the C API.\n"                                                              \
    ":class:`" MODULE_NAME ".PyNeoDeviceEx` contains two extra members:\n"                                             \
    ":class:`" MODULE_NAME ".PyNeoDeviceEx.AutoHandleClose` and :class:`" MODULE_NAME ".PyNeoDeviceEx._Handle`\n\n"    \
    "The handle normally returned from `icsneoOpenNeoDevice()` is stored inside _Handle and setting AutoHandleClose "  \
    "to True (Default)\n"                                                                                              \
    "will automatically close the handle when the :class:`" MODULE_NAME ".PyNeoDeviceEx"                               \
    "` goes out of scope.\n"                                                                                           \
    "\n"                                                                                                               \
    "\n"                                                                                                               \
    "Installation:\n"                                                                                                  \
    "\n"                                                                                                               \
    "\tpip install python_ics\n"                                                                                       \
    "\n"                                                                                                               \
    "https://pypi.python.org/pypi/python-ics\n"

static PyModuleDef IcsModule = {
    PyModuleDef_HEAD_INIT, MODULE_NAME, _DOC_ICS_MODULE, -1, IcsMethods, NULL, NULL, NULL, NULL
};

void initialize_ics_library() {    
#if (defined(_WIN32) || defined(__WIN32__))
    // Everything besides windows uses libicsneo
    constexpr char LIBRARY_NAME[] = "icsneo40";
#else
    constexpr char LIBRARY_NAME[] = "icsneolegacy";
#endif
    auto& mgr = ice::LibraryManager::instance();
    const auto& library_name = ice::LibraryName(LIBRARY_NAME);
    mgr.add("ics", library_name.build(), true);
}

#ifdef __cplusplus
extern "C"
{
#endif

    PyMODINIT_FUNC PyInit_ics(void)
    {
        PyObject* module = PyModule_Create(&IcsModule);
        if (!module) {
            return module;
        }
        PyDateTime_IMPORT;

        initialize_ics_library();

#ifdef Py_GIL_DISABLED
        // Enable the experimental free threaded introduced in 3.13
        PyUnstable_Module_SetGIL(module, Py_MOD_GIL_NOT_USED);
#endif
        // Add build constant variables
        setup_module_defines(module);
        setup_module_auto_defines(module);

        initialize_exceptions(module);

        setup_spy_message_object(module);

        return module;
    }

#ifdef __cplusplus
}
#endif
