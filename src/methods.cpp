#include "methods.h"
#include "exceptions.h"
#include "dll.h"
#include "defines.h"
#ifndef USING_STUDIO_8
#define USING_STUDIO_8 1
#endif
#pragma warning(push, 0)
#include <icsnVC40.h>
#ifdef _USE_INTERNAL_HEADER_
#include <icsnVC40Internal.h>
#endif
#pragma warning(pop)
#include <datetime.h>
#include "object_spy_message.h"
#include "setup_module_auto_defines.h"

#include <memory>
#include <sstream>
#include <string>

// This class allows RAII of the python GIL. This is a C++ replacement of
// Py_BEGIN_ALLOW_THREADS / Py_END_ALLOW_THREADS
class PyAllowThreads
{
    PyThreadState* _save = nullptr;

  public:
    // Save the thread state and Release the GIL
    PyAllowThreads() { _save = PyEval_SaveThread(); }
    // Restore the thread state and Acquire the GIL
    virtual ~PyAllowThreads() { restore(); }

    // Restore the thread and GIL state, this is safe to call multiple times.
    void restore()
    {
        if (_save) {
            PyEval_RestoreThread(_save);
        }
        _save = nullptr;
    }
};

extern PyTypeObject spy_message_object_type;
// __func__, __FUNCTION__ and __PRETTY_FUNCTION__ are not preprocessor macros.
// but MSVC doesn't follow c standard and treats __FUNCTION__ as a string literal macro...
#ifdef _MSC_VER
#define arg_parse(a, f) a f
#else
const char* arg_parse(const char* args, const char* func)
{
    static char buffer[128];
    memset(buffer, '\0', sizeof(buffer) / sizeof(buffer[0]));
    strcpy(buffer, args);
    strcat(buffer, func);
    return (const char*)buffer;
}
#endif

#ifndef _USE_INTERNAL_HEADER_
typedef struct
{
    unsigned char sec;   // --- Seconds (00-59)
    unsigned char min;   // --- (00-59)
    unsigned char hour;  // --- (00-23)
    unsigned char day;   // --- (01-31)
    unsigned char month; // --- (01-12)
    unsigned char year;  // --- (00-99)
} icsSpyTime;
#endif

// Linux specific fixes
#if !(defined(_WIN32) || defined(__WIN32__))

// __int64 is a msvc specific type
#include <inttypes.h>
#define __int64 int64_t

// __stdcall is a windows calling convention
#ifndef __stdcall
#define __stdcall

#endif
#endif

#pragma warning(push)
// warning C4191: 'type cast': unsafe conversion from 'PyObject *(__cdecl *)(PyObject *,PyObject *,PyObject *)'
// to 'PyCFunction' Making a function call using the resulting pointer may cause your program to fail
#pragma warning(disable : 4191)
PyMethodDef IcsMethods[] = {
    _EZ_ICS_STRUCT_METHOD("find_devices",
                          "icsneoFindNeoDevices",
                          "FindNeoDevices",
                          meth_find_devices,
                          METH_VARARGS | METH_KEYWORDS,
                          _DOC_FIND_DEVICES),
    _EZ_ICS_STRUCT_METHOD("open_device",
                          "icsneoOpenNeoDevice",
                          "OpenNeoDevice",
                          meth_open_device,
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
                          "Accepts a  PyNeoDeviceEx"
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
                          "icsneoReadSDCard(), Accepts a  PyNeoDeviceEx"
                          " and sector index. Returns a bytearray of 512 bytes max. Exception on error."),
    _EZ_ICS_STRUCT_METHOD("write_sdcard",
                          "icsneoWriteSDCard",
                          "WriteSDCard",
                          meth_write_sdcard,
                          METH_VARARGS,
                          "icsneoReadSDCard(), Accepts a  PyNeoDeviceEx"
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
    _EZ_ICS_STRUCT_METHOD("set_safe_boot_mode",
                          "icsneoSetSafeBootMode",
                          "SetSafeBootMode",
                          meth_set_safe_boot_mode,
                          METH_VARARGS,
                          _DOC_SET_SAFE_BOOT_MODE),
    _EZ_ICS_STRUCT_METHOD("get_device_name",
                          "icsneoGetDeviceName",
                          "GetDeviceName",
                          meth_get_device_name,
                          METH_VARARGS,
                          _DOC_GET_DEVICE_NAME),
    _EZ_ICS_STRUCT_METHOD("get_imei", "icsneoGetIMEI", "GetIMEI", meth_get_imei, METH_VARARGS, _DOC_GET_IMEI),
    _EZ_ICS_STRUCT_METHOD("get_component_versions",
                          "icsneoGetComponentVersions",
                          "GetComponentVersions",
                          meth_get_component_versions,
                          METH_VARARGS,
                          _DOC_GET_COMPONENT_VERSIONS),
    _EZ_ICS_STRUCT_METHOD("request_set_neovi_miscio",
                          "icsneoRequestSetNeoVIMiscIO",
                          "RequestSetNeoVIMiscIO",
                          meth_request_set_neovi_miscio,
                          METH_VARARGS,
                          _DOC_REQUEST_SET_NEOVI_MISCIO),

    { "override_library_name", (PyCFunction)meth_override_library_name, METH_VARARGS, _DOC_OVERRIDE_LIBRARY_NAME },
    { "get_library_path", (PyCFunction)meth_get_library_path, METH_NOARGS, "" },

    { NULL, NULL, 0, NULL }
};

#pragma warning(pop)

// Internal function
// This function doesn't call any python methods and doesn't do anything with thread states or GIL
auto device_name_from_nde(NeoDeviceEx* nde) -> std::string
{
    if (!nde) {
        return std::string("Bug: nde invalid!");
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return std::string(dll_get_error(buffer));
        }
        std::string name;
        name.reserve(255);
        name.resize(255);
        // Get the struct
        // int _stdcall icsneoGetDeviceName(const NeoDeviceEx* nde, char* name, const size_t length, const enum
        // _EDevNameType devNameType)
        ice::Function<int __stdcall(const NeoDeviceEx*, char*, const size_t, const enum _EDevNameType)>
            icsneoGetDeviceName(lib, "icsneoGetDeviceName");
        if (auto length =
                icsneoGetDeviceName(const_cast<NeoDeviceEx*>(nde), &name[0], name.capacity(), EDevNameTypeNoSerial);
            length == 0) {
            return std::string("icsneoGetDeviceName() Failed");
        } else {
            name.resize(length, '\0');
        }
        return name;
    } catch (ice::Exception&) {
        // Legacy support - we are assuming icsneoGetDeviceName isn't available here
        // and suppressing ex error message.
        switch (nde->neoDevice.DeviceType) {
            case NEODEVICE_UNKNOWN:
                return "Unknown";
            case NEODEVICE_BLUE:
                return "neoVI BLUE";
            case NEODEVICE_DW_VCAN:
                return "ValueCAN DW";
            case NEODEVICE_RADMOON2:
                return "RAD-Moon 2";
            case NEODEVICE_VCAN41:
                return "ValueCAN 4-1";
            case NEODEVICE_FIRE:
                return "neoVI FIRE";
            case NEODEVICE_VCAN42_EL:
                return "ValueCAN 4-2EL";
            case NEODEVICE_RADIO_CANHUB:
                return "neoRAD-IO2-CANHUB";
            case NEODEVICE_NEOECU12:
                return "neoECU12";
            case NEODEVICE_OBD2_LC:
                return "neoOBD2-LC";
            case NEODEVICE_VCAN3:
                return "ValueCAN 3";
            case NEODEVICE_FIRE3:
                return "neoVI FIRE 3";
            case NEODEVICE_RADJUPITER:
                return "RAD-Jupiter";
            case NEODEVICE_VCAN4_IND:
                return "ValueCAN 4 Industrial";
            case NEODEVICE_GIGASTAR:
                return "RAD-Gigastar";
            case NEODEVICE_RED2:
                return "neoVI RED 2";
            case NEODEVICE_RAD_A2B:
                return "RAD-A2B";
            case NEODEVICE_RADEPSILON:
                return "RAD-Epsilon";
            case NEODEVICE_RADEPSILON_T:
                return "RAD-EpsilonT";
            case NEODEVICE_RADEPSILON_EXPRESS:
                return "RAD-Epsilon Express";
            case NEODEVICE_RADPROXIMA:
                return "RAD-Proxima";
            case NEODEVICE_RAD_BMS:
                return "RAD-wBMS";
            case NEODEVICE_RADMOON3:
                return "RAD-Moon3";
            case NEODEVICE_RADCOMET:
                return "RAD-Comet";
            case NEODEVICE_FIRE3_FLEXRAY:
                return "neoVI FIRE 3 Flexray";
            case NEODEVICE_NEOVI_CONNECT:
                return "neoVI CONNECT";
            case NEODEVICE_RADCOMET3:
                return "RAD-COMET3";
            case NEODEVICE_RADMOONT1S:
                return "RAD-MOON-T1S";
            case NEODEVICE_GIGASTAR2:
                return "RAD-GigaStar2";
            case NEODEVICE_RED:
                return "neoVI RED";
            case NEODEVICE_ECU:
                return "neoECU";
            case NEODEVICE_PENDANT:
                return "Pendant";
            case NEODEVICE_PLASMA: // also NEODEVICE_ANY_PLASMA
                return "neoVI PLASMA";
            case NEODEVICE_NEOANALOG:
                return "neoAnalog";
            case NEODEVICE_CT_OBD:
                return "neoOBD CT";
            case NEODEVICE_ION: // also NEODEVICE_ANY_ION
                return "neoVI ION";
            case NEODEVICE_VCAN44:
                return "ValueCAN 4-4";
            case NEODEVICE_VCAN42:
                return "ValueCAN 4-2";
            case NEODEVICE_FIRE2:
                return "neoVI FIRE 2";
            case NEODEVICE_RADGALAXY:
                return "RAD-Galaxy";
            case NEODEVICE_RADSTAR2:
                return "RAD-Star 2";
            case NEODEVICE_VIVIDCAN:
                return "VividCAN";
            case NEODEVICE_DONT_REUSE0:
            case NEODEVICE_DONT_REUSE1:
            case NEODEVICE_DONT_REUSE2:
            case NEODEVICE_DONT_REUSE3:
            case NEODEVICE_DONT_REUSE4:
            default:
                return "Unknown";
        };
    }
}

bool _convertListOrTupleToArray(PyObject* obj, std::vector<PyObject*>* results)
{
    if (!obj || !results) {
        set_ics_exception(exception_runtime_error(), "passed invalid arguments");
        return false;
    }
    results->clear();
    if (PyList_CheckExact(obj)) {
        Py_ssize_t length = PyList_Size(obj);
        for (Py_ssize_t i = 0; i < length; ++i)
            results->push_back(PyList_GetItem(obj, i));
        return true;
    } else if (PyTuple_CheckExact(obj)) {
        Py_ssize_t length = PyTuple_Size(obj);
        for (Py_ssize_t i = 0; i < length; ++i)
            results->push_back(PyTuple_GetItem(obj, i));
        return true;
    } else {
        set_ics_exception(exception_runtime_error(), "was passed neither a list or tuple");
        return false;
    }
    set_ics_exception(exception_runtime_error(), "bug!");
    return false;
}

// Returns a PyObject from PyObject_CallObject() on success, sets exception and NULL on failure.
PyObject* _getPythonModuleObject(const char* module_name, const char* module_object_name)
{
    // Before we do anything, we need to grab the python s_device_settings ctype.Structure.
    PyObject* module = PyImport_ImportModule(module_name);
    if (!module) {
        return set_ics_exception(exception_runtime_error(), "_getPythonModuleObject(): Failed to import module");
    }
    // Grab the module Dictionary
    PyObject* module_dict = PyModule_GetDict(module);
    if (!module_dict) {
        return set_ics_exception(exception_runtime_error(),
                                 "_getPythonModuleObject(): Failed to grab module dict from module");
    }
    // Grab the actual object
    PyObject* module_object = PyDict_GetItemString(module_dict, module_object_name);
    if (!module_object) {
        return set_ics_exception(exception_runtime_error(),
                                 "_getPythonModuleObject(): Failed to grab object s_device_settings from module");
    }
    // Call the object so we have our own reference - we are going to return this
    PyObject* object = PyObject_CallObject(module_object, NULL);
    if (!object) {
        return set_ics_exception(exception_runtime_error(),
                                 "_getPythonModuleObject(): Failed to call object from module");
    }
    return object;
}

// Returns same as PyObject_IsInstance()
int _isPythonModuleObject_IsInstance(PyObject* object, const char* module_name, const char* module_object_name)
{
    // Before we do anything, we need to grab the python s_device_settings ctype.Structure.
    PyObject* module = PyImport_ImportModule(module_name);
    if (!module) {
        set_ics_exception(exception_runtime_error(), "_isPythonModuleObjectInstanceOf(): Failed to import module");
        return -1;
    }
    // Grab the module Dictionary
    PyObject* module_dict = PyModule_GetDict(module);
    if (!module_dict) {
        set_ics_exception(exception_runtime_error(),
                          "_isPythonModuleObjectInstanceOf(): Failed to grab module dict from module");
        return -1;
    }
    // Grab the actual object
    PyObject* module_object = PyDict_GetItemString(module_dict, module_object_name);
    if (!module_object) {
        set_ics_exception(exception_runtime_error(),
                          "_isPythonModuleObjectInstanceOf(): Failed to grab object s_device_settings from module");
        return -1;
    }
    return PyObject_IsInstance(object, module_object);
}

// Returns true if object instance is the same as ics.py_neo_device_ex.PyNeoDeviceEx
bool PyNeoDeviceEx_CheckExact(PyObject* object)
{
    const char CLASS_NAME[] = "PyNeoDeviceEx";
    if (!object) {
        return false;
    }
    PyTypeObject* type_obj = Py_TYPE(object);
    if (!type_obj && !type_obj->tp_name) {
        return false;
    }

    return strncmp(type_obj->tp_name, CLASS_NAME, sizeof(CLASS_NAME) / sizeof(CLASS_NAME[0])) == 0;
    // This will fail on cleanup because we can't import ics anymore...
    // return _isPythonModuleObject_IsInstance(object, "ics.py_neo_device_ex", "PyNeoDeviceEx") == 1;
}

// Get the NeoDeviceEx from PyNeoDeviceEx. Caller is responsible for managing the
// Py_buffer and nde is UB once Py_buffer goes out of scope.
// Note: Calls to PyNeoDeviceEx_GetNeoDeviceEx() must be paired with calls
// to PyBuffer_Release(), similar to malloc() and free().
//
// Returns true on success, false on failure with exception set. nde will be set to NULL on failure.
// Example:
//   Py_buffer buffer = {};
//   NeoDeviceEx* nde = NULL;
//   if (PyNeoDeviceEx_GetNeoDeviceEx(obj, &buffer, &nde)) {
//       // use nde here
//   }
//   PyBuffer_Release(&buffer);
bool PyNeoDeviceEx_GetNeoDeviceEx(PyObject* object, Py_buffer* buffer, NeoDeviceEx** nde)
{
    if (!object && !buffer && !nde) {
        set_ics_exception(exception_runtime_error(), "Object and or buffer is not valid");
        nde = NULL;
        return false;
    }
    if (!PyNeoDeviceEx_CheckExact(object)) {
        set_ics_exception(exception_runtime_error(), "Object is not of type PyNeoDeviceEx");
        nde = NULL;
        return false;
    }
    if (PyObject_GetBuffer(object, buffer, PyBUF_CONTIG) != 0) {
        *nde = NULL;
        return false;
    }
    *nde = (NeoDeviceEx*)buffer->buf;
    return true;
}

// Copies the NeoDeviceEx src_nde to the PyNeoDeviceEx object. Returns true on success, false on
// error with an exception set.
bool PyNeoDeviceEx_SetNeoDeviceEx(PyObject* object, NeoDeviceEx* src_nde)
{
    if (!object || !src_nde) {
        return false;
    }
    if (!PyNeoDeviceEx_CheckExact(object)) {
        set_ics_exception(exception_runtime_error(), "Object is not of type PyNeoDeviceEx");
        return false;
    }
    // Get the NeoDeviceEx from PyNeoDeviceEx
    Py_buffer buffer = {};
    if (PyObject_GetBuffer(object, &buffer, PyBUF_CONTIG) != 0) {
        return false;
    }
    memcpy(buffer.buf, src_nde, sizeof(*src_nde));
    PyBuffer_Release(&buffer);
    return true;
}

extern "C" void __destroy_PyNeoDeviceEx_Handle(PyObject* handle)
{
    (void)handle;
    /*
    if (handle) {
        delete handle;
        handle = NULL;
    }
    */
}

// Return the _handle attribute of PyNeoDeviceEx. Sets handle to NULL on failure or not valid.
// Returns false on error and exception is set. Returns true on success.
bool PyNeoDeviceEx_GetHandle(PyObject* object, void** handle)
{
    if (!object && !handle && !*handle) {
        set_ics_exception(exception_runtime_error(), "Object is not valid");
        return false;
    }
    *handle = NULL;
    if (!PyNeoDeviceEx_CheckExact(object)) {
        set_ics_exception(exception_runtime_error(), "Object is not of type PyNeoDeviceEx");
        return false;
    }
    PyObject* _handle = PyObject_GetAttrString(object, "_handle");
    if (!_handle) {
        return false;
    }
    if (!PyCapsule_CheckExact(_handle)) {
        return true;
    }
    void* ptr = PyCapsule_GetPointer(_handle, NULL);
    if (!ptr) {
        return false;
    }
    *handle = ptr;
    return true;
}
// Returns false on error and exception is set. Returns true on success.
bool PyNeoDeviceEx_SetHandle(PyObject* object, void* handle)
{
    if (!object) {
        set_ics_exception(exception_runtime_error(), "Object is not valid");
        return false;
    }
    if (!PyNeoDeviceEx_CheckExact(object)) {
        set_ics_exception(exception_runtime_error(), "Object is not of type PyNeoDeviceEx");
        return false;
    }
    PyObject* _handle = PyObject_GetAttrString(object, "_handle");
    if (!_handle) {
        return false;
    }
    if (!PyCapsule_CheckExact(_handle) && handle) {
        PyObject* capsule = PyCapsule_New(handle, NULL, __destroy_PyNeoDeviceEx_Handle);
        if (!capsule) {
            return false;
        }
        if (PyObject_SetAttrString(object, "_handle", capsule) != 0) {
            return false;
        }
    } else if (handle) {
        if (!PyCapsule_SetPointer(_handle, handle)) {
            return NULL;
        }
    } else {
        if (PyObject_SetAttrString(object, "_handle", Py_None) != 0) {
            return false;
        }
    }
    return true;
}

// Get the _name attribute of PyNeoDeviceEx.
// Returns false on error and exception is set. Returns true on success.
bool PyNeoDeviceEx_GetName(PyObject* object, PyObject* name)
{
    if (!object) {
        set_ics_exception(exception_runtime_error(), "Object is not valid");
        return false;
    }
    if (!PyNeoDeviceEx_CheckExact(object)) {
        set_ics_exception(exception_runtime_error(), "Object is not of type PyNeoDeviceEx");
        return false;
    }
    // Get the _name of PyNeoDeviceEx
    name = PyObject_GetAttrString(object, "_name");
    return name != NULL;
}

// Set the _name attribute of PyNeoDeviceEx. Will create if needed.
// Returns false on error and exception is set. Returns true on success.
bool PyNeoDeviceEx_SetName(PyObject* object, PyObject* name)
{
    if (!object) {
        set_ics_exception(exception_runtime_error(), "Object is not valid");
        return false;
    }
    if (!PyNeoDeviceEx_CheckExact(object)) {
        set_ics_exception(exception_runtime_error(), "Object is not of type PyNeoDeviceEx");
        return false;
    }
    if (!PyUnicode_CheckExact(name)) {
        set_ics_exception(exception_runtime_error(), "name is not of type str");
        return false;
    }
    // Get the _handle of PyNeoDeviceEx
    return PyObject_SetAttrString(object, "_name", name) == 0;
}

PyObject* meth_find_devices(PyObject* self, PyObject* args, PyObject* keywords)
{
    (void)self;
    PyObject* device_types = NULL;
    int network_id = -1;
#if (PY_MAJOR_VERSION) >= 3 && (PY_MINOR_VERSION >= 13)
    const
#endif
        char* kwords[] = { "device_types", "network_id", NULL };
    if (!PyArg_ParseTupleAndKeywords(
            args, keywords, arg_parse("|Oi:", __FUNCTION__), kwords, &device_types, &network_id)) {
        return NULL;
    }

    // Grab the library before we start doing anything...
    ice::Library* lib = dll_get_library();
    if (!lib) {
        char buffer[512];
        return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
    }

    // Create a vector from the device_types python container
    std::unique_ptr<unsigned int[]> device_types_list;
    unsigned int device_types_list_size = 0;
    if (device_types && device_types != Py_None) {
        std::vector<PyObject*> device_type_vector;
        if (!_convertListOrTupleToArray(device_types, &device_type_vector))
            return NULL;
        device_types_list_size = static_cast<unsigned int>(device_type_vector.size());
        device_types_list.reset((new unsigned int(device_types_list_size)));
        for (unsigned int i = 0; i < device_types_list_size; ++i)
            device_types_list[i] = (unsigned int)PyLong_AsLong(device_type_vector[i]);
    }
    // Lets finally call the icsneo40 function
    try {
        /*
        int _stdcall icsneoFindDevices(NeoDeviceEx* pNeoDeviceEx,
                                       int* pNumDevices,
                                       unsigned int* deviceTypes,
                                       unsigned int numDeviceTypes,
                                       POptionsFindNeoEx* pOptionsFindNeoEx,
                                       unsigned long reserved​)
        */
        ice::Function<int __stdcall(NeoDeviceEx*, int*, unsigned int*, unsigned int, POptionsFindNeoEx*, unsigned long)>
            icsneoFindDevices(lib, "icsneoFindDevices");
        NeoDeviceEx devices[255] = {};
        int count = 255;

        OptionsFindNeoEx opts = {};
        opts.CANOptions.iNetworkID = network_id;
        POptionsFindNeoEx popts = NULL;
        if (network_id != -1)
            popts = &opts;

        auto gil = PyAllowThreads();
        if (!icsneoFindDevices(devices,
                               &count,
                               device_types_list.get(),
                               device_types_list_size,
                               (network_id != -1) ? &popts : NULL,
                               0)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoFindDevices() Failed");
        }
        gil.restore();

        PyObject* tuple = PyTuple_New(count);
        if (!tuple) {
            return NULL;
        }
        for (int i = 0; i < count; ++i) {
            PyObject* obj = _getPythonModuleObject("ics.py_neo_device_ex", "PyNeoDeviceEx");
            if (!obj) {
                return set_ics_exception(exception_runtime_error(), "Failed to allocate PyNeoDeviceEx");
            }
            // Copy the NeoDeviceEx struct into our python NeoDevice object
            if (!PyNeoDeviceEx_SetNeoDeviceEx(obj, &devices[i])) {
                return NULL;
            }
            std::string device_name = device_name_from_nde(&devices[i]);
            PyObject* py_device_name =
                PyUnicode_FromStringAndSize(device_name.c_str(), static_cast<Py_ssize_t>(device_name.length()));
            if (!py_device_name || !PyNeoDeviceEx_SetName(obj, py_device_name)) {
                return NULL;
            }
            PyTuple_SetItem(tuple, i, obj);
        }
        return tuple;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_open_device(PyObject* self, PyObject* args, PyObject* keywords)
{
    (void)self;
    unsigned long serial_number = 0;
    PyObject* device = NULL;
    PyObject* network_ids = NULL;
    int config_read = 0;
    int options = 0;
    int network_id = -1;
    bool use_neovi_server = false;
    bool device_need_ref_inc = false;
#if (PY_MAJOR_VERSION) >= 3 && (PY_MINOR_VERSION >= 13)
    const
#endif
        char* kwords[] = { "device", "network_ids", "config_read", "options", "network_id", "use_server", NULL };
    if (!PyArg_ParseTupleAndKeywords(args,
                                     keywords,
                                     arg_parse("|OOiiib:", __FUNCTION__),
                                     kwords,
                                     &device,
                                     &network_ids,
                                     &config_read,
                                     &options,
                                     &network_id,
                                     &use_neovi_server)) {
        return NULL;
    }

    // Grab the library before we start doing anything...
    ice::Library* lib = dll_get_library();
    if (!lib) {
        char buffer[512];
        return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
    }

    // Create a vector from the device_types python container
    std::unique_ptr<unsigned char[]> network_ids_list;
    unsigned int network_ids_list_size = 0;
    bool use_network_ids = false;
    if (network_ids && network_ids != Py_None) {
        std::vector<PyObject*> network_ids_vector;
        if (!_convertListOrTupleToArray(network_ids, &network_ids_vector))
            return NULL;
        network_ids_list_size = static_cast<unsigned int>(network_ids_vector.size());
        network_ids_list.reset(new unsigned char[network_ids_list_size]);
        for (unsigned int i = 0; i < network_ids_list_size; ++i)
            network_ids_list[i] = (unsigned char)PyLong_AsLong(network_ids_vector[i]);
        use_network_ids = true;
    }

    // Verify device type
    if (device && PyLong_CheckExact(device)) {
        // Device is a serial number in integer format
        serial_number = PyLong_AsUnsignedLong(device);
    } else if (device && PyUnicode_CheckExact(device)) {
        // Lets convert the base36 string into an integer
        PyObject* module_name = PyUnicode_FromString("builtins");
        PyObject* builtins_module = PyImport_Import(module_name);
        if (!builtins_module) {
            return set_ics_exception(exception_runtime_error(), "Failed to import __builtins__ module");
        }
        PyObject* builtin_dict = PyModule_GetDict(builtins_module);
        PyObject* builtin_int = PyDict_GetItemString(builtin_dict, "int");
        if (PyCallable_Check(builtin_int)) {
            PyObject* return_value = PyObject_CallFunction(builtin_int, "Oi", device, 36);
            Py_DECREF(builtins_module);
            if (return_value == NULL) {
                // We failed for some reason...
                PyErr_Print();
                return NULL;
            } else {
                serial_number = PyLong_AsUnsignedLong(return_value);
            }
        } else {
            return set_ics_exception(exception_runtime_error(), "Failed to convert serial number string to integer.");
        }
    } else if (device && !PyNeoDeviceEx_CheckExact(device)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Invalid 'device' parameter object type passed to open_device().");
    } else if (device && PyNeoDeviceEx_CheckExact(device)) {
        // If the user passed in a NeoDevice device we need to increment
        // the reference counter when we return it since device is a borrowed
        // reference.
        // devs = ics.find_devices()
        // device = ics.open_device(devs[0])
        // del device # This will decrement the reference and crash interp
        device_need_ref_inc = true;
    }

    if ((device && !PyNeoDeviceEx_CheckExact(device)) || !device) {
        // We don't have a device parameter so lets find the first one
        try {
            ice::Function<int __stdcall(
                NeoDeviceEx*, int*, unsigned int*, unsigned int, POptionsFindNeoEx*, unsigned long)>
                icsneoFindDevices(lib, "icsneoFindDevices");
            NeoDeviceEx devices[255];
            int count = 255;

            OptionsFindNeoEx opts = {};
            opts.CANOptions.iNetworkID = network_id;
            POptionsFindNeoEx popts = NULL;
            if (network_id != -1)
                popts = &opts;

            auto gil = PyAllowThreads();
            if (!icsneoFindDevices(devices, &count, NULL, 0, (network_id != -1) ? &popts : NULL, 0)) {
                gil.restore();
                return set_ics_exception(exception_runtime_error(), "icsneoFindDevices() Failed");
            }
            gil.restore();
            // Find the first free device
            for (int i = 0; i < count; ++i) {
                // If we are looking for a serial number, check here
                if (serial_number && devices[i].neoDevice.SerialNumber != (int32_t)serial_number)
                    continue;
                // If we aren't using neoVI Server and already have a connection we can't proceed.
                if (!use_neovi_server && devices[i].neoDevice.NumberOfClients != 0) {
                    continue;
                    // return set_ics_exception(exception_runtime_error(), "Found device, but its already open!");
                }
                // We matched a neoDevice, lets allocate it here.
                device = _getPythonModuleObject("ics.py_neo_device_ex", "PyNeoDeviceEx");
                if (!device) {
                    return NULL;
                }
                if (!PyNeoDeviceEx_SetNeoDeviceEx(device, &devices[i])) {
                    return NULL;
                }
                if (!PyNeoDeviceEx_SetName(device, PyUnicode_FromString(device_name_from_nde(&devices[i]).c_str()))) {
                    return NULL;
                }
                break;
            }
            if (!device || !PyNeoDeviceEx_CheckExact(device)) {
                return set_ics_exception(exception_runtime_error(), "Failed to find a device to open.");
            }
        } catch (ice::Exception& ex) {
            return set_ics_exception(exception_runtime_error(), (char*)ex.what());
        }
    }

    // We should finally have our device allocated at this point!
    try {
        /*
        int _stdcall icsneoOpenDevice(NeoDeviceEx* pNeoDeviceEx,
                                      void** hObject,
                                      unsigned char* bNetworkIDs,
                                      int bConfigRead,
                                      int iOptions,
                                      OptionsOpenNeoEx* stOptionsOpenNeoEx,
                                      unsigned long reserved)
        */
        ice::Function<int __stdcall(NeoDeviceEx*, void**, unsigned char*, int, int, OptionsFindNeoEx*, unsigned long)>
            icsneoOpenDevice(lib, "icsneoOpenDevice");
        OptionsFindNeoEx opts = {};
        opts.CANOptions.iNetworkID = network_id;
        POptionsFindNeoEx popts = NULL;
        if (network_id != -1)
            popts = &opts;
        // Get the handle from PyNeoDeviceEx
        void* handle = NULL;
        if (!PyNeoDeviceEx_GetHandle(device, &handle)) {
            return NULL;
        }
        // Get the NeoDeviceEx from PyNeoDeviceEx
        Py_buffer buffer = {};
        NeoDeviceEx* nde = NULL;
        if (!PyNeoDeviceEx_GetNeoDeviceEx(device, &buffer, &nde)) {
            PyBuffer_Release(&buffer);
            return NULL;
        }
        auto gil = PyAllowThreads();
        if (!icsneoOpenDevice(nde,
                              &handle,
                              use_network_ids ? network_ids_list.get() : NULL,
                              config_read,
                              options,
                              (network_id != -1) ? popts : NULL,
                              0)) {
            gil.restore();
            PyBuffer_Release(&buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoOpenDevice() Failed");
        }
        gil.restore();
        PyBuffer_Release(&buffer);
        if (!PyNeoDeviceEx_SetHandle(device, handle)) {
            return NULL;
        }
        if (device_need_ref_inc) {
            Py_INCREF(device);
        }
        return device;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_close_device(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (obj == NULL) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type PyNeoDeviceEx, got NULL");
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type PyNeoDeviceEx");
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, int*)> icsneoClosePort(lib, "icsneoClosePort");
        ice::Function<void __stdcall(void*)> icsneoFreeObject(lib, "icsneoFreeObject");
        int error_count = 0;
        void* handle = NULL;
        if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
            return NULL;
        }
        // nothing to do here, we have an invalid handle. We probably were never opened.
        if (!handle) {
            return Py_BuildValue("i", error_count);
        }
        auto gil = PyAllowThreads();
        if (!icsneoClosePort(handle, &error_count)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoClosePort() Failed");
        }
        icsneoFreeObject(handle);
        gil.restore();
        if (!PyNeoDeviceEx_SetHandle(obj, NULL)) {
            return NULL;
        }
        return Py_BuildValue("i", error_count);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

/*
 * Converts tm structure to second resolution.
 * Returns seconds elapsed since the beginning of the month.
 */
__int64 _tm_secs(tm* t)
{
    __int64 result = -1;
    if (!t)
        return result;
    result = t->tm_mday * 86400;
    result += t->tm_hour * 3600;
    result += t->tm_min * 60;
    result += t->tm_sec;

    return result;
}

/*
 * Calculates the offset (in seconds) between two tm structures.
 * Returns -1 on NULL parameters, -2 if month and year are not
 * the same. Order of t1 and t2 doesn't matter as the difference
 * will always be positive.
 * Returns the difference of the two in seconds.
 */
__int64 _tm_secs_offset(tm* t1, tm* t2)
{
    __int64 result = -1;
    __int64 r1 = _tm_secs(t1);
    __int64 r2 = _tm_secs(t2);
    if (r1 == -1 || r2 == -1)
        return result;
    if (t1->tm_year != t2->tm_year || t1->tm_mon != t2->tm_mon)
        return -2;
    if ((result = r1 - r2) < 0)
        result *= -1;
    return result;
}

PyObject* meth_get_rtc(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    icsSpyTime ics_time;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, icsSpyTime*)> icsneoGetRTC(lib, "icsneoGetRTC");
        auto gil = PyAllowThreads();
        if (!icsneoGetRTC(handle, &ics_time)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetRTC() Failed");
        }
        gil.restore();
        time_t current_time = time(0);
        // Bug #6600 - icsneoSetRTC is utc, icsneoGetRTC is local
        // tm* current_utc_time = gmtime(&current_time); // UTC
        tm* current_utc_time = localtime(&current_time); // Local
        tm device_utc_time;
        device_utc_time.tm_hour = ics_time.hour;
        device_utc_time.tm_min = ics_time.min;
        device_utc_time.tm_sec = ics_time.sec;
        device_utc_time.tm_mon = ics_time.month - 1;
        device_utc_time.tm_mday = ics_time.day;
        device_utc_time.tm_year = ics_time.year;
        device_utc_time.tm_isdst = -1;
        device_utc_time.tm_year += 100;
        unsigned long offset = (unsigned long)_tm_secs_offset(&device_utc_time, current_utc_time);
        PyDateTime_IMPORT;
        if (!PyDateTimeAPI) {
            return set_ics_exception(exception_runtime_error(), "Failed to initialize PyDateTime");
        }
        PyObject* datetime = PyDateTime_FromDateAndTime(device_utc_time.tm_year + 1900,
                                                        device_utc_time.tm_mon + 1,
                                                        device_utc_time.tm_mday,
                                                        device_utc_time.tm_hour,
                                                        device_utc_time.tm_min,
                                                        device_utc_time.tm_sec,
                                                        0);
        return Py_BuildValue("(O,i)", datetime, offset);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_set_rtc(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* datetime_object = NULL;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O|O:", __FUNCTION__), &obj, &datetime_object)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    PyDateTime_IMPORT;
    if (!PyDateTimeAPI) {
        return set_ics_exception(exception_runtime_error(), "Failed to initialize PyDateTime");
    }
    if (!datetime_object || !PyDateTime_Check(datetime_object)) {
        // We didn't get a valid Python DateTime Object, use current UTC Time
        time_t current_time = time(0);
        tm* current_utc_time = gmtime(&current_time);
        datetime_object = PyDateTime_FromDateAndTime(current_utc_time->tm_year + 1900,
                                                     current_utc_time->tm_mon + 1,
                                                     current_utc_time->tm_mday,
                                                     current_utc_time->tm_hour,
                                                     current_utc_time->tm_min,
                                                     current_utc_time->tm_sec,
                                                     0);
    }
    // Convert Python DateTime object to icsSpyTime
    icsSpyTime ics_time;
    ics_time.sec = PyDateTime_DATE_GET_SECOND(datetime_object);
    ics_time.min = PyDateTime_DATE_GET_MINUTE(datetime_object);
    ics_time.hour = PyDateTime_DATE_GET_HOUR(datetime_object);
    ics_time.day = PyDateTime_GET_DAY(datetime_object);
    ics_time.month = PyDateTime_GET_MONTH(datetime_object);
    ics_time.year = static_cast<unsigned char>(PyDateTime_GET_YEAR(datetime_object) % 100);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, icsSpyTime*)> icsneoSetRTC(lib, "icsneoSetRTC");
        auto gil = PyAllowThreads();
        if (!icsneoSetRTC(handle, &ics_time)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoSetRTC() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_load(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* arg_data = NULL;
    int location;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OOi:", __FUNCTION__), &obj, &arg_data, &location)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    long fsize;
    unsigned char* data = NULL;
    int data_size = 0;
#if PY_MAJOR_VERSION >= 3
    if (PyUnicode_CheckExact(arg_data)) {
        char* file_name = PyUniStr_AsStrOrUTF8(arg_data);
#else
    if (PyString_Check(arg_data)) {
        char* file_name = PyUniStr_AsStrOrUTF8(arg_data);
#endif
        if (!file_name) {
            return set_ics_exception(exception_runtime_error(), "Failed to convert file path to string");
        }
        FILE* f;
        f = fopen(file_name, "rb");
        if (!f) {
            std::stringstream ss;
            ss << "Failed to open CoreMini script file: '" << file_name << "'. Please make sure path exists";
            return set_ics_exception(exception_runtime_error(), (char*)ss.str().c_str());
        }
        fseek(f, 0, SEEK_END);
        fsize = ftell(f);
        rewind(f);
        data = (unsigned char*)malloc(sizeof(char) * fsize);
        data_size = (int)fread(data, 1, static_cast<size_t>(fsize), f);
        fclose(f);
        if (fsize != data_size) {
            return set_ics_exception(exception_runtime_error(), "CoreMini binary file size mismatch");
        }
    } else if (PyTuple_CheckExact(arg_data)) {
        Py_ssize_t tuple_size = PyTuple_Size(arg_data);
        data = (unsigned char*)malloc(sizeof(char) * tuple_size);
        // Move tuple data into array
        for (int i = 0; i < tuple_size; ++i) {
            PyObject* value = PyTuple_GET_ITEM(arg_data, i);
            if (!PyLong_CheckExact(value)) {
                return set_ics_exception(exception_runtime_error(),
                                         "Failed to convert tuple data. Tuple data must be integer type");
            }
            data[i] = (unsigned char)PyLong_AsLong(PyTuple_GET_ITEM(arg_data, i));
        }
        fsize = static_cast<long>(tuple_size);
        data_size = fsize;
    } else {
        return set_ics_exception(exception_runtime_error(), "Argument must be filepath or tuple");
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, const unsigned char*, unsigned long, int)> icsneoScriptLoad(
            lib, "icsneoScriptLoad");
        auto gil = PyAllowThreads();
        if (!icsneoScriptLoad(handle, data, static_cast<unsigned long>(data_size), location)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptLoad() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_start(PyObject* self, PyObject* args)
{
    (void)self;
    int location;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &location)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, int)> icsneoScriptStart(lib, "icsneoScriptStart");
        auto gil = PyAllowThreads();
        if (!icsneoScriptStart(handle, location)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStart() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_stop(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*)> icsneoScriptStop(lib, "icsneoScriptStop");
        auto gil = PyAllowThreads();
        if (!icsneoScriptStop(handle)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStop() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_clear(PyObject* self, PyObject* args)
{
    (void)self;
    int location;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &location)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, int)> icsneoScriptClear(lib, "icsneoScriptClear");
        auto gil = PyAllowThreads();
        if (!icsneoScriptClear(handle, location)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptClear() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_get_status(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, int*)> icsneoScriptGetScriptStatus(lib, "icsneoScriptGetScriptStatus");
        int status = 0;
        auto gil = PyAllowThreads();
        if (!icsneoScriptGetScriptStatus(handle, &status)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptClear() Failed");
        }
        gil.restore();
        return Py_BuildValue("b", status == 1);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_transmit_messages(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* temp;
    bool created_tuple = false;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OO:", __FUNCTION__), &obj, &temp)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    PyObject* tuple = temp;
    if (!PyTuple_CheckExact(temp)) {
        tuple = Py_BuildValue("(O)", temp);
        if (!tuple) {
            return NULL;
        }
        created_tuple = true;
    }
    if (!PyTuple_CheckExact(tuple)) {
        return set_ics_exception(exception_argument_error(), "Second argument must be of tuple type!");
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, icsSpyMessage*, int, int)> icsneoTxMessages(lib, "icsneoTxMessages");
        const Py_ssize_t TUPLE_COUNT = PyTuple_Size(tuple);
        icsSpyMessage** msgs = new icsSpyMessage*[static_cast<size_t>(TUPLE_COUNT)]();
        for (int i = 0; i < TUPLE_COUNT; ++i) {
            spy_message_object* _obj = (spy_message_object*)PyTuple_GetItem(tuple, static_cast<Py_ssize_t>(i));
            if (!_obj) {
                if (created_tuple) {
                    Py_XDECREF(tuple);
                }
                delete[] msgs;
                return set_ics_exception(exception_runtime_error(),
                                         "Tuple item must be of " MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME);
            }
            msgs[i] = &(_obj->msg);
        }
        auto gil = PyAllowThreads();
        for (int i = 0; i < TUPLE_COUNT; ++i) {
            if (!icsneoTxMessages(handle, msgs[i], (msgs[i]->NetworkID2 << 8) | msgs[i]->NetworkID, 1)) {
                gil.restore();
                if (created_tuple) {
                    Py_XDECREF(tuple);
                }
                delete[] msgs;
                return set_ics_exception(exception_runtime_error(), "icsneoTxMessages() Failed");
            }
        }
        gil.restore();
        if (created_tuple) {
            Py_XDECREF(tuple);
        }
        delete[] msgs;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_messages(PyObject* self, PyObject* args)
{
    (void)self;
    double timeout = 0.1;
    int use_j1850 = 0;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O|bd:", __FUNCTION__), &obj, &use_j1850, &timeout)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    // Convert timeout to ms
    timeout *= 1000;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int)> icsneoWaitForRxMessagesWithTimeOut(
            lib, "icsneoWaitForRxMessagesWithTimeOut");
        ice::Function<int __stdcall(void*, icsSpyMessage*, int*, int*)> icsneoGetMessages(lib, "icsneoGetMessages");
        int count = 20000;
        int errors = 0;
        union SpyMessage
        {
            icsSpyMessageJ1850 msg_j1850;
            icsSpyMessage msg;
        };
        SpyMessage* msgs = PyMem_New(SpyMessage, count);
        if (!msgs) {
            // This should only happen if we run out of memory (malloc failure)?
            PyErr_Print();
            return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
        }
        auto gil = PyAllowThreads();
        if (timeout == 0 || icsneoWaitForRxMessagesWithTimeOut(handle, (unsigned int)timeout)) {
            if (!icsneoGetMessages(handle, (icsSpyMessage*)msgs, &count, &errors)) {
                gil.restore();
                PyMem_Free(msgs);
                return set_ics_exception(exception_runtime_error(), "icsneoGetMessages() Failed");
            }
        } else {
            count = 0;
        }
        gil.restore();
        PyObject* tuple = PyTuple_New(count);
        for (int i = 0; i < count; ++i) {
            PyObject* _obj = NULL;
            if (use_j1850) {
                _obj = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            } else {
                _obj = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            }
            if (!_obj) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
            }
            if (use_j1850) {
                spy_message_j1850_object* msg = (spy_message_j1850_object*)_obj;
                memcpy(&msg->msg, &msgs[i].msg_j1850, sizeof(msgs[i].msg_j1850));
                // Looks like icsneo40 does its own memory management so don't delete when we dealloc
                msg->noExtraDataPtrCleanup = true;
            } else {
                spy_message_object* msg = (spy_message_object*)_obj;
                memcpy(&msg->msg, &msgs[i].msg, sizeof(msgs[i].msg));
                // Looks like icsneo40 does its own memory management so don't delete when we dealloc
                msg->noExtraDataPtrCleanup = true;
            }
            PyTuple_SetItem(tuple, i, _obj);
        }
        PyObject* result = Py_BuildValue("(O,i)", tuple, errors);
        // We have to decrement the ref counter here because BuildValue increases it and
        // the tuple and its objects will never get freed causing a memory leak.
        Py_XDECREF(tuple);
        PyMem_Del(msgs);
        return result;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_script_status(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }

    unsigned long parameters[255] = { 0 };
    unsigned long parameters_count = 0;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned long*, unsigned long, unsigned long&)>
            icsneoScriptGetScriptStatusEx(lib, "icsneoScriptGetScriptStatusEx");
        auto gil = PyAllowThreads();
        if (!icsneoScriptGetScriptStatusEx(
                handle, parameters, sizeof(parameters) / sizeof(&parameters[0]), parameters_count)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptGetScriptStatusEx() Failed");
        }
        gil.restore();
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    PyObject* list_object = PyList_New(0);
    for (unsigned long i = 0; i < parameters_count; ++i) {
        PyObject* _obj = Py_BuildValue("i", parameters[i]);
        PyList_Append(list_object, _obj);
    }
    return list_object;
}

PyObject* meth_get_error_messages(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    int errors[600] = { 0 };
    int error_count = 600;

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, int*, int*)> icsneoGetErrorMessages(lib, "icsneoGetErrorMessages");
        auto gil = PyAllowThreads();
        if (!icsneoGetErrorMessages(handle, errors, &error_count)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetErrorMessages() Failed");
        }
        gil.restore();
        ice::Function<int __stdcall(int, char*, char*, int*, int*, int*, int*)> icsneoGetErrorInfo(
            lib, "icsneoGetErrorInfo");
        PyObject* list = PyList_New(0);
        for (int i = 0; i < error_count; ++i) {
            char description_short[255] = { 0 };
            char description_long[255] = { 0 };
            int description_short_length = 255;
            int description_long_length = 255;
            int severity = 0, restart_needed = 0;
            auto gil2 = PyAllowThreads();
            if (!icsneoGetErrorInfo(errors[i],
                                    description_short,
                                    description_long,
                                    &description_short_length,
                                    &description_long_length,
                                    &severity,
                                    &restart_needed)) {
                gil2.restore();
                Py_XDECREF(list);
                return set_ics_exception(exception_runtime_error(), "icsneoGetErrorInfo() Failed");
            }
            gil2.restore();
            PyObject* tuple = Py_BuildValue(
                "i, s, s, i, i", errors[i], description_short, description_long, severity, restart_needed);

            PyList_Append(list, tuple);
            Py_XDECREF(tuple);
        }
        return list;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

#ifdef _USE_INTERNAL_HEADER_
PyObject* msg_callback = NULL;
static void message_callback(const char* message, bool success)
{
    // We need to relock the GIL here otherwise we crash
    PyGILState_STATE state = PyGILState_Ensure();
    if (!msg_callback) {
        PySys_WriteStdout("%s\n", message);
    } else if (PyObject_HasAttrString(msg_callback, "message_callback")) {
        PyObject_CallMethod(msg_callback, "message_callback", "s,b", message, success);
    } else {
        PyObject_CallFunction(msg_callback, "s,b", message, success);
    }
    // Unlock the GIL here again...
    PyGILState_Release(state);
}

PyObject* meth_flash_devices(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    PyObject* callback = NULL;
    PyObject* dict;
    int network_id = -1;
    unsigned long iOptions = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OO|Oik:", __FUNCTION__), &obj, &dict, &callback, &network_id, &iOptions)) {
        return NULL;
    }
    if (obj && !PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "First argument must be of PyNeoDeviceEx type");
    }
    if (PyCallable_Check(callback) || PyObject_HasAttrString(callback, "message_callback")) {
        msg_callback = callback;
    } else {
        msg_callback = NULL;
    }
    if (dict && !PyDict_CheckExact(dict)) {
        return set_ics_exception(exception_runtime_error(), "Third argument must be of dictionary type");
    }
    // Populate rc array from the python dictionary
    SReflashChip_t rc[16] = { 0 };
    unsigned long reflash_count = 0;
    Py_ssize_t pos = 0;
    PyObject *key, *value;
    while (PyDict_Next(dict, &pos, &key, &value)) {
        unsigned long id = PyLong_AsUnsignedLong(key);
        char* path = PyUniStr_AsStrOrUTF8(value);
        if (!path) {
            return NULL;
        }
        // Make sure the file exists
        FILE* file;
        if (!(file = fopen(path, "r"))) {
            return set_ics_exception(exception_runtime_error(), "IEF file path is not valid");
        } else {
            fclose(file);
        }
        rc[reflash_count].chipId = id;
        strcpy(rc[reflash_count].path, path);
        reflash_count++;
    }
    // handle network_id if provided, otherwise 0
    OptionsFindNeoEx opts = { 0 };
    opts.CANOptions.iNetworkID = static_cast<unsigned long>(network_id);
    POptionsFindNeoEx popts = NULL;
    if (network_id != -1)
        popts = &opts;
    // If iOptions was provided, use it. Otherwise, fall back to network_id.
    if (iOptions == 0 && network_id != -1) {
        iOptions = opts.CANOptions.iNetworkID;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // Get the NeoDeviceEx from PyNeoDeviceEx
        Py_buffer buffer = {};
        NeoDeviceEx* nde = NULL;
        if (!PyNeoDeviceEx_GetNeoDeviceEx(obj, &buffer, &nde)) {
            PyBuffer_Release(&buffer);
            return NULL;
        }
        ice::Function<int __stdcall(unsigned long,
                                    NeoDevice*,
                                    const SReflashChip_t*,
                                    unsigned long,
                                    unsigned long,
                                    unsigned long,
                                    unsigned long,
                                    void (*MessageCallback)(const char* message, bool success))>
            FlashDevice2(lib, "FlashDevice2");
        auto gil = PyAllowThreads();
        if (!FlashDevice2(0x3835C256, &nde->neoDevice, rc, reflash_count, network_id, iOptions, 0, &message_callback)) {
            gil.restore();
            PyBuffer_Release(&buffer);
            return set_ics_exception(exception_runtime_error(), "FlashDevice2() Failed");
        }
        gil.restore();
        PyBuffer_Release(&buffer);
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}
#endif // _USE_INTERNAL_HEADER_

PyObject* msg_reflash_callback = NULL;
static void message_reflash_callback(const wchar_t* message, unsigned long progress)
{
    // We need to relock the GIL here otherwise we crash
    PyGILState_STATE state = PyGILState_Ensure();
    if (!msg_reflash_callback) {
        PySys_WriteStdout("%ls -%ld\n", message, progress);
    } else if (PyObject_HasAttrString(msg_reflash_callback, "reflash_callback")) {
        PyObject_CallMethod(msg_reflash_callback, "reflash_callback", "u,i", message, progress);
    } else {
        PyObject_CallFunction(msg_reflash_callback, "u,i", message, progress);
    }
    // Unlock the GIL here again...
    PyGILState_Release(state);
}

// void _stdcall icsneoSetReflashCallback( void(*OnReflashUpdate)(const wchar_t*,unsigned long) )
PyObject* meth_set_reflash_callback(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* callback = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("|O:", __FUNCTION__), &callback)) {
        return NULL;
    }
    if (!callback) {
        msg_reflash_callback = NULL;
    } else {
        msg_reflash_callback = callback;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<void __stdcall(void (*)(const wchar_t*, unsigned long))> icsneoSetReflashCallback(
            lib, "icsneoSetReflashCallback");
        auto gil = PyAllowThreads();
        if (callback == Py_None) {
            icsneoSetReflashCallback(NULL);
        } else {
            icsneoSetReflashCallback(&message_reflash_callback);
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_device_settings(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    long device_type_override = -1;
    EPlasmaIonVnetChannel_t vnet_slot = (EPlasmaIonVnetChannel_t)PlasmaIonVnetChannelMain;
    if (!PyArg_ParseTuple(args, arg_parse("O|lk:", __FUNCTION__), &obj, &device_type_override, &vnet_slot)) {
        return NULL;
    }

    // Before we do anything, we need to grab the python s_device_settings ctype.Structure.
    PyObject* settings = _getPythonModuleObject("ics.structures.s_device_settings", "s_device_settings");
    if (!settings) {
        return NULL;
    }
    // Grab the buffer out of the newly created object - make sure to call PyBuffer_Release(&settings_buffer) when done.
    Py_buffer settings_buffer = {};
    PyObject_GetBuffer(settings, &settings_buffer, PyBUF_CONTIG);

    // Verify we have a valid NeoDevice Object - This comes after s_device_settings allocation for testing purposes
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        PyBuffer_Release(&settings_buffer);
        Py_DECREF(settings);
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            PyBuffer_Release(&settings_buffer);
            Py_DECREF(settings);
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // Set/Get the DeviceSettingsType
        auto gil = PyAllowThreads();
        EDeviceSettingsType* setting_type = &((SDeviceSettings*)settings_buffer.buf)->DeviceSettingType;
        if (device_type_override == -1) {
            // int _stdcall icsneoGetDeviceSettingsType(void* hObject, EPlasmaIonVnetChannel_t vnetSlot,
            // EDeviceSettingsType* pDeviceSettingsType)
            ice::Function<int __stdcall(void*, EPlasmaIonVnetChannel_t, EDeviceSettingsType*)>
                icsneoGetDeviceSettingsType(lib, "icsneoGetDeviceSettingsType");
            if (!icsneoGetDeviceSettingsType(handle, vnet_slot, setting_type)) {
                gil.restore();
                PyBuffer_Release(&settings_buffer);
                Py_DECREF(settings);
                return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceSettingsType() Failed");
            }
        }
        // int _stdcall icsneoGetDeviceSettings(void* hObject, SDeviceSettings* pSettings, int iNumBytes,
        // EPlasmaIonVnetChannel_t vnetSlot)
        ice::Function<int __stdcall(void*, SDeviceSettings*, int, EPlasmaIonVnetChannel_t)> icsneoGetDeviceSettings(
            lib, "icsneoGetDeviceSettings");
        if (!icsneoGetDeviceSettings(
                handle, (SDeviceSettings*)settings_buffer.buf, static_cast<int>(settings_buffer.len), vnet_slot)) {
            gil.restore();
            PyBuffer_Release(&settings_buffer);
            Py_DECREF(settings);
            return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceSettings() Failed");
        }
        gil.restore();
        PyBuffer_Release(&settings_buffer);
        return settings;
    } catch (ice::Exception& ex) {
        PyBuffer_Release(&settings_buffer);
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_set_device_settings(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    PyObject* settings = NULL;
    int save_to_eeprom = 1;
    EPlasmaIonVnetChannel_t vnet_slot = PlasmaIonVnetChannelMain;
    if (!PyArg_ParseTuple(args, arg_parse("OO|ik:", __FUNCTION__), &obj, &settings, &save_to_eeprom, &vnet_slot)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoSetDeviceSettings(void* hObject, SDeviceSettings* pSettings, int bSaveToEEPROM,
        // EPlasmaIonVnetChannel_t vnetSlot) int _stdcall icsneoSetDeviceSettings(void* hObject, SDeviceSettings*
        // pSettings, int iNumBytes, int bSaveToEEPROM, EPlasmaIonVnetChannel_t vnetSlot)
        ice::Function<int __stdcall(void*, SDeviceSettings*, int, int, EPlasmaIonVnetChannel_t)>
            icsneoSetDeviceSettings(lib, "icsneoSetDeviceSettings");
        Py_buffer settings_buffer = {};
        PyObject_GetBuffer(settings, &settings_buffer, PyBUF_CONTIG);
        auto gil = PyAllowThreads();
        if (!icsneoSetDeviceSettings(handle,
                                     (SDeviceSettings*)settings_buffer.buf,
                                     static_cast<int>(settings_buffer.len),
                                     save_to_eeprom,
                                     vnet_slot)) {
            gil.restore();
            PyBuffer_Release(&settings_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoSetDeviceSettings() Failed");
        }
        gil.restore();
        PyBuffer_Release(&settings_buffer);
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_load_default_settings(PyObject* self, PyObject* args) // icsneoLoadDefaultSettings
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*)> icsneoLoadDefaultSettings(lib, "icsneoLoadDefaultSettings");
        auto gil = PyAllowThreads();
        if (!icsneoLoadDefaultSettings(handle)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoLoadDefaultSettings() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_read_sdcard(PyObject* self,
                           PyObject* args) // icsneoReadSDCard(int hObject,unsigned long iSectorIndex,unsigned char
                                           // *data, unsigned long *bytesRead)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned long index = 0;
    unsigned long size = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Okk:", __FUNCTION__), &obj, &index, &size)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    // We only read 512 bytes internally, x4 for future compatibility?
    unsigned char data[2048] = { 0 };
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned long, unsigned char*, unsigned long*)> icsneoReadSDCard(
            lib, "icsneoReadSDCard");
        void* handle = NULL;
        if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
            return NULL;
        }
        auto gil = PyAllowThreads();
        if (!icsneoReadSDCard(handle, index, data, &size)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoReadSDCard() Failed");
        }
        gil.restore();
        PyObject* tuple = PyTuple_New(size);
        if (!tuple) {
            return NULL;
        }
        for (unsigned long i = 0; i < size; ++i) {
            PyTuple_SetItem(tuple, i, PyLong_FromLong(data[i]));
        }
        PyObject* byte_array = PyByteArray_FromObject(tuple);
        Py_DECREF(tuple);
        return byte_array;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_write_sdcard(
    PyObject* self,
    PyObject* args) // icsneoWriteSDCard(int hObject,unsigned long iSectorIndex,const unsigned char *data)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned long index = 0;
    PyObject* ba_obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OkO:", __FUNCTION__), &obj, &index, &ba_obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    if (!PyByteArray_CheckExact(ba_obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be a bytearray");
    }
    if (PyByteArray_Size(ba_obj) != 512) {
        return set_ics_exception(exception_runtime_error(), "bytearray must be 512 in length");
    }
    // We only read 512 bytes internally, x4 for future compatibility?
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned long, unsigned char*)> icsneoWriteSDCard(lib, "icsneoWriteSDCard");
        void* handle = NULL;
        if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
            return NULL;
        }
        auto gil = PyAllowThreads();
        if (!icsneoWriteSDCard(handle, index, (unsigned char*)PyByteArray_AsString(ba_obj))) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoWriteSDCard() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_create_neovi_radio_message(PyObject* self, PyObject* args, PyObject* keywords)
{
    (void)self;
    int relay1 = 0;
    int relay2 = 0;
    int relay3 = 0;
    int relay4 = 0;
    int relay5 = 0;
    int led5 = 0;
    int led6 = 0;
    int msb = 0;
    int lsb = 0;
    int analog = 0;
    int relay_timeout = 0;
#if (PY_MAJOR_VERSION) >= 3 && (PY_MINOR_VERSION >= 13)
    const
#endif
        char* kwords[] = { "Relay1",       "Relay2", "Relay3",          "Relay4",          "Relay5",
                           "LED5",         "LED6",   "MSB_report_rate", "LSB_report_rate", "analog_change_report_rate",
                           "relay_timeout" };
    // Accepts keywords: Relay1-Relay5 (boolean), LED5 (boolean), LED6 (boolean), MSB_report_rate (int),
    // LSB_report_rate (int), analog_change_report_rate (int), relay_timeout (int).
    if (!PyArg_ParseTupleAndKeywords(args,
                                     keywords,
                                     arg_parse("|bbbbbbbiiii:", __FUNCTION__),
                                     kwords,
                                     &relay1,
                                     &relay2,
                                     &relay3,
                                     &relay4,
                                     &relay5,
                                     &led5,
                                     &led6,
                                     &msb,
                                     &lsb,
                                     &analog,
                                     &relay_timeout)) {
        return NULL;
    }
    int byte1 = 0;
    byte1 |= (relay1 ? 1 : 0) << 6;
    byte1 |= (relay2 ? 1 : 0) << 5;
    byte1 |= (relay3 ? 1 : 0) << 4;
    byte1 |= (relay4 ? 1 : 0) << 3;
    byte1 |= (relay5 ? 1 : 0) << 2;
    byte1 |= (led5 ? 1 : 0) << 1;
    byte1 |= (led6 ? 1 : 0) << 0;
    int byte2 = msb & 0xFF;
    int byte3 = lsb & 0xFF;
    int byte4 = analog & 0xFF;
    int byte5 = relay_timeout & 0xFF;
    return Py_BuildValue("(i,i,i,i,i)", byte1, byte2, byte3, byte4, byte5);
}

PyObject* meth_coremini_start_fblock(PyObject* self, PyObject* args)
{
    (void)self;
    unsigned int index;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &index)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int)> icsneoScriptStartFBlock(lib, "icsneoScriptStartFBlock");
        auto gil = PyAllowThreads();
        if (!icsneoScriptStartFBlock(handle, index)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStartFBlock() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_stop_fblock(PyObject* self, PyObject* args)
{
    (void)self;
    unsigned int index;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &index)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int)> icsneoScriptStopFBlock(lib, "icsneoScriptStopFBlock");
        auto gil = PyAllowThreads();
        if (!icsneoScriptStopFBlock(handle, index)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStopFBlock() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_get_fblock_status(PyObject* self, PyObject* args)
{
    (void)self;
    unsigned int index;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &index)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int, int*)> icsneoScriptGetFBlockStatus(
            lib, "icsneoScriptGetFBlockStatus");
        int status = 0;
        auto gil = PyAllowThreads();
        if (!icsneoScriptGetFBlockStatus(handle, index, &status)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptGetFBlockStatus() Failed");
        }
        gil.restore();
        return Py_BuildValue("b", status == 1);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_read_app_signal(PyObject* self, PyObject* args) // ScriptReadAppSignal
{
    (void)self;
    unsigned int index;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &index)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int, double*)> icsneoScriptReadAppSignal(
            lib, "icsneoScriptReadAppSignal");
        double value = 0;
        auto gil = PyAllowThreads();
        if (!icsneoScriptReadAppSignal(handle, index, &value)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptReadAppSignal() Failed");
        }
        gil.restore();
        return Py_BuildValue("d", value);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_write_app_signal(PyObject* self, PyObject* args) // ScriptWriteAppSignal
{
    (void)self;
    unsigned int index;
    PyObject* obj = NULL;
    double value = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OId:", __FUNCTION__), &obj, &index, &value)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int, double)> icsneoScriptWriteAppSignal(
            lib, "icsneoScriptWriteAppSignal");
        auto gil = PyAllowThreads();
        if (!icsneoScriptWriteAppSignal(handle, index, value)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptWriteAppSignal() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_read_tx_message(PyObject* self, PyObject* args) // ScriptReadTxMessage
{
    (void)self;
    unsigned int index;
    PyObject* obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OI|b:", __FUNCTION__), &obj, &index, &j1850)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int, void*)> icsneoScriptReadTxMessage(lib,
                                                                                           "icsneoScriptReadTxMessage");
        PyObject* msg = NULL;
        if (j1850) {
            msg = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            if (!msg) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(),
                                         "Failed to allocate " SPY_MESSAGE_J1850_OBJECT_NAME);
            }
            auto gil = PyAllowThreads();
            if (!icsneoScriptReadTxMessage(handle, index, &PySpyMessageJ1850_GetObject(msg)->msg)) {
                gil.restore();
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadTxMessage() Failed");
            }
            gil.restore();
        } else {
            msg = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            if (!msg) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
            }
            auto gil = PyAllowThreads();
            if (!icsneoScriptReadTxMessage(handle, index, &PySpyMessage_GetObject(msg)->msg)) {
                gil.restore();
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadTxMessage() Failed");
            }
            gil.restore();
        }
        return msg;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_read_rx_message(PyObject* self, PyObject* args) // ScriptReadRxMessage
{
    (void)self;
    unsigned int index;
    PyObject* obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OI|b:", __FUNCTION__), &obj, &index, &j1850)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int, void*, void*)> icsneoScriptReadRxMessage(
            lib, "icsneoScriptReadRxMessage");
        PyObject* msg = NULL;
        PyObject* msg_mask = NULL;
        if (j1850) {
            msg = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            if (!msg) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(),
                                         "Failed to allocate " SPY_MESSAGE_J1850_OBJECT_NAME);
            }
            msg_mask = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            if (!msg_mask) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(),
                                         "Failed to allocate " SPY_MESSAGE_J1850_OBJECT_NAME);
            }
            auto gil = PyAllowThreads();
            if (!icsneoScriptReadRxMessage(handle,
                                           index,
                                           &PySpyMessageJ1850_GetObject(msg_mask)->msg,
                                           &PySpyMessageJ1850_GetObject(msg_mask)->msg)) {
                gil.restore();
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadRxMessage() Failed");
            }
            gil.restore();
        } else {
            msg = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            if (!msg) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
            }
            msg_mask = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            if (!msg_mask) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
            }
            auto gil = PyAllowThreads();
            if (!icsneoScriptReadRxMessage(
                    handle, index, &PySpyMessage_GetObject(msg)->msg, &PySpyMessage_GetObject(msg_mask)->msg)) {
                gil.restore();
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadRxMessage() Failed");
            }
            gil.restore();
        }
        return Py_BuildValue("(O,O)", msg, msg_mask);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_write_tx_message(PyObject* self, PyObject* args) // icsneoScriptWriteTxMessage
{
    (void)self;
    unsigned int index;
    PyObject* obj = NULL;
    PyObject* msg_obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OIO|b:", __FUNCTION__), &obj, &index, &msg_obj, &j1850)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    void* msg = NULL;
    if (j1850) {
        // We are going to use icsSpyMessageJ1850 objects here.
        if (!PySpyMessageJ1850_CheckExact(msg_obj)) {
            return set_ics_exception(exception_runtime_error(),
                                     "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_J1850_OBJECT_NAME);
        }
        msg = (void*)&PySpyMessageJ1850_GetObject(msg_obj)->msg;
    } else {
        // We are going to use icsSpyMessage objects here.
        if (!PySpyMessage_CheckExact(msg_obj)) {
            return set_ics_exception(exception_runtime_error(),
                                     "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME);
        }
        msg = (void*)&PySpyMessage_GetObject(msg_obj)->msg;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int, void*)> icsneoScriptWriteTxMessage(
            lib, "icsneoScriptWriteTxMessage");
        auto gil = PyAllowThreads();
        if (!icsneoScriptWriteTxMessage(handle, index, msg)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptWriteTxMessage() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_coremini_write_rx_message(PyObject* self, PyObject* args) // icsneoScriptWriteRxMessage
{
    (void)self;
    unsigned int index;
    PyObject* obj = NULL;
    PyObject* msg_obj = NULL;
    PyObject* msg_mask_obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OIOO|b:", __FUNCTION__), &obj, &index, &msg_obj, &msg_mask_obj, &j1850)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    void* msg = NULL;
    void* msg_mask = NULL;
    if (j1850) {
        // We are going to use icsSpyMessageJ1850 objects here.
        if (!PySpyMessageJ1850_CheckExact(msg_obj)) {
            return set_ics_exception(exception_runtime_error(),
                                     "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_J1850_OBJECT_NAME);
        }
        msg = (void*)&PySpyMessageJ1850_GetObject(msg_obj)->msg;
        if (!PySpyMessageJ1850_CheckExact(msg_mask_obj)) {
            msg_mask = (void*)new icsSpyMessageJ1850();
            memset(msg_mask, 0, sizeof(icsSpyMessageJ1850));
        } else {
            msg_mask = (void*)&PySpyMessageJ1850_GetObject(msg_mask_obj)->msg;
        }
    } else {
        // We are going to use icsSpyMessage objects here.
        if (!PySpyMessage_CheckExact(msg_obj)) {
            return set_ics_exception(exception_runtime_error(),
                                     "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME);
        }
        msg = (void*)&PySpyMessage_GetObject(msg_obj)->msg;
        if (!PySpyMessage_CheckExact(msg_mask_obj)) {
            msg_mask = (void*)new icsSpyMessage();
            memset(msg_mask, 0, sizeof(icsSpyMessage));
        } else {
            msg_mask = (void*)&PySpyMessage_GetObject(msg_mask_obj)->msg;
        }
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int, void*, void*)> icsneoScriptWriteRxMessage(
            lib, "icsneoScriptWriteRxMessage");
        if (!icsneoScriptWriteRxMessage(handle, index, msg, msg_mask)) {
            return set_ics_exception(exception_runtime_error(), "icsneoScriptWriteRxMessage() Failed");
        }
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_performance_parameters(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, int*, int*, int*, int*, int*, int*, int*, int*)>
            icsneoGetPerformanceParameters(lib, "icsneoGetPerformanceParameters");
        int buffer_count = 0;
        int buffer_max = 0;
        int overflow_count = 0;
        int reserved1 = 0;
        int reserved2 = 0;
        int reserved3 = 0;
        int reserved4 = 0;
        int reserved5 = 0;
        auto gil = PyAllowThreads();
        if (!icsneoGetPerformanceParameters(handle,
                                            &buffer_count,
                                            &buffer_max,
                                            &overflow_count,
                                            &reserved1,
                                            &reserved2,
                                            &reserved3,
                                            &reserved4,
                                            &reserved5)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetPerformanceParameters() Failed");
        }
        gil.restore();
        return Py_BuildValue("(i,i,i,i,i,i,i,i)",
                             buffer_count,
                             buffer_max,
                             overflow_count,
                             reserved1,
                             reserved2,
                             reserved3,
                             reserved4,
                             reserved5);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_validate_hobject(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyLong_CheckExact(obj) && !PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx"
                                 " or Integer");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*)> icsneoValidateHObject(lib, "icsneoValidateHObject");
        auto gil = PyAllowThreads();
        if (!icsneoValidateHObject(handle)) {
            gil.restore();
            return Py_BuildValue("b", false);
        }
        gil.restore();
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_last_api_error(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned long*)> icsneoGetLastAPIError(lib, "icsneoGetLastAPIError");
        ice::Function<int __stdcall(unsigned long, char*, char*, int*, int*, int*, int*)> icsneoGetErrorInfo(
            lib, "icsneoGetErrorInfo");
        unsigned long error = 0;
        auto gil = PyAllowThreads();
        if (!icsneoGetLastAPIError(handle, &error)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetLastAPIError() Failed");
        }
        gil.restore();
        char description_short[255] = { 0 };
        char description_long[255] = { 0 };
        int description_short_length = 255;
        int description_long_length = 255;
        int severity = 0, restart_needed = 0;
        if (!icsneoGetErrorInfo(error,
                                description_short,
                                description_long,
                                &description_short_length,
                                &description_long_length,
                                &severity,
                                &restart_needed)) {
            return set_ics_exception(exception_runtime_error(), "icsneoGetErrorInfo() Failed");
        }
        return Py_BuildValue("k, s, s, i, i", error, description_short, description_long, severity, restart_needed);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_dll_version(PyObject* self, PyObject* args)
{
    (void)self;
    (void)args;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall()> icsneoGetDLLVersion(lib, "icsneoGetDLLVersion");
        int result = 0;
        auto gil = PyAllowThreads();
        result = icsneoGetDLLVersion();
        gil.restore();
        return Py_BuildValue("i", result);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_serial_number(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int*)> icsneoGetSerialNumber(lib, "icsneoGetSerialNumber");
        unsigned int serial = 0;
        auto gil = PyAllowThreads();
        if (!icsneoGetSerialNumber(handle, &serial)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetSerialNumber() Failed");
        }
        gil.restore();
        return Py_BuildValue("i", serial);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_hw_firmware_info(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, stAPIFirmwareInfo*)> icsneoGetHWFirmwareInfo(lib, "icsneoGetHWFirmwareInfo");
        PyObject* info = _getPythonModuleObject("ics.structures.st_api_firmware_info", "st_api_firmware_info");
        if (!info) {
            return NULL;
        }
        Py_buffer info_buffer = {};
        PyObject_GetBuffer(info, &info_buffer, PyBUF_CONTIG);

        auto gil = PyAllowThreads();
        if (!icsneoGetHWFirmwareInfo(handle, (stAPIFirmwareInfo*)info_buffer.buf)) {
            gil.restore();
            PyBuffer_Release(&info_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoGetHWFirmwareInfo() Failed");
        }
        gil.restore();
        return info;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_base36enc(PyObject* self, PyObject* args)
{
    (void)self;
    unsigned long long value = 0;
    if (!PyArg_ParseTuple(args, arg_parse("K:", __FUNCTION__), &value)) {
        return NULL;
    }
    constexpr char base36[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    /* log(2**64) / log(36) = 12.38 => max 13 char + '\0' */
    char buffer[100];
    unsigned int offset = sizeof(buffer);

    buffer[--offset] = '\0';
    do {
        buffer[--offset] = base36[value % 36];
    } while (value /= 36);
    return Py_BuildValue("s", &buffer[offset]);
}

PyObject* meth_request_enter_sleep_mode(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned int timeout_ms = 0;
    unsigned int mode = 0;
    unsigned int reserved = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oii|i:", __FUNCTION__), &obj, &timeout_ms, &mode, &reserved)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int, unsigned int, unsigned int)> icsneoRequestEnterSleepMode(
            lib, "icsneoRequestEnterSleepMode");
        auto gil = PyAllowThreads();
        if (!icsneoRequestEnterSleepMode(handle, timeout_ms, mode, reserved)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoRequestEnterSleepMode() Failed");
        }
        gil.restore();
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_set_context(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_CheckExact(obj) && obj != Py_None && obj != Py_False &&
        !(PyLong_Check(obj) && PyLong_AsLong(obj) == 0)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx, or False");
    }
    // Set 'handle' to NULL if 'obj' is None, False, or a zero-valued integer.
    // Otherwise, attempt to retrieve the handle using 'PyNeoDeviceEx_GetHandle'.
    // If handle retrieval fails, raise a runtime error exception.
    if (obj == Py_None || obj == Py_False || (PyLong_Check(obj) && PyLong_AsLong(obj) == 0)) {
        handle = NULL;
    } else {
        if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
            return set_ics_exception(exception_runtime_error(), "Failed to retrieve handle.");
        }
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*)> icsneoSetContext(lib, "icsneoSetContext");
        auto gil = PyAllowThreads();
        if (!icsneoSetContext(handle)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoSetContext() Failed");
        }
        gil.restore();
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_force_firmware_update(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj) && !PyLong_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*)> icsneoForceFirmwareUpdate(lib, "icsneoForceFirmwareUpdate");
        auto gil = PyAllowThreads();
        if (!icsneoForceFirmwareUpdate(handle)) {
            gil.restore();
            return Py_BuildValue("b", false);
        }
        gil.restore();
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_firmware_update_required(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj) && !PyLong_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*)> icsneoFirmwareUpdateRequired(lib, "icsneoFirmwareUpdateRequired");
        auto gil = PyAllowThreads();
        if (!icsneoFirmwareUpdateRequired(handle)) {
            gil.restore();
            return Py_BuildValue("b", false);
        }
        gil.restore();
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_dll_firmware_info(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, stAPIFirmwareInfo*)> icsneoGetDLLFirmwareInfo(lib,
                                                                                         "icsneoGetDLLFirmwareInfo");
        PyObject* info = _getPythonModuleObject("ics.structures.st_api_firmware_info", "st_api_firmware_info");
        if (!info) {
            return NULL;
        }
        Py_buffer info_buffer = {};
        PyObject_GetBuffer(info, &info_buffer, PyBUF_CONTIG);
        auto gil = PyAllowThreads();
        if (!icsneoGetDLLFirmwareInfo(handle, (stAPIFirmwareInfo*)info_buffer.buf)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetDLLFirmwareInfo() Failed");
        }
        gil.restore();
        return info;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_backup_power_enabled(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned int enabled = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int&)> icsneoGetBackupPowerEnabled(lib,
                                                                                       "icsneoGetBackupPowerEnabled");
        auto gil = PyAllowThreads();
        if (!icsneoGetBackupPowerEnabled(handle, enabled)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetBackupPowerEnabled() Failed");
        }
        gil.restore();
        return Py_BuildValue("b", enabled);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_set_backup_power_enabled(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned int enabled = 1;
    if (!PyArg_ParseTuple(args, arg_parse("O|b:", __FUNCTION__), &obj, &enabled)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int)> icsneoSetBackupPowerEnabled(lib,
                                                                                      "icsneoSetBackupPowerEnabled");
        auto gil = PyAllowThreads();
        if (!icsneoSetBackupPowerEnabled(handle, enabled)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoSetBackupPowerEnabled() Failed");
        }
        gil.restore();
        return Py_BuildValue("b", enabled);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_backup_power_ready(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned int enabled = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int&)> icsneoGetBackupPowerReady(lib, "icsneoGetBackupPowerReady");
        auto gil = PyAllowThreads();
        if (!icsneoGetBackupPowerReady(handle, enabled)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetBackupPowerReady() Failed");
        }
        gil.restore();
        return Py_BuildValue("b", enabled);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

// icsneoScriptLoadReadBin
PyObject* meth_load_readbin(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* arg_data = NULL;
    int location;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OOi:", __FUNCTION__), &obj, &arg_data, &location)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    long fsize;
    unsigned char* data = NULL;
    int data_size = 0;
#if PY_MAJOR_VERSION >= 3
    if (PyUnicode_CheckExact(arg_data)) {
        char* file_name = PyUniStr_AsStrOrUTF8(arg_data);
#else
    if (PyString_Check(arg_data)) {
        char* file_name = PyUniStr_AsStrOrUTF8(arg_data);
#endif
        if (!file_name) {
            return set_ics_exception(exception_runtime_error(), "Failed to convert file path to string");
        }
        FILE* f;
        f = fopen(file_name, "rb");
        if (!f) {
            std::stringstream ss;
            ss << "Failed to open Readbin: '" << file_name << "'. Please make sure path exists";
            return set_ics_exception(exception_runtime_error(), (char*)ss.str().c_str());
        }
        fseek(f, 0, SEEK_END);
        fsize = ftell(f);
        rewind(f);
        data = (unsigned char*)malloc(sizeof(char) * fsize);
        data_size = (int)fread(data, 1, static_cast<size_t>(fsize), f);
        fclose(f);
        if (fsize != data_size) {
            return set_ics_exception(exception_runtime_error(), "Readbin file size mismatch");
        }
    } else if (PyTuple_CheckExact(arg_data)) {
        Py_ssize_t tuple_size = PyTuple_Size(arg_data);
        data = (unsigned char*)malloc(sizeof(char) * tuple_size);
        // Move tuple data into array
        for (int i = 0; i < tuple_size; ++i) {
            PyObject* value = PyTuple_GET_ITEM(arg_data, i);
            if (!PyLong_CheckExact(value)) {
                return set_ics_exception(exception_runtime_error(),
                                         "Failed to convert tuple data. Tuple data must be integer type");
            }
            data[i] = (unsigned char)PyLong_AsLong(PyTuple_GET_ITEM(arg_data, i));
        }
        fsize = static_cast<long>(tuple_size);
        data_size = fsize;
    } else {
        return set_ics_exception(exception_runtime_error(), "Argument must be filepath or tuple");
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, const unsigned char*, unsigned long, int)> icsneoScriptLoadReadBin(
            lib, "icsneoScriptLoadReadBin");
        auto gil = PyAllowThreads();
        if (!icsneoScriptLoadReadBin(handle, data, static_cast<unsigned long>(data_size), location)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoScriptLoadReadBin() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

// void* hObject, unsigned long ulNetworkID, stCM_ISO157652_TxMessage *pMsg, unsigned long ulBlockingTimeout)
PyObject* meth_iso15765_transmit_message(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned long ulNetworkID = 0;
    PyObject* obj_tx_msg = NULL;
    unsigned long ulBlockingTimeout = 0;
    if (!PyArg_ParseTuple(
            args, arg_parse("OkOk:", __FUNCTION__), &obj, &ulNetworkID, &obj_tx_msg, &ulBlockingTimeout)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    if (_isPythonModuleObject_IsInstance(
            obj_tx_msg, "ics.structures.st_cm_iso157652_tx_message", "st_cm_iso157652_tx_message") != 1) {
        return NULL;
    }
    Py_buffer obj_tx_msg_buffer = {};
    PyObject_GetBuffer(obj_tx_msg, &obj_tx_msg_buffer, PyBUF_CONTIG);

    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned long, stCM_ISO157652_TxMessage*, unsigned long)>
            icsneoISO15765_TransmitMessage(lib, "icsneoISO15765_TransmitMessage");
        auto gil = PyAllowThreads();
        if (!icsneoISO15765_TransmitMessage(
                handle, ulNetworkID, (stCM_ISO157652_TxMessage*)obj_tx_msg_buffer.buf, ulBlockingTimeout)) {
            gil.restore();
            PyBuffer_Release(&obj_tx_msg_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_TransmitMessage() Failed");
        }
        gil.restore();
        PyBuffer_Release(&obj_tx_msg_buffer);
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_iso15765_receive_message(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    PyObject* obj_rx_msg = NULL;
    unsigned int iIndex = 0;
    // PyObject* obj_rx_msg = PyObject_CallObject((PyObject*)&cm_iso157652_rx_message_object_type, NULL);
    if (!PyArg_ParseTuple(args, arg_parse("OiO:", __FUNCTION__), &obj, &iIndex, &obj_rx_msg)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    if (_isPythonModuleObject_IsInstance(
            obj_rx_msg, "ics.structures.st_cm_iso157652_rx_message", "st_cm_iso157652_rx_message") != 1) {
        return NULL;
    }
    Py_buffer obj_rx_msg_buffer = {};
    PyObject_GetBuffer(obj_rx_msg, &obj_rx_msg_buffer, PyBUF_CONTIG);

    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            PyBuffer_Release(&obj_rx_msg_buffer);
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // stCM_ISO157652_RxMessage rx_msg_temp = {0};
        // memcpy(&rx_msg_temp, &(temp->s), sizeof(temp->s));
        ice::Function<int __stdcall(void*, unsigned int, stCM_ISO157652_RxMessage*)> icsneoISO15765_ReceiveMessage(
            lib, "icsneoISO15765_ReceiveMessage");
        auto gil = PyAllowThreads();
        if (!icsneoISO15765_ReceiveMessage(handle, iIndex, (stCM_ISO157652_RxMessage*)obj_rx_msg_buffer.buf)) {
            gil.restore();
            PyBuffer_Release(&obj_rx_msg_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_ReceiveMessage() Failed");
        }
        gil.restore();
        PyBuffer_Release(&obj_rx_msg_buffer);
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        PyBuffer_Release(&obj_rx_msg_buffer);
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_iso15765_enable_networks(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned long networks = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Ok:", __FUNCTION__), &obj, &networks)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned long)> icsneoISO15765_EnableNetworks(
            lib, "icsneoISO15765_EnableNetworks");
        auto gil = PyAllowThreads();
        if (!icsneoISO15765_EnableNetworks(handle, networks)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_EnableNetworks() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_iso15765_disable_networks(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*)> icsneoISO15765_DisableNetworks(lib, "icsneoISO15765_DisableNetworks");
        auto gil = PyAllowThreads();
        if (!icsneoISO15765_DisableNetworks(handle)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_DisableNetworks() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_active_vnet_channel(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned long channel = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned long*)> icsneoGetActiveVNETChannel(lib,
                                                                                       "icsneoGetActiveVNETChannel");
        auto gil = PyAllowThreads();
        if (!icsneoGetActiveVNETChannel(handle, &channel)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetActiveVNETChannel() Failed");
        }
        gil.restore();
        return Py_BuildValue("i", channel);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_set_active_vnet_channel(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned long channel = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Ok:", __FUNCTION__), &obj, &channel)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned long)> icsneoSetActiveVNETChannel(lib,
                                                                                      "icsneoSetActiveVNETChannel");
        auto gil = PyAllowThreads();
        if (!icsneoSetActiveVNETChannel(handle, channel)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoSetActiveVNETChannel() Failed");
        }
        gil.restore();
        return Py_BuildValue("i", channel);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_set_bit_rate(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    int bitrate = 0;
    int net_id = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oii:", __FUNCTION__), &obj, &bitrate, &net_id)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, int, int)> icsneoSetBitRate(lib, "icsneoSetBitRate");
        auto gil = PyAllowThreads();
        if (!icsneoSetBitRate(handle, bitrate, net_id)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoSetBitRate() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_set_fd_bit_rate(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    int bitrate = 0;
    int net_id = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oii:", __FUNCTION__), &obj, &bitrate, &net_id)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, int, int)> icsneoSetFDBitRate(lib, "icsneoSetFDBitRate");
        auto gil = PyAllowThreads();
        if (!icsneoSetFDBitRate(handle, bitrate, net_id)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoSetFDBitRate() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_set_bit_rate_ex(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned long bitrate = 0;
    int net_id = 0;
    int options = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Okii:", __FUNCTION__), &obj, &bitrate, &net_id, &options)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned long, int, int)> icsneoSetBitRateEx(lib, "icsneoSetBitRateEx");
        auto gil = PyAllowThreads();
        if (!icsneoSetBitRateEx(handle, bitrate, net_id, options)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoSetBitRateEx() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_timestamp_for_msg(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    PyObject* obj_msg = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OO:", __FUNCTION__), &obj, &obj_msg)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    if (!PySpyMessage_CheckExact(obj_msg) && !PySpyMessageJ1850_CheckExact(obj_msg)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME);
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    icsSpyMessage* msg = &PySpyMessage_GetObject(obj_msg)->msg;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, icsSpyMessage*, double*)> icsneoGetTimeStampForMsg(
            lib, "icsneoGetTimeStampForMsg");
        double timestamp = 0;
        auto gil = PyAllowThreads();
        if (!icsneoGetTimeStampForMsg(handle, msg, &timestamp)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetTimeStampForMsg() Failed");
        }
        gil.restore();
        return Py_BuildValue("d", timestamp);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_device_status(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    int throw_exception_on_size_mismatch = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O|b:", __FUNCTION__), &obj, &throw_exception_on_size_mismatch)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        PyObject* device_status = _getPythonModuleObject("ics.structures.ics_device_status", "ics_device_status");
        if (!device_status) {
            return NULL;
        }
        Py_buffer device_status_buffer = {};
        PyObject_GetBuffer(device_status, &device_status_buffer, PyBUF_CONTIG);

        size_t device_status_size = static_cast<size_t>(device_status_buffer.len);
        ice::Function<int __stdcall(void*, icsDeviceStatus*, size_t*)> icsneoGetDeviceStatus(lib,
                                                                                             "icsneoGetDeviceStatus");
        auto gil = PyAllowThreads();
        if (!icsneoGetDeviceStatus(handle, (icsDeviceStatus*)device_status_buffer.buf, &device_status_size)) {
            gil.restore();
            PyBuffer_Release(&device_status_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceStatus() Failed");
        }
        if (throw_exception_on_size_mismatch) {
            if (device_status_size != (size_t)device_status_buffer.len) {
                gil.restore();
                PyBuffer_Release(&device_status_buffer);
                return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceStatus() API mismatch detected!");
            }
        }
        gil.restore();
        return device_status;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_enable_network_com(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    bool enable = true;
    long net_id = -1;
    if (!PyArg_ParseTuple(args, arg_parse("O|bk:", __FUNCTION__), &obj, &enable, &net_id)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoEnableNetworkCom(void* hObject, int iEnable)
        // int _stdcall icsneoEnableNetworkComEx(void* hObject, int iEnable, int iNetId)
        ice::Function<int __stdcall(void*, int)> icsneoEnableNetworkCom(lib, "icsneoEnableNetworkCom");
        ice::Function<int __stdcall(void*, int, int)> icsneoEnableNetworkComEx(lib, "icsneoEnableNetworkComEx");
        auto gil = PyAllowThreads();
        if (net_id == -1) {
            if (!icsneoEnableNetworkCom(handle, enable)) {
                gil.restore();
                return set_ics_exception(exception_runtime_error(), "icsneoEnableNetworkCom() Failed");
            }
        } else {
            if (!icsneoEnableNetworkComEx(handle, enable, net_id)) {
                gil.restore();
                return set_ics_exception(exception_runtime_error(), "icsneoEnableNetworkComEx() Failed");
            }
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_enable_bus_voltage_monitor(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned int enable = 1;
    unsigned int reserved = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O|ii:", __FUNCTION__), &obj, &enable, &reserved)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoEnableBusVoltageMonitor(void* hObject, unsigned int enable, unsigned int reserved)
        ice::Function<int __stdcall(void*, unsigned int, unsigned int)> icsneoEnableBusVoltageMonitor(
            lib, "icsneoEnableBusVoltageMonitor");
        auto gil = PyAllowThreads();
        if (!icsneoEnableBusVoltageMonitor(handle, enable, reserved)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoEnableBusVoltageMonitor() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_bus_voltage(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned int reserved = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O|i:", __FUNCTION__), &obj, &reserved)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        unsigned long mV = 0;
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoGetBusVoltage(void* hObject, unsigned long* pVBusVoltage, unsigned int reserved
        ice::Function<int __stdcall(void*, unsigned long*, unsigned int)> icsneoGetBusVoltage(lib,
                                                                                              "icsneoGetBusVoltage");
        auto gil = PyAllowThreads();
        if (!icsneoGetBusVoltage(handle, &mV, reserved)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetBusVoltage() Failed");
        }
        gil.restore();
        return Py_BuildValue("i", mV);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_read_jupiter_firmware(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    size_t fileSize = 0;
    EPlasmaIonVnetChannel_t channel = PlasmaIonVnetChannelMain;
    if (!PyArg_ParseTuple(args, arg_parse("Oi|i:", __FUNCTION__), &obj, &fileSize, &channel)) {
        return NULL;
    }

    // Create the ByteArray
    PyObject* ba = PyObject_CallObject((PyObject*)&PyByteArray_Type, NULL);
    if (!ba) {
        return NULL;
    }
    // Resize the ByteArray
    int ret_val = PyByteArray_Resize(ba, static_cast<Py_ssize_t>(fileSize));
    (void)ret_val;
    // TODO: Documentation doesn't say what return value is.

    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int __stdcall icsneoReadJupiterFirmware(void* hObject, char* fileData, size_t* fileDataSize,
        // EPlasmaIonVnetChannel_t channel)
        ice::Function<int __stdcall(void*, char*, size_t*, EPlasmaIonVnetChannel_t)> icsneoReadJupiterFirmware(
            lib, "icsneoReadJupiterFirmware");

        // Grab the ByteArray Buffer Object
        Py_buffer ba_buffer = {};
        PyObject_GetBuffer(ba, &ba_buffer, PyBUF_CONTIG);

        auto gil = PyAllowThreads();
        if (!icsneoReadJupiterFirmware(handle, (char*)ba_buffer.buf, &fileSize, channel)) {

            gil.restore();
            PyBuffer_Release(&ba_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoReadJupiterFirmware() Failed");
        }
        gil.restore();
        PyBuffer_Release(&ba_buffer);
        return Py_BuildValue("Oi", ba, fileSize);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_write_jupiter_firmware(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    PyObject* bytes_obj = NULL;
    EPlasmaIonVnetChannel_t channel = PlasmaIonVnetChannelMain;
    if (!PyArg_ParseTuple(args, arg_parse("OO|i:", __FUNCTION__), &obj, &bytes_obj, &channel)) {
        return NULL;
    }
    if (!PyBytes_CheckExact(bytes_obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of Bytes type ");
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int __stdcall icsneoWriteJupiterFirmware(void* hObject, char* fileData, size_t fileDataSize,
        // EPlasmaIonVnetChannel_t channel)
        ice::Function<int __stdcall(void*, char*, size_t, EPlasmaIonVnetChannel_t)> icsneoWriteJupiterFirmware(
            lib, "icsneoWriteJupiterFirmware");

        // Convert the object to a bytes object
        PyObject* bytes = PyBytes_FromObject(bytes_obj);
        // Grab the byte size
        Py_ssize_t bsize = PyBytes_Size(bytes);
        // Grab the data out of the bytes
        char* bytes_str = PyBytes_AsString(bytes);
        if (!bytes_str) {
            return NULL;
        }

        auto gil = PyAllowThreads();
        // if (!icsneoWriteJupiterFirmware(handle, (char*)bytes_buffer.buf, bytes_buffer.len, channel)) {
        if (!icsneoWriteJupiterFirmware(handle, bytes_str, static_cast<size_t>(bsize), channel)) {
            gil.restore();
            Py_DECREF(bytes);
            // PyBuffer_Release(&bytes_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoWriteJupiterFirmware() Failed");
        }
        gil.restore();
        Py_DECREF(bytes);
        // PyBuffer_Release(&bytes_buffer);
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_flash_accessory_firmware(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    PyObject* parms = NULL;
    bool check_success = true;
    if (!PyArg_ParseTuple(args, arg_parse("OO|b:", __FUNCTION__), &obj, &parms, &check_success)) {
        return NULL;
    }

    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }

    try {

        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        int function_error = (int)AccessoryOperationError;
        // int __stdcall icsneoFlashAccessoryFirmware(void* hObject, FlashAccessoryFirmwareParams* param, int*
        // errorCode)
        // int __stdcall icsneoFlashPhyFirmware(void* hObject, unsigned char phyIndx, unsigned char* fileData, size_t
        // fileDataSize, int* errorCode)
        ice::Function<int __stdcall(void*, FlashAccessoryFirmwareParams*, int*)> icsneoFlashAccessoryFirmware(
            lib, "icsneoFlashAccessoryFirmware");

        Py_buffer parms_buffer = {};
        PyObject_GetBuffer(parms, &parms_buffer, PyBUF_CONTIG_RO);

        auto gil = PyAllowThreads();
        if (!icsneoFlashAccessoryFirmware(handle, (FlashAccessoryFirmwareParams*)parms_buffer.buf, &function_error)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoFlashAccessoryFirmware() Failed");
        }
        // check the return value to make sure we are good
        if (check_success && function_error != AccessoryOperationSuccess) {
            std::stringstream ss;
            ss << "icsneoFlashAccessoryFirmware() Failed with error code: " << function_error << " (";
            switch (function_error) {
                case AccessoryOperationError:
                    ss << "AccessoryOperationError";
                    break;
                case AccessoryOperationSuccess:
                    ss << "AccessoryOperationSuccess";
                    break;
                case AccessoryFlashingInitError:
                    ss << "AccessoryFlashingInitError";
                    break;
                case AccessoryFlashingEraseError:
                    ss << "AccessoryFlashingEraseError";
                    break;
                case AccessoryFlashingWriteError:
                    ss << "AccessoryFlashingWriteError";
                    break;
                case AccessoryFlashingReadError:
                    ss << "AccessoryFlashingReadError";
                    break;
                case AccessoryFlashingVerifyError:
                    ss << "AccessoryFlashingVerifyError";
                    break;
                case AccessoryFlashingDeinitError:
                    ss << "AccessoryFlashingDeinitError";
                    break;
                case AccessoryFlashingInvalidHardware:
                    ss << "AccessoryFlashingInvalidHardware";
                    break;
                case AccessoryFlashingInvalidDataFile:
                    ss << "AccessoryFlashingInvalidDataFile";
                    break;
                case AccessoryGetVersionError:
                    ss << "AccessoryGetVersionError";
                    break;
                case AccessoryIndexError:
                    ss << "AccessoryIndexError";
                    break;
                case AccessoryParamApiVersionError:
                    ss << "AccessoryParamApiVersionError ";
                    break;
                case AccessoryParamSizeMismatchError:
                    ss << "AccessoryParamSizeMismatchError";
                    break;
                case AccessoryParameterNull:
                    ss << "AccessoryParameterNull";
                    break;
                default:
                    ss << "Unknown";
                    break;
            };
            return set_ics_exception(exception_runtime_error(), (char*)ss.str().c_str());
        }
        gil.restore();
        return Py_BuildValue("i", function_error);

    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_accessory_firmware_version(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    char accessory_indx = 0;
    bool check_success = true;
    if (!PyArg_ParseTuple(args, arg_parse("Oi|b:", __FUNCTION__), &obj, &accessory_indx, &check_success)) {
        return NULL;
    }

    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int __stdcall icsneoGetAccessoryFirmwareVersion(void* hObject, unsigned char index, unsigned int* fwVers,
        // int* errorCode)
        ice::Function<int __stdcall(void*, unsigned char, unsigned int*, int*)> icsneoGetAccessoryFirmwareVersion(
            lib, "icsneoGetAccessoryFirmwareVersion");

        unsigned int accessory_version = 0;
        int function_error = 0;
        auto gil = PyAllowThreads();
        if (!icsneoGetAccessoryFirmwareVersion(handle, accessory_indx, &accessory_version, &function_error)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetAccessoryFirmwareVersion() Failed");
        }
        gil.restore();
        // check the return value to make sure we are good
        if (check_success && function_error != AccessoryOperationSuccess) {
            std::stringstream ss;
            ss << "icsneoFlashAccessoryFirmware() Failed with error code: " << function_error << " (";
            switch (function_error) {
                case AccessoryOperationError:
                    ss << "AccessoryOperationError";
                    break;
                case AccessoryOperationSuccess:
                    ss << "AccessoryOperationSuccess";
                    break;
                case AccessoryFlashingInitError:
                    ss << "AccessoryFlashingInitError";
                    break;
                case AccessoryFlashingEraseError:
                    ss << "AccessoryFlashingEraseError";
                    break;
                case AccessoryFlashingWriteError:
                    ss << "AccessoryFlashingWriteError";
                    break;
                case AccessoryFlashingReadError:
                    ss << "AccessoryFlashingReadError";
                    break;
                case AccessoryFlashingVerifyError:
                    ss << "AccessoryFlashingVerifyError";
                    break;
                case AccessoryFlashingDeinitError:
                    ss << "AccessoryFlashingDeinitError";
                    break;
                case AccessoryFlashingInvalidHardware:
                    ss << "AccessoryFlashingInvalidHardware";
                    break;
                case AccessoryFlashingInvalidDataFile:
                    ss << "AccessoryFlashingInvalidDataFile";
                    break;
                case AccessoryGetVersionError:
                    ss << "AccessoryGetVersionError";
                    break;
                case AccessoryIndexError:
                    ss << "AccessoryIndexError";
                    break;
                case AccessoryParamApiVersionError:
                    ss << "AccessoryParamApiVersionError ";
                    break;
                case AccessoryParamSizeMismatchError:
                    ss << "AccessoryParamSizeMismatchError";
                    break;
                case AccessoryParameterNull:
                    ss << "AccessoryParameterNull";
                    break;
                default:
                    ss << "Unknown";
                    break;
            };
            ss << ")";
            return set_ics_exception(exception_runtime_error(), (char*)ss.str().c_str());
        }
        return Py_BuildValue("Ii", accessory_version, function_error);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_set_safe_boot_mode(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    bool enable = true;
    if (!PyArg_ParseTuple(args, arg_parse("Ob:", __FUNCTION__), &obj, &enable)) {
        return NULL;
    }

    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoSetSafeBootMode(void* hObject, const uint8_t enable)
        ice::Function<int __stdcall(void*, const uint8_t)> icsneoSetSafeBootMode(lib, "icsneoSetSafeBootMode");

        auto gil = PyAllowThreads();
        if (!icsneoSetSafeBootMode(handle, enable)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoSetSafeBootMode() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_override_library_name(PyObject* self, PyObject* args)
{
    (void)self;
    const char* name = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("s:", __FUNCTION__), &name)) {
        return NULL;
    }
    try {
        if (!dll_reinitialize((char*)name)) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_library_path(PyObject* self)
{
    (void)self;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        bool okay = false;
        auto path = lib->getPath(&okay);
        // auto isLoaded = lib->isLoaded();
        return Py_BuildValue("s", path.c_str());
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_disk_details(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, SDiskDetails*)> icsneoRequestDiskDetails(lib, "icsneoRequestDiskDetails");

        PyObject* details = _getPythonModuleObject("ics.structures.s_disk_details", "s_disk_details");
        if (!details) {
            return NULL;
        }
        Py_buffer details_buffer = {};
        PyObject_GetBuffer(details, &details_buffer, PyBUF_CONTIG);

        auto gil = PyAllowThreads();
        if (!icsneoRequestDiskDetails(handle, (SDiskDetails*)details_buffer.buf)) {
            gil.restore();
            PyBuffer_Release(&details_buffer);
            Py_DECREF(details);
            return set_ics_exception(exception_runtime_error(), "icsneoRequestDiskDetails() Failed");
        }
        gil.restore();
        PyBuffer_Release(&details_buffer);
        return details;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_disk_format(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* details = NULL;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OO:", __FUNCTION__), &obj, &details)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        Py_buffer details_buffer = {};
        PyObject_GetBuffer(details, &details_buffer, PyBUF_CONTIG);
        ice::Function<int __stdcall(void*, SDiskDetails*)> icsneoRequestDiskFormat(lib, "icsneoRequestDiskFormat");

        auto gil = PyAllowThreads();
        if (!icsneoRequestDiskFormat(handle, (SDiskDetails*)details_buffer.buf)) {
            gil.restore();
            PyBuffer_Release(&details_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoRequestDiskFormat() Failed");
        }
        gil.restore();
        PyBuffer_Release(&details_buffer);
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_disk_format_cancel(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*)> icsneoRequestDiskFormatCancel(lib, "icsneoRequestDiskFormatCancel");

        auto gil = PyAllowThreads();
        if (!icsneoRequestDiskFormatCancel(handle)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoRequestDiskFormatCancel() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_disk_format_progress(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, SDiskFormatProgress*)> icsneoRequestDiskFormatProgress(
            lib, "icsneoRequestDiskFormatProgress");

        PyObject* progress = _getPythonModuleObject("ics.structures.s_disk_format_progress", "s_disk_format_progress");
        if (!progress) {
            return NULL;
        }
        Py_buffer progress_buffer = {};
        PyObject_GetBuffer(progress, &progress_buffer, PyBUF_CONTIG);

        auto gil = PyAllowThreads();
        if (!icsneoRequestDiskFormatProgress(handle, (SDiskFormatProgress*)progress_buffer.buf)) {
            gil.restore();
            PyBuffer_Release(&progress_buffer);
            Py_DECREF(progress);
            return set_ics_exception(exception_runtime_error(), "icsneoRequestDiskFormatProgress() Failed");
        }
        gil.restore();
        PyBuffer_Release(&progress_buffer);
        return progress;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_enable_doip_line(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    bool enable = false;
    if (!PyArg_ParseTuple(args, arg_parse("O|b:", __FUNCTION__), &obj, &enable)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, bool)> icsneoEnableDOIPLine(lib, "icsneoEnableDOIPLine");
        auto gil = PyAllowThreads();
        if (!icsneoEnableDOIPLine(handle, enable)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoEnableDOIPLine() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_is_device_feature_supported(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned int feature = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &feature)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        unsigned int supported = 0;
        ice::Function<int __stdcall(void*, DeviceFeature, unsigned int*)> icsneoIsDeviceFeatureSupported(
            lib, "icsneoIsDeviceFeatureSupported");
        auto gil = PyAllowThreads();
        if (!icsneoIsDeviceFeatureSupported(handle, (DeviceFeature)feature, &supported)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoIsDeviceFeatureSupported() Failed");
        }
        gil.restore();
        return Py_BuildValue("I", supported);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_pcb_serial_number(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        char pcbsn[32] = { 0 };
        size_t length = sizeof pcbsn / sizeof pcbsn[0];
        ice::Function<int __stdcall(void*, char*, size_t*)> icsneoGetPCBSerialNumber(lib, "icsneoGetPCBSerialNumber");
        auto gil = PyAllowThreads();
        if (!icsneoGetPCBSerialNumber(handle, pcbsn, &length)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetPCBSerialNumber() Failed");
        }
        gil.restore();
        return Py_BuildValue("s", pcbsn);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_set_led_property(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned int led = 0;
    unsigned int prop = 0;
    unsigned int value = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OIII:", __FUNCTION__), &obj, &led, &prop, &value)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int, unsigned int, unsigned int)> icsneoSetLedProperty(
            lib, "icsneoSetLedProperty");
        auto gil = PyAllowThreads();
        if (!icsneoSetLedProperty(handle, led, prop, value)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoSetLedProperty() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_start_dhcp_server(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned int NetworkID = 0;
    const char* pDeviceIPAddress = NULL;
    const char* pSubnetmask = NULL;
    const char* pGateway = NULL;
    const char* pStartaddress = NULL;
    const char* pEndaddress = NULL;
    bool bOverwriteDHCPSettings = false;
    uint32_t leaseTime;
    uint8_t reserved = 0;
    if (!PyArg_ParseTuple(args,
                          arg_parse("OIsssssbI|b:", __FUNCTION__),
                          &obj,
                          &NetworkID,
                          &pDeviceIPAddress,
                          &pSubnetmask,
                          &pGateway,
                          &pStartaddress,
                          &pEndaddress,
                          &bOverwriteDHCPSettings,
                          &leaseTime,
                          &reserved)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoStartDHCPServer(void* hObject, unsigned int NetworkID, const char* pDeviceIPAddress,const
        // char* pSubnetmask,
        //      const char* pGateway,const char* pStartaddress,
        //      const char* pEndaddress,bool bOverwriteDHCPSettings,uint32_t leaseTime,uint8_t reserved)
        ice::Function<int __stdcall(void*,
                                    unsigned int,
                                    const char*,
                                    const char*,
                                    const char*,
                                    const char*,
                                    const char*,
                                    bool,
                                    uint32_t,
                                    uint8_t)>
            icsneoStartDHCPServer(lib, "icsneoStartDHCPServer");
        auto gil = PyAllowThreads();
        if (!icsneoStartDHCPServer(handle,
                                   NetworkID,
                                   pDeviceIPAddress,
                                   pSubnetmask,
                                   pGateway,
                                   pStartaddress,
                                   pEndaddress,
                                   bOverwriteDHCPSettings,
                                   leaseTime,
                                   reserved)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoStartDHCPServer() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_stop_dhcp_server(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned int NetworkID = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &NetworkID)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int)> icsneoStopDHCPServer(lib, "icsneoStopDHCPServer");
        auto gil = PyAllowThreads();
        if (!icsneoStopDHCPServer(handle, NetworkID)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoStopDHCPServer() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_wbms_manager_write_lock(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    EwBMSManagerPort_t manager = eManagerPortA;
    EwBMSManagerLockState_t lock_state = eLockManager;
    if (!PyArg_ParseTuple(args, arg_parse("OII:", __FUNCTION__), &obj, &manager, &lock_state)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, const EwBMSManagerPort_t, const EwBMSManagerLockState_t)>
            icsneowBMSManagerWriteLock(lib, "icsneowBMSManagerWriteLock");
        auto gil = PyAllowThreads();
        if (!icsneowBMSManagerWriteLock(handle, manager, lock_state)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneowBMSManagerWriteLock() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_wbms_manager_reset(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    EwBMSManagerPort_t manager = eManagerPortA;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &manager)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, const EwBMSManagerPort_t)> icsneowBMSManagerReset(lib,
                                                                                             "icsneowBMSManagerReset");
        auto gil = PyAllowThreads();
        if (!icsneowBMSManagerReset(handle, manager)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneowBMSManagerReset() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_uart_write(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    EUartPort_t port = eUART0;
    Py_buffer data = {};
    uint8_t flags = 0;
    bool check_size = true;
    if (!PyArg_ParseTuple(args, arg_parse("OIy*|Bp:", __FUNCTION__), &obj, &port, &data, &flags, &check_size)) {
        return NULL;
    }

    // Get the device handle
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoUartWrite(void* hObject, const EUartPort_t uart, const void* bData, const size_t
        // bytesToSend, size_t* bytesActuallySent, uint8_t* flags)
        size_t bytesActuallySent = 0;
        ice::Function<int __stdcall(void*, const EUartPort_t, const void*, const size_t, size_t*, uint8_t*)>
            icsneoUartWrite(lib, "icsneoUartWrite");
        auto gil = PyAllowThreads();
        if (!icsneoUartWrite(handle, port, data.buf, static_cast<size_t>(data.len), &bytesActuallySent, &flags)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoUartWrite() Failed");
        }
        gil.restore();
        if (check_size && (size_t)data.len != bytesActuallySent) {
            return set_ics_exception(exception_runtime_error(),
                                     "Bytes actually sent didn't match bytes to send length");
        }
        return Py_BuildValue("i", bytesActuallySent);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_uart_read(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    EUartPort_t port = eUART0;
    unsigned int bytesToRead = 256;
    uint8_t flags = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OI|IB:", __FUNCTION__), &obj, &port, &bytesToRead, &flags)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    uint8_t* buffer = (uint8_t*)malloc(bytesToRead * sizeof(uint8_t));
    if (!buffer) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            free(buffer);
            buffer = NULL;
            char _buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(_buffer));
        }
        size_t bytesActuallyRead = 0;
        // int _stdcall icsneoUartRead(void* hObject, const EUartPort_t uart, void* bData, const size_t bytesToRead,
        // size_t* bytesActuallyRead, uint8_t* flags)
        ice::Function<int __stdcall(void*, const EUartPort_t, void*, const size_t, size_t*, uint8_t*)>
            icsneoUartRead(lib, "icsneoUartRead");
        auto gil = PyAllowThreads();
        if (!icsneoUartRead(handle, port, buffer, bytesToRead, &bytesActuallyRead, &flags)) {
            gil.restore();
            free(buffer);
            buffer = NULL;
            return set_ics_exception(exception_runtime_error(), "icsneoUartRead() Failed");
        }
        gil.restore();
        PyObject* ba_result =
            PyByteArray_FromStringAndSize((const char*)buffer, static_cast<Py_ssize_t>(bytesActuallyRead));
        // PyObject* value = Py_BuildValue("O", ba_result);
        free(buffer);
        buffer = NULL;
        return ba_result;
    } catch (ice::Exception& ex) {
        free(buffer);
        buffer = NULL;
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_uart_set_baudrate(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    EUartPort_t port = eUART0;
    unsigned int baudrate = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OII:", __FUNCTION__), &obj, &port, &baudrate)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoUartSetBaudrate(void* hObject, const EUartPort_t uart, const uint32_t baudrate)
        ice::Function<int __stdcall(void*, const EUartPort_t, const uint32_t)> icsneoUartSetBaudrate(
            lib, "icsneoUartSetBaudrate");
        auto gil = PyAllowThreads();
        if (!icsneoUartSetBaudrate(handle, port, baudrate)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoUartSetBaudrate() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;

    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_uart_get_baudrate(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    EUartPort_t port = eUART0;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &port)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        uint32_t baudrate = 0;
        // int _stdcall icsneoUartGetBaudrate(void* hObject, const EUartPort_t uart, uint32_t* baudrate)
        ice::Function<int __stdcall(void*, const EUartPort_t, uint32_t*)> icsneoUartGetBaudrate(
            lib, "icsneoUartGetBaudrate");
        auto gil = PyAllowThreads();
        if (!icsneoUartGetBaudrate(handle, port, &baudrate)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoUartGetBaudrate() Failed");
        }
        gil.restore();
        return Py_BuildValue("I", baudrate);

    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_generic_api_send_command(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned char apiIndex = 0;
    unsigned char instanceIndex = 0;
    unsigned char functionIndex = 0;
    Py_buffer data = {};
    if (!PyArg_ParseTuple(
            args, arg_parse("Obbby*:", __FUNCTION__), &obj, &apiIndex, &instanceIndex, &functionIndex, &data)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        /*
        int _stdcall icsneoGenericAPISendCommand(void* hObject,
            unsigned char apiIndex,
            unsigned char instanceIndex,
            unsigned char functionIndex,
            void* bData,
            unsigned int length,
            unsigned char* functionError)
        */
        ice::Function<int __stdcall(
            void*, unsigned char, unsigned char, unsigned char, void*, unsigned int, unsigned char*)>
            icsneoGenericAPISendCommand(lib, "icsneoGenericAPISendCommand");
        unsigned char functionError = 0;
        auto gil = PyAllowThreads();
        if (!icsneoGenericAPISendCommand(handle,
                                         apiIndex,
                                         instanceIndex,
                                         functionIndex,
                                         (void*)data.buf,
                                         static_cast<unsigned int>(data.len),
                                         &functionError)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGenericAPISendCommand() Failed");
        }
        gil.restore();
        return Py_BuildValue("i", functionError);

    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_generic_api_read_data(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned char apiIndex = 0;
    unsigned char instanceIndex = 0;
    unsigned int length = GENERIC_API_DATA_BUFFER_SIZE;
    if (!PyArg_ParseTuple(args, arg_parse("Obb|I:", __FUNCTION__), &obj, &apiIndex, &instanceIndex, &length)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    unsigned char* buffer = (unsigned char*)malloc(length * sizeof(unsigned char));
    if (!buffer) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            free(buffer);
            buffer = NULL;
            char _buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(_buffer));
        }
        /*
        int _stdcall icsneoGenericAPIReadData(void* hObject,
            unsigned char apiIndex,
            unsigned char instanceIndex,
            unsigned char* functionIndex,
            unsigned char* bData,
            unsigned int* length)
        */
        ice::Function<int __stdcall(void*, unsigned char, unsigned char, unsigned char*, unsigned char*, unsigned int*)>
            icsneoGenericAPIReadData(lib, "icsneoGenericAPIReadData");
        unsigned char functionIndex = 0;
        auto gil = PyAllowThreads();
        if (!icsneoGenericAPIReadData(handle, apiIndex, instanceIndex, &functionIndex, buffer, &length)) {
            gil.restore();
            free(buffer);
            buffer = NULL;
            return set_ics_exception(exception_runtime_error(), "icsneoGenericAPIReadData() Failed");
        }
        gil.restore();

        PyObject* ba = PyByteArray_FromStringAndSize((const char*)buffer, length);
        PyObject* value = Py_BuildValue("IO", functionIndex, ba);
        Py_DecRef(ba);
        free(buffer);
        buffer = NULL;
        return value;
    } catch (ice::Exception& ex) {
        free(buffer);
        buffer = NULL;
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_generic_api_get_status(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    unsigned char apiIndex = 0;
    unsigned char instanceIndex = 0;

    if (!PyArg_ParseTuple(args, arg_parse("Obb:", __FUNCTION__), &obj, &apiIndex, &instanceIndex)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        /*
        int _stdcall icsneoGenericAPIGetStatus(void* hObject,
            unsigned char apiIndex,
            unsigned char instanceIndex,
            unsigned char* functionIndex,
            unsigned char* callbackError,
            unsigned char* finishedProcessing)
        */
        ice::Function<int __stdcall(
            void*, unsigned char, unsigned char, unsigned char*, unsigned char*, unsigned char*)>
            icsneoGenericAPIGetStatus(lib, "icsneoGenericAPIGetStatus");
        unsigned char functionIndex = 0;
        unsigned char callbackError = 0;
        unsigned char finishedProcessing = 0;
        auto gil = PyAllowThreads();
        if (!icsneoGenericAPIGetStatus(
                handle, apiIndex, instanceIndex, &functionIndex, &callbackError, &finishedProcessing)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGenericAPIGetStatus() Failed");
        }
        gil.restore();

        PyObject* value = Py_BuildValue("III", functionIndex, callbackError, finishedProcessing);
        return value;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_gptp_status(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    // Before we do anything, we need to grab the python gptp_status ctype.Structure.
    PyObject* status = _getPythonModuleObject("ics.structures.gptp_status", "gptp_status");
    if (!status) {
        return NULL;
    }
    // Grab the buffer out of the newly created object - make sure to call PyBuffer_Release(&status_buffer) when done.
    Py_buffer status_buffer = {};
    PyObject_GetBuffer(status, &status_buffer, PyBUF_CONTIG);
    // Verify we have a valid NeoDevice Object - This comes after gptp_status allocation for testing purposes
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        PyBuffer_Release(&status_buffer);
        Py_DECREF(status);
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            PyBuffer_Release(&status_buffer);
            Py_DECREF(status);
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // Get the gptp_status
        auto gil = PyAllowThreads();
        // int _stdcall icsneoGetGPTPStatus(void* hObject, GPTPStatus* gptpStatus)
        ice::Function<int __stdcall(void*, GPTPStatus*)> icsneoGetGPTPStatus(lib, "icsneoGetGPTPStatus");
        if (!icsneoGetGPTPStatus(handle, (GPTPStatus*)status_buffer.buf)) {
            gil.restore();
            PyBuffer_Release(&status_buffer);
            Py_DECREF(status);
            return set_ics_exception(exception_runtime_error(), "icsneoGetGPTPStatus() Failed");
        }
        gil.restore();
        PyBuffer_Release(&status_buffer);
        return status;
    } catch (ice::Exception& ex) {
        PyBuffer_Release(&status_buffer);
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

// int _stdcall icsneoGetAllChipVersions(void* hObject, stChipVersions* pInfo, int ipInfoSize)
PyObject* meth_get_all_chip_versions(PyObject* self, PyObject* args)
{
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    // Before we do anything, we need to grab the python ctype.Structure.
    PyObject* py_struct = _getPythonModuleObject("ics.structures.st_chip_versions", "st_chip_versions");
    if (!py_struct) {
        return NULL;
    }
    // Grab the buffer out of the newly created object - make sure to call PyBuffer_Release(&py_struct_buffer) when
    // done.
    Py_buffer py_struct_buffer = {};
    PyObject_GetBuffer(py_struct, &py_struct_buffer, PyBUF_CONTIG);
    // Verify we have a valid NeoDevice Object - This comes after ctypes struct allocation for testing purposes
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        PyBuffer_Release(&py_struct_buffer);
        Py_DECREF(py_struct);
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            PyBuffer_Release(&py_struct_buffer);
            Py_DECREF(py_struct);
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // Get the struct
        auto gil = PyAllowThreads();
        // int _stdcall icsneoGetAllChipVersions(void* hObject, stChipVersions* pInfo, int ipInfoSize)
        ice::Function<int __stdcall(void*, stChipVersions*, int)> icsneoGetAllChipVersions(lib,
                                                                                           "icsneoGetAllChipVersions");
        if (!icsneoGetAllChipVersions(
                handle, (stChipVersions*)py_struct_buffer.buf, static_cast<int>(py_struct_buffer.len))) {
            gil.restore();
            PyBuffer_Release(&py_struct_buffer);
            Py_DECREF(py_struct);
            return set_ics_exception(exception_runtime_error(), "icsneoGetAllChipVersions() Failed");
        }
        gil.restore();
        PyBuffer_Release(&py_struct_buffer);
        return py_struct;
    } catch (ice::Exception& ex) {
        PyBuffer_Release(&py_struct_buffer);
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_device_name(PyObject* self, PyObject* args) // icsneoGetDeviceName
{
    (void)self;
    PyObject* obj = NULL;
    EDevNameType dev_name_type = EDevNameTypeDefault;
    if (!PyArg_ParseTuple(args, arg_parse("O|I:", __FUNCTION__), &obj, &dev_name_type)) {
        return NULL;
    }
    // Get the NeoDeviceEx from PyNeoDeviceEx
    Py_buffer nde_buffer = {};
    NeoDeviceEx* nde = NULL;
    if (!PyNeoDeviceEx_GetNeoDeviceEx(obj, &nde_buffer, &nde)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            PyBuffer_Release(&nde_buffer);
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        const size_t NAME_SIZE = 255;
        char name[NAME_SIZE] = {};
        // Get the struct
        // int _stdcall icsneoGetDeviceName(const NeoDeviceEx* nde, char* name, const size_t length, const enum
        // _EDevNameType devNameType)
        auto gil = PyAllowThreads();
        ice::Function<int __stdcall(const NeoDeviceEx*, char*, const size_t, const enum _EDevNameType)>
            icsneoGetDeviceName(lib, "icsneoGetDeviceName");
        if (auto length = icsneoGetDeviceName(const_cast<NeoDeviceEx*>(nde), name, NAME_SIZE, dev_name_type);
            length == 0) {
            gil.restore();
            PyBuffer_Release(&nde_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceName() Failed");
        }
        gil.restore();
        PyBuffer_Release(&nde_buffer);
        PyObject* value = Py_BuildValue("s", name);
        return value;
    } catch (ice::Exception& ex) {
        PyBuffer_Release(&nde_buffer);
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_imei(PyObject* self, PyObject* args)
{ // icsneoGetIMEI
    (void)self;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        uint64_t imei = 0;
        ice::Function<int __stdcall(void*, uint64_t*)> icsneoGetIMEI(lib, "icsneoGetIMEI");
        auto gil = PyAllowThreads();
        if (!icsneoGetIMEI(handle, &imei)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetIMEI() Failed");
        }
        gil.restore();
        return Py_BuildValue("K", imei);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_component_versions(PyObject* self, PyObject* args) // icsneoGetComponentVersions
{
#ifndef _USE_INTERNAL_HEADER_
    (void)self;
    (void)args;
    return set_ics_exception(exception_runtime_error(), "icsneoGetComponentVersions is not available");
#else
    (void)self;
    PyObject* obj = NULL;
    bool force_update = true;
    uint64_t length = 25;
    if (!PyArg_ParseTuple(args, arg_parse("O|bK:", __FUNCTION__), &obj, &force_update, &length)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, VersionReport*, uint64_t*, bool)> icsneoGetComponentVersions(
            lib, "icsneoGetComponentVersions");
        auto gil = PyAllowThreads();
        std::vector<VersionReport> version_reports;
        version_reports.reserve(length);
        version_reports.resize(length);
        if (!icsneoGetComponentVersions(handle, version_reports.data(), &length, force_update)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoGetComponentVersions() Failed");
        }
        gil.restore();

        PyObject* tuple = PyTuple_New(length);
        if (!tuple) {
            return NULL;
        }
        for (uint64_t i = 0; i < length; ++i) {
            PyObject* obj = _getPythonModuleObject("ics.structures.version_report", "version_report");
            if (!obj) {
                return set_ics_exception(exception_runtime_error(), "Failed to allocate version_report");
            }

            // Get the internal buffer from version_report
            Py_buffer buffer = {};
            if (PyObject_GetBuffer(obj, &buffer, PyBUF_CONTIG) != 0) {
                return NULL;
            }
            memcpy(buffer.buf, &version_reports[i], sizeof(version_reports[i]));
            PyBuffer_Release(&buffer);

            PyTuple_SetItem(tuple, i, obj);
        }
        return tuple;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
#endif
}

PyObject* meth_request_set_neovi_miscio(PyObject* self, PyObject* args) // icsneoRequestSetNeoVIMiscIO
{
    (void)self;
    PyObject* obj = NULL;
    uint32_t ddrs = 0;
    uint32_t ddrs_mask = 0;
    uint32_t states = 0;
    uint32_t states_mask = 0;
    uint32_t leds = 0;
    uint32_t leds_mask = 0;
    if (!PyArg_ParseTuple(args,
                          arg_parse("OIIIIII:", __FUNCTION__),
                          &obj,
                          &ddrs,
                          &ddrs_mask,
                          &states,
                          &states_mask,
                          &leds,
                          &leds_mask)) {
        return NULL;
    }
    if (!PyNeoDeviceEx_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME ".PyNeoDeviceEx");
    }
    void* handle = NULL;
    if (!PyNeoDeviceEx_GetHandle(obj, &handle)) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoRequestSetNeoVIMiscIO(void* hObject,
        //      uint32_t ddrs,
        //      uint32_t ddrs_mask,
        //      uint32_t states,
        //      uint32_t states_mask,
        //      uint32_t leds,
        //      uint32_t leds_mask)
        ice::Function<int __stdcall(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)>
            icsneoRequestSetNeoVIMiscIO(lib, "icsneoRequestSetNeoVIMiscIO");
        auto gil = PyAllowThreads();
        if (!icsneoRequestSetNeoVIMiscIO(handle, ddrs, ddrs_mask, states, states_mask, leds, leds_mask)) {
            gil.restore();
            return set_ics_exception(exception_runtime_error(), "icsneoRequestSetNeoVIMiscIO() Failed");
        }
        gil.restore();
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}
