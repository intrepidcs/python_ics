
#include <Python.h>
#include <datetime.h>
#include "defines.h"
#include "setup_module_auto_defines.h"
#include "methods.h"
#include "exceptions.h"
#include "object_spy_message.h"
#include "object_can_settings.h"
#include "object_swcan_settings.h"
#include "object_lin_settings.h"
#include "object_uart_settings.h"
#include "object_textapi_settings.h"
#include "object_iso9141_keyword2000_settings.h"
#include "object_iso9141_keyword2000_init_steps.h"
#include "object_vcan3_settings.h"
#include "object_fire_settings.h"
#include "object_neo_device.h"
#include "object_vcanrf_settings.h"
#include "object_cyan_settings.h"
#include "object_canfd_settings.h"
#include "object_api_firmware_info.h"
#include "object_op_eth_general_settings.h"
#include "object_op_eth_settings.h"
#include "object_rad_galaxy_settings.h"
#include "object_ethernet_settings.h"
#include "object_cm_iso157652_tx_message.h"
#include "object_cm_iso157652_rx_message.h"
#include "object_vcan412_settings.h"
#include "object_vividcan_settings.h"
#include "object_fire2_device_status.h"
#include "object_vcan4_device_status.h"
#include "object_ics_device_status.h"
#include "object_device_settings.h"

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
    setup_can_settings_object(module);
    setup_swcan_settings_object(module);
    setup_lin_settings_object(module);
    setup_uart_settings_object(module);
    setup_textapi_settings_object(module);
    setup_iso9141keyword2000_settings_object(module);
    setup_iso9141keyword2000_init_steps_object(module);
    setup_vcan3_settings_object(module);
    setup_fire_settings_object(module);
    setup_vcanrf_settings_object(module);
    setup_cyan_settings_object(module);
    setup_canfd_settings_object(module);
    setup_api_firmware_info_object(module);
    setup_op_eth_general_settings_object(module);
    setup_op_eth_settings_object(module);
    setup_rad_galaxy_settings_object(module);
    setup_ethernet_settings_object(module);
    setup_cm_iso157652_tx_message_object(module);
    setup_cm_iso157652_rx_message_object(module);
    setup_vcan412_settings_object(module);
    setup_vividcan_settings_object(module);
    setup_fire2_device_status_object(module);
    setup_vcan4_device_status_object(module); // 803+
    setup_ics_device_status_object(module);
    setup_device_settings_object(module);

#if PY_MAJOR_VERSION >= 3
    return module;
#else
    return;
#endif
}

#ifdef __cplusplus
}
#endif
