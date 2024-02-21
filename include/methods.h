#ifndef _METHODS_H_
#define _METHODS_H_
#include <Python.h>
#include "object_neo_device.h"
#include "object_spy_message.h"
#include "setup_module_auto_defines.h"

#ifdef _cplusplus
extern "C"
{
#endif

    PyObject* meth_find_devices(PyObject* self, PyObject* args, PyObject* keywords);
    PyObject* meth_open_device(PyObject* self, PyObject* args, PyObject* keywords);
    PyObject* meth_close_device(PyObject* self, PyObject* args);
    PyObject* meth_get_rtc(PyObject* self, PyObject* args);
    PyObject* meth_set_rtc(PyObject* self, PyObject* args);
    PyObject* meth_coremini_load(PyObject* self, PyObject* args);
    PyObject* meth_coremini_start(PyObject* self, PyObject* args);
    PyObject* meth_coremini_stop(PyObject* self, PyObject* args);
    PyObject* meth_coremini_clear(PyObject* self, PyObject* args);
    PyObject* meth_coremini_get_status(PyObject* self, PyObject* args);
    PyObject* meth_transmit_messages(PyObject* self, PyObject* args);
    PyObject* meth_get_messages(PyObject* self, PyObject* args);
    PyObject* meth_get_script_status(PyObject* self, PyObject* args);
    PyObject* meth_get_error_messages(PyObject* self, PyObject* args);
#ifdef _USE_INTERNAL_HEADER_
    PyObject* meth_flash_devices(PyObject* self, PyObject* args);
#endif // _USE_INTERNAL_HEADER_
    PyObject* meth_set_reflash_callback(PyObject* self, PyObject* args);
    PyObject* meth_get_device_settings(PyObject* self, PyObject* args);
    PyObject* meth_set_device_settings(PyObject* self, PyObject* args);
    PyObject* meth_load_default_settings(PyObject* self, PyObject* args); // icsneoLoadDefaultSettings
    // PyObject* meth_spy_message_to_j1850(PyObject* self, PyObject* args);
    PyObject* meth_read_sdcard(PyObject* self, PyObject* args);
    PyObject* meth_write_sdcard(PyObject* self, PyObject* args);
    PyObject* meth_create_neovi_radio_message(PyObject* self, PyObject* args, PyObject* keywords);
    PyObject* meth_coremini_start_fblock(PyObject* self, PyObject* args);      // ScriptStartFBlock
    PyObject* meth_coremini_stop_fblock(PyObject* self, PyObject* args);       // ScriptStopFBlock
    PyObject* meth_coremini_get_fblock_status(PyObject* self, PyObject* args); // ScriptGetFBlockStatus
    PyObject* meth_coremini_read_app_signal(PyObject* self, PyObject* args);   // ScriptReadAppSignal
    PyObject* meth_coremini_write_app_signal(PyObject* self, PyObject* args);  // ScriptWriteAppSignal
    PyObject* meth_coremini_read_tx_message(PyObject* self, PyObject* args);   // ScriptReadTxMessage
    PyObject* meth_coremini_read_rx_message(PyObject* self, PyObject* args);   // ScriptReadRxMessage
    PyObject* meth_coremini_write_tx_message(PyObject* self, PyObject* args);  // ScriptWriteTxMessage
    PyObject* meth_coremini_write_rx_message(PyObject* self, PyObject* args);  // ScriptWriteRxMessage
    PyObject* meth_get_performance_parameters(PyObject* self, PyObject* args);
    PyObject* meth_validate_hobject(PyObject* self, PyObject* args);
    PyObject* meth_get_last_api_error(PyObject* self, PyObject* args);
    PyObject* meth_get_dll_version(PyObject* self, PyObject* args);
    PyObject* meth_get_hw_firmware_info(PyObject* self, PyObject* args);
    PyObject* meth_base36enc(PyObject* self, PyObject* args);
    PyObject* meth_get_serial_number(PyObject* self, PyObject* args);
    PyObject* meth_request_enter_sleep_mode(PyObject* self, PyObject* args);
    PyObject* meth_set_context(PyObject* self, PyObject* args);
    PyObject* meth_force_firmware_update(PyObject* self, PyObject* args);
    PyObject* meth_firmware_update_required(PyObject* self, PyObject* args);
    PyObject* meth_get_dll_firmware_info(PyObject* self, PyObject* args);
    PyObject* meth_get_backup_power_enabled(PyObject* self, PyObject* args);
    PyObject* meth_set_backup_power_enabled(PyObject* self, PyObject* args);
    PyObject* meth_get_backup_power_ready(PyObject* self, PyObject* args);
    PyObject* meth_load_readbin(PyObject* self, PyObject* args);
    PyObject* meth_iso15765_transmit_message(PyObject* self, PyObject* args); // icsneoISO15765_TransmitMessage
    PyObject* meth_iso15765_receive_message(PyObject* self, PyObject* args);  // icsneoISO15765_ReceiveMessageMessage
    PyObject* meth_iso15765_enable_networks(PyObject* self, PyObject* args);  // icsneoISO15765_EnableNetworks
    PyObject* meth_iso15765_disable_networks(PyObject* self, PyObject* args); // icsneoISO15765_DisableNetworks
    PyObject* meth_get_active_vnet_channel(PyObject* self, PyObject* args);
    PyObject* meth_set_active_vnet_channel(PyObject* self, PyObject* args);
    PyObject* meth_override_library_name(PyObject* self, PyObject* args);
    PyObject* meth_get_library_path(PyObject* self);
    PyObject* meth_set_bit_rate(PyObject* self, PyObject* args);
    PyObject* meth_set_fd_bit_rate(PyObject* self, PyObject* args);
    PyObject* meth_set_bit_rate_ex(PyObject* self, PyObject* args);
    PyObject* meth_get_timestamp_for_msg(PyObject* self, PyObject* args);
    PyObject* meth_get_device_status(PyObject* self, PyObject* args);
    PyObject* meth_enable_network_com(PyObject* self, PyObject* args); // icsneoEnableNetworkCom
    PyObject* meth_enable_bus_voltage_monitor(PyObject* self, PyObject* args);
    PyObject* meth_get_bus_voltage(PyObject* self, PyObject* args);
    PyObject* meth_read_jupiter_firmware(PyObject* self, PyObject* args);
    PyObject* meth_write_jupiter_firmware(PyObject* self, PyObject* args);
    PyObject* meth_get_disk_details(PyObject* self, PyObject* args);
    PyObject* meth_disk_format(PyObject* self, PyObject* args);
    PyObject* meth_disk_format_cancel(PyObject* self, PyObject* args);
    PyObject* meth_get_disk_format_progress(PyObject* self, PyObject* args);
    PyObject* meth_enable_doip_line(PyObject* self, PyObject* args);            // icsneoEnableDOIPLine
    PyObject* meth_is_device_feature_supported(PyObject* self, PyObject* args); // icsneoIsDeviceFeatureSupported
    PyObject* meth_get_pcb_serial_number(PyObject* self, PyObject* args);
    PyObject* meth_set_led_property(PyObject* self, PyObject* args);
    PyObject* meth_start_dhcp_server(PyObject* self, PyObject* args);
    PyObject* meth_stop_dhcp_server(PyObject* self, PyObject* args);
    PyObject* meth_wbms_manager_write_lock(PyObject* self, PyObject* args);
    PyObject* meth_wbms_manager_reset(PyObject* self, PyObject* args);
    PyObject* meth_uart_write(PyObject* self, PyObject* args);
    PyObject* meth_uart_read(PyObject* self, PyObject* args);
    PyObject* meth_uart_set_baudrate(PyObject* self, PyObject* args);
    PyObject* meth_uart_get_baudrate(PyObject* self, PyObject* args);
    PyObject* meth_generic_api_send_command(PyObject* self, PyObject* args);
    PyObject* meth_generic_api_read_data(PyObject* self, PyObject* args);
    PyObject* meth_generic_api_get_status(PyObject* self, PyObject* args);
    PyObject* meth_get_gptp_status(PyObject* self, PyObject* args);       // icsneoGetGPTPStatus
    PyObject* meth_get_all_chip_versions(PyObject* self, PyObject* args); // icsneoGetAllChipVersions
    PyObject* meth_flash_accessory_firmware(PyObject* self, PyObject* args);
    PyObject* meth_get_accessory_firmware_version(PyObject* self, PyObject* args);

#ifdef _cplusplus
}
#endif

#define _EZ_ICS_STRUCT_METHOD(name, icsname, icsname_no_icsneo, meth, flags, doc)                                      \
    { name, (PyCFunction)meth, flags, doc },                                                                           \
        { icsname,                                                                                                     \
          (PyCFunction)meth,                                                                                           \
          flags,                                                                                                       \
          "\n.. note:: Compatibility Function: Identical to PEP8 compliant :func:`" MODULE_NAME "." name               \
          "` method.\n\n" },                                                                                           \
    {                                                                                                                  \
        icsname_no_icsneo, (PyCFunction)meth, flags,                                                                   \
            "\n.. note:: Compatibility Function: Identical to PEP8 compliant :func:`" MODULE_NAME "." name             \
            "` method.\n\n"                                                                                            \
    }

#define _EZ_ICS_STRUCT_METHOD_MULTIPLE(name, icsname, icsname_no_icsneo, meth, flags, doc)                             \
    { icsname,                                                                                                         \
      (PyCFunction)meth,                                                                                               \
      flags,                                                                                                           \
      "\n.. note:: Compatibility Function: Identical to PEP8 compliant :func:`" MODULE_NAME "." name                   \
      "` method.\n\n" },                                                                                               \
    {                                                                                                                  \
        icsname_no_icsneo, (PyCFunction)meth, flags,                                                                   \
            "\n.. note:: Compatibility Function: Identical to PEP8 compliant :func:`" MODULE_NAME "." name             \
            "` method.\n\n"                                                                                            \
    }

#define _DOC_FIND_DEVICES                                                                                              \
    MODULE_NAME ".find_devices(device_type=" MODULE_NAME ".NEODEVICE_ALL)\n"                                           \
                "\n"                                                                                                   \
                "Finds all connected devices and returns a tuple of :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME   \
                "` for use in :func:`" MODULE_NAME ".open_device`\n"                                                   \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice_type (int): Accepts " MODULE_NAME ".NEODEVICE_* Macros\n\n"                                  \
                "\t*New in 3.0 (803):*\n\n"                                                                            \
                "\tdevice_types (List/Tuple): Accepts a Container of " MODULE_NAME ".NEODEVICE_* Macros\n\n"           \
                "\tnetwork_id (int): OptionsFindNeoEx.CANOptions.iNetworkID. Usually ics.NETID_CAN, if needed\n\n"     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tTuple of :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "` for use in :func:`" MODULE_NAME        \
                ".open_device`\n"                                                                                      \
                "\n"                                                                                                   \
                "\t>>> for device in ics.find_devices():\n"                                                            \
                "\t...     print(device.Name, device.SerialNumber)\n"                                                  \
                "\t...\n"                                                                                              \
                "\tneoVI FIRE 59886\n"                                                                                 \
                "\n*New in 3.0 (803):*\n"                                                                              \
                "\t>>> for device in ics.find_devices([ics.NEODEVICE_FIRE, ics.NEODEVICE_VCAN3]):\n"                   \
                "\t...     print(device.Name, device.SerialNumber)\n"                                                  \
                "\t...\n"                                                                                              \
                "\tneoVI FIRE 59886\n"

#define _DOC_OPEN_DEVICES                                                                                              \
    MODULE_NAME                                                                                                        \
    ".open_device(device)\n"                                                                                           \
    "\n"                                                                                                               \
    "Opens the device. `device` can be omitted to return a :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME            \
    "` of the\n"                                                                                                       \
    "first free availible device, a :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME                                   \
    "`, or a serial number of the device.\n"                                                                           \
    "\n"                                                                                                               \
    "Args:\n"                                                                                                          \
    "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME  \
    "`\n\n"                                                                                                            \
    "\tdevice (int): Serial Number of the device\n\n"                                                                  \
    "\tnetwork_ids (List/Tuple): This is an array of number IDs which specify the NetworkID parameter of each "        \
    "network. This allows you to assign a custom network ID to each network. Normally, you will assign consecutive "   \
    "IDs to each of the networks. See NetworkIDList for a list of current network ID's. You may also set this "        \
    "parameter to NULL (zero) and the default network ID's will be used.\n\n"                                          \
    "\tconfig_read (int): Specifies whether the DLL should read the neoVI's device configuration before enabling the " \
    "device. It is recommended that this value be set to 1.\n\n"                                                       \
    "\toptions (int): DEVICE_OPTION_* defines\n\n"                                                                     \
    "\tnetwork_id (int): OptionsFindNeoEx.CANOptions.iNetworkID. Usually ics.NETID_CAN, if needed\n\n"                 \
    "\tuse_server (int): Defaults to False, Setting to True allows opening the same device more than once.\n\n"        \
    "\n"                                                                                                               \
    "Raises:\n"                                                                                                        \
    "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                                        \
    "\n"                                                                                                               \
    "Returns:\n"                                                                                                       \
    "\tIf :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "` is passed as a parameter, None. \n"                      \
    "\tIf serial number is passed as a parameter, a :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME                   \
    "` will be returned. \n"                                                                                           \
    "\tIf `device` parameter is omitted, a :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME                            \
    "` will be returned with the first availible free device. \n"                                                      \
    "\n"                                                                                                               \
    "\t>>> for device in ics.find_devices():\n"                                                                        \
    "\t...     ics.open_device(device)\n"                                                                              \
    "\t...\n"                                                                                                          \
    "\n"                                                                                                               \
    ".. note::\n\t:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME                                                     \
    "` will automatically close the device when it goes out of scope.\n\n"

#define _DOC_CLOSE_DEVICES                                                                                             \
    MODULE_NAME ".close_device(device)\n"                                                                              \
                "\n"                                                                                                   \
                "Closes the device.\n"                                                                                 \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tError Count (int)\n"                                                                                \
                "\n"                                                                                                   \
                "\t>>> for device in ics.find_devices():\n"                                                            \
                "\t...     ics.open_device(device)\n"                                                                  \
                "\t...     # Do something with the device...\n"                                                        \
                "\t...     ics.close_device(device)\n"                                                                 \
                "\t...\n"                                                                                              \
                "\n"                                                                                                   \
                ".. note::\n\t:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME                                         \
                "` will automatically close the device when it goes out of scope.\n\n"

#define _DOC_GET_RTC                                                                                                   \
    MODULE_NAME ".get_rtc(device)\n"                                                                                   \
                "\n"                                                                                                   \
                "Gets the Real-Time Clock of the device.\n"                                                            \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tTuple: (datetime.datetime object, offset in seconds)\n"                                             \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.get_rtc(device)\n"                                                                          \
                "\t(datetime.datetime(2014, 9, 10, 17, 45, 45), 3)\n"

#define _DOC_SET_RTC                                                                                                   \
    MODULE_NAME ".set_rtc(device[, time])\n"                                                                           \
                "\n"                                                                                                   \
                "Sets the Real-Time Clock of the device.\n"                                                            \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\ttime (:class:`datetime.datetime`): Optional. Sets to current time, if omitted.\n\n"                 \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.set_rtc(device)\n"

#define _DOC_COREMINI_LOAD                                                                                             \
    MODULE_NAME ".coremini_load(device, coremini, location)\n"                                                         \
                "\n"                                                                                                   \
                "Loads the CoreMini into the device.\n"                                                                \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tcoremini (str/tuple): Use string to load from file, Use Tuple if file data.\n\n"                    \
                "\tlocation (int): Accepts :class:`" MODULE_NAME ".SCRIPT_LOCATION_FLASH_MEM`, :class:`" MODULE_NAME   \
                ".SCRIPT_LOCATION_SDCARD`, or :class:`" MODULE_NAME ".SCRIPT_LOCATION_VCAN3_MEM`\n\n"                  \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.coremini_load(device, 'cmvspy.vs3cmb', ics.SCRIPT_LOCATION_SDCARD)\n"

#define _DOC_COREMINI_START                                                                                            \
    MODULE_NAME ".coremini_start(device, location)\n"                                                                  \
                "\n"                                                                                                   \
                "Starts the CoreMini into the device.\n"                                                               \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tlocation (int): Accepts :class:`" MODULE_NAME ".SCRIPT_LOCATION_FLASH_MEM`, :class:`" MODULE_NAME   \
                ".SCRIPT_LOCATION_SDCARD`, or :class:`" MODULE_NAME ".SCRIPT_LOCATION_VCAN3_MEM`\n\n"                  \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.coremini_start(device, ics.SCRIPT_LOCATION_SDCARD)\n"

#define _DOC_COREMINI_STOP                                                                                             \
    MODULE_NAME ".coremini_stop(device)\n"                                                                             \
                "\n"                                                                                                   \
                "Stops the CoreMini into the device.\n"                                                                \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.coremini_stop(device)\n"

#define _DOC_COREMINI_CLEAR                                                                                            \
    MODULE_NAME ".coremini_clear(device, location)\n"                                                                  \
                "\n"                                                                                                   \
                "Clears the CoreMini into the device.\n"                                                               \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tlocation (int): Accepts :class:`" MODULE_NAME ".SCRIPT_LOCATION_FLASH_MEM`, :class:`" MODULE_NAME   \
                ".SCRIPT_LOCATION_SDCARD`, or :class:`" MODULE_NAME ".SCRIPT_LOCATION_VCAN3_MEM`\n\n"                  \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.coremini_clear(device, ics.SCRIPT_LOCATION_SDCARD)\n"

#define _DOC_COREMINI_GET_STATUS                                                                                       \
    MODULE_NAME ".coremini_get_status(device)\n"                                                                       \
                "\n"                                                                                                   \
                "Gets the status of the CoreMini in the device.\n"                                                     \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tTrue if running, otherwise False.\n"                                                                \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.coremini_get_status(device)\n"                                                              \
                "\t>>>\n"

#define _DOC_TRANSMIT_MESSAGES                                                                                         \
    MODULE_NAME ".transmit_messages(device, messages)\n"                                                               \
                "\n"                                                                                                   \
                "Transmits message(s) on the device. `messages` can be a tuple of :class:`" MODULE_NAME                \
                "." SPY_MESSAGE_OBJECT_NAME "`\n"                                                                      \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tmessages (:class:`" MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME "`): :class:`" MODULE_NAME              \
                "." SPY_MESSAGE_OBJECT_NAME "`\n\n"                                                                    \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> msg = ics.SpyMessage()\n"                                                                       \
                "\t>>> msg.ArbIDOrHeader = 0xFF\n"                                                                     \
                "\t>>> msg.NetworkID = ics.NETID_HSCAN\n"                                                              \
                "\t>>> msg.Data = (0,1,2,3,4,5,6,7)\n"                                                                 \
                "\t>>> ics.transmit_messages(device, msg)\n"                                                           \
                "\t>>>\n"

#define _DOC_GET_MESSAGES                                                                                              \
    MODULE_NAME ".get_messages(device[, j1850, timeout])\n"                                                            \
                "\n"                                                                                                   \
                "Gets the message(s) on the device.\n"                                                                 \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tj1850 (:class:`bool`): Return :class:`" MODULE_NAME "." SPY_MESSAGE_J1850_OBJECT_NAME               \
                "` instead.\n\n"                                                                                       \
                "\ttimeout (:class:`float`): Optional timeout to wait for messages in seconds (0.1 = 100ms).\n\n"      \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\t:class:`tuple` of two items. First item is a :class:`tuple` of :class:`" MODULE_NAME                \
                "." SPY_MESSAGE_OBJECT_NAME "` and second is the error count.\n"                                       \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> messages, errors = ics.get_messages(device)\n"                                                  \
                "\t>>> len(messages)\n"                                                                                \
                "\t14\n"                                                                                               \
                "\t>>> hex(messages[0].ArbIDOrHeader)\n"                                                               \
                "\t'0x160'\n"                                                                                          \
                "\t>>> messages[0].Data\n"                                                                             \
                "\t(36, 11, 11, 177, 37, 3, 11, 199)\n"                                                                \
                "\t>>> errors\n"                                                                                       \
                "\t0\n"

//"Accepts a " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME ", exception on error. Returns a list of (error #, string)"
#define _DOC_GET_ERROR_MESSAGES                                                                                        \
    MODULE_NAME ".get_error_messages(device[, j1850, timeout])\n"                                                      \
                "\n"                                                                                                   \
                "Gets the error message(s) on the device.\n"                                                           \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\t:class:`list` of :class:`tuple`s. :class:`tuple` contents: (error_number, description_short, "      \
                "description_long, severity, restart_needed)\n"                                                        \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> errors = ics.get_error_messages(device)\n"

//_DOC_SET_REFLASH_DISPLAY_CALLBACKS), "icsneoSetReflashCallback(), pass a python function func(msg, progress)"
#define _DOC_SET_REFLASH_CALLBACK                                                                                      \
    MODULE_NAME                                                                                                        \
    ".set_reflash_callback(callback)\n"                                                                                \
    "\n"                                                                                                               \
    "Sets the reflash display callback.\n"                                                                             \
    "\n"                                                                                                               \
    "Args:\n"                                                                                                          \
    "\tcallback (:class:`function`): Must be a callable Python function (`def callback(msg, progress)`)\n\n"           \
    "\n"                                                                                                               \
    "Raises:\n"                                                                                                        \
    "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                                        \
    "\n"                                                                                                               \
    "Returns:\n"                                                                                                       \
    "\tNone.\n"                                                                                                        \
    "\n"                                                                                                               \
    "\t>>> def callback(msg, progress):\n"                                                                             \
    "\t...     print(msg, progress)\n"                                                                                 \
    "\t...\n"                                                                                                          \
    "\t>>> ics.set_reflash_callback(callback)\n"                                                                       \
    "\t>>> \n"

#define _DOC_GET_DEVICE_SETTINGS                                                                                       \
    MODULE_NAME                                                                                                        \
    ".get_device_settings(device, device_type, vnet_slot)\n"                                                           \
    "\n"                                                                                                               \
    "Gets the settings in the device. vnet_slot defaults to " MODULE_NAME ".PlasmaIonVnetChannelMain\n"                \
    "\n"                                                                                                               \
    "Args:\n"                                                                                                          \
    "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME  \
    "`\n\n"                                                                                                            \
    "\tdevice_type (EDeviceSettingsType): Optional: Overrides default device setings type. Defaults to '-1'\n\n"       \
    "\tvnet_slot (PlasmaIonVnetChannelMain): Optional: Defaults to PlasmaIonVnetChannelMain, Used only for "           \
    "PLASMA/ION Devices.\n\n"                                                                                          \
    "\n"                                                                                                               \
    "Raises:\n"                                                                                                        \
    "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                                        \
    "\n"                                                                                                               \
    "Returns:\n"                                                                                                       \
    "\t:class:`" MODULE_NAME "."                                                                                       \
    "device_settings"                                                                                                  \
    "`\n"                                                                                                              \
    "\n"                                                                                                               \
    "\t>>> d = ics.open_device()\n"                                                                                    \
    "\t>>> d.Name\n"                                                                                                   \
    "\t'neoVI ION'\n"                                                                                                  \
    "\t>>> d.SerialNumber\n"                                                                                           \
    "\t404444\n"                                                                                                       \
    "\t>>> s = ics.get_device_settings(d)\n"                                                                           \
    "\t>>> s.DeviceSettingType\n"                                                                                      \
    "\t2\n"                                                                                                            \
    "\t>>> s.cyan\n"                                                                                                   \
    "\t<ics.CyanSettings object at 0x01E61B40>\n"                                                                      \
    "\t>>> s.cyan.canfd1.FDMode\n"                                                                                     \
    "\t4\n"                                                                                                            \
    "\t>>> s2.cyan\n"                                                                                                  \
    "\t<ics.CyanSettings object at 0x02B113C8>\n"                                                                      \
    "\t>>> s2 = ics.get_device_settings(d, -1, ics.PlasmaIonVnetChannelA)\n"                                           \
    "\t>>> s2.DeviceSettingType\n"                                                                                     \
    "\t2\n"                                                                                                            \
    "\t>>> s2.cyan.canfd1.FDMode\n"                                                                                    \
    "\t4\n"

#define _DOC_SET_DEVICE_SETTINGS                                                                                       \
    MODULE_NAME ".set_device_settings(device, settings, save_to_eeprom, vnet_slot)\n"                                  \
                "\n"                                                                                                   \
                "Sets the settings in the device. vnet_slot defaults to " MODULE_NAME ".PlasmaIonVnetChannelMain\n"    \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tsettings (:class:`" MODULE_NAME "."                                                                 \
                "device_settings"                                                                                      \
                "`): :class:`" MODULE_NAME "."                                                                         \
                "device_settings"                                                                                      \
                "`\n\n"                                                                                                \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> d.Name\n"                                                                                       \
                "\t'neoVI ION'\n"                                                                                      \
                "\t>>> d.SerialNumber\n"                                                                               \
                "\t404444\n"                                                                                           \
                "\t>>> s = ics.get_device_settings(d, ics.PlasmaIonVnetChannelA) # Get Slave settings, channel "       \
                "selection not needed if not a Plasma/Ion\n"                                                           \
                "\t>>> s.DeviceSettingType\n"                                                                          \
                "\t2\n"                                                                                                \
                "\t>>> s.cyan.can_switch_mode\n"                                                                       \
                "\t1\n"                                                                                                \
                "\t>>> s.cyan.can_switch_mode = 2\n"                                                                   \
                "\t>>> ics.set_device_settings(d, s, True, ics.PlasmaIonVnetChannelA)\n"                               \
                "\t>>> \n"

//"Accepts a " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME ", exception on error."
#define _DOC_LOAD_DEFAULT_SETTINGS                                                                                     \
    MODULE_NAME ".load_default_settings(device)\n"                                                                     \
                "\n"                                                                                                   \
                "Load the default settings in the device.\n"                                                           \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.load_default_settings(device)\n"                                                            \
                "\t>>> \n"

#define _DOC_CREATE_NEOVI_RADIO_MESSAGE                                                                                \
    MODULE_NAME                                                                                                        \
    ".create_neovi_radio_message(Relay1, Relay2, Relay3, Relay4, Relay5, LED6, LED5, MSB_report_rate, "                \
    "LSB_report_rate, analog_change_report_rate, relay_timeout)\n\n"                                                   \
    "Python API only. Generates data bytes for use with neoVI RADI/O CAN Messages\n\n"                                 \
    "Kwargs:\n"                                                                                                        \
    "\tRelay1 (boolean): Enable/Disable Relay1\n\n"                                                                    \
    "\tRelay2 (boolean): Enable/Disable Relay2\n\n"                                                                    \
    "\tRelay3 (boolean): Enable/Disable Relay3\n\n"                                                                    \
    "\tRelay4 (boolean): Enable/Disable Relay4\n\n"                                                                    \
    "\tRelay5 (boolean): Enable/Disable Relay5\n\n"                                                                    \
    "\tLED5 (boolean): Enable/Disable LED5\n\n"                                                                        \
    "\tLED6 (boolean): Enable/Disable LED6\n\n"                                                                        \
    "\tMSB_report_rate (int): MSB Report Rate in ms (0-255)\n\n"                                                       \
    "\tLSB_report_rate (int): LSB Report Rate in ms (0-255)\n\n"                                                       \
    "\tanalog_change_report_rate (int): Analog change report rate\n\n"                                                 \
    "\trelay_timeout (int): Relay Timeout (0-255)*255ms\n\n"                                                           \
    "\n"                                                                                                               \
    "Returns:\n"                                                                                                       \
    "\n"                                                                                                               \
    "\tTuple of data bytes for use with :class:`" MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME "`\n"                        \
    "\n"                                                                                                               \
    "Raises:\n"                                                                                                        \
    "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                                        \
    "\n"                                                                                                               \
    "\t>>> msg = ics.SpyMessage()\n"                                                                                   \
    "\t>>> msg.Data = ics.create_neovi_radio_message(Relay1=True, Relay4=False, LED6=True, MSB_report_rate=10)\n"      \
    "\t>>> msg.Data\n"                                                                                                 \
    "\t(65, 10, 0, 0, 0)\n"

#define _DOC_COREMINI_START_FBLOCK                                                                                     \
    MODULE_NAME ".coremini_start_fblock(device, index)\n"                                                              \
                "\n"                                                                                                   \
                "Starts a Coremini Function Block at `index` on `device`.\n"                                           \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tindex (int): Index of the function block.\n\n"                                                      \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone on Success.\n"                                                                                 \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.coremini_start_fblock(device, 1)\n"

#define _DOC_COREMINI_STOP_FBLOCK                                                                                      \
    MODULE_NAME ".coremini_stop_fblock(device, index)\n"                                                               \
                "\n"                                                                                                   \
                "Stops a Coremini Function Block at `index` on `device`.\n"                                            \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tindex (int): Index of the function block.\n\n"                                                      \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone on Success.\n"                                                                                 \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.coremini_stop_fblock(device, 1)\n"

#define _DOC_COREMINI_GET_FBLOCK_STATUS                                                                                \
    MODULE_NAME ".coremini_get_fblock_status(device, index)\n"                                                         \
                "\n"                                                                                                   \
                "Gets the status of a Coremini Function Block at `index` on `device`.\n"                               \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tindex (int): Index of the function block.\n\n"                                                      \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone on Success.\n"                                                                                 \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.coremini_get_fblock_status(device, 1)\n"                                                    \
                "\tTrue\n"

#define _DOC_COREMINI_READ_APP_SIGNAL                                                                                  \
    MODULE_NAME ".coremini_read_app_signal(device, index)\n"                                                           \
                "\n"                                                                                                   \
                "Gets the value of a Coremini application signal at `index` on `device`.\n"                            \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tindex (int): Index of the application signal.\n\n"                                                  \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tfloat on Success.\n"                                                                                \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.coremini_read_app_signal(device, 1)\n"                                                      \
                "\t52\n"

#define _DOC_COREMINI_WRITE_APP_SIGNAL                                                                                 \
    MODULE_NAME ".coremini_write_app_signal(device, index, value)\n"                                                   \
                "\n"                                                                                                   \
                "Sets the value of a Coremini application signal at `index` on `device`.\n"                            \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tindex (int): Index of the application signal.\n\n"                                                  \
                "\tvalue (float): New value of the application signal.\n\n"                                            \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone on Success.\n"                                                                                 \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.coremini_write_app_signal(device, 1, 52)\n"                                                 \
                "\t>>>\n"

#define _DOC_COREMINI_READ_TX_MESSAGE                                                                                  \
    MODULE_NAME ".coremini_read_tx_message(device, index, j1850=False)\n"                                              \
                "\n"                                                                                                   \
                "Gets the value of a Coremini Message at `index` on `device`.\n"                                       \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tindex (int): Index of the application signal.\n\n"                                                  \
                "\tj1850 (bool): Use :class:`" MODULE_NAME "." SPY_MESSAGE_J1850_OBJECT_NAME "` instead.\n\n"          \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\t:class:`" MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME "` Success.\n"                                    \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> msg = ics.coremini_read_tx_message(device, 0)\n"

#define _DOC_COREMINI_READ_RX_MESSAGE                                                                                  \
    MODULE_NAME ".coremini_read_rx_message(device, index, j1850=False)\n"                                              \
                "\n"                                                                                                   \
                "Gets the value of a Coremini Message at `index` on `device`.\n"                                       \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tindex (int): Index of the application signal.\n\n"                                                  \
                "\tj1850 (bool): Use :class:`" MODULE_NAME "." SPY_MESSAGE_J1850_OBJECT_NAME "` instead.\n\n"          \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\t:class:`" MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME "` Success.\n"                                    \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> msg = ics.coremini_read_tx_message(device, 0)\n"

#define _DOC_COREMINI_WRITE_TX_MESSAGE                                                                                 \
    MODULE_NAME ".coremini_write_tx_message(device, index, msg)\n"                                                     \
                "TODO"

#define _DOC_COREMINI_WRITE_RX_MESSAGE                                                                                 \
    MODULE_NAME ".coremini_write_rx_message(device, index, TODO)\n"                                                    \
                "TODO"

#define _DOC_GET_PERFORMANCE_PARAMETERS                                                                                \
    MODULE_NAME ".get_performance_parameters(device)\n"                                                                \
                "\n"                                                                                                   \
                "Gets the Performance Parameters on `device`.\n"                                                       \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tTuple on Success: (buffer count, buffer max, overflow count, reserved, reserved, reserved, "        \
                "reserved, reserved)\n"                                                                                \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.get_performance_parameters(device)\n"                                                       \
                "\t(0, 24576, 0, 0, 0, 0, 0, 0)\n"

#define _DOC_VALIDATE_HOBJECT                                                                                          \
    MODULE_NAME ".validate_hobject(device)\n"                                                                          \
                "\n"                                                                                                   \
                "Validates the handle is valid for a `device`. Handles are only valid when the device is open.\n"      \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tor:\n\n"                                                                                            \
                "\tdevice (int): c style integer handle to the device.\n\n"                                            \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True if valid, false otherwise.\n"                                                         \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> ics.validate_hobject(device)\n"                                                                 \
                "\t1\n"                                                                                                \
                "\t>>> ics.validate_hobject(device._Handle)\n"                                                         \
                "\t1\n"

#define _DOC_GET_LAST_API_ERROR                                                                                        \
    MODULE_NAME ".get_last_api_error(device)\n"                                                                        \
                "\n"                                                                                                   \
                "Gets the error message from the last API call.\n"                                                     \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tTuple: (error, description short, description long, severity, restart needed)\n"                    \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> try:\n"                                                                                         \
                "\t...     msg = ics.coremini_read_tx_message(device, 0)\n"                                            \
                "\t... except ics.RuntimeError as ex:\n"                                                               \
                "\t...     print(ex)\n"                                                                                \
                "\t...     print(ics.get_last_api_error(device))\n"                                                    \
                "\t...\n"                                                                                              \
                "\tError: coremini_read_tx_message(): icsneoScriptReadTxMessage() Failed\n"                            \
                "\t(224, 'Invalid Message Index for script.', 'Invalid Message Index for script.', 16, 0)\n"

#define _DOC_GET_DLL_VERSION                                                                                           \
    MODULE_NAME ".get_dll_version(device)\n"                                                                           \
                "\n"                                                                                                   \
                "Gets the DLL version.\n"                                                                              \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tNone\n\n"                                                                                           \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tInt: DLL Version\n"                                                                                 \
                "\n"                                                                                                   \
                "\t>>> ics.get_dll_version()\n"                                                                        \
                "\t700\n"

#define _DOC_BASE36ENC                                                                                                 \
    MODULE_NAME ".base36enc(serial)\n"                                                                                 \
                "\n"                                                                                                   \
                "Converts a decimal serial number to base36.\n"                                                        \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tserial (int): serial number.\n\n"                                                                   \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tStr: Serial Number\n"                                                                               \
                "\n"                                                                                                   \
                "\t>>> ics.base36enc(device.SerialNumber)\n"                                                           \
                "\tCY0024\n"

#define _DOC_GET_SERIAL_NUMBER                                                                                         \
    MODULE_NAME ".get_serial_number(device)\n"                                                                         \
                "\n"                                                                                                   \
                "Gets the serial number out of the device.\n"                                                          \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tInt: Serial Number Version\n"                                                                       \
                "\n"                                                                                                   \
                "\t>>> ics.get_serial_number(device)\n"                                                                \
                "\t53123\n"

#define _DOC_REQUEST_ENTER_SLEEP_MODE                                                                                  \
    MODULE_NAME ".request_enter_sleep_mode(device, timeout_ms, mode, reserved_zero)\n"                                 \
                "\n"                                                                                                   \
                "Signal neoVI to immediete go to sleep. Currently only supported by FIREVNET/PLASMA.\n"                \
                "If using over USB this will likely return true but never cause PLASMA to sleep\n"                     \
                "since USB insertion keeps it alive.\n"                                                                \
                "This API allows Android/Linux applications to invoke power management.\n"                             \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\ttimeout_ms (int): 16bit word for how long to wait on idle bus before going to sleep. "              \
                "If caller does not want to change it pass in 65535 (0xFFFF) and it "                                  \
                "will stay whatever it was set to in explorer/coremini.\n\n"                                           \
                "\n"                                                                                                   \
                "\tmode (int): 16bit word for power mode to enter. "                                                   \
                "If caller does not want to change it pass in 65535 (0xFFFF) and it "                                  \
                "will stay whatever it was set to in explorer/coremini. "                                              \
                "If it is zero then neoVI will do 'normal sleep'. "                                                    \
                "0 - power mode off but calling this function will do 'normal sleep'. "                                \
                "1 - normal sleep. "                                                                                   \
                "2 - instant sleep. "                                                                                  \
                "3 - comatose sleep.\n\n"                                                                              \
                "\n"                                                                                                   \
                "\treserved_zero (int): Reserved, Keep as zero.\n\n"                                                   \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True on success, False on failure.\n"                                                      \
                "\n"                                                                                                   \
                "\t>>> ics.request_enter_sleep_mode(device, 1, 0)\n"                                                   \
                "\tTrue\n"

#define _DOC_SET_CONTEXT                                                                                               \
    MODULE_NAME ".set_context(device)\n"                                                                               \
                "\n"                                                                                                   \
                "Sets the \"context\" of how icsneoFindNeoDevices(Ex) and icsneoOpenNeoDevice(Ex)\n"                   \
                "function. If the context is 0 (null) than icsneoFindNeoDevices(Ex) will be system\n"                  \
                "wide, searching USB and other supported computer interfaces. icsneoFindNeoDevices can\n"              \
                "then be used to connect to devices found in this manner. If the context is a handle\n"                \
                "to connected CAN tool than icsneoFindNeoDevices(Ex) will search a specific CAN bus\n"                 \
                "for supported IntrepidCS CAN Nodes. Again icsneoOpenNeoDevice(Ex) would be used\n"                    \
                "create logical connections to found CAN Nodes.\n"                                                     \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True on success, False on failure.\n"                                                      \
                "\n"                                                                                                   \
                "\t>>> ics.set_context(device)\n"                                                                      \
                "\tTrue\n"

#define _DOC_FORCE_FIRMWARE_UPDATE                                                                                     \
    MODULE_NAME ".force_firmware_update(device)\n"                                                                     \
                "\n"                                                                                                   \
                "Forces the device to flash firmware.\n"                                                               \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True on success, False on failure.\n"                                                      \
                "\n"                                                                                                   \
                "\t>>> ics.force_firmware_update(device)\n"                                                            \
                "\tTrue\n"

#define _DOC_FIRMWARE_UPDATE_REQUIRED                                                                                  \
    MODULE_NAME ".firmware_update_required(device)\n"                                                                  \
                "\n"                                                                                                   \
                "Determines if the device firmware needs flashing.\n"                                                  \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True on success, False on failure.\n"                                                      \
                "\n"                                                                                                   \
                "\t>>> ics.force_firmware_update(device)\n"                                                            \
                "\tTrue\n"

#define _DOC_GET_DLL_FIRMWARE_INFO                                                                                     \
    MODULE_NAME ".get_dll_firmware_info(device)\n"                                                                     \
                "\n"                                                                                                   \
                "Returns the DLL firmware info for the device.\n"                                                      \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\t(:class:`" MODULE_NAME "."                                                                          \
                "st_api_firmware_info"                                                                                 \
                "`)\n"                                                                                                 \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> info = ics.get_dll_firmware_info(device)\n"                                                     \
                "\t>>> info.iAppMajor\n"                                                                               \
                "\t7\n"                                                                                                \
                "\t>>> info.iAppMinor\n"                                                                               \
                "\t55\n"                                                                                               \
                "\t>>>\n"

#define _DOC_GET_HW_FIRMWARE_INFO                                                                                      \
    MODULE_NAME ".get_hw_firmware_info(device)\n"                                                                      \
                "\n"                                                                                                   \
                "Returns the device firmware info for the device.\n"                                                   \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\t(:class:`" MODULE_NAME "."                                                                          \
                "st_api_firmware_info"                                                                                 \
                "`)\n"                                                                                                 \
                "\n"                                                                                                   \
                "\t>>> device = ics.open_device()\n"                                                                   \
                "\t>>> info = ics.get_hw_firmware_info(device)\n"                                                      \
                "\t>>> info.iAppMajor\n"                                                                               \
                "\t7\n"                                                                                                \
                "\t>>> info.iAppMinor\n"                                                                               \
                "\t55\n"                                                                                               \
                "\t>>>\n"

#define _DOC_GET_BACKUP_POWER_ENABLED                                                                                  \
    MODULE_NAME ".get_backup_power_enabled(device)\n"                                                                  \
                "\n"                                                                                                   \
                "Returns the device backup power enabled for the device.\n"                                            \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True on success, False on failure.\n"                                                      \
                "\n"

#define _DOC_SET_BACKUP_POWER_ENABLED                                                                                  \
    MODULE_NAME ".set_backup_power_enabled(device, enable)\n"                                                          \
                "\n"                                                                                                   \
                "Sets the device backup power enabled for the device.\n"                                               \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True on success, False on failure.\n"                                                      \
                "\n"

#define _DOC_GET_BACKUP_POWER_READY                                                                                    \
    MODULE_NAME ".get_backup_power_ready(device)\n"                                                                    \
                "\n"                                                                                                   \
                "Returns the device backup power is ready for the device.\n"                                           \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True on success, False on failure.\n"                                                      \
                "\n"

#define _DOC_LOAD_READBIN "Internal Use only\n"

// void* hObject, unsigned long ulNetworkID, stCM_ISO157652_TxMessage *pMsg, unsigned long ulBlockingTimeout
#define _DOC_ISO15765_TRANSMIT_MESSAGE                                                                                 \
    MODULE_NAME ".iso15765_transmit_message(device, ulNetworkID, pMsg, ulBlockingTimeout)\n"                           \
                "\n"                                                                                                   \
                "Transmits an ISO15765 Message.\n"                                                                     \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tpMsg (:class:`" MODULE_NAME "."                                                                     \
                "st_cm_iso157652_tx_message"                                                                           \
                "`): :class:`" MODULE_NAME "."                                                                         \
                "st_cm_iso157652_tx_message"                                                                           \
                "`\n\n"                                                                                                \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True on success, False on failure.\n"                                                      \
                "\n"

// (void* hObject, unsigned int iIndex, const stCM_ISO157652_RxMessage * pRxMessage)
#define _DOC_ISO15765_RECEIVE_MESSAGE                                                                                  \
    MODULE_NAME ".iso15765_receive_message(device, netid, rx_msg)\n"                                                   \
                "\n"                                                                                                   \
                "Setup rx ISO15765 Message.\n"                                                                         \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tprx_msg (:class:`" MODULE_NAME "."                                                                  \
                "st_cm_iso157652_rx_message"                                                                           \
                "`): :class:`" MODULE_NAME "."                                                                         \
                "st_cm_iso157652_rx_message"                                                                           \
                "`\n\n"                                                                                                \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True on success, False on failure.\n"                                                      \
                "\n"

#define _DOC_ISO15765_ENABLE_NETWORKS                                                                                  \
    MODULE_NAME ".iso15765_enable_networks(device, networks)\n"                                                        \
                "\n"                                                                                                   \
                "Enables ISO15765 networks.\n"                                                                         \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone\n"                                                                                             \
                "\n"

#define _DOC_ISO15765_DISABLE_NETWORKS                                                                                 \
    MODULE_NAME ".iso15765_disable_networks(device)\n"                                                                 \
                "\n"                                                                                                   \
                "Disables ISO15765 networks.\n"                                                                        \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone\n"                                                                                             \
                "\n"

#define _DOC_GET_ACTIVE_VNET_CHANNEL                                                                                   \
    MODULE_NAME ".get_active_vnet_channel(device)\n"                                                                   \
                "\n"                                                                                                   \
                "Gets active vnet channel for the device.\n"                                                           \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tInt: Returns active vnet channel.\n"                                                                \
                "\n"

#define _DOC_SET_ACTIVE_VNET_CHANNEL                                                                                   \
    MODULE_NAME ".set_active_vnet_channel(device, channel)\n"                                                          \
                "\n"                                                                                                   \
                "Sets active vnet channel for the device.\n"                                                           \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tBoolean: True on success, False on failure.\n"                                                      \
                "\n"

#define _DOC_OVERRIDE_LIBRARY_NAME                                                                                     \
    MODULE_NAME                                                                                                        \
    ".override_library_name(new_name)\n"                                                                               \
    "\n"                                                                                                               \
    "Overrides the default search for loading the icsneo40 library\n"                                                  \
    "\n"                                                                                                               \
    "Args:\n"                                                                                                          \
    "\tname: Absolute path or relative path including filename.\n\n"                                                   \
    "\n"                                                                                                               \
    "Raises:\n"                                                                                                        \
    "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                                        \
    "\n"                                                                                                               \
    "Returns:\n"                                                                                                       \
    "\tNone\n"                                                                                                         \
    "\n"                                                                                                               \
    "\t>>> import ics\n"                                                                                               \
    "\t>>> ics.find_devices()\n"                                                                                       \
    "\tTraceback (most recent call last):\n"                                                                           \
    "\t  File \"<stdin>\", line 1, in <module>\n"                                                                      \
    "\tics.RuntimeError: Error: find_devices(): Failed to open library: 'icsneo40.dll' with error code: #126\n"        \
    "\t>>> ics.override_library_name(r\"C:\\Windows\\SysWOW64\\icsneo40-different.dll\")\n"                            \
    "\t>>> ics.find_devices()\n"                                                                                       \
    "\t(<ics.NeoDevice object at 0x00284C50>, <ics.NeoDevice object at 0x007C9A10>)\n"

#define _DOC_SET_BIT_RATE                                                                                              \
    MODULE_NAME                                                                                                        \
    ".set_bit_rate(device, BitRate, NetworkID)\n"                                                                      \
    "\n"                                                                                                               \
    "Specifies bit rate setting. Valid values depend on the network specified.\n"                                      \
    "\n"                                                                                                               \
    "For the networks NETID_HSCAN, NETID_MSCAN, NETID_SWCAN, NETID_FIRE_HSCAN2, NETID_HSCAN3, NETID_LSFTCAN,\n"        \
    "valid bit rates are 2000, 33333, 50000, 62500, 83333, 100000, 125000, 250000, 500000, 800000, 1000000\n"          \
    "\n"                                                                                                               \
    "For the networks NETID_LIN, NETID_ISO2, NETID_FIRE_LIN2, NETID_FIRE_LIN3, NETID_FIRE_LIN4,\n"                     \
    "valid bit rates are\n"                                                                                            \
    "\n"                                                                                                               \
    "For the network NETID_FIRE_CGI valid bit rates are 625000 and 115200\n"                                           \
    "\n"                                                                                                               \
    "Args:\n"                                                                                                          \
    "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME  \
    "`\n\n"                                                                                                            \
    "\n"                                                                                                               \
    "Raises:\n"                                                                                                        \
    "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                                        \
    "\n"                                                                                                               \
    "Returns:\n"                                                                                                       \
    "\tInt: None.\n"                                                                                                   \
    "\n"

#define _DOC_SET_FD_BIT_RATE                                                                                           \
    MODULE_NAME ".set_fd_bit_rate(device, BitRate, NetworkID)\n"                                                       \
                "\n"                                                                                                   \
                "Sets the FD bitrate for a given Network ID on the device..\n"                                         \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tInt: None.\n"                                                                                       \
                "\n"

#define _DOC_SET_BIT_RATE_EX                                                                                           \
    MODULE_NAME ".set_bit_rate_ex(device, BitRate, NetworkID, iOptions)\n"                                             \
                "\n"                                                                                                   \
                "Sets the bitrate for a given Network ID on the device with extended options.\n"                       \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tInt: None.\n"                                                                                       \
                "\n"

#define _DOC_GET_TIMESTAMP_FOR_MSG                                                                                     \
    MODULE_NAME ".get_timestamp_for_msg(device, msg)\n"                                                                \
                "\n"                                                                                                   \
                "Calculates the timestamp for a message.\n"                                                            \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tmsg (:class:`" MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME "`): :class:`" MODULE_NAME                   \
                "." SPY_MESSAGE_OBJECT_NAME "`\n\n"                                                                    \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tFloat: Timestamp for the message.\n"                                                                \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> msgs, error_count = ics.get_messages(d)\n"                                                      \
                "\t>>> ics.get_timestamp_for_msg(d, msgs[0])\n"                                                        \
                "\t354577568.9145524\n"

#define _DOC_GET_DEVICE_STATUS                                                                                         \
    MODULE_NAME ".get_device_status(device)\n"                                                                         \
                "\n"                                                                                                   \
                "Returns the device status.\n"                                                                         \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\t(:class:`" MODULE_NAME "."                                                                          \
                "ics_device_status"                                                                                    \
                "`).\n"                                                                                                \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> status = ics.get_device_status(d)\n"                                                            \
                "\t>>> status.fire2Status.ethernetActivationLineEnabled\n"                                             \
                "\t0\n"

#define _DOC_ENABLE_NETWORK_COM                                                                                        \
    MODULE_NAME ".enable_network_com(device, enable, net_id)\n"                                                        \
                "\n"                                                                                                   \
                "Enable or disable network communication.\n"                                                           \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tenable (:class:`bool`): :class:`bool`\n\n"                                                          \
                "\n"                                                                                                   \
                "\tnet_id (:class:`int`): :class:`int`: Optional. If left blank, disables/enables all networks.\n\n"   \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> status = ics.enable_network_com(d, True)\n"                                                     \
                "\t>>> \n"

#define _DOC_ENABLE_BUS_VOLTAGE_MONITOR                                                                                \
    MODULE_NAME ".enable_bus_voltage_monitor(device, enable, reserved)\n"                                              \
                "\n"                                                                                                   \
                "Enable or disable bus voltage monitoring.\n"                                                          \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tenable (:class:`bool`): :class:`int`\n\n"                                                           \
                "\n"                                                                                                   \
                "\treserved (:class:`int`): :class:`int`: Optional. Should be set to zero. Don't set, if unsure.\n\n"  \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> status = ics.enable_bus_voltage_monitor(d, 1)\n"                                                \
                "\t>>> \n"

#define _DOC_GET_BUS_VOLTAGE                                                                                           \
    MODULE_NAME ".get_bus_voltage(device, reserved)\n"                                                                 \
                "\n"                                                                                                   \
                "Reads bus voltage. (:class:`" MODULE_NAME ".enable_bus_voltage_monitor`) needs to be called first.\n" \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\treserved (:class:`int`): :class:`int`: Optional. Should be set to zero. Don't set, if unsure.\n\n"  \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tInt: value returned is in mV.\n"                                                                    \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> status = ics.enable_bus_voltage_monitor(d, 1)\n"                                                \
                "\t>>> ics.get_bus_voltage(d)\n"                                                                       \
                "\t12000\n"                                                                                            \
                "\t>>> \n"

#define _DOC_READ_JUPITER_FIRMWARE                                                                                     \
    MODULE_NAME ".read_jupiter_firmware(device, size, [vnetChannel])\n"                                                \
                "\n"                                                                                                   \
                "Reads firmware binary from a RAD-Jupiter. If not sure, don't use this method\n"                       \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tsize (:class:`int`): :class:`int`: size of the bytes to read of the firmware binary.\n\n"           \
                "\n"                                                                                                   \
                "\tvnetChannel (:class:`int`): :class:`int`: Optional. Don't set, if unsure.\n\n"                      \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone\n"                                                                                             \
                "\n"

#define _DOC_WRITE_JUPITER_FIRMWARE                                                                                    \
    MODULE_NAME ".write_jupiter_firmware(device, bytes, [vnetChannel])\n"                                              \
                "\n"                                                                                                   \
                "Writes firmware binary to a RAD-Jupiter. If not sure, don't use this method\n"                        \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tbytes (:class:`bytes`): :class:`bytes`: bytes of the firmware binary.\n\n"                          \
                "\n"                                                                                                   \
                "\tvnetChannel (:class:`int`): :class:`int`: Optional. Don't set, if unsure.\n\n"                      \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone\n"                                                                                             \
                "\n"

#define _DOC_GET_DISK_DETAILS                                                                                          \
    MODULE_NAME ".get_disk_details(device)\n"                                                                          \
                "\n"                                                                                                   \
                "Returns the device disk details.\n"                                                                   \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\t(:class:`" MODULE_NAME "."                                                                          \
                "srad_gigalog_disk_details"                                                                            \
                "`).\n"                                                                                                \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> details = ics.get_disk_details(d)\n"                                                            \
                "\t>>> details.structure.options\n"                                                                    \
                "\t>>> \n"

#define _DOC_DISK_FORMAT                                                                                               \
    MODULE_NAME ".disk_format(device)\n"                                                                               \
                "\n"                                                                                                   \
                "Starts disk formatting on the device.\n"                                                              \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> details = ics.get_disk_details(d)\n"                                                            \
                "\t>>> details. = ics.get_disk_details(d)\n"                                                           \
                "\t>>> ics.disk_format(d, details)\n"                                                                  \
                "\t>>> \n"

#define _DOC_DISK_FORMAT_CANCEL                                                                                        \
    MODULE_NAME ".disk_format_cancel(device)\n"                                                                        \
                "\n"                                                                                                   \
                "Cancel in progress disk formatting on the device.\n"                                                  \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> ics.disk_format(d, details)\n"                                                                  \
                "\t>>> ics.disk_format_cancel(d)\n"                                                                    \
                "\t>>> \n"

#define _DOC_DISK_FORMAT_PROGRESS                                                                                      \
    MODULE_NAME ".get_disk_format_progress(device)\n"                                                                  \
                "\n"                                                                                                   \
                "Returns the device disk formatting progress.\n"                                                       \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\t(:class:`" MODULE_NAME "."                                                                          \
                "srad_gigalog_disk_format_progress"                                                                    \
                "`).\n"                                                                                                \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> d = ics.disk_format(d, details)\n"                                                              \
                "\t>>> progress = ics.get_disk_format_progress(d)\n"                                                   \
                "\t>>> progress.sectorsRemaining\n"                                                                    \
                "\t>>> \n"

#define _DOC_ENABLE_DOIP_LINE                                                                                          \
    MODULE_NAME ".enable_doip_line(device, enable)\n"                                                                  \
                "\n"                                                                                                   \
                "Activate or De-activate DOIP Line.\n"                                                                 \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tenable (:class:`bool`): :class:`bool`\n\n"                                                          \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> status = ics.enable_doip_line(d, True)\n"                                                       \
                "\t>>> \n"

#define _DOC_IS_DEVICE_FEATURE_SUPPORTED                                                                               \
    MODULE_NAME ".is_device_feature_supported(device, feature)\n"                                                      \
                "\n"                                                                                                   \
                "Polls firmware in device to see if the feature is supported. As of 908 only ValueCAN4-2EL, "          \
                "ValueCAN4-4 and ValueCAN4-Industrial are supported.\n"                                                \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tenable (:class:`DeviceFeature`): :class:`DeviceFeature`\n\n"                                        \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> from ics.structures.device_feature import DeviceFeature\n"                                      \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> supported = ics.is_device_feature_supported(d, DeviceFeature.networkTerminationDWCAN01)\n"      \
                "\t>>> \n"

#define _DOC_GET_PCB_SERIAL_NUMBER                                                                                     \
    MODULE_NAME ".get_pcb_serial_number(device)\n"                                                                     \
                "\n"                                                                                                   \
                "Gets the unique PCB serial number of the device.\n"                                                   \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\t(:class:`str`): PCB Serial Number\n"                                                                \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> pcb_sn = ics.get_pcb_serial_number(d)\n"                                                        \
                "\t>>> \n"

#define _DOC_SET_LED_PROPERTY                                                                                          \
    MODULE_NAME ".set_led_property(device, led, prop, value)\n"                                                        \
                "\n"                                                                                                   \
                "Sets the LED property on the device.\n"                                                               \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tled (:class:`int`): Index or position of the LED\n\n"                                               \
                "\tprop (:class:`int`): Property of the LED\n\n"                                                       \
                "\tvalue (:class:`int`): Value of the LED Property\n\n"                                                \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> ics.set_led_property(d, TODO, TODO, TODO)\n"                                                    \
                "\t>>> \n"

#define _DOC_START_DHCP_SERVER                                                                                         \
    MODULE_NAME ".start_dhcp_server(device, network_id, device_ip_address, subnet_mask, gateway, start_address, "      \
                "end_address, overwrite_dhcp_settings, lease_time, reserved)\n"                                        \
                "\n"                                                                                                   \
                "Starts a DHCP Server.\n"                                                                              \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tnetwork_id (:class:`int`): NetworkID\n\n"                                                           \
                "\tdevice_ip_address (:class:`str`): Device IP Address\n\n"                                            \
                "\tsubnet_mask (:class:`str`): Subnet Mask\n\n"                                                        \
                "\tgateway (:class:`str`): Gateway\n\n"                                                                \
                "\tstart_address (:class:`str`): Start Address\n\n"                                                    \
                "\tend_address (:class:`str`): End Address\n\n"                                                        \
                "\toverwrite_dhcp_settings (:class:`bool`): Overwrite DHCP Settings\n\n"                               \
                "\tlease_time (:class:`int`): Lease time\n\n"                                                          \
                "\treserved (:class:`int`): (Optional) Reserved, set to 0\n\n"                                         \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> ics.start_dhcp_server(d, TODO)\n"                                                               \
                "\t>>> \n"

#define _DOC_STOP_DHCP_SERVER                                                                                          \
    MODULE_NAME ".stop_dhcp_server(device, network_id)\n"                                                              \
                "\n"                                                                                                   \
                "Stops the DHCP Server\n"                                                                              \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tnetwork_id (:class:`int`): NetworkID\n\n"                                                           \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> ics.stop_dhcp_server(d, TODO)\n"                                                                \
                "\t>>> \n"

#define _DOC_WBMS_MANAGER_WRITE_LOCK                                                                                   \
    MODULE_NAME ".wbms_manager_write_lock(device, manager, lock_state)\n"                                              \
                "\n"                                                                                                   \
                "Sets the lock state on the manager\n"                                                                 \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tmanager (:class:`" MODULE_NAME                                                                      \
                ".structures.ew_bms_manager_port_t.ew_bms_manager_port_t`): :class:`" MODULE_NAME                      \
                ".structures.ew_bms_manager_port_t.ew_bms_manager_port_t`\n\n"                                         \
                "\tlock_state (:class:`" MODULE_NAME                                                                   \
                ".structures.ew_bms_manager_lock_state_t.ew_bms_manager_lock_state_t`): :class:`" MODULE_NAME          \
                ".structures.ew_bms_manager_lock_state_t.ew_bms_manager_lock_state_t`\n\n"                             \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> from ics.structures.ew_bms_manager_port_t import ew_bms_manager_port_t\n"                       \
                "\t>>> from ics.structures.ew_bms_manager_lock_state_t import ew_bms_manager_lock_state_t\n"           \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> ics.wbms_manager_write_lock(d, ew_bms_manager_port_t.eManagerPortA.value, "                     \
                "ew_bms_manager_lock_state_t.eLockManager.value)\n"                                                    \
                "\t>>> \n"

#define _DOC_WBMS_MANAGER_RESET                                                                                        \
    MODULE_NAME ".wbms_manager_reset(device, manager)\n"                                                               \
                "\n"                                                                                                   \
                "Resets the manager\n"                                                                                 \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tmanager (:class:`" MODULE_NAME                                                                      \
                ".structures.ew_bms_manager_port_t.ew_bms_manager_port_t`): :class:`" MODULE_NAME                      \
                ".structures.ew_bms_manager_port_t.ew_bms_manager_port_t`\n\n"                                         \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> from ics.structures.ew_bms_manager_port_t import ew_bms_manager_port_t\n"                       \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> ics.wbms_manager_reset(d, ew_bms_manager_port_t.eManagerPortA.value)\n"                         \
                "\t>>> \n"

#define _DOC_UART_WRITE                                                                                                \
    MODULE_NAME ".uart_write(device, port, data, flags)\n"                                                             \
                "\n"                                                                                                   \
                "Writes UART on the given port\n"                                                                      \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tport (:class:`" MODULE_NAME ".structures.e_uart_port_t.e_uart_port_t`): :class:`" MODULE_NAME       \
                ".structures.e_uart_port_t.e_uart_port_t`\n\n"                                                         \
                "\tdata (:class:`bytes`): :class:`bytes`\n\n"                                                          \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> from ics.structures.e_uart_port_t import e_uart_port_t\n"                                       \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> ics.uart_write(d, e_uart_port_t.eUART0, b'my uart data goes here')\n"                           \
                "\t>>> \n"

#define _DOC_UART_READ                                                                                                 \
    MODULE_NAME ".uart_read(device, port, bytes_to_read, flags)\n"                                                     \
                "\n"                                                                                                   \
                "Reads UART on the given port. \n"                                                                     \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tport (:class:`" MODULE_NAME ".structures.e_uart_port_t.e_uart_port_t`): :class:`" MODULE_NAME       \
                ".structures.e_uart_port_t.e_uart_port_t`\n\n"                                                         \
                "\tbytes_to_read (:class:`int`): Optional. How many bytes to read from the UART, 256 if omitted.\n\n"  \
                "\tflags (:class:`int`): Optional. Flags to be used. Don't use if unsure.\n\n"                         \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> from ics.structures.e_uart_port_t import e_uart_port_t\n"                                       \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> data = ics.uart_read(d, e_uart_port_t.eUART0)\n"                                                \
                "\t>>> print(f\"Read {len(data)} bytes: {data}\")\n"                                                   \
                "\t>>> \n"

#define _DOC_UART_SET_BAUDRATE                                                                                         \
    MODULE_NAME ".uart_set_baudrate(device, port, baudrate)\n"                                                         \
                "\n"                                                                                                   \
                "Sets the UART baudrate on the given port. \n"                                                         \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tport (:class:`" MODULE_NAME ".structures.e_uart_port_t.e_uart_port_t`): :class:`" MODULE_NAME       \
                ".structures.e_uart_port_t.e_uart_port_t`\n\n"                                                         \
                "\tbaudrate (:class:`int`): Baudrate of the UART to set.\n\n"                                          \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> from ics.structures.e_uart_port_t import e_uart_port_t\n"                                       \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> ics.uart_set_baudrate(d, e_uart_port_t.eUART0, 115200)\n"                                       \
                "\t>>> print(f\"Read {len(data)} bytes: {data}\")\n"                                                   \
                "\t>>> \n"

#define _DOC_UART_GET_BAUDRATE                                                                                         \
    MODULE_NAME ".uart_get_baudrate(device, port)\n"                                                                   \
                "\n"                                                                                                   \
                "Gets the UART baudrate on the given port. \n"                                                         \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tport (:class:`" MODULE_NAME ".structures.e_uart_port_t.e_uart_port_t`): :class:`" MODULE_NAME       \
                ".structures.e_uart_port_t.e_uart_port_t`\n\n"                                                         \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone.\n"                                                                                            \
                "\n"                                                                                                   \
                "\t>>> import ics\n"                                                                                   \
                "\t>>> from ics.structures.e_uart_port_t import e_uart_port_t\n"                                       \
                "\t>>> d = ics.open_device()\n"                                                                        \
                "\t>>> baudrate = ics.uart_set_baudrate(d, e_uart_port_t.eUART0)\n"                                    \
                "\t>>> \n"

#define _DOC_GENERIC_API_SEND_COMMAND                                                                                  \
    MODULE_NAME ".generic_api_send_command(device, api_index, instance_index, function_index, data)\n"                 \
                "\n"                                                                                                   \
                "Sends a command in a generic way.\n"                                                                  \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tapi_index (:class:`int`): api_index.\n\n"                                                           \
                "\tinstance_index (:class:`int`): instance_index.\n\n"                                                 \
                "\tfunction_index (:class:`int`): function_index.\n\n"                                                 \
                "\tdata (:class:`bytes`): Data to be passed in.\n\n"                                                   \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tfunctionError (:class:`int`): functionError.\n\n"                                                   \
                "\n"

// if (!PyArg_ParseTuple(args, arg_parse("ObbI:", __FUNCTION__), &obj, &apiIndex, &instanceIndex, &length)) {
#define _DOC_GENERIC_API_READ_DATA                                                                                     \
    MODULE_NAME                                                                                                        \
    ".generic_api_read_data(device, api_index, instance_index, [length])\n"                                            \
    "\n"                                                                                                               \
    "Reads data in a generic way.\n"                                                                                   \
    "\n"                                                                                                               \
    "Args:\n"                                                                                                          \
    "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME  \
    "`\n\n"                                                                                                            \
    "\tapi_index (:class:`int`): api_index.\n\n"                                                                       \
    "\tinstance_index (:class:`int`): instance_index.\n\n"                                                             \
    "\tfunction_index (:class:`int`): function_index.\n\n"                                                             \
    "\tlength (:class:`int`): (optional) Length of the data to read. defaults to `GENERIC_API_DATA_BUFFER_SIZE`\n\n"   \
    "\n"                                                                                                               \
    "Raises:\n"                                                                                                        \
    "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                                        \
    "\n"                                                                                                               \
    "Returns:\n"                                                                                                       \
    "\ttuple of (functionIndex, data) \n\n"                                                                            \
    "\n"

// if (!PyArg_ParseTuple(args, arg_parse("Obb:", __FUNCTION__), &obj, &apiIndex, &instanceIndex)) {
#define _DOC_GENERIC_API_GET_STATUS                                                                                    \
    MODULE_NAME ".generic_api_get_status(device, api_index, instance_index)\n"                                         \
                "\n"                                                                                                   \
                "Reads data in a generic way.\n"                                                                       \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\tapi_index (:class:`int`): api_index.\n\n"                                                           \
                "\tinstance_index (:class:`int`): instance_index.\n\n"                                                 \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\ttuple of (:class:`int`): (functionIndex, callbackError, finishedProcessing) \n\n"                   \
                "\n"

#define _DOC_GET_GPTP_STATUS                                                                                           \
    MODULE_NAME ".get_gptp_status(device)\n"                                                                           \
                "\n"                                                                                                   \
                "Gets the gPTP Status from the device.\n"                                                              \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tics.structures.gptp_status.gptp_status (:class:`ics.structures.gptp_status.gptp_status`)\n\n"       \
                "\n"

#define _DOC_GET_ALL_CHIP_VERSIONS                                                                                     \
    MODULE_NAME ".get_all_chip_versions(device, api_index, instance_index)\n"                                          \
                "\n"                                                                                                   \
                "Get all the chip (firmware) versions of the device.\n"                                                \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tics.structures.st_chip_versions.st_chip_versions "                                                  \
                "(:class:`ics.structures.st_chip_versions.st_chip_versions`)\n\n"                                      \
                "\n"

#define _DOC_FLASH_ACCESSORY_FIRMWARE                                                                                        \
    MODULE_NAME ".flash_accessory_firmware(device, data, index[, check_success])\n"                                      \
                "\n"                                                                                                   \
                "Flashes Accessory Firmware. If not sure, don't use this method\n"                                           \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tdata (:class:`bytes`): :class:`bytes`: data of the firmware binary.\n\n"                            \
                "\n"                                                                                                   \
                "\tindex (:class:`int`): :class:`int`: Index enum.\n\n"                                        \
                "\n"                                                                                                   \
                "\tcheck_success (:class:`bool`): :class:`bool`: Optional, raises an exception if not successful \n\n" \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone\n"                                                                                             \
                "\n"

#define _DOC_GET_ACCESSORY_FIRMWARE_VERSION                                                                                  \
    MODULE_NAME ".get_Accessory_firmware_version(device, index[, check_success])\n"                                      \
                "\n"                                                                                                   \
                "Gets Accessory Firmware version. If not sure, don't use this method\n"                                      \
                "\n"                                                                                                   \
                "Args:\n"                                                                                              \
                "\tdevice (:class:`" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME "`): :class:`" MODULE_NAME                 \
                "." NEO_DEVICE_OBJECT_NAME "`\n\n"                                                                     \
                "\n"                                                                                                   \
                "\tindex (:class:`int`): :class:`int`: Index enum.\n\n"                                        \
                "\n"                                                                                                   \
                "\tcheck_success (:class:`bool`): :class:`bool`: Optional, raises an exception if not successful \n\n" \
                "\n"                                                                                                   \
                "Raises:\n"                                                                                            \
                "\t:class:`" MODULE_NAME ".RuntimeError`\n"                                                            \
                "\n"                                                                                                   \
                "Returns:\n"                                                                                           \
                "\tNone\n"                                                                                             \
                "\n"

static PyMethodDef IcsMethods[] = {
    _EZ_ICS_STRUCT_METHOD("find_devices",
                          "icsneoFindNeoDevices",
                          "FindNeoDevices",
                          (PyCFunction)meth_find_devices,
                          METH_VARARGS | METH_KEYWORDS,
                          _DOC_FIND_DEVICES),
    _EZ_ICS_STRUCT_METHOD("open_device",
                          "icsneoOpenNeoDevice",
                          "OpenNeoDevice",
                          (PyCFunction)meth_open_device,
                          METH_VARARGS | METH_KEYWORDS,
                          _DOC_OPEN_DEVICES),
    _EZ_ICS_STRUCT_METHOD("close_device",
                          "icsneoClosePort",
                          "ClosePort",
                          meth_close_device,
                          METH_VARARGS,
                          _DOC_CLOSE_DEVICES),
    _EZ_ICS_STRUCT_METHOD("get_rtc", "icsneoGetRTC", "GetRTC", meth_get_rtc, METH_VARARGS, _DOC_GET_RTC),
    _EZ_ICS_STRUCT_METHOD("set_rtc", "icsneoSetRTC", "SetRTC", meth_set_rtc, METH_VARARGS, _DOC_SET_RTC),
    _EZ_ICS_STRUCT_METHOD("coremini_load",
                          "icsneoScriptLoad",
                          "ScriptLoad",
                          meth_coremini_load,
                          METH_VARARGS,
                          _DOC_COREMINI_LOAD),
    _EZ_ICS_STRUCT_METHOD("coremini_start",
                          "icsneoScriptStart",
                          "ScriptStart",
                          meth_coremini_start,
                          METH_VARARGS,
                          _DOC_COREMINI_START),
    _EZ_ICS_STRUCT_METHOD("coremini_stop",
                          "icsneoScriptStop",
                          "ScriptStop",
                          meth_coremini_stop,
                          METH_VARARGS,
                          _DOC_COREMINI_STOP),
    _EZ_ICS_STRUCT_METHOD("coremini_clear",
                          "icsneoScriptClear",
                          "ScriptClear",
                          meth_coremini_clear,
                          METH_VARARGS,
                          _DOC_COREMINI_CLEAR),
    _EZ_ICS_STRUCT_METHOD("coremini_get_status",
                          "icsneoScriptGetScriptStatus",
                          "ScriptGetScriptStatus",
                          meth_coremini_get_status,
                          METH_VARARGS,
                          _DOC_COREMINI_GET_STATUS),
    _EZ_ICS_STRUCT_METHOD("transmit_messages",
                          "icsneoTxMessages",
                          "TxMessages",
                          meth_transmit_messages,
                          METH_VARARGS,
                          _DOC_TRANSMIT_MESSAGES),
    _EZ_ICS_STRUCT_METHOD("get_messages",
                          "icsneoGetMessages",
                          "GetMessages",
                          meth_get_messages,
                          METH_VARARGS,
                          _DOC_GET_MESSAGES),
    _EZ_ICS_STRUCT_METHOD("get_script_status",
                          "icsneoScriptGetScriptStatusEx",
                          "ScriptGetScriptStatusEx",
                          meth_get_script_status,
                          METH_VARARGS,
                          "Accepts a " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME
                          ", exception on error. Returns a list of values of what ulParameters would hold"),
    _EZ_ICS_STRUCT_METHOD("get_error_messages",
                          "icsneoGetErrorMessages",
                          "GetErrorMessages",
                          meth_get_error_messages,
                          METH_VARARGS,
                          _DOC_GET_ERROR_MESSAGES),
#ifdef _USE_INTERNAL_HEADER_
    _EZ_ICS_STRUCT_METHOD("flash_devices",
                          "FlashDevice2",
                          "FlashDevice2",
                          meth_flash_devices,
                          METH_VARARGS,
                          "int _stdcall FlashDevice2()"),
#endif
    _EZ_ICS_STRUCT_METHOD("set_reflash_callback",
                          "icsneoSetReflashDisplayCallbacks",
                          "SetReflashDisplayCallback",
                          meth_set_reflash_callback,
                          METH_VARARGS,
                          _DOC_SET_REFLASH_CALLBACK),
    _EZ_ICS_STRUCT_METHOD("get_device_settings",
                          "icsneoGetDeviceSettings",
                          "GetDeviceSettings",
                          meth_get_device_settings,
                          METH_VARARGS,
                          _DOC_GET_DEVICE_SETTINGS),
    _EZ_ICS_STRUCT_METHOD("set_device_settings",
                          "icsneoSetDeviceSettings",
                          "SetDeviceSettings",
                          meth_set_device_settings,
                          METH_VARARGS,
                          _DOC_SET_DEVICE_SETTINGS),
    _EZ_ICS_STRUCT_METHOD("load_default_settings",
                          "icsneoLoadDefaultSettings",
                          "LoadDefaultSettings",
                          meth_load_default_settings,
                          METH_VARARGS,
                          _DOC_LOAD_DEFAULT_SETTINGS),
    //_EZ_ICS_STRUCT_METHOD("spy_message_to_j1850", METH_spy_message_to_j1850, METH_VARARGS, "Accepts a "
    // MODULE_NAME
    //"."
    // SPY_MESSAGE_OBJECT_NAME ", and returns a " MODULE_NAME "." SPY_MESSAGE_J1850_OBJECT_NAME ". Exception on
    // error."),
    _EZ_ICS_STRUCT_METHOD("read_sdcard",
                          "icsneoReadSDCard",
                          "ReadSDCard",
                          meth_read_sdcard,
                          METH_VARARGS,
                          "icsneoReadSDCard(), Accepts a " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME
                          " and sector index. Returns a bytearray of 512 bytes max. Exception on error."),
    _EZ_ICS_STRUCT_METHOD("write_sdcard",
                          "icsneoWriteSDCard",
                          "WriteSDCard",
                          meth_write_sdcard,
                          METH_VARARGS,
                          "icsneoReadSDCard(), Accepts a " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME
                          ", sector index, and a bytearray of 512 bytes. Exception on error."),
    { "create_neovi_radio_message",
      (PyCFunction)meth_create_neovi_radio_message,
      METH_VARARGS | METH_KEYWORDS,
      _DOC_CREATE_NEOVI_RADIO_MESSAGE },
    _EZ_ICS_STRUCT_METHOD("coremini_start_fblock",
                          "icsneoScriptStartFBlock",
                          "ScriptStartFBlock",
                          meth_coremini_start_fblock,
                          METH_VARARGS,
                          _DOC_COREMINI_START_FBLOCK),
    _EZ_ICS_STRUCT_METHOD("coremini_stop_fblock",
                          "icsneoScriptStopFBlock",
                          "ScriptStopFBlock",
                          meth_coremini_stop_fblock,
                          METH_VARARGS,
                          _DOC_COREMINI_STOP_FBLOCK),
    _EZ_ICS_STRUCT_METHOD("coremini_get_fblock_status",
                          "icsneoScriptGetFBlockStatus",
                          "ScriptGetFBlockStatus",
                          meth_coremini_get_fblock_status,
                          METH_VARARGS,
                          _DOC_COREMINI_GET_FBLOCK_STATUS),
    _EZ_ICS_STRUCT_METHOD("coremini_read_app_signal",
                          "icsneoScriptReadAppSignal",
                          "ScriptReadAppSignal",
                          meth_coremini_read_app_signal,
                          METH_VARARGS,
                          _DOC_COREMINI_READ_APP_SIGNAL),
    _EZ_ICS_STRUCT_METHOD("coremini_write_app_signal",
                          "icsneoScriptWriteAppSignal",
                          "ScriptWriteAppSignal",
                          meth_coremini_write_app_signal,
                          METH_VARARGS,
                          _DOC_COREMINI_WRITE_APP_SIGNAL),
    _EZ_ICS_STRUCT_METHOD("coremini_read_tx_message",
                          "icsneoScriptReadTxMessage",
                          "ScriptReadTxMessage",
                          meth_coremini_read_tx_message,
                          METH_VARARGS,
                          _DOC_COREMINI_READ_TX_MESSAGE),
    _EZ_ICS_STRUCT_METHOD("coremini_read_rx_message",
                          "icsneoScriptReadRxMessage",
                          "ScriptReadRxMessage",
                          meth_coremini_read_rx_message,
                          METH_VARARGS,
                          _DOC_COREMINI_READ_RX_MESSAGE),
    _EZ_ICS_STRUCT_METHOD("coremini_write_tx_message",
                          "icsneoScriptWriteTxMessage",
                          "ScriptWriteTxMessage",
                          meth_coremini_write_tx_message,
                          METH_VARARGS,
                          _DOC_COREMINI_WRITE_TX_MESSAGE),
    _EZ_ICS_STRUCT_METHOD("coremini_write_rx_message",
                          "icsneoScriptWriteRxMessage",
                          "ScriptWriteRxMessage",
                          meth_coremini_write_rx_message,
                          METH_VARARGS,
                          _DOC_COREMINI_WRITE_RX_MESSAGE),
    _EZ_ICS_STRUCT_METHOD("get_performance_parameters",
                          "icsneoGetPerformanceParameters",
                          "GetPerformanceParameters",
                          meth_get_performance_parameters,
                          METH_VARARGS,
                          _DOC_GET_PERFORMANCE_PARAMETERS),
    _EZ_ICS_STRUCT_METHOD("validate_hobject",
                          "icsneoValidateHObject",
                          "ValidateHObject",
                          meth_validate_hobject,
                          METH_VARARGS,
                          _DOC_VALIDATE_HOBJECT),
    _EZ_ICS_STRUCT_METHOD("get_last_api_error",
                          "icsneoGetLastAPIError",
                          "GetLastAPIError",
                          meth_get_last_api_error,
                          METH_VARARGS,
                          _DOC_GET_LAST_API_ERROR),
    _EZ_ICS_STRUCT_METHOD("get_dll_version",
                          "icsneoGetDLLVersion",
                          "GetDLLVersion",
                          meth_get_dll_version,
                          METH_NOARGS,
                          _DOC_GET_DLL_VERSION),
    _EZ_ICS_STRUCT_METHOD("get_serial_number",
                          "icsneoGetSerialNumber",
                          "GetSerialNumber",
                          meth_get_serial_number,
                          METH_VARARGS,
                          _DOC_GET_SERIAL_NUMBER),
    _EZ_ICS_STRUCT_METHOD("get_hw_firmware_info",
                          "icsneoGetHWFirmwareInfo",
                          "GetHWFirmwareInfo",
                          meth_get_hw_firmware_info,
                          METH_VARARGS,
                          _DOC_GET_HW_FIRMWARE_INFO),
    _EZ_ICS_STRUCT_METHOD("request_enter_sleep_mode",
                          "icsneoRequestEnterSleepMode",
                          "RequestEnterSleepMode",
                          meth_request_enter_sleep_mode,
                          METH_VARARGS,
                          _DOC_REQUEST_ENTER_SLEEP_MODE),
    { "base36enc", (PyCFunction)meth_base36enc, METH_VARARGS | METH_KEYWORDS, _DOC_BASE36ENC },
    _EZ_ICS_STRUCT_METHOD("set_context",
                          "icsneoSetContext",
                          "SetContext",
                          meth_set_context,
                          METH_VARARGS,
                          _DOC_SET_CONTEXT),
    _EZ_ICS_STRUCT_METHOD("force_firmware_update",
                          "icsneoForceFirmwareUpdate",
                          "ForceFirmwareUpdate",
                          meth_force_firmware_update,
                          METH_VARARGS,
                          _DOC_FORCE_FIRMWARE_UPDATE),
    _EZ_ICS_STRUCT_METHOD("firmware_update_required",
                          "icsneoFirmwareUpdateRequired",
                          "FirmwareUpdateRequired",
                          meth_firmware_update_required,
                          METH_VARARGS,
                          _DOC_FIRMWARE_UPDATE_REQUIRED),
    _EZ_ICS_STRUCT_METHOD("get_dll_firmware_info",
                          "icsneoGetDLLFirmwareInfo",
                          "GetDLLFirmwareInfo",
                          meth_get_dll_firmware_info,
                          METH_VARARGS,
                          _DOC_GET_DLL_FIRMWARE_INFO),
    _EZ_ICS_STRUCT_METHOD("get_backup_power_enabled",
                          "icsneoGetBackupPowerEnabled",
                          "GetBackupPowerEnabled",
                          meth_get_backup_power_enabled,
                          METH_VARARGS,
                          _DOC_GET_BACKUP_POWER_ENABLED),
    _EZ_ICS_STRUCT_METHOD("set_backup_power_enabled",
                          "icsneoSetBackupPowerEnabled",
                          "SetBackupPowerEnabled",
                          meth_set_backup_power_enabled,
                          METH_VARARGS,
                          _DOC_SET_BACKUP_POWER_ENABLED),
    _EZ_ICS_STRUCT_METHOD("get_backup_power_ready",
                          "icsneoGetBackupPowerReady",
                          "GetBackupPowerReady",
                          meth_get_backup_power_ready,
                          METH_VARARGS,
                          _DOC_GET_BACKUP_POWER_READY),
#ifdef _USE_INTERNAL_HEADER_
    _EZ_ICS_STRUCT_METHOD("load_readbin",
                          "icsneoScriptLoadReadBin",
                          "ScriptLoadReadBin",
                          meth_load_readbin,
                          METH_VARARGS,
                          _DOC_LOAD_READBIN),
#endif
    _EZ_ICS_STRUCT_METHOD("iso15765_transmit_message",
                          "icsneoISO15765_TransmitMessage",
                          "ISO15765_TransmitMessage",
                          meth_iso15765_transmit_message,
                          METH_VARARGS,
                          _DOC_ISO15765_TRANSMIT_MESSAGE),
    _EZ_ICS_STRUCT_METHOD("iso15765_receive_message",
                          "icsneoISO15765_ReceiveMessage",
                          "ISO15765_ReceiveMessage",
                          meth_iso15765_receive_message,
                          METH_VARARGS,
                          _DOC_ISO15765_RECEIVE_MESSAGE),
    _EZ_ICS_STRUCT_METHOD("iso15765_enable_networks",
                          "icsneoISO15765_EnableNetworks",
                          "ISO15765_EnableNetworks",
                          meth_iso15765_enable_networks,
                          METH_VARARGS,
                          _DOC_ISO15765_ENABLE_NETWORKS),
    _EZ_ICS_STRUCT_METHOD("iso15765_disable_networks",
                          "icsneoISO15765_DisableNetworks",
                          "ISO15765_DisableNetworks",
                          meth_iso15765_disable_networks,
                          METH_VARARGS,
                          _DOC_ISO15765_DISABLE_NETWORKS),

    _EZ_ICS_STRUCT_METHOD("get_active_vnet_channel",
                          "icsneoGetActiveVNETChannel",
                          "GetActiveVNETChannel",
                          meth_get_active_vnet_channel,
                          METH_VARARGS,
                          _DOC_GET_ACTIVE_VNET_CHANNEL),
    _EZ_ICS_STRUCT_METHOD("set_active_vnet_channel",
                          "icsneoSetActiveVNETChannel",
                          "SetActiveVNETChannel",
                          meth_set_active_vnet_channel,
                          METH_VARARGS,
                          _DOC_SET_ACTIVE_VNET_CHANNEL),
    _EZ_ICS_STRUCT_METHOD("set_bit_rate",
                          "icsneoSetBitRate",
                          "SetBitRate",
                          meth_set_bit_rate,
                          METH_VARARGS,
                          _DOC_SET_BIT_RATE),
    _EZ_ICS_STRUCT_METHOD("set_fd_bit_rate",
                          "icsneoSetFDBitRate",
                          "SetFDBitRate",
                          meth_set_fd_bit_rate,
                          METH_VARARGS,
                          _DOC_SET_FD_BIT_RATE),
    _EZ_ICS_STRUCT_METHOD("set_bit_rate_ex",
                          "icsneoSetBitRateEx",
                          "SetBitRateEx",
                          meth_set_bit_rate_ex,
                          METH_VARARGS,
                          _DOC_SET_BIT_RATE_EX),
    _EZ_ICS_STRUCT_METHOD("get_timestamp_for_msg",
                          "icsneoGetTimeStampForMsg",
                          "GetTimeStampForMsg",
                          meth_get_timestamp_for_msg,
                          METH_VARARGS,
                          _DOC_GET_TIMESTAMP_FOR_MSG),
    _EZ_ICS_STRUCT_METHOD("get_device_status",
                          "icsneoGetDeviceStatus",
                          "GetDeviceStatus",
                          meth_get_device_status,
                          METH_VARARGS,
                          _DOC_GET_DEVICE_STATUS),

    _EZ_ICS_STRUCT_METHOD("enable_network_com",
                          "icsneoEnableNetworkCom",
                          "EnableNetworkCom",
                          meth_enable_network_com,
                          METH_VARARGS,
                          _DOC_ENABLE_NETWORK_COM),

    _EZ_ICS_STRUCT_METHOD("enable_bus_voltage_monitor",
                          "icsneoEnableBusVoltageMonitor",
                          "EnableBusVoltageMonitor",
                          meth_enable_bus_voltage_monitor,
                          METH_VARARGS,
                          _DOC_ENABLE_BUS_VOLTAGE_MONITOR),
    _EZ_ICS_STRUCT_METHOD("get_bus_voltage",
                          "icsneoGetBusVoltage",
                          "GetBusVoltage",
                          meth_get_bus_voltage,
                          METH_VARARGS,
                          _DOC_GET_BUS_VOLTAGE),

    _EZ_ICS_STRUCT_METHOD("read_jupiter_firmware",
                          "icsneoReadJupiterFirmware",
                          "ReadJupiterFirmware",
                          meth_read_jupiter_firmware,
                          METH_VARARGS,
                          _DOC_READ_JUPITER_FIRMWARE),
    _EZ_ICS_STRUCT_METHOD("write_jupiter_firmware",
                          "icsneoWriteJupiterFirmware",
                          "WriteJupiterFirmware",
                          meth_write_jupiter_firmware,
                          METH_VARARGS,
                          _DOC_WRITE_JUPITER_FIRMWARE),

    _EZ_ICS_STRUCT_METHOD("get_disk_details",
                          "icsneoRequestDiskDetails",
                          "RequestDiskDetails",
                          meth_get_disk_details,
                          METH_VARARGS,
                          _DOC_GET_DISK_DETAILS),
    _EZ_ICS_STRUCT_METHOD("disk_format",
                          "icsneoRequestDiskFormat",
                          "RequestDiskFormat",
                          meth_disk_format,
                          METH_VARARGS,
                          _DOC_DISK_FORMAT),
    _EZ_ICS_STRUCT_METHOD("disk_format_cancel",
                          "icsneoRequestDiskFormatCancel",
                          "RequestDiskFormatCancel",
                          meth_disk_format_cancel,
                          METH_VARARGS,
                          _DOC_DISK_FORMAT_CANCEL),
    _EZ_ICS_STRUCT_METHOD("get_disk_format_progress",
                          "icsneoRequestDiskFormatProgress",
                          "RequestDiskFormatProgress",
                          meth_get_disk_format_progress,
                          METH_VARARGS,
                          _DOC_DISK_FORMAT_PROGRESS),
    _EZ_ICS_STRUCT_METHOD("enable_doip_line",
                          "icsneoEnableDOIPLine",
                          "EnableDOIPLine",
                          meth_enable_doip_line,
                          METH_VARARGS,
                          _DOC_ENABLE_DOIP_LINE),
    _EZ_ICS_STRUCT_METHOD("is_device_feature_supported",
                          "icsneoIsDeviceFeatureSupported",
                          "IsDeviceFeatureSupported",
                          meth_is_device_feature_supported,
                          METH_VARARGS,
                          _DOC_IS_DEVICE_FEATURE_SUPPORTED),
    _EZ_ICS_STRUCT_METHOD("get_pcb_serial_number",
                          "icsneoGetPCBSerialNumber",
                          "GetPCBSerialNumber",
                          meth_get_pcb_serial_number,
                          METH_VARARGS,
                          _DOC_GET_PCB_SERIAL_NUMBER),
    _EZ_ICS_STRUCT_METHOD("set_led_property",
                          "icsneoSetLedProperty",
                          "SetLedProperty",
                          meth_set_led_property,
                          METH_VARARGS,
                          _DOC_SET_LED_PROPERTY),
    _EZ_ICS_STRUCT_METHOD("start_dhcp_server",
                          "icsneoStartDHCPServer",
                          "StartDHCPServer",
                          meth_start_dhcp_server,
                          METH_VARARGS,
                          _DOC_START_DHCP_SERVER),
    _EZ_ICS_STRUCT_METHOD("stop_dhcp_server",
                          "icsneoStopDHCPServer",
                          "StopDHCPServer",
                          meth_stop_dhcp_server,
                          METH_VARARGS,
                          _DOC_STOP_DHCP_SERVER),

    _EZ_ICS_STRUCT_METHOD("wbms_manager_write_lock",
                          "icsneowBMSManagerWriteLock",
                          "wBMSManagerWriteLock",
                          meth_wbms_manager_write_lock,
                          METH_VARARGS,
                          _DOC_WBMS_MANAGER_WRITE_LOCK),
    _EZ_ICS_STRUCT_METHOD("wbms_manager_reset",
                          "icsneowBMSManagerReset",
                          "wBMSManagerReset",
                          meth_wbms_manager_reset,
                          METH_VARARGS,
                          _DOC_WBMS_MANAGER_RESET),
    _EZ_ICS_STRUCT_METHOD("uart_write", "icsneoUartWrite", "UartWrite", meth_uart_write, METH_VARARGS, _DOC_UART_WRITE),
    _EZ_ICS_STRUCT_METHOD("uart_read", "icsneoUartRead", "UartRead", meth_uart_read, METH_VARARGS, _DOC_UART_READ),
    _EZ_ICS_STRUCT_METHOD("uart_set_baudrate",
                          "icsneoUartSetBaudrate",
                          "UartSetBaudrate",
                          meth_uart_set_baudrate,
                          METH_VARARGS,
                          _DOC_UART_SET_BAUDRATE),
    _EZ_ICS_STRUCT_METHOD("uart_get_baudrate",
                          "icsneoUartGetBaudrate",
                          "UartGetBaudrate",
                          meth_uart_get_baudrate,
                          METH_VARARGS,
                          _DOC_UART_GET_BAUDRATE),
    _EZ_ICS_STRUCT_METHOD("generic_api_send_command",
                          "icsneoGenericAPISendCommand",
                          "GenericAPISendCommand",
                          meth_generic_api_send_command,
                          METH_VARARGS,
                          _DOC_GENERIC_API_SEND_COMMAND),
    _EZ_ICS_STRUCT_METHOD("generic_api_read_data",
                          "icsneoGenericAPIReadData",
                          "GenericAPIReadData",
                          meth_generic_api_read_data,
                          METH_VARARGS,
                          _DOC_GENERIC_API_READ_DATA),
    _EZ_ICS_STRUCT_METHOD("generic_api_get_status",
                          "icsneoGenericAPIGetStatus",
                          "GenericAPIGetStatus",
                          meth_generic_api_get_status,
                          METH_VARARGS,
                          _DOC_GENERIC_API_GET_STATUS),
    _EZ_ICS_STRUCT_METHOD("get_gptp_status",
                          "icsneoGetGPTPStatus",
                          "GetGPTPStatus",
                          meth_get_gptp_status,
                          METH_VARARGS,
                          _DOC_GET_GPTP_STATUS),
    _EZ_ICS_STRUCT_METHOD("get_all_chip_versions",
                          "icsneoGetAllChipVersions",
                          "GetAllChipVersions",
                          meth_get_all_chip_versions,
                          METH_VARARGS,
                          _DOC_GET_ALL_CHIP_VERSIONS),

    _EZ_ICS_STRUCT_METHOD("flash_accessory_firmware",
                          "icsneoFlashAccessoryFirmware",
                          "FlashAccessoryFirmware",
                          meth_flash_accessory_firmware,
                          METH_VARARGS,
                          _DOC_FLASH_ACCESSORY_FIRMWARE),
    _EZ_ICS_STRUCT_METHOD("get_accessory_firmware_version",
                          "icsneoGetAccessoryFwVersion",
                          "GetAccessoryFwVersion",
                          meth_get_accessory_firmware_version,
                          METH_VARARGS,
                          _DOC_GET_ACCESSORY_FIRMWARE_VERSION),

    { "override_library_name", (PyCFunction)meth_override_library_name, METH_VARARGS, _DOC_OVERRIDE_LIBRARY_NAME },
    { "get_library_path", (PyCFunction)meth_get_library_path, METH_NOARGS, "" },

    { NULL, NULL, 0, NULL }
};

#endif // _METHODS_H_
