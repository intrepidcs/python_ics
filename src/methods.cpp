#include "methods.h"
#include "exceptions.h"
#include "dll.h"
#ifndef USING_STUDIO_8
    #define USING_STUDIO_8 1
#endif
#include <icsnVC40.h>
#ifdef _USE_INTERNAL_HEADER_
#include <icsnVC40Internal.h>
#endif
#include <datetime.h>
#include "object_spy_message.h"
#include "object_neo_device.h"
#include "object_vcan3_settings.h"
#include "object_fire_settings.h"
#include "object_can_settings.h"
#include "object_iso9141_keyword2000_settings.h"
#include "object_iso9141_keyword2000_init_steps.h"
#include "object_lin_settings.h"
#include "object_swcan_settings.h"
#include "object_textapi_settings.h"
#include "object_uart_settings.h"
#include "object_vcanrf_settings.h"
#include "object_cyan_settings.h"
#include "object_api_firmware_info.h"
#include "object_op_eth_general_settings.h"
#include "object_op_eth_settings.h"
#include "object_rad_galaxy_settings.h"
#include "setup_module_auto_defines.h"
#include "object_cm_iso157652_tx_message.h"
#include "object_cm_iso157652_rx_message.h"
#include "object_vcan412_settings.h"
#include "object_vividcan_settings.h"
//#include "object_vcan4_settings.h" // Not implemented in 802

extern PyTypeObject spy_message_object_type;
// __func__, __FUNCTION__ and __PRETTY_FUNCTION__ are not preprocessor macros.
// but MSVC doesn't follow c standard and treats __FUNCTION__ as a string literal macro...
#if (defined(_WIN32) || defined(__WIN32__))
#define arg_parse(a,f) a f
#else
const char* arg_parse(const char* args, const char* func)
{
    static const char buffer[128];
    memset(buffer, '\0', sizeof(buffer)/sizeof(buffer[0]));
    strcpy(buffer, args);
    strcat(buffer, func);
    return buffer;
}
#endif

#ifndef _USE_INTERNAL_HEADER_
typedef struct 
{
    unsigned char sec;           // --- Seconds (00-59)
    unsigned char min;        // --- (00-59)
    unsigned char hour;        // --- (00-23)
    unsigned char day;        // --- (01-31)
    unsigned char month;            // --- (01-12)
    unsigned char year;        // --- (00-99)
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

// Sleep is a windows.h specific function.
#include <unistd.h>
#define Sleep(i) sleep(i)


#endif
#endif

// Internal function
char* neodevice_to_string(unsigned long type)
{
    switch (type) {
    case NEODEVICE_BLUE: return "neoVI BLUE";
    case NEODEVICE_ECU_AVB: return "neoECU AVB/TSN";
    case NEODEVICE_RADSUPERMOON: return "RAD SuperMoon";
    case NEODEVICE_DW_VCAN: return "ValueCAN2 DW";
    case NEODEVICE_RADMOON2: return "RAD Moon2";
    case NEODEVICE_RADGIGALOG: return "RAD Gigalog";
    case NEODEVICE_VCAN41: return "ValueCAN4-1";
    case NEODEVICE_FIRE: return "neoVI FIRE";
    case NEODEVICE_VCAN3: return "ValueCAN3";
    case NEODEVICE_RED: return "neoVI RED";
    case NEODEVICE_ECU: return "ECU";
    case NEODEVICE_IEVB: return "IEVB";
    case NEODEVICE_PENDANT: return "Pendant";
    case NEODEVICE_OBD2_PRO: return "neoOBD2 Pro";
    case NEODEVICE_ECUCHIP_UART: return "neoECU Chip";
    case NEODEVICE_PLASMA: return "neoVI PLASMA";
    //case NEODEVICE_DONT_REUSE0: return "DONT REUSE0";
    case NEODEVICE_NEOANALOG: return "neoAnalog";
    //case NEODEVICE_CT_OBD: return "";
    //case NEODEVICE_DONT_REUSE1: return "DONT REUSE1";
    //case NEODEVICE_DONT_REUSE2: return "DONT REUSE2";
    case NEODEVICE_ION: return "neoVI ION";
    case NEODEVICE_RADSTAR: return "RAD Star";
    //case NEODEVICE_DONT_REUSE3: return "DONT REUSE3";
    case NEODEVICE_VCAN4: return "ValueCAN4";
    case NEODEVICE_VCAN42: return "ValueCAN4-2";
    case NEODEVICE_CMPROBE: return "CMProbe";
    case NEODEVICE_EEVB: return "EEVB";
    case NEODEVICE_VCANRF: return "ValueCAN.RF";
    case NEODEVICE_FIRE2: return "neoVI FIRE2";
    case NEODEVICE_FLEX: return "FLEX";
    case NEODEVICE_RADGALAXY: return "RAD Galaxy";
    case NEODEVICE_RADSTAR2: return "RAD Star2";
    case NEODEVICE_VIVIDCAN: return "VividCAN";
    case NEODEVICE_OBD2_SIM: return "OBD2 Sim";
    default: return "unknown/unsupported";
    };
    return "unknown/unsupported";
}

bool _convertListOrTupleToArray(PyObject* obj, std::vector<PyObject*>* results)
{
    if (!obj || !results)
    {
        set_ics_exception(exception_runtime_error(), "_convertListOrTupleToArray() was passed invalid arguments");
        return false;
    }
    results->clear();
    if (PyList_CheckExact(obj))
    {
        Py_ssize_t length = PyList_Size(obj);
        for (Py_ssize_t i=0; i < length; ++i)
            results->push_back(PyList_GetItem(obj, i));
        return true;
    } 
    else if (PyTuple_CheckExact(obj))
    {
        Py_ssize_t length = PyTuple_Size(obj);
        for (Py_ssize_t i=0; i < length; ++i)
            results->push_back(PyTuple_GetItem(obj, i));
        return true;
    } 
    else
    {
        set_ics_exception(exception_runtime_error(), "_convertListOrTupleToArray() was passed neither a list or tuple");
        return false;
    }
    set_ics_exception(exception_runtime_error(), "_convertListOrTupleToArray() bug!");
    return false;
}

PyObject* meth_find_devices(PyObject* self, PyObject* args, PyObject* keywords)
{
    PyObject* device_type = NULL;
    int ex_options = -1;
    char* kwords[] = { "type", "stOptionsOpenNeoEx", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywords, arg_parse("|Oi:", __FUNCTION__), 
            kwords, &device_type, &ex_options)) {
        return NULL;
    }
    ice::Library* lib = dll_get_library();
    if (!lib) { 
        char buffer[512];
        return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
    }
    NeoDevice devices[255];
    int count = 255;
    try
    {
#ifndef USE_LEGACY_FIND_DEVICES
        // Get the list of device types
        unsigned int* device_type_list = NULL;
        unsigned int device_type_list_size = 0;
        if (device_type && device_type != Py_None)
        {
            std::vector<PyObject*> device_type_vector;
            if (!_convertListOrTupleToArray(device_type, &device_type_vector))
                return NULL;
            device_type_list_size = device_type_vector.size();
            device_type_list = new unsigned int[device_type_list_size];
            for (unsigned int i=0; i < device_type_list_size; ++i)
                device_type_list[i] = PyLong_AsLong(device_type_vector[i]);
        }
        Py_BEGIN_ALLOW_THREADS
        try
        {
            if (ex_options != -1)
                throw ice::Exception("Need to use old style find function");
            //int _stdcall icsneoFindNeoDevicesNewStyle(unsigned int* deviceTypes, unsigned int numDeviceTypes, NeoDevice* pNeoDevice, int* pNumDevices)
            ice::Function<int __stdcall (unsigned int*, unsigned int, NeoDevice*, int*)> icsneoFindNeoDevicesNewStyle(lib, "icsneoFindNeoDevicesNewStyle");
            if (!icsneoFindNeoDevicesNewStyle(device_type_list, device_type_list_size, devices, &count))
            {
                Py_BLOCK_THREADS
                if (device_type_list)
                    delete[] device_type_list;
                return set_ics_exception(exception_runtime_error(), "icsneoFindNeoDevicesNewStyle() Failed");
            }
        }
        catch (ice::Exception& ex)
        {
            // Use the old style, we are using an old DLL
            if (device_type_list) {
                delete[] device_type_list;
                device_type_list = NULL;
            }
            if (!PyLong_CheckExact(device_type)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "device_type argument is not of type long");
            }
            unsigned long dev_type = PyLong_AsLong(device_type);
            ice::Function<int __stdcall (unsigned long, NeoDevice*, int*)> icsneoFindNeoDevices(lib, "icsneoFindNeoDevices");
            if (ex_options == -1 && !icsneoFindNeoDevices(dev_type, devices, &count)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoFindNeoDevices() Failed");
            } 
            if (ex_options != -1) {
                ice::Function<int __stdcall (unsigned long, NeoDevice*, int*, const POptionsFindNeoEx)> icsneoFindNeoDevicesEx(lib, "icsneoFindNeoDevicesEx");
                OptionsFindNeoEx opts = {0};
                opts.CANOptions.iNetworkID = ex_options;
                if (!icsneoFindNeoDevicesEx(dev_type, devices, &count, &opts)) {
                    Py_BLOCK_THREADS
                    return set_ics_exception(exception_runtime_error(), "icsneoFindNeoDevicesEx() Failed");
                }
            }
        }
        if (device_type_list)
            delete[] device_type_list;
        Py_END_ALLOW_THREADS
#else
        ice::Function<int __stdcall (unsigned long, NeoDevice*, int*)> icsneoFindNeoDevices(lib, "icsneoFindNeoDevices");
        Py_BEGIN_ALLOW_THREADS
        if (ex_options == -1 && !icsneoFindNeoDevices(device_type, devices, &count)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoFindNeoDevices() Failed");
        } 
        if (ex_options != -1) {
            ice::Function<int __stdcall (unsigned long, NeoDevice*, int*, const POptionsFindNeoEx)> icsneoFindNeoDevicesEx(lib, "icsneoFindNeoDevicesEx");
            OptionsFindNeoEx opts = {0};
            opts.CANOptions.iNetworkID = ex_options;
            if (!icsneoFindNeoDevicesEx(device_type, devices, &count, &opts)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoFindNeoDevicesEx() Failed");
            }
        }
        Py_END_ALLOW_THREADS
#endif
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    //PyObject* list_object = PyList_New(count);
    PyObject* tuple = PyTuple_New(count);
    if (!tuple) {
        return NULL;
    }
    for (int i=0; i < count; ++i) {
        PyObject* obj = PyObject_CallObject((PyObject*)&neo_device_object_type, NULL);
        if (!obj) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(), "Failed to allocate " NEO_DEVICE_OBJECT_NAME);
        }
        // Copy the NeoDevice struct into our python NeoDevice object
        neo_device_object* neo_device = (neo_device_object*)obj;
        neo_device->dev = devices[i];
        neo_device->name = PyUnicode_FromString(neodevice_to_string(devices[i].DeviceType));
        //PyList_Append(list_object, neo_device);
        PyTuple_SetItem(tuple, i, obj);
    }
    return tuple;
}

PyObject* meth_open_device(PyObject* self, PyObject* args, PyObject* keywords)
{
    /*
    unsigned char * bNetworkIDs,
                                 int bConfigRead, 
                                 int iOptions
                                 */
    //int PyArg_ParseTupleAndKeywords(PyObject *args, PyObject *kw, const char *format, char *keywords[], ...)
    unsigned long serial_number = 0;
    PyObject* obj = NULL;
    PyObject* bNetworkIDs = NULL;
    int bConfigRead = 0;
    int iOptions = 0;
    int ex_options = -1;
    char* kwords[] = { "device", "bNetworkIDs", "bConfigRead", "iOptions", "stOptionsOpenNeoEx", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywords, arg_parse("|OOiii:", __FUNCTION__), kwords, &obj, &bNetworkIDs, 
        &bConfigRead, &iOptions, &ex_options)) {
        return NULL;
    }
//        if (!PyArg_ParseTupleAndKeywords(args, keywords, arg_parse("|bbbbbbbiiii:", __FUNCTION__), kwords, &relay1, &relay2, 
//        &relay3, &relay4, &relay5, &led5, &led6, &msb, &lsb, &analog, &relay_timeout)) {


    // Argument Parsing
    bool use_user_neo_device = false;
    if (obj && PyLong_CheckExact(obj)) {
        serial_number = PyLong_AsLong(obj);
    } else if (serial_number == 0 && obj && !PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument is not of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    } else if (obj && PyNeoDevice_CheckExact(obj)) {
        // User supplied us with a ics.NeoDevice object, so lets use it.
        use_user_neo_device = true;
    }
    unsigned char net_ids[NETID_MAX] = {0};
    if (bNetworkIDs && PyTuple_CheckExact(bNetworkIDs)) {
        for (int i=0; i < PyTuple_Size(bNetworkIDs); ++i) {
            long id = PyLong_AsLong(PyTuple_GetItem(bNetworkIDs, i));
            net_ids[i] = (unsigned char)id;
        }
    } else if (!bNetworkIDs) {
        for (int i=0; i < NETID_MAX; ++i) {
            net_ids[i] = i;
        }
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        bool use_new_finder = false;
        try
        {
            //int _stdcall icsneoFindNeoDevicesNewStyle(unsigned int* deviceTypes, unsigned int numDeviceTypes, NeoDevice* pNeoDevice, int* pNumDevices)
            ice::Function<int __stdcall (unsigned int*, unsigned int, NeoDevice*, int*)> icsneoFindNeoDevicesNewStyle(lib, "icsneoFindNeoDevicesNewStyle");
            use_new_finder = true;
        } catch (ice::Exception& ex)
        {
            use_new_finder = false;
        }
        ice::Function<int __stdcall (unsigned long, NeoDevice*, int*)> icsneoFindNeoDevices(lib, "icsneoFindNeoDevices");
        ice::Function<int __stdcall (NeoDevice*, ICS_HANDLE*, unsigned char*, int, int)> icsneoOpenNeoDevice(lib, "icsneoOpenNeoDevice");
        if (use_user_neo_device) {
            neo_device_object* neo_device = PyNeoDevice_GetNeoDevice(obj);
            ICS_HANDLE handle = PyNeoDevice_GetHandle(neo_device);
            Py_BEGIN_ALLOW_THREADS
            if (ex_options == -1 && !icsneoOpenNeoDevice(&PyNeoDevice_GetNeoDevice(obj)->dev, &handle, (bNetworkIDs ? net_ids : NULL), bConfigRead, iOptions)) {
                Py_BLOCK_THREADS
                return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to open device");
            }
            if (ex_options != -1) {
                ice::Function<int __stdcall (NeoDevice*, ICS_HANDLE*, unsigned char*, int, int, POptionsOpenNeoEx)> icsneoOpenNeoDeviceEx(lib, "icsneoOpenNeoDeviceEx");
                OptionsOpenNeoEx opts = {0};
                opts.CANOptions.iNetworkID = ex_options;
                if (!icsneoOpenNeoDeviceEx(&PyNeoDevice_GetNeoDevice(obj)->dev, &handle, (bNetworkIDs ? net_ids : NULL), bConfigRead, iOptions, &opts)) {
                    Py_BLOCK_THREADS
                    return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to open device");
                }
            }
            PyNeoDevice_SetHandle(obj, handle);
            Py_END_ALLOW_THREADS
            Py_RETURN_NONE;
        } else {
            // We need to find the device and create the ics.NeoDevice object our self
            PyObject* device = PyObject_CallObject((PyObject*)&neo_device_object_type, NULL);
            if (!device) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(), "Failed to allocate " NEO_DEVICE_OBJECT_NAME);
            }
            NeoDevice devices[255];
            int count = 255;
            unsigned long device_type = -1;
            Py_BEGIN_ALLOW_THREADS
            // Get a list of devices to find serial number
            if (use_new_finder && ex_options == -1) {
                 //int _stdcall icsneoFindNeoDevicesNewStyle(unsigned int* deviceTypes, unsigned int numDeviceTypes, NeoDevice* pNeoDevice, int* pNumDevices)
                ice::Function<int __stdcall (unsigned int*, unsigned int, NeoDevice*, int*)> icsneoFindNeoDevicesNewStyle(lib, "icsneoFindNeoDevicesNewStyle");
                if (!icsneoFindNeoDevicesNewStyle(NULL, 0, devices, &count)) {
                    Py_BLOCK_THREADS
                    return set_ics_exception(exception_runtime_error(), "icsneoFindNeoDevicesNewStyle() Failed");
                }
            } else {
                // Use old find method
                if (ex_options == -1 && !icsneoFindNeoDevices(device_type, devices, &count)) {
                    Py_BLOCK_THREADS
                    return set_ics_exception(exception_runtime_error(), "icsneoFindNeoDevices() failed");
                }
                if (ex_options != -1) {
                    ice::Function<int __stdcall (unsigned long, NeoDevice*, int*, const POptionsFindNeoEx)> icsneoFindNeoDevicesEx(lib, "icsneoFindNeoDevicesEx");
                    OptionsFindNeoEx opts = {0};
                    opts.CANOptions.iNetworkID = ex_options;
                    if (!icsneoFindNeoDevicesEx(device_type, devices, &count, &opts)) {
                        Py_BLOCK_THREADS
                        return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoFindNeoDevicesEx() failed");
                    }
                }
            }
            Py_END_ALLOW_THREADS
            // Find the serial number
            for (int i=0; i < count; ++i) {
                // Grab the first device we find and return it
                if (serial_number == 0 && devices[i].NumberOfClients == 0) {
                    PyNeoDevice_GetNeoDevice(device)->dev = devices[i];
                    PyNeoDevice_GetNeoDevice(device)->name = PyUnicode_FromString(neodevice_to_string(devices[i].DeviceType));
                    ICS_HANDLE handle = 0;
                    Py_BEGIN_ALLOW_THREADS
                    if (ex_options == -1 && !icsneoOpenNeoDevice(&PyNeoDevice_GetNeoDevice(device)->dev, &handle, (bNetworkIDs ? net_ids : NULL), bConfigRead, iOptions)) {
                        Py_BLOCK_THREADS
                        return set_ics_exception_dev(exception_runtime_error(), device, "Failed to open device");
                    }
                    if (ex_options != -1) {
                        ice::Function<int __stdcall (NeoDevice*, ICS_HANDLE*, unsigned char*, int, int, POptionsOpenNeoEx)> icsneoOpenNeoDeviceEx(lib, "icsneoOpenNeoDeviceEx");
                        OptionsOpenNeoEx opts = {0};
                        opts.CANOptions.iNetworkID = ex_options;
                        if (!icsneoOpenNeoDeviceEx(&PyNeoDevice_GetNeoDevice(obj)->dev, &handle, (bNetworkIDs ? net_ids : NULL), bConfigRead, iOptions, &opts)) {
                            Py_BLOCK_THREADS
                            return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to open device");
                        }
                    }
                    PyNeoDevice_SetHandle(device, handle);
                    Py_END_ALLOW_THREADS
                    return device;
                } else if (devices[i].SerialNumber == serial_number) {
                    PyNeoDevice_GetNeoDevice(device)->dev = devices[i];
                    PyNeoDevice_GetNeoDevice(device)->name = PyUnicode_FromString(neodevice_to_string(devices[i].DeviceType));
                    ICS_HANDLE handle = 0;
                    Py_BEGIN_ALLOW_THREADS
                    if (ex_options == -1 && !icsneoOpenNeoDevice(&PyNeoDevice_GetNeoDevice(device)->dev, &handle, (bNetworkIDs ? net_ids : NULL), bConfigRead, iOptions)) {
                        Py_BLOCK_THREADS
                        return set_ics_exception_dev(exception_runtime_error(), device, "Failed to open device");
                    }
                    if (ex_options != -1) {
                        ice::Function<int __stdcall (NeoDevice*, ICS_HANDLE*, unsigned char*, int, int, POptionsOpenNeoEx)> icsneoOpenNeoDeviceEx(lib, "icsneoOpenNeoDeviceEx");
                        OptionsOpenNeoEx opts = {0};
                        opts.CANOptions.iNetworkID = ex_options;
                        if (!icsneoOpenNeoDeviceEx(&PyNeoDevice_GetNeoDevice(obj)->dev, &handle, (bNetworkIDs ? net_ids : NULL), bConfigRead, iOptions, &opts)) {
                            Py_BLOCK_THREADS
                            return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to open device");
                        }
                    }
                    PyNeoDevice_SetHandle(device, handle);
                    Py_END_ALLOW_THREADS
                    return device;
                }
            }
            return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to find a free device to open"); 
        }
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");

}

PyObject* meth_close_device(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, int*)>  icsneoClosePort(lib, "icsneoClosePort");
        ice::Function<int __stdcall (ICS_HANDLE)>  icsneoFreeObject(lib, "icsneoFreeObject");
        int error_count = 0;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoClosePort(PyNeoDevice_GetNeoDevice(obj)->handle, &error_count)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoClosePort() Failed");
        }
        icsneoFreeObject(PyNeoDevice_GetNeoDevice(obj)->handle);
        Py_END_ALLOW_THREADS
        PyNeoDevice_GetNeoDevice(obj)->handle = 0;
        return Py_BuildValue("i", error_count);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
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
    result = t->tm_mday*86400;
    result += t->tm_hour*3600;
    result += t->tm_min*60;
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
    if (t1->tm_year != t2->tm_year ||
        t1->tm_mon != t1->tm_mon)
        return -2;
    if ((result = r1 - r2) < 0)
        result *= -1;
    return result;
}

PyObject* meth_get_rtc(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    icsSpyTime ics_time;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, icsSpyTime*)>  icsneoGetRTC(lib, "icsneoGetRTC");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetRTC(handle, &ics_time)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetRTC() Failed");
        }
        Py_END_ALLOW_THREADS
        time_t current_time = time(0);
        // Bug #6600 - icsneoSetRTC is utc, icsneoGetRTC is local
        //tm* current_utc_time = gmtime(&current_time); // UTC
        tm* current_utc_time = localtime(&current_time); // Local
        tm device_utc_time;
        device_utc_time.tm_hour = ics_time.hour;
        device_utc_time.tm_min = ics_time.min;
        device_utc_time.tm_sec = ics_time.sec;
        device_utc_time.tm_mon = ics_time.month-1;
        device_utc_time.tm_mday = ics_time.day;
        device_utc_time.tm_year = ics_time.year;
        device_utc_time.tm_isdst = -1;
        device_utc_time.tm_year += 100;
        unsigned long offset = (unsigned long)_tm_secs_offset(&device_utc_time, current_utc_time);
        PyDateTime_IMPORT;
        if (!PyDateTimeAPI) {
            return set_ics_exception(exception_runtime_error(), "Failed to initialize PyDateTime");
        }
        PyObject* datetime = PyDateTime_FromDateAndTime(device_utc_time.tm_year+1900,
            device_utc_time.tm_mon,
            device_utc_time.tm_mday,
            device_utc_time.tm_hour,
            device_utc_time.tm_min,
            device_utc_time.tm_sec,
            0);
        return Py_BuildValue("(O,i)", datetime, offset);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_set_rtc(PyObject* self, PyObject* args)
{
    PyObject* datetime_object = NULL;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O|O:", __FUNCTION__), &obj, &datetime_object)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    PyDateTime_IMPORT;
    if (!PyDateTimeAPI) {
        return set_ics_exception(exception_runtime_error(), "Failed to initialize PyDateTime");
    }
    if (!datetime_object || !PyDateTime_Check(datetime_object)) {
        // We didn't get a valid Python DateTime Object, use current UTC Time
        time_t current_time = time(0);
        tm* current_utc_time = gmtime(&current_time);
        datetime_object = PyDateTime_FromDateAndTime(current_utc_time->tm_year+1900,
            current_utc_time->tm_mon+1,
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
    ics_time.year = PyDateTime_GET_YEAR(datetime_object) % 100;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, icsSpyTime*)>  icsneoSetRTC(lib, "icsneoSetRTC");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetRTC(handle, &ics_time)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoSetRTC() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_load(PyObject* self, PyObject* args)
{
    PyObject* arg_data = NULL;
    int location;
    PyObject* obj = NULL;
    bool isFileData = false;
    if (!PyArg_ParseTuple(args, arg_parse("OOi:", __FUNCTION__), &obj, &arg_data, &location)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;    
    long fsize;
    unsigned char* data = NULL;
    int data_size = 0;
#if PY_MAJOR_VERSION >= 3
    if (PyUnicode_CheckExact(arg_data)) {
        char* file_name = PyUnicode_AsUTF8(arg_data);
#else
    if (PyString_Check(arg_data)) {
        char* file_name = PyString_AsString(arg_data);
#endif
        if (!file_name) {
            return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to convert file path to string");
        }
        FILE* f;
        f = fopen(file_name, "rb");
        if (!f)    {
            std::stringstream ss;
            ss << "Failed to open CoreMini script file: '" << file_name << "'. Please make sure path exists";
            return set_ics_exception_dev(exception_runtime_error(), obj, (char*)ss.str().c_str());
        }
        fseek(f, 0, SEEK_END);
        fsize = ftell(f);
        rewind(f);
        data = (unsigned char*) malloc(sizeof(char)*fsize);
        data_size = (int)fread(data, 1, fsize, f);
        fclose(f);
        if (fsize != data_size) {
            return set_ics_exception_dev(exception_runtime_error(), obj, "CoreMini binary file size mismatch");
        }
    } else if (PyTuple_CheckExact(arg_data)) {
        Py_ssize_t tuple_size = PyTuple_Size(arg_data);
        data = (unsigned char*) malloc(sizeof(char)*tuple_size);
        // Move tuple data into array
        for (int i=0; i < tuple_size; ++i) {
            PyObject* value = PyTuple_GET_ITEM(arg_data, i);
            if (!PyLong_CheckExact(value)) {
                return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to convert tuple data. Tuple data must be integer type");
            }
            data[i] = (unsigned char)PyLong_AsLong(PyTuple_GET_ITEM(arg_data, i));
        }
        fsize = tuple_size;
        data_size = fsize;
    } else {
        return set_ics_exception_dev(exception_runtime_error(), obj, "Argument must be filepath or tuple");
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, const unsigned char*, unsigned long, int)> icsneoScriptLoad(lib, "icsneoScriptLoad");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptLoad(handle, data, data_size, location)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptLoad() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_start(PyObject* self, PyObject* args)
{
    int location;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &location)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, int)>   icsneoScriptStart(lib, "icsneoScriptStart");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptStart(handle, location)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStart() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_stop(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE)>  icsneoScriptStop(lib, "icsneoScriptStop");
        Py_BEGIN_ALLOW_THREADS
        if (! icsneoScriptStop(handle)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStop() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_clear(PyObject* self, PyObject* args)
{
    int location;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &location)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);

    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, int)> icsneoScriptClear(lib, "icsneoScriptClear");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptClear(handle, location)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptClear() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}


PyObject* meth_coremini_get_status(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;

    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, int*)> icsneoScriptGetScriptStatus(lib, "icsneoScriptGetScriptStatus");
        int status = 0;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptGetScriptStatus(handle, &status)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptClear() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", status==1);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_transmit_messages(PyObject* self, PyObject* args)
{
    PyObject* temp;
    bool created_tuple = false;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OO:", __FUNCTION__), &obj, &temp)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
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
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, icsSpyMessage*, int, int)> icsneoTxMessages(lib, "icsneoTxMessages");
        const Py_ssize_t TUPLE_COUNT = PyTuple_Size(tuple);
        icsSpyMessage** msgs = new icsSpyMessage*[TUPLE_COUNT]();
        for (int i=0; i < TUPLE_COUNT; ++i) {
            spy_message_object* obj = (spy_message_object*)PyTuple_GetItem(tuple, i);
            if (!obj) {
                if (created_tuple) {
                    Py_XDECREF(tuple);
                }
                delete[] msgs;
                return set_ics_exception(exception_runtime_error(), "Tuple item must be of " MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME);
            }
            msgs[i] = &(obj->msg);
        }
        Py_BEGIN_ALLOW_THREADS
        for (int i=0; i < TUPLE_COUNT; ++i) {
            if (!icsneoTxMessages(handle, msgs[i], msgs[i]->NetworkID, 1)) {
                Py_BLOCK_THREADS
                if (created_tuple) {
                    Py_XDECREF(tuple);
                }
                delete[] msgs;
                return set_ics_exception(exception_runtime_error(), "icsneoTxMessages() Failed");
            }
            /*
            if (msgs[i]->ExtraDataPtrEnabled && msgs[i]->ExtraDataPtr != NULL) {
                delete msgs[i]->ExtraDataPtr;
                msgs[i]->ExtraDataPtr = NULL;
                msgs[i]->ExtraDataPtrEnabled = 0;
            } 
            */
        }
        Py_END_ALLOW_THREADS
        if (created_tuple) {
            Py_XDECREF(tuple);
        }
        delete[] msgs;
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_messages(PyObject* self, PyObject* args)
{
    //Py_RETURN_NONE;
    double timeout = 0.1;
    int use_j1850 = 0;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O|bd:", __FUNCTION__), &obj, &use_j1850, &timeout)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    // Convert timeout to ms
    timeout *= 1000;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, icsSpyMessage*, int*, int*)> icsneoGetMessages(lib, "icsneoGetMessages");
        int count;
        int errors = 0;
        union SpyMessage {
            icsSpyMessageJ1850 msg_j1850;
            icsSpyMessage msg;
        };
        SpyMessage *msgs = PyMem_New(SpyMessage, 20000);
        if (!msgs) {
            // This should only happen if we run out of memory (malloc failure)?
            PyErr_Print();
            return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
        }
        for (double i=timeout; i > 0; --i) {
            count = 20000;
            errors = 0;
            Py_BEGIN_ALLOW_THREADS
            if (!icsneoGetMessages(handle, (icsSpyMessage*)msgs, &count, &errors) && !errors) {
                // We are going to try one more time just incase
                count = 20000;
                errors = 0;
                if (!icsneoGetMessages(handle, (icsSpyMessage*)msgs, &count, &errors)) {
                    Py_BLOCK_THREADS
                    return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoGetMessages() Failed");
                }
            }
            Py_END_ALLOW_THREADS
            if (count || errors) {
                break;
            }
            // We don't want to sleep, if there isn't a timeout left.
            if (i) {
                Sleep(1);
            }
        }
        PyObject* tuple = PyTuple_New(count);
        for (int i=0; i < count; ++i) {
            PyObject* obj = NULL;
            if (use_j1850) {
                obj = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            } else {
                obj = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            }
            if (!obj) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
            }
            if (use_j1850) {
                spy_message_j1850_object* msg = (spy_message_j1850_object*)obj;
                memcpy(&msg->msg, &msgs[i].msg_j1850, sizeof(msgs[i].msg_j1850));
                // Looks like icsneo40 does its own memory management so don't delete when we dealloc
                msg->noExtraDataPtrCleanup = true;
            } else {
                spy_message_object* msg = (spy_message_object*)obj;
                memcpy(&msg->msg, &msgs[i].msg, sizeof(msgs[i].msg));
                // Looks like icsneo40 does its own memory management so don't delete when we dealloc
                msg->noExtraDataPtrCleanup = true;
            }
            PyTuple_SetItem(tuple, i, obj);
        }
        PyObject* result = Py_BuildValue("(O,i)", tuple, errors);
        // We have to decrement the ref counter here because BuildValue increases it and
        // the tuple and its objects will never get freed causing a memory leak.
        Py_XDECREF(tuple);
        PyMem_Del(msgs);
        return result;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception_dev(exception_runtime_error(), obj, (char*)ex.what());
    }
    return set_ics_exception_dev(exception_runtime_error(), obj, "This is a bug!");
}

PyObject* meth_get_script_status(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    } 
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);

    unsigned long parameters[255] = {0};
    unsigned long parameters_count = 0;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned long*, unsigned long, unsigned long&)> icsneoScriptGetScriptStatusEx(lib, "icsneoScriptGetScriptStatusEx");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptGetScriptStatusEx(handle, parameters, sizeof(parameters)/sizeof(&parameters[0]), parameters_count)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptGetScriptStatusEx() Failed");
        }
        Py_END_ALLOW_THREADS
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    PyObject* list_object = PyList_New(0);
    for (unsigned long i=0; i < parameters_count; ++i) {
        PyObject* obj = Py_BuildValue("i", parameters[i]);
        PyList_Append(list_object, obj);
    }
    return list_object;
}

PyObject* meth_get_error_messages(PyObject* self, PyObject* args)
{
    //return PyList_New(0);
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    int errors[600] = {0};
    int error_count = 600;
    PyObject* list = PyList_New(0);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, int*, int*)> icsneoGetErrorMessages(lib, "icsneoGetErrorMessages");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetErrorMessages(handle, errors, &error_count)) {
            Py_UNBLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptGetScriptStatusEx() Failed");
        }
        Py_END_ALLOW_THREADS
        ice::Function<int __stdcall (int, char*, char*, int*, int*, int*, int*)> icsneoGetErrorInfo(lib, "icsneoGetErrorInfo");
        for (int i=0; i < error_count; ++i) {
            char description_short[255] = {0};
            char description_long[255] = {0};
            int description_short_length = 255;
            int description_long_length = 255;
            int severity = 0, restart_needed = 0;
            Py_BEGIN_ALLOW_THREADS
            if (!icsneoGetErrorInfo(errors[i], description_short, description_long, 
                &description_short_length, &description_long_length, &severity, &restart_needed)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoGetErrorInfo() Failed");
            }
            Py_END_ALLOW_THREADS
            PyObject* tuple = Py_BuildValue("i, s, s, i, i", errors[i], description_short, description_long, severity, restart_needed);
            PyList_Append(list, tuple);
        }
        return list;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyThreadState* _callback_save = NULL;
PyObject* msg_callback = NULL;
static void message_callback(const char* message, bool success)
{
    // We need to relock the GIL here otherwise we crash
    if (_callback_save) {
        PyEval_RestoreThread(_callback_save);
    }
    if (!msg_callback) {
        PySys_WriteStdout("%s\n", message);
    } else if (PyObject_HasAttrString(msg_callback, "message_callback")) {
        PyObject_CallMethod(msg_callback, "message_callback", "s,b", message, success);
    } else {
        PyObject_CallFunction(msg_callback, "s,b", message, success);
    }
    // Unlock the GIL here again...
    if (_callback_save) {
        _callback_save = PyEval_SaveThread();
    }
}

#ifdef _USE_INTERNAL_HEADER_
PyObject* meth_flash_devices(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    PyObject* callback = NULL;
    PyObject* dict;
    if (!PyArg_ParseTuple(args, arg_parse("OO|O:", __FUNCTION__), &obj, &dict, &callback)) {
        return NULL;
    }
    if (obj && !PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "First argument must be of " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME " type");
    }
    neo_device_object* neo_device = (neo_device_object*)obj;
    if (PyCallable_Check(callback) || PyObject_HasAttrString(callback, "message_callback")) {
        msg_callback = callback;
    } else {
        msg_callback = NULL;
    }
    if (dict && !PyDict_CheckExact(dict)) {
        return set_ics_exception(exception_runtime_error(), "Third argument must be of dictionary type");
    }
    // Populate rc array from the python dictionary
    SReflashChip_t rc[16] = {0};
    unsigned long reflash_count = 0;
    Py_ssize_t pos = 0;
    PyObject* key, * value;
    while (PyDict_Next(dict, &pos, &key, &value)) {
        unsigned long id = PyLong_AsUnsignedLong(key);
#if PY_MAJOR_VERSION >= 3
        char* path = PyUnicode_AsUTF8(value);
#else
        char* path = PyString_AsString(value);
#endif
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
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (unsigned long, NeoDevice*, const SReflashChip_t*, unsigned long, unsigned long, unsigned long, unsigned long, void*)> FlashDevice2(lib, "FlashDevice2");
        _callback_save = PyEval_SaveThread();
        if (!FlashDevice2(0x3835C256, &(neo_device->dev), rc, reflash_count, 0, 0, 0, &message_callback)) {
            PyEval_RestoreThread(_callback_save);
            return set_ics_exception(exception_runtime_error(), "FlashDevice2() Failed");
        }
        PyEval_RestoreThread(_callback_save);
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
#endif // _USE_INTERNAL_HEADER_

PyObject* msg_reflash_callback = NULL;
static void message_reflash_callback(const wchar_t* message, unsigned long progress)
{
    // We need to relock the GIL here otherwise we crash
    if (_callback_save) {
        PyEval_RestoreThread(_callback_save);
    }
    if (!msg_reflash_callback) {
        PySys_WriteStdout("%s -%d\n", message, progress);
    } else if (PyObject_HasAttrString(msg_reflash_callback, "reflash_callback")) {
        PyObject_CallMethod(msg_reflash_callback, "reflash_callback", "u,i", message, progress);
    } else {
        PyObject_CallFunction(msg_reflash_callback, "u,i", message, progress);
    }
    // Unlock the GIL here again...
    if (_callback_save) {
        _callback_save = PyEval_SaveThread();
    }
}

// void _stdcall icsneoSetReflashCallback( void(*OnReflashUpdate)(const wchar_t*,unsigned long) )
PyObject* meth_set_reflash_callback(PyObject* self, PyObject* args)
{
    PyObject* callback = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("|O:", __FUNCTION__), &callback)) {
        return NULL;
    }
    if (!callback) {
        msg_reflash_callback = NULL;
    } else {
        msg_reflash_callback = callback;
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (void(*)(const wchar_t*,unsigned long))> icsneoSetReflashCallback(lib, "icsneoSetReflashCallback");
        Py_BEGIN_ALLOW_THREADS
        if (callback == Py_None) {
            if (!icsneoSetReflashCallback(NULL)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoSetReflashCallback() Failed");
            }
        } else {
            if (!icsneoSetReflashCallback(&message_reflash_callback)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoSetReflashCallback() Failed");
            }
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

#define _get_vcan3_settings(handle) __get_vcan3_settings(handle, __FUNCTION__);
static PyObject* __get_vcan3_settings(ICS_HANDLE handle, char* func_name)
{
    PyObject* settings = PyObject_CallObject((PyObject*)&vcan3_settings_object_type, NULL);
    if (!settings) {
        // This should only happen if we run out of memory (malloc failure)?
        PyErr_Print();
        return set_ics_exception(exception_runtime_error(), "Failed to allocate " VCAN3_SETTINGS_OBJECT_NAME);
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, SVCAN3Settings*, int)> icsneoGetVCAN3Settings(lib, "icsneoGetVCAN3Settings");
        SVCAN3Settings* s = &((vcan3_settings_object*)settings)->s;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetVCAN3Settings(handle, s, sizeof(*s))) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoGetVCAN3Settings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        vcan3_settings_object* s_obj = (vcan3_settings_object*)settings;
        // Since CAN Structures are Python objects, we need to manually update them here.
        ((can_settings_object*)s_obj->can1)->s = s->can1;
        ((can_settings_object*)s_obj->can2)->s = s->can2;
        return settings;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

#define _get_vcan412_settings(handle) __get_vcan412_settings(handle, __FUNCTION__);
static PyObject* __get_vcan412_settings(ICS_HANDLE handle, char* func_name)
{
    PyObject* settings = PyObject_CallObject((PyObject*)&vcan412_settings_object_type, NULL);
    if (!settings) {
        // This should only happen if we run out of memory (malloc failure)?
        PyErr_Print();
        return set_ics_exception(exception_runtime_error(), "Failed to allocate " VCAN412_SETTINGS_OBJECT_NAME);
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, SVCAN412Settings*, int)> icsneoGetVCAN412Settings(lib, "icsneoGetVCAN412Settings");
        SVCAN412Settings* s = &((vcan412_settings_object*)settings)->s;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetVCAN412Settings(handle, s, sizeof(*s))) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoGetVCAN412Settings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        vcan412_settings_object* s_obj = (vcan412_settings_object*)settings;
        // Since CAN Structures are Python objects, we need to manually update them here.
        ((can_settings_object*)s_obj->can1)->s = s->can1;
        ((can_settings_object*)s_obj->can2)->s = s->can2;
        ((canfd_settings_object*)s_obj->canfd1)->s = s->canfd1;
        ((canfd_settings_object*)s_obj->canfd2)->s = s->canfd2;

        // Since TextAPI Structures are Python objects, we need to manually update them here.
        ((textapi_settings_object*)s_obj->textapi)->s = s->text_api;
        return settings;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

#if 0 // Not implemented in 802
#define _get_vcan4_settings(handle) __get_vcan4_settings(handle, __FUNCTION__);
static PyObject* __get_vcan4_settings(ICS_HANDLE handle, char* func_name)
{
    PyObject* settings = PyObject_CallObject((PyObject*)&vcan4_settings_object_type, NULL);
    if (!settings) {
        // This should only happen if we run out of memory (malloc failure)?
        PyErr_Print();
        return set_ics_exception(exception_runtime_error(), "Failed to allocate " VCAN4_SETTINGS_OBJECT_NAME);
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, SVCAN4Settings*, int)> icsneoGetVCAN4Settings(lib, "icsneoGetVCAN4Settings");
        SVCAN4Settings* s = &((vcan4_settings_object*)settings)->s;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetVCAN4Settings(handle, s, sizeof(*s))) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoGetVCAN4Settings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        vcan4_settings_object* s_obj = (vcan4_settings_object*)settings;
        // Since CAN Structures are Python objects, we need to manually update them here.
        ((can_settings_object*)s_obj->can1)->s = s->can1;
        ((can_settings_object*)s_obj->can2)->s = s->can2;
        ((can_settings_object*)s_obj->can3)->s = s->can3;
        ((can_settings_object*)s_obj->can4)->s = s->can4;
        ((canfd_settings_object*)s_obj->canfd1)->s = s->canfd1;
        ((canfd_settings_object*)s_obj->canfd2)->s = s->canfd2;
        ((canfd_settings_object*)s_obj->canfd3)->s = s->canfd3;
        ((canfd_settings_object*)s_obj->canfd4)->s = s->canfd4;
        // Since LIN Structures are Python objects, we need to manually update them here.
        ((lin_settings_object*)s_obj->lin1)->s = s->lin1;
        // Since ETHERNET Structures are Python objects, we need to manually update them here.
        ((ethernet_settings_object*)s_obj->ethernet)->s = s->ethernet;
        // Since ISO9141 Structures are Python objects, we need to manually update them here.
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s = s->iso9141_kwp_settings_1;
        // Since TextAPI Structures are Python objects, we need to manually update them here.
        ((textapi_settings_object*)s_obj->textapi)->s = s->text_api;

        return settings;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
#endif // 0

#define _get_vcanrf_settings(handle) __get_vcanrf_settings(handle, __FUNCTION__);
static PyObject* __get_vcanrf_settings(ICS_HANDLE handle, char* func_name)
{
    PyObject* settings = PyObject_CallObject((PyObject*)&vcanrf_settings_object_type, NULL);
    if (!settings) {
        // This should only happen if we run out of memory (malloc failure)?
        PyErr_Print();
        return set_ics_exception(exception_runtime_error(), "Failed to allocate " VCANRF_SETTINGS_OBJECT_NAME);
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SVCANRFSettings*, int)> icsneoGetVCANRFSettings(lib, "icsneoGetVCANRFSettings");
        SVCANRFSettings* s = &((vcanrf_settings_object*)settings)->s;
        int s_size = sizeof(*s);
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetVCANRFSettings(handle, s, s_size)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoGetVCANRFSettings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        vcanrf_settings_object* s_obj = (vcanrf_settings_object*)settings;
        // Since CAN Structures are Python objects, we need to manually update them here.
        ((can_settings_object*)s_obj->can1)->s = s->can1;
        ((can_settings_object*)s_obj->can2)->s = s->can2;
        ((can_settings_object*)s_obj->can3)->s = s->can3;
        ((can_settings_object*)s_obj->can4)->s = s->can4;
        // Since LIN Structures are Python objects, we need to manually update them here.
        ((lin_settings_object*)s_obj->lin1)->s = s->lin1;
        ((lin_settings_object*)s_obj->lin2)->s = s->lin2;
        // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp)->s = s->iso9141_kwp_settings;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp2)->s = s->iso9141_kwp_settings_2;
        // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
        PyObject* tuple1 = PyTuple_New(s->iso9141_kwp_settings.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple1); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings.init_steps[i];
            PyTuple_SetItem(tuple1, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp)->init_steps = tuple1;

        PyObject* tuple2 = PyTuple_New(s->iso9141_kwp_settings_2.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple2); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings_2.init_steps[i];
            PyTuple_SetItem(tuple2, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp2)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp2)->init_steps = tuple2;
        return settings;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

#define _get_fire_settings(handle) __get_fire_settings(handle, __FUNCTION__);
static PyObject* __get_fire_settings(ICS_HANDLE handle, char* func_name)
{
    PyObject* settings = PyObject_CallObject((PyObject*)&fire_settings_object_type, NULL);
    if (!settings) {
        // This should only happen if we run out of memory (malloc failure)?
        PyErr_Print();
        return set_ics_exception(exception_runtime_error(), "Failed to allocate " FIRE_SETTINGS_OBJECT_NAME);
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SFireSettings*, int)> icsneoGetFireSettings(lib, "icsneoGetFireSettings");
        SFireSettings* s = &((fire_settings_object*)settings)->s;
        int s_size = sizeof(*s);
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetFireSettings(handle, s, s_size)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoGetFireSettings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        fire_settings_object* s_obj = (fire_settings_object*)settings;
        // Since CAN Structures are Python objects, we need to manually update them here.
        ((can_settings_object*)s_obj->can1)->s = s->can1;
        ((can_settings_object*)s_obj->can2)->s = s->can2;
        ((can_settings_object*)s_obj->can3)->s = s->can3;
        ((can_settings_object*)s_obj->can4)->s = s->can4;
        ((can_settings_object*)s_obj->lsftcan)->s = s->lsftcan;
        ((swcan_settings_object*)s_obj->swcan)->s = s->swcan;
        // Since LIN Structures are Python objects, we need to manually update them here.
        ((lin_settings_object*)s_obj->lin1)->s = s->lin1;
        ((lin_settings_object*)s_obj->lin2)->s = s->lin2;
        ((lin_settings_object*)s_obj->lin3)->s = s->lin3;
        ((lin_settings_object*)s_obj->lin4)->s = s->lin4;
        // Since UART Structures are Python objects, we need to manually update them here.
        ((uart_settings_object*)s_obj->uart)->s = s->uart;
        ((uart_settings_object*)s_obj->uart2)->s = s->uart2;
        // Since TextAPI Structures are Python objects, we need to manually update them here.
        ((textapi_settings_object*)s_obj->textapi)->s = s->text_api;
        // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s = s->iso9141_kwp_settings;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s = s->iso9141_kwp_settings_2;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s = s->iso9141_kwp_settings_3;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s = s->iso9141_kwp_settings_4;
        // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
        PyObject* tuple1 = PyTuple_New(s->iso9141_kwp_settings.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple1); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings.init_steps[i];
            PyTuple_SetItem(tuple1, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple1;

        PyObject* tuple2 = PyTuple_New(s->iso9141_kwp_settings_2.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple2); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings_2.init_steps[i];
            PyTuple_SetItem(tuple2, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple2;

        PyObject* tuple3 = PyTuple_New(s->iso9141_kwp_settings_3.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple3); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings_3.init_steps[i];
            PyTuple_SetItem(tuple3, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple3;

        PyObject* tuple4 = PyTuple_New(s->iso9141_kwp_settings_4.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple4); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings_4.init_steps[i];
            PyTuple_SetItem(tuple4, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple4;
        return settings;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

#define _get_cyan_settings(handle) __get_cyan_settings(handle, __FUNCTION__);
static PyObject* __get_cyan_settings(ICS_HANDLE handle, char* func_name)
{
    PyObject* settings = PyObject_CallObject((PyObject*)&cyan_settings_object_type, NULL);
    if (!settings) {
        // This should only happen if we run out of memory (malloc failure)?
        PyErr_Print();
        return set_ics_exception(exception_runtime_error(), "Failed to allocate " FIRE_SETTINGS_OBJECT_NAME);
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SCyanSettings*, int)> icsneoGetFire2Settings(lib, "icsneoGetFire2Settings");
        SCyanSettings* s = &((cyan_settings_object*)settings)->s;
        int s_size = sizeof(*s);
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetFire2Settings(handle, s, s_size)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoGetFire2Settings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        cyan_settings_object* s_obj = (cyan_settings_object*)settings;
        // Since CAN Structures are Python objects, we need to manually update them here.
        ((can_settings_object*)s_obj->can1)->s = s->can1;
        ((can_settings_object*)s_obj->can2)->s = s->can2;
        ((can_settings_object*)s_obj->can3)->s = s->can3;
        ((can_settings_object*)s_obj->can4)->s = s->can4;
        ((can_settings_object*)s_obj->can5)->s = s->can5;
        ((can_settings_object*)s_obj->can6)->s = s->can6;
        ((can_settings_object*)s_obj->can7)->s = s->can7;
        ((can_settings_object*)s_obj->can8)->s = s->can8;
        // Since CAN Structures are Python objects, we need to manually update them here.
        ((canfd_settings_object*)s_obj->canfd1)->s = s->canfd1;
        ((canfd_settings_object*)s_obj->canfd2)->s = s->canfd2;
        ((canfd_settings_object*)s_obj->canfd3)->s = s->canfd3;
        ((canfd_settings_object*)s_obj->canfd4)->s = s->canfd4;
        ((canfd_settings_object*)s_obj->canfd5)->s = s->canfd5;
        ((canfd_settings_object*)s_obj->canfd6)->s = s->canfd6;
        ((canfd_settings_object*)s_obj->canfd7)->s = s->canfd7;
        ((canfd_settings_object*)s_obj->canfd8)->s = s->canfd8;
        ((can_settings_object*)s_obj->lsftcan1)->s = s->lsftcan1;
        ((can_settings_object*)s_obj->lsftcan2)->s = s->lsftcan2;
        ((swcan_settings_object*)s_obj->swcan1)->s = s->swcan1;
        ((swcan_settings_object*)s_obj->swcan2)->s = s->swcan2;
        // Since LIN Structures are Python objects, we need to manually update them here.
        ((lin_settings_object*)s_obj->lin1)->s = s->lin1;
        ((lin_settings_object*)s_obj->lin2)->s = s->lin2;
        ((lin_settings_object*)s_obj->lin3)->s = s->lin3;
        ((lin_settings_object*)s_obj->lin4)->s = s->lin4;
        ((lin_settings_object*)s_obj->lin5)->s = s->lin5;
        ((lin_settings_object*)s_obj->lin6)->s = s->lin6;
        // Since TextAPI Structures are Python objects, we need to manually update them here.
        ((textapi_settings_object*)s_obj->textapi)->s = s->text_api;
        // Since ETHERNET_SETTINGS Structures are Python objects, we need to manually update them here.
        ((ethernet_settings_object*)s_obj->ethernet)->s = s->ethernet;
        // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s = s->iso9141_kwp_settings_1;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s = s->iso9141_kwp_settings_2;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s = s->iso9141_kwp_settings_3;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s = s->iso9141_kwp_settings_4;
        // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
        PyObject* tuple1 = PyTuple_New(s->iso9141_kwp_settings_1.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple1); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings_1.init_steps[i];
            PyTuple_SetItem(tuple1, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple1;

        PyObject* tuple2 = PyTuple_New(s->iso9141_kwp_settings_2.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple2); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings_2.init_steps[i];
            PyTuple_SetItem(tuple2, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple2;

        PyObject* tuple3 = PyTuple_New(s->iso9141_kwp_settings_3.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple3); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings_3.init_steps[i];
            PyTuple_SetItem(tuple3, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple3;

        PyObject* tuple4 = PyTuple_New(s->iso9141_kwp_settings_4.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple4); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings_4.init_steps[i];
            PyTuple_SetItem(tuple4, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple4;
        return settings;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

#define _get_rad_galaxy_settings(handle) __get_rad_galaxy_settings(handle, __FUNCTION__);
static PyObject* __get_rad_galaxy_settings(ICS_HANDLE handle, char* func_name)
{
    PyObject* settings = PyObject_CallObject((PyObject*)&rad_galaxy_settings_object_type, NULL);
    if (!settings) {
        // This should only happen if we run out of memory (malloc failure)?
        PyErr_Print();
        return set_ics_exception(exception_runtime_error(), "Failed to allocate " FIRE_SETTINGS_OBJECT_NAME);
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SRADGalaxySettings*, int)> icsneoGetRADGalaxySettings(lib, "icsneoGetRADGalaxySettings");
        SRADGalaxySettings* s = &((rad_galaxy_settings_object*)settings)->s;
        int s_size = sizeof(*s);
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetRADGalaxySettings(handle, s, s_size)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoGetRADGalaxySettings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        rad_galaxy_settings_object* s_obj = (rad_galaxy_settings_object*)settings;
        // Since ETH Structures are Python objects, we need to manually update them here.
        ((op_eth_general_settings_object*)s_obj->opEthGen)->s = s->opEthGen;
        ((op_eth_settings_object*)s_obj->opEth1)->s = s->opEth1;
        ((op_eth_settings_object*)s_obj->opEth2)->s = s->opEth2;
        ((op_eth_settings_object*)s_obj->opEth3)->s = s->opEth3;
        ((op_eth_settings_object*)s_obj->opEth4)->s = s->opEth4;
        ((op_eth_settings_object*)s_obj->opEth5)->s = s->opEth5;
        ((op_eth_settings_object*)s_obj->opEth6)->s = s->opEth6;
        ((op_eth_settings_object*)s_obj->opEth7)->s = s->opEth7;
        ((op_eth_settings_object*)s_obj->opEth8)->s = s->opEth8;
        ((op_eth_settings_object*)s_obj->opEth9)->s = s->opEth9;
        ((op_eth_settings_object*)s_obj->opEth10)->s = s->opEth10;
        ((op_eth_settings_object*)s_obj->opEth11)->s = s->opEth11;
        ((op_eth_settings_object*)s_obj->opEth12)->s = s->opEth12;
        // Since CAN Structures are Python objects, we need to manually update them here.
        ((can_settings_object*)s_obj->can1)->s = s->can1;
        ((can_settings_object*)s_obj->can2)->s = s->can2;
        ((can_settings_object*)s_obj->can3)->s = s->can3;
        ((can_settings_object*)s_obj->can4)->s = s->can4;
        ((can_settings_object*)s_obj->can5)->s = s->can5;
        ((can_settings_object*)s_obj->can6)->s = s->can6;
        ((can_settings_object*)s_obj->can7)->s = s->can7;
        ((can_settings_object*)s_obj->can8)->s = s->can8;
        // Since CAN Structures are Python objects, we need to manually update them here.
        ((canfd_settings_object*)s_obj->canfd1)->s = s->canfd1;
        ((canfd_settings_object*)s_obj->canfd2)->s = s->canfd2;
        ((canfd_settings_object*)s_obj->canfd3)->s = s->canfd3;
        ((canfd_settings_object*)s_obj->canfd4)->s = s->canfd4;
        ((canfd_settings_object*)s_obj->canfd5)->s = s->canfd5;
        ((canfd_settings_object*)s_obj->canfd6)->s = s->canfd6;
        ((canfd_settings_object*)s_obj->canfd7)->s = s->canfd7;
        ((canfd_settings_object*)s_obj->canfd8)->s = s->canfd8;
        ((swcan_settings_object*)s_obj->swcan1)->s = s->swcan1;
        ((swcan_settings_object*)s_obj->swcan2)->s = s->swcan2;
        // Since LIN Structures are Python objects, we need to manually update them here.
        ((lin_settings_object*)s_obj->lin1)->s = s->lin1;
        // Since TextAPI Structures are Python objects, we need to manually update them here.
        ((textapi_settings_object*)s_obj->textapi)->s = s->text_api;
        // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s = s->iso9141_kwp_settings_1;

        // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
        PyObject* tuple1 = PyTuple_New(s->iso9141_kwp_settings_1.init_step_count);
        for (int i=0; i < PyTuple_Size(tuple1); ++i) {
            iso9141keyword2000_init_steps_object* temp = 
                (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
            temp->s = s->iso9141_kwp_settings_1.init_steps[i];
            PyTuple_SetItem(tuple1, i, (PyObject*)temp);
        }
        Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps);
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple1;
        return settings;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

#define _get_vividcan_settings(handle) __get_vividcan_settings(handle, __FUNCTION__);
static PyObject* __get_vividcan_settings(ICS_HANDLE handle, char* func_name)
{
    PyObject* settings = PyObject_CallObject((PyObject*)&vividcan_settings_object_type, NULL);
    if (!settings) {
        // This should only happen if we run out of memory (malloc failure)?
        PyErr_Print();
        return set_ics_exception(exception_runtime_error(), "Failed to allocate " VIVIDCAN_SETTINGS_OBJECT_NAME);
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, SVividCANSettings*, int)> icsneoGetVividCANSettings(lib, "icsneoGetVividCANSettings");
        SVividCANSettings* s = &((vividcan_settings_object*)settings)->s;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetVividCANSettings(handle, s, sizeof(*s))) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoGetVividCANSettings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        vividcan_settings_object* s_obj = (vividcan_settings_object*)settings;
        // Since CAN Structures are Python objects, we need to manually update them here.
        ((can_settings_object*)s_obj->can1)->s = s->can1;
		((swcan_settings_object*)s_obj->swcan1)->s = s->swcan1;
		((can_settings_object*)s_obj->lsftcan1)->s = s->lsftcan1;
        return settings;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_device_settings(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned long device_type = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O|k:", __FUNCTION__), &obj, &device_type)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    // User is overriding the device type here, this is useful for FIRE2 VNET for PLASMA/ION.
    if (!device_type)
        device_type = ((neo_device_object*)obj)->dev.DeviceType;
    switch(device_type)
    {
        case NEODEVICE_VCAN3:
            return _get_vcan3_settings(handle);
            break;
        case NEODEVICE_VCAN41:
        case NEODEVICE_VCAN42:
            return _get_vcan412_settings(handle);
            break;
#if 0 // Not implemented in 802
        case NEODEVICE_VCAN4:
            return _get_vcan4_settings(handle);
            break;
#endif // 0
        case NEODEVICE_VCANRF:
            return _get_vcanrf_settings(handle);
            break;
        case NEODEVICE_FIRE2:
            return _get_cyan_settings(handle);
            break;
        case NEODEVICE_RADGALAXY:
            return _get_rad_galaxy_settings(handle);
            break;
        case NEODEVICE_VIVIDCAN:
            return _get_vividcan_settings(handle);
            break;
        default:
            return _get_fire_settings(handle);
            break;
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

static PyObject* __set_vcan3_settings(ICS_HANDLE handle, PyObject* settings, int& save, char* func_name)
{
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SVCAN3Settings*, int, int)> icsneoSetVCAN3Settings(lib, "icsneoSetVCAN3Settings");
        vcan3_settings_object* s_obj = (vcan3_settings_object*)settings;
        SVCAN3Settings* s = &s_obj->s;
        // Since CAN Structures are Python objects, we need to manually update them here.
        s->can1 = ((can_settings_object*)s_obj->can1)->s;
        s->can2 = ((can_settings_object*)s_obj->can2)->s;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetVCAN3Settings(handle, s, sizeof(*s), save)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoSetVCAN3Settings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
#define _set_vcan3_settings(handle, settings, save) __set_vcan3_settings(handle, settings, save, __FUNCTION__);

static PyObject* __set_vcan412_settings(ICS_HANDLE handle, PyObject* settings, int& save, char* func_name)
{
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SVCAN412Settings*, int, unsigned char)> icsneoSetVCAN412Settings(lib, "icsneoSetVCAN412Settings");
        vcan412_settings_object* s_obj = (vcan412_settings_object*)settings;
        SVCAN412Settings* s = &s_obj->s;
        // Since CAN Structures are Python objects, we need to manually update them here.
        s->can1 = ((can_settings_object*)s_obj->can1)->s;
        s->can2 = ((can_settings_object*)s_obj->can2)->s;
        s->canfd1 = ((canfd_settings_object*)s_obj->canfd1)->s;
        s->canfd2 = ((canfd_settings_object*)s_obj->canfd2)->s;
        // Since textapi Structures are Python objects, we need to manually update them here.
        s->text_api = ((textapi_settings_object*)s_obj->textapi)->s;

        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetVCAN412Settings(handle, s, sizeof(*s), save)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoSetVCAN412Settings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
#define _set_vcan412_settings(handle, settings, save) __set_vcan412_settings(handle, settings, save, __FUNCTION__);

#if 0 // not implemented in 802
static PyObject* __set_vcan4_settings(ICS_HANDLE handle, PyObject* settings, int& save, char* func_name)
{
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SVCAN4Settings*, int, unsigned char)> icsneoSetVCAN4Settings(lib, "icsneoSetVCAN4Settings");
        vcan4_settings_object* s_obj = (vcan4_settings_object*)settings;
        SVCAN4Settings* s = &s_obj->s;
        // Since CAN Structures are Python objects, we need to manually update them here.
        s->can1 = ((can_settings_object*)s_obj->can1)->s;
        s->can2 = ((can_settings_object*)s_obj->can2)->s;
        s->can3 = ((can_settings_object*)s_obj->can3)->s;
        s->can4 = ((can_settings_object*)s_obj->can4)->s;
        s->canfd1 = ((canfd_settings_object*)s_obj->canfd1)->s;
        s->canfd2 = ((canfd_settings_object*)s_obj->canfd2)->s;
        s->canfd3 = ((canfd_settings_object*)s_obj->canfd3)->s;
        s->canfd4 = ((canfd_settings_object*)s_obj->canfd4)->s;
        // Since LIN Structures are Python objects, we need to manually update them here.
        s->lin1 = ((lin_settings_object*)s_obj->lin1)->s;
        // Since ETHERNET Structures are Python objects, we need to manually update them here.
        s->ethernet = ((ethernet_settings_object*)s_obj->ethernet)->s;
        // Since ISO Structures are Python objects, we need to manually update them here.
        s->iso9141_kwp_settings_1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s;
        // Since textapi Structures are Python objects, we need to manually update them here.
        s->text_api = ((textapi_settings_object*)s_obj->textapi)->s;

        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetVCAN4Settings(handle, s, sizeof(*s), save)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoSetVCAN4Settings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
#define _set_vcan4_settings(handle, settings, save) __set_vcan4_settings(handle, settings, save, __FUNCTION__);
#endif // 0

static PyObject* __set_vcanrf_settings(ICS_HANDLE handle, PyObject* settings, int& save, char* func_name)
{
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SVCANRFSettings*, int, int)> icsneoSetVCANRFSettings(lib, "icsneoSetVCANRFSettings");
        vcanrf_settings_object* s_obj = (vcanrf_settings_object*)settings;
        SVCANRFSettings* s = &s_obj->s;
        // Since CAN Structures are Python objects, we need to manually update them here.
        s->can1 = ((can_settings_object*)s_obj->can1)->s;
        s->can2 = ((can_settings_object*)s_obj->can2)->s;
        s->can3 = ((can_settings_object*)s_obj->can3)->s;
        s->can4 = ((can_settings_object*)s_obj->can4)->s;
        // Since LIN Structures are Python objects, we need to manually update them here.
        s->lin1 = ((lin_settings_object*)s_obj->lin1)->s;
        s->lin2 = ((lin_settings_object*)s_obj->lin2)->s;
        // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
        s->iso9141_kwp_settings = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp)->s;
        s->iso9141_kwp_settings_2 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp2)->s;
        // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
        PyObject* tuple1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp)->s.init_step_count = PyTuple_Size(tuple1);
        for (int i=0; i < PyTuple_Size(tuple1); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple1, i);
            s->iso9141_kwp_settings.init_steps[i] = temp->s;
        }
        PyObject* tuple2 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp2)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kwp2)->s.init_step_count = PyTuple_Size(tuple2);
        for (int i=0; i < PyTuple_Size(tuple2); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple2, i);
            s->iso9141_kwp_settings_2.init_steps[i] = temp->s;
        }
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetVCANRFSettings(handle, s, sizeof(*s), save)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoSetVCANRFSettings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
#define _set_vcanrf_settings(handle, settings, save) __set_vcanrf_settings(handle, settings, save, __FUNCTION__);

static PyObject* __set_fire_settings(ICS_HANDLE handle, PyObject* settings, int& save, char* func_name)
{
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SFireSettings*, int, int)> icsneoSetFireSettings(lib, "icsneoSetFireSettings");
        fire_settings_object* s_obj = (fire_settings_object*)settings;
        SFireSettings* s = &s_obj->s;
        // Since CAN Structures are Python objects, we need to manually update them here.
        s->can1 = ((can_settings_object*)s_obj->can1)->s;
        s->can2 = ((can_settings_object*)s_obj->can2)->s;
        s->can3 = ((can_settings_object*)s_obj->can3)->s;
        s->can4 = ((can_settings_object*)s_obj->can4)->s;
        s->lsftcan = ((can_settings_object*)s_obj->lsftcan)->s;
        s->swcan = ((swcan_settings_object*)s_obj->swcan)->s;
        // Since LIN Structures are Python objects, we need to manually update them here.
        s->lin1 = ((lin_settings_object*)s_obj->lin1)->s;
        s->lin2 = ((lin_settings_object*)s_obj->lin2)->s;
        s->lin3 = ((lin_settings_object*)s_obj->lin3)->s;
        s->lin4 = ((lin_settings_object*)s_obj->lin4)->s;
        // Since UART Structures are Python objects, we need to manually update them here.
        s->uart = ((uart_settings_object*)s_obj->uart)->s;
        s->uart2 = ((uart_settings_object*)s_obj->uart2)->s;
        // Since TextAPI Structures are Python objects, we need to manually update them here.
        ((textapi_settings_object*)s_obj->textapi)->s = s->text_api; 
        // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
        s->iso9141_kwp_settings = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s;
        s->iso9141_kwp_settings_2 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s;
        s->iso9141_kwp_settings_3 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s;
        s->iso9141_kwp_settings_4 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s;
        // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
        PyObject* tuple1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s.init_step_count = PyTuple_Size(tuple1);
        for (int i=0; i < PyTuple_Size(tuple1); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple1, i);
            s->iso9141_kwp_settings.init_steps[i] = temp->s;
        }
        PyObject* tuple2 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s.init_step_count = PyTuple_Size(tuple2);
        for (int i=0; i < PyTuple_Size(tuple2); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple2, i);
            s->iso9141_kwp_settings_2.init_steps[i] = temp->s;
        }
        PyObject* tuple3 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s.init_step_count = PyTuple_Size(tuple3);
        for (int i=0; i < PyTuple_Size(tuple3); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple3, i);
            s->iso9141_kwp_settings_3.init_steps[i] = temp->s;
        }
        PyObject* tuple4 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s.init_step_count = PyTuple_Size(tuple4);
        for (int i=0; i < PyTuple_Size(tuple4); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple4, i);
            s->iso9141_kwp_settings_4.init_steps[i] = temp->s;
        }
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetFireSettings(handle, s, sizeof(*s), save)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoSetFireSettings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
#define _set_fire_settings(handle, settings, save) __set_fire_settings(handle, settings, save, __FUNCTION__);

static PyObject* __set_cyan_settings(ICS_HANDLE handle, PyObject* settings, int& save, char* func_name)
{
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SCyanSettings*, int, int)> icsneoSetFire2Settings(lib, "icsneoSetFire2Settings");
        cyan_settings_object* s_obj = (cyan_settings_object*)settings;
        SCyanSettings* s = &s_obj->s;
        // Since CAN Structures are Python objects, we need to manually update them here.
        s->can1 = ((can_settings_object*)s_obj->can1)->s;
        s->can2 = ((can_settings_object*)s_obj->can2)->s;
        s->can3 = ((can_settings_object*)s_obj->can3)->s;
        s->can4 = ((can_settings_object*)s_obj->can4)->s;
        s->can5 = ((can_settings_object*)s_obj->can5)->s;
        s->can6 = ((can_settings_object*)s_obj->can6)->s;
        s->can7 = ((can_settings_object*)s_obj->can7)->s;
        s->can8 = ((can_settings_object*)s_obj->can8)->s;
        // Since CANFD Structures are Python objects, we need to manually update them here.
        s->canfd1 = ((canfd_settings_object*)s_obj->canfd1)->s;
        s->canfd2 = ((canfd_settings_object*)s_obj->canfd2)->s;
        s->canfd3 = ((canfd_settings_object*)s_obj->canfd3)->s;
        s->canfd4 = ((canfd_settings_object*)s_obj->canfd4)->s;
        s->canfd5 = ((canfd_settings_object*)s_obj->canfd5)->s;
        s->canfd6 = ((canfd_settings_object*)s_obj->canfd6)->s;
        s->canfd7 = ((canfd_settings_object*)s_obj->canfd7)->s;
        s->canfd8 = ((canfd_settings_object*)s_obj->canfd8)->s;

        s->lsftcan1 = ((can_settings_object*)s_obj->lsftcan1)->s;
        s->lsftcan2 = ((can_settings_object*)s_obj->lsftcan2)->s;
        s->swcan1 = ((swcan_settings_object*)s_obj->swcan1)->s;
        s->swcan2 = ((swcan_settings_object*)s_obj->swcan2)->s;
        // Since LIN Structures are Python objects, we need to manually update them here.
        s->lin1 = ((lin_settings_object*)s_obj->lin1)->s;
        s->lin2 = ((lin_settings_object*)s_obj->lin2)->s;
        s->lin3 = ((lin_settings_object*)s_obj->lin3)->s;
        s->lin4 = ((lin_settings_object*)s_obj->lin4)->s;
        s->lin5 = ((lin_settings_object*)s_obj->lin5)->s;
        s->lin6 = ((lin_settings_object*)s_obj->lin6)->s;
        // Since TextAPI Structures are Python objects, we need to manually update them here.
        ((textapi_settings_object*)s_obj->textapi)->s = s->text_api; 
        // Since ETHERNET_SETTINGS Structures are Python objects, we need to manually update them here.
        ((ethernet_settings_object*)s_obj->ethernet)->s = s->ethernet; 
        // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
        s->iso9141_kwp_settings_1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s;
        s->iso9141_kwp_settings_2 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s;
        s->iso9141_kwp_settings_3 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s;
        s->iso9141_kwp_settings_4 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s;
        // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
        PyObject* tuple1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s.init_step_count = PyTuple_Size(tuple1);
        for (int i=0; i < PyTuple_Size(tuple1); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple1, i);
            s->iso9141_kwp_settings_1.init_steps[i] = temp->s;
        }
        PyObject* tuple2 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s.init_step_count = PyTuple_Size(tuple2);
        for (int i=0; i < PyTuple_Size(tuple2); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple2, i);
            s->iso9141_kwp_settings_2.init_steps[i] = temp->s;
        }
        PyObject* tuple3 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s.init_step_count = PyTuple_Size(tuple3);
        for (int i=0; i < PyTuple_Size(tuple3); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple3, i);
            s->iso9141_kwp_settings_3.init_steps[i] = temp->s;
        }
        PyObject* tuple4 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s.init_step_count = PyTuple_Size(tuple4);
        for (int i=0; i < PyTuple_Size(tuple4); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple4, i);
            s->iso9141_kwp_settings_4.init_steps[i] = temp->s;
        }
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetFire2Settings(handle, s, sizeof(*s), save)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoSetFire2Settings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
#define _set_cyan_settings(handle, settings, save) __set_cyan_settings(handle, settings, save, __FUNCTION__);

static PyObject* __set_rad_galaxy_settings(ICS_HANDLE handle, PyObject* settings, int& save, char* func_name)
{
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SRADGalaxySettings*, int, int)> icsneoSetRADGalaxySettings(lib, "icsneoSetRADGalaxySettings");
        rad_galaxy_settings_object* s_obj = (rad_galaxy_settings_object*)settings;
        SRADGalaxySettings* s = &s_obj->s;
        // Since ETH Structures are Python objects, we need to manually update them here.
        s->opEthGen = ((op_eth_general_settings_object*)s_obj->opEthGen)->s;
        s->opEth1 = ((op_eth_settings_object*)s_obj->opEth1)->s;
        s->opEth2 = ((op_eth_settings_object*)s_obj->opEth2)->s;
        s->opEth3 = ((op_eth_settings_object*)s_obj->opEth3)->s;
        s->opEth4 = ((op_eth_settings_object*)s_obj->opEth4)->s;
        s->opEth5 = ((op_eth_settings_object*)s_obj->opEth5)->s;
        s->opEth6 = ((op_eth_settings_object*)s_obj->opEth6)->s;
        s->opEth7 = ((op_eth_settings_object*)s_obj->opEth7)->s;
        s->opEth8 = ((op_eth_settings_object*)s_obj->opEth8)->s;
        s->opEth9 = ((op_eth_settings_object*)s_obj->opEth9)->s;
        s->opEth10 = ((op_eth_settings_object*)s_obj->opEth10)->s;
        s->opEth11 = ((op_eth_settings_object*)s_obj->opEth11)->s;
        s->opEth12 = ((op_eth_settings_object*)s_obj->opEth12)->s;
        // Since CAN Structures are Python objects, we need to manually update them here.
        s->can1 = ((can_settings_object*)s_obj->can1)->s;
        s->can2 = ((can_settings_object*)s_obj->can2)->s;
        s->can3 = ((can_settings_object*)s_obj->can3)->s;
        s->can4 = ((can_settings_object*)s_obj->can4)->s;
        s->can5 = ((can_settings_object*)s_obj->can5)->s;
        s->can6 = ((can_settings_object*)s_obj->can6)->s;
        s->can7 = ((can_settings_object*)s_obj->can7)->s;
        s->can8 = ((can_settings_object*)s_obj->can8)->s;
        // Since CANFD Structures are Python objects, we need to manually update them here.
        s->canfd1 = ((canfd_settings_object*)s_obj->canfd1)->s;
        s->canfd2 = ((canfd_settings_object*)s_obj->canfd2)->s;
        s->canfd3 = ((canfd_settings_object*)s_obj->canfd3)->s;
        s->canfd4 = ((canfd_settings_object*)s_obj->canfd4)->s;
        s->canfd5 = ((canfd_settings_object*)s_obj->canfd5)->s;
        s->canfd6 = ((canfd_settings_object*)s_obj->canfd6)->s;
        s->canfd7 = ((canfd_settings_object*)s_obj->canfd7)->s;
        s->canfd8 = ((canfd_settings_object*)s_obj->canfd8)->s;

        s->swcan1 = ((swcan_settings_object*)s_obj->swcan1)->s;
        s->swcan2 = ((swcan_settings_object*)s_obj->swcan2)->s;
        // Since LIN Structures are Python objects, we need to manually update them here.
        s->lin1 = ((lin_settings_object*)s_obj->lin1)->s;
        // Since TextAPI Structures are Python objects, we need to manually update them here.
        ((textapi_settings_object*)s_obj->textapi)->s = s->text_api; 
        // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
        s->iso9141_kwp_settings_1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s;
        // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
        PyObject* tuple1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps;
        ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s.init_step_count = PyTuple_Size(tuple1);
        for (int i=0; i < PyTuple_Size(tuple1); ++i) {
            iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple1, i);
            s->iso9141_kwp_settings_1.init_steps[i] = temp->s;
        }
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetRADGalaxySettings(handle, s, sizeof(*s), save)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoSetRADGalaxySettings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
#define _set_rad_galaxy_settings(handle, settings, save) __set_rad_galaxy_settings(handle, settings, save, __FUNCTION__);

static PyObject* __set_vividcan_settings(ICS_HANDLE handle, PyObject* settings, int& save, char* func_name)
{
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return _set_ics_exception(exception_runtime_error(), dll_get_error(buffer), func_name);
        }
        ice::Function<int __stdcall (ICS_HANDLE, SVividCANSettings*, int, unsigned char)> icsneoSetVividCANSettings(lib, "icsneoSetVividCANSettings");
        vividcan_settings_object* s_obj = (vividcan_settings_object*)settings;
        SVividCANSettings* s = &s_obj->s;
        // Since CAN Structures are Python objects, we need to manually update them here.
        s->can1 = ((can_settings_object*)s_obj->can1)->s;
		s->swcan1 = ((swcan_settings_object*)s_obj->swcan1)->s;
		s->lsftcan1 = ((can_settings_object*)s_obj->lsftcan1)->s;

        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetVividCANSettings(handle, s, sizeof(*s), save)) {
            Py_BLOCK_THREADS
            return _set_ics_exception(exception_runtime_error(), "icsneoSetVividCANSettings() Failed", func_name);
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return _set_ics_exception(exception_runtime_error(), (char*)ex.what(), func_name);
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
#define _set_vividcan_settings(handle, settings, save) __set_vividcan_settings(handle, settings, save, __FUNCTION__);

PyObject* meth_set_device_settings(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    PyObject* settings = NULL;
    unsigned long device_type = 0;
    int save_to_eeprom = 1;
    if (!PyArg_ParseTuple(args, arg_parse("OO|ki:", __FUNCTION__), &obj, &settings, &device_type, &save_to_eeprom)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    if (!device_type)
        device_type = ((neo_device_object*)obj)->dev.DeviceType;
    switch(device_type)
    {
        case NEODEVICE_VCAN3:
            return _set_vcan3_settings(handle, settings, save_to_eeprom);
            break;
        case NEODEVICE_VCAN41:
        case NEODEVICE_VCAN42:
            return _set_vcan412_settings(handle, settings, save_to_eeprom);
            break;
#if 0 // Not implemented in 802
        case NEODEVICE_VCAN4:
            return _set_vcan4_settings(handle, settings, save_to_eeprom);
            break;
#endif // 0
        case NEODEVICE_VCANRF:
            return _set_vcanrf_settings(handle, settings, save_to_eeprom);
            break;
        case NEODEVICE_FIRE2:
            return _set_cyan_settings(handle, settings, save_to_eeprom);
            break;
        case NEODEVICE_RADGALAXY:
            return _set_rad_galaxy_settings(handle, settings, save_to_eeprom);
            break;
        case NEODEVICE_VIVIDCAN:
            return _set_vividcan_settings(handle, settings, save_to_eeprom);
            break;
        default:
            return _set_fire_settings(handle, settings, save_to_eeprom);
            break;
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_load_default_settings(PyObject* self, PyObject* args) // icsneoLoadDefaultSettings
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    int errors[600] = {0};
    int error_count = 600;
    PyObject* list = PyList_New(0);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE)> icsneoLoadDefaultSettings(lib, "icsneoLoadDefaultSettings");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoLoadDefaultSettings(PyNeoDevice_GetNeoDevice(obj)->handle)) {
            Py_BLOCK_THREADS
            return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoLoadDefaultSettings() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_read_sdcard(PyObject* self, PyObject* args) // icsneoReadSDCard(int hObject,unsigned long iSectorIndex,unsigned char *data, unsigned long *bytesRead)
{
    PyObject* obj = NULL;
    unsigned long index = 0;
    unsigned long size = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Ok:", __FUNCTION__), &obj, &index, &size)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    // We only read 512 bytes internally, x4 for future compatibility?
    unsigned char data[2048] = {0};
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned long, unsigned char*, unsigned long*)> icsneoReadSDCard(lib, "icsneoReadSDCard");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoReadSDCard(PyNeoDevice_GetNeoDevice(obj)->handle, index, data, &size)) {
            Py_BLOCK_THREADS
            return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoReadSDCard() Failed");
        }
        Py_END_ALLOW_THREADS
        PyObject* tuple = PyTuple_New(size);
        if (!tuple) {
            return NULL;
        }
        for (unsigned long i=0; i < size; ++i) {
            PyTuple_SetItem(tuple, i, PyLong_FromLong(data[i]));
        }
        PyObject* byte_array = PyByteArray_FromObject(tuple);
        Py_DECREF(tuple);
        return byte_array;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_write_sdcard(PyObject* self, PyObject* args) // icsneoWriteSDCard(int hObject,unsigned long iSectorIndex,const unsigned char *data)
{
    PyObject* obj = NULL;
    unsigned long index = 0;
    PyObject* ba_obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OkO:", __FUNCTION__), &obj, &index, &ba_obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    if (!PyByteArray_CheckExact(ba_obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be a bytearray");
    }
    if (PyByteArray_Size(ba_obj) != 512) {
        return set_ics_exception(exception_runtime_error(), "bytearray must be 512 in length");
    }
    // We only read 512 bytes internally, x4 for future compatibility?
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned long, unsigned char*)> icsneoWriteSDCard(lib, "icsneoWriteSDCard");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoWriteSDCard(PyNeoDevice_GetNeoDevice(obj)->handle, index, (unsigned char*)PyByteArray_AsString(ba_obj))) {
            Py_BLOCK_THREADS    
            return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoWriteSDCard() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_create_neovi_radio_message(PyObject* self, PyObject* args, PyObject* keywords)
{
    //int PyArg_ParseTupleAndKeywords(PyObject *args, PyObject *kw, const char *format, char *keywords[], ...)
    PyObject* obj = NULL;
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
    int relay_timeout=0;
    char* kwords[] = { "Relay1", "Relay2", "Relay3", "Relay4", "Relay5", "LED5",
        "LED6", "MSB_report_rate", "LSB_report_rate", "analog_change_report_rate", "relay_timeout" };
    // Accepts keywords: Relay1-Relay5 (boolean), LED5 (boolean), LED6 (boolean), MSB_report_rate (int), 
    // LSB_report_rate (int), analog_change_report_rate (int), relay_timeout (int).
    if (!PyArg_ParseTupleAndKeywords(args, keywords, arg_parse("|bbbbbbbiiii:", __FUNCTION__), kwords, &relay1, &relay2, 
        &relay3, &relay4, &relay5, &led5, &led6, &msb, &lsb, &analog, &relay_timeout)) {
        return NULL;
    }
    int byte1 = 0;
    byte1 |= (relay1 ? 1:0) << 6;
    byte1 |= (relay2 ? 1:0) << 5;
    byte1 |= (relay3 ? 1:0) << 4;
    byte1 |= (relay4 ? 1:0) << 3;
    byte1 |= (relay5 ? 1:0) << 2;
    byte1 |= (led5 ? 1:0) << 1;
    byte1 |= (led6 ? 1:0) << 0;
    int byte2 = msb & 0xFF;
    int byte3 = lsb & 0xFF;
    int byte4 = analog & 0xFF;
    int byte5 = relay_timeout & 0xFF;
    return Py_BuildValue("(i,i,i,i,i)", byte1, byte2, byte3, byte4, byte5);
}

PyObject* meth_coremini_start_fblock(PyObject* self, PyObject* args)
{
    int index;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &index)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int)> icsneoScriptStartFBlock(lib, "icsneoScriptStartFBlock");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptStartFBlock(handle, index)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStartFBlock() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_stop_fblock(PyObject* self, PyObject* args)
{
    int index;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &index)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int)> icsneoScriptStopFBlock(lib, "icsneoScriptStopFBlock");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptStopFBlock(handle, index)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStopFBlock() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_get_fblock_status(PyObject* self, PyObject* args)
{
    int index;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &index)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, int*)> icsneoScriptGetFBlockStatus(lib, "icsneoScriptGetFBlockStatus");
        int status = 0;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptGetFBlockStatus(handle, index, &status)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptGetFBlockStatus() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", status == 1);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_read_app_signal(PyObject* self, PyObject* args) //ScriptReadAppSignal
{
    int index;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &index)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, double*)> icsneoScriptReadAppSignal(lib, "icsneoScriptReadAppSignal");
        double value = 0;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptReadAppSignal(handle, index, &value)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptReadAppSignal() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("i", value);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_write_app_signal(PyObject* self, PyObject* args) //ScriptWriteAppSignal
{
    int index;
    PyObject* obj = NULL;
    double value = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oii:", __FUNCTION__), &obj, &index, &value)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, double)> icsneoScriptWriteAppSignal(lib, "icsneoScriptWriteAppSignal");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptWriteAppSignal(handle, index, value)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptWriteAppSignal() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_read_tx_message(PyObject* self, PyObject* args) //ScriptReadTxMessage
{
    int index;
    PyObject* obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oi|b:", __FUNCTION__), &obj, &index, &j1850)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, void*)> icsneoScriptReadTxMessage(lib, "icsneoScriptReadTxMessage");
        PyObject* msg = NULL;
        if (j1850) {
            msg = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            if (!msg) {
                    // This should only happen if we run out of memory (malloc failure)?
                    PyErr_Print();
                    return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_J1850_OBJECT_NAME);
            }
            Py_BEGIN_ALLOW_THREADS
            if (!icsneoScriptReadTxMessage(handle, index, &PySpyMessageJ1850_GetObject(msg)->msg)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadTxMessage() Failed");
            }
            Py_END_ALLOW_THREADS
        } else {
            PyObject* msg = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            if (!msg) {
                    // This should only happen if we run out of memory (malloc failure)?
                    PyErr_Print();
                    return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
            }
            Py_BEGIN_ALLOW_THREADS
            if (!icsneoScriptReadTxMessage(handle, index, &PySpyMessage_GetObject(msg)->msg)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadTxMessage() Failed");
            }
            Py_END_ALLOW_THREADS
        }
        return msg;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_read_rx_message(PyObject* self, PyObject* args) //ScriptReadRxMessage
{
    int index;
    PyObject* obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oi|b:", __FUNCTION__), &obj, &index, &j1850)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, void*, void*)> icsneoScriptReadRxMessage(lib, "icsneoScriptReadRxMessage");
        PyObject* msg = NULL;
        PyObject* msg_mask = NULL;
        if (j1850) {
            msg = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            if (!msg) {
                    // This should only happen if we run out of memory (malloc failure)?
                    PyErr_Print();
                    return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_J1850_OBJECT_NAME);
            }
            msg_mask = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            if (!msg_mask) {
                    // This should only happen if we run out of memory (malloc failure)?
                    PyErr_Print();
                    return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_J1850_OBJECT_NAME);
            }
            Py_BEGIN_ALLOW_THREADS
            if (!icsneoScriptReadRxMessage(handle, index, &PySpyMessageJ1850_GetObject(msg_mask)->msg, &PySpyMessageJ1850_GetObject(msg_mask)->msg)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadRxMessage() Failed");
            }
            Py_END_ALLOW_THREADS
        } else {
            PyObject* msg = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            if (!msg) {
                    // This should only happen if we run out of memory (malloc failure)?
                    PyErr_Print();
                    return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
            }
            PyObject* msg_mask = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            if (!msg_mask) {
                    // This should only happen if we run out of memory (malloc failure)?
                    PyErr_Print();
                    return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
            }
            Py_BEGIN_ALLOW_THREADS
            if (!icsneoScriptReadRxMessage(handle, index, &PySpyMessage_GetObject(msg)->msg, &PySpyMessage_GetObject(msg_mask)->msg)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadRxMessage() Failed");
            }
            Py_END_ALLOW_THREADS
        }
        return Py_BuildValue("(O,O)", msg, msg_mask);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_write_tx_message(PyObject* self, PyObject* args) //icsneoScriptWriteTxMessage
{
    int index;
    PyObject* obj = NULL;
    PyObject* msg_obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OiO|b:", __FUNCTION__), &obj, &index, &msg_obj, &j1850)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    void* msg = NULL;
    void* msg_mask = NULL;
    if (j1850) {
        // We are going to use icsSpyMessageJ1850 objects here.
        if (!PySpyMessageJ1850_CheckExact(msg_obj)) {
            return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_J1850_OBJECT_NAME);
        }
        msg = (void*)&PySpyMessageJ1850_GetObject(msg_obj)->msg;
    } else {
        // We are going to use icsSpyMessage objects here.
        if (!PySpyMessage_CheckExact(msg_obj)) {
            return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME);
        }
        msg = (void*)&PySpyMessage_GetObject(msg_obj)->msg;
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, void*)> icsneoScriptWriteTxMessage(lib, "icsneoScriptWriteTxMessage");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptWriteTxMessage(handle, index, msg)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptWriteTxMessage() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_write_rx_message(PyObject* self, PyObject* args) //icsneoScriptWriteRxMessage
{
    int index;
    PyObject* obj = NULL;
    PyObject* msg_obj = NULL;
    PyObject* msg_mask_obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OiOO|b:", __FUNCTION__), &obj, &index, &msg_obj, &msg_mask_obj, &j1850)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    void* msg = NULL;
    void* msg_mask = NULL;
    if (j1850) {
        // We are going to use icsSpyMessageJ1850 objects here.
        if (!PySpyMessageJ1850_CheckExact(msg_obj)) {
            return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_J1850_OBJECT_NAME);
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
            return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME);
        }
        msg = (void*)&PySpyMessage_GetObject(msg_obj)->msg;
        if (!PySpyMessage_CheckExact(msg_mask_obj)) {
            msg_mask = (void*)new icsSpyMessage();
            memset(msg_mask, 0, sizeof(icsSpyMessage));
        } else {
            msg_mask = (void*)&PySpyMessage_GetObject(msg_mask_obj)->msg;
        }
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, void*, void*)> icsneoScriptWriteRxMessage(lib, "icsneoScriptWriteRxMessage");
        if (!icsneoScriptWriteRxMessage(handle, index, msg, msg_mask)) {
            return set_ics_exception(exception_runtime_error(), "icsneoScriptWriteRxMessage() Failed");
        }
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_performance_parameters(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, int*, int*, int*, int*, int*, int*, int*, int*)> icsneoGetPerformanceParameters(lib, "icsneoGetPerformanceParameters");
        int buffer_count = 0;
        int buffer_max = 0;
        int overflow_count = 0;
        int reserved1 = 0;
        int reserved2 = 0;
        int reserved3 = 0;
        int reserved4 = 0;
        int reserved5 = 0;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetPerformanceParameters(handle, &buffer_count, &buffer_max, &overflow_count, &reserved1, &reserved2, &reserved3, &reserved4, &reserved5)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetPerformanceParameters() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("(i,i,i,i,i,i,i,i)", buffer_count, buffer_max, overflow_count, reserved1, reserved2, reserved3, reserved4, reserved5);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_validate_hobject(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyLong_CheckExact(obj) && !PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME " or Integer");
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE)> icsneoValidateHObject(lib, "icsneoValidateHObject");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoValidateHObject(handle)) {
            Py_BLOCK_THREADS
            return Py_BuildValue("b", false);
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", true);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_last_api_error(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, int*)> icsneoGetLastAPIError(lib, "icsneoGetLastAPIError");
        ice::Function<int __stdcall (int, char*, char*, int*, int*, int*, int*)> icsneoGetErrorInfo(lib, "icsneoGetErrorInfo");
        int error = 0;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetLastAPIError(handle, &error)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetLastAPIError() Failed");
        }
        Py_END_ALLOW_THREADS
        char description_short[255] = {0};
        char description_long[255] = {0};
        int description_short_length = 255;
        int description_long_length = 255;
        int severity = 0, restart_needed = 0;
        if (!icsneoGetErrorInfo(error, description_short, description_long, 
            &description_short_length, &description_long_length, &severity, &restart_needed)) {
            return set_ics_exception(exception_runtime_error(), "icsneoGetErrorInfo() Failed");
        }
        return Py_BuildValue("i, s, s, i, i", error, description_short, description_long, severity, restart_needed);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_dll_version(PyObject* self, PyObject* args)
{
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall ()> icsneoGetDLLVersion(lib, "icsneoGetDLLVersion");
        int result = 0;
        Py_BEGIN_ALLOW_THREADS
        result = icsneoGetDLLVersion();
        Py_END_ALLOW_THREADS
        return Py_BuildValue("i", result);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}


PyObject* meth_get_serial_number(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (void*, unsigned int*)> icsneoGetSerialNumber(lib, "icsneoGetSerialNumber");
        unsigned int serial = 0;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetSerialNumber(handle, &serial)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetSerialNumber() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("i", serial);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_hw_firmware_info(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, stAPIFirmwareInfo*)> icsneoGetHWFirmwareInfo(lib, "icsneoGetHWFirmwareInfo");
        PyObject* info = PyObject_CallObject((PyObject*)&api_firmware_info_object_type, NULL);
        if (!info) {
            // This should only happen if we run out of memory (malloc failure)?
            PyErr_Print();
            return set_ics_exception(exception_runtime_error(), "Failed to allocate " API_FIRMWARE_INFO_OBJECT_NAME);
        }
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetHWFirmwareInfo(handle, &PyApiFirmwareInfo_GetApiFirmwareInfo(info)->s)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetHWFirmwareInfo() Failed");
        }
        Py_END_ALLOW_THREADS
        return info;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_base36enc(PyObject* self, PyObject* args)
{
    unsigned long value = 0;
    if (!PyArg_ParseTuple(args, arg_parse("i:", __FUNCTION__), &value)) {
        return NULL;
    }
    char base36[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
    PyObject* obj = NULL;
    unsigned int timeout_ms = 0;
    unsigned int mode = 0;
    unsigned int reserved = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oii|i:", __FUNCTION__), &obj, &timeout_ms, &mode, &reserved)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, unsigned int, unsigned int)> icsneoRequestEnterSleepMode(lib, "icsneoRequestEnterSleepMode");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoRequestEnterSleepMode(handle, timeout_ms, mode, reserved)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoRequestEnterSleepMode() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", true);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_set_context(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj) && !PyLong_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = 0;
    if (PyNeoDevice_CheckExact(obj))
        handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE)> icsneoSetContext(lib, "icsneoSetContext");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetContext(handle)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoSetContext() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", true);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_force_firmware_update(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj) && !PyLong_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = 0;
    if (PyNeoDevice_CheckExact(obj))
        handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE)> icsneoForceFirmwareUpdate(lib, "icsneoForceFirmwareUpdate");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoForceFirmwareUpdate(handle)) {
            Py_BLOCK_THREADS
            return Py_BuildValue("b", false);
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", true);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_firmware_update_required(PyObject* self, PyObject* args)
{ 
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj) && !PyLong_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = 0;
    if (PyNeoDevice_CheckExact(obj))
        handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE)> icsneoFirmwareUpdateRequired(lib, "icsneoFirmwareUpdateRequired");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoFirmwareUpdateRequired(handle)) {
            Py_BLOCK_THREADS
            return Py_BuildValue("b", false);
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", true);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_dll_firmware_info(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, stAPIFirmwareInfo*)> icsneoGetDLLFirmwareInfo(lib, "icsneoGetDLLFirmwareInfo");
        PyObject* info = PyObject_CallObject((PyObject*)&api_firmware_info_object_type, NULL);
        if (!info) {
            // This should only happen if we run out of memory (malloc failure)?
            PyErr_Print();
            return set_ics_exception(exception_runtime_error(), "Failed to allocate " API_FIRMWARE_INFO_OBJECT_NAME);
        }
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetDLLFirmwareInfo(handle, &PyApiFirmwareInfo_GetApiFirmwareInfo(info)->s)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetDLLFirmwareInfo() Failed");
        }
        Py_END_ALLOW_THREADS
        return info;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_backup_power_enabled(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned int enabled = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int&)> icsneoGetBackupPowerEnabled(lib, "icsneoGetBackupPowerEnabled");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetBackupPowerEnabled(handle, enabled)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetBackupPowerEnabled() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", enabled);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_set_backup_power_enabled(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned int enabled = 1;
    if (!PyArg_ParseTuple(args, arg_parse("O|b:", __FUNCTION__), &obj, &enabled)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int)> icsneoSetBackupPowerEnabled(lib, "icsneoSetBackupPowerEnabled");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetBackupPowerEnabled(handle, enabled)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoSetBackupPowerEnabled() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", enabled);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_set_backup_power_ready(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned int enabled = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int&)> icsneoGetBackupPowerReady(lib, "icsneoGetBackupPowerReady");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetBackupPowerReady(handle, enabled)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetBackupPowerReady() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", enabled);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

//icsneoScriptLoadReadBin
PyObject* meth_load_readbin(PyObject* self, PyObject* args)
{
    PyObject* arg_data = NULL;
    int location;
    PyObject* obj = NULL;
    bool isFileData = false;
    if (!PyArg_ParseTuple(args, arg_parse("OOi:", __FUNCTION__), &obj, &arg_data, &location)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;    
    long fsize;
    unsigned char* data = NULL;
    int data_size = 0;
#if PY_MAJOR_VERSION >= 3
    if (PyUnicode_CheckExact(arg_data)) {
        char* file_name = PyUnicode_AsUTF8(arg_data);
#else
    if (PyString_Check(arg_data)) {
        char* file_name = PyString_AsString(arg_data);
#endif
        if (!file_name) {
            return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to convert file path to string");
        }
        FILE* f;
        f = fopen(file_name, "rb");
        if (!f)    {
            std::stringstream ss;
            ss << "Failed to open Readbin: '" << file_name << "'. Please make sure path exists";
            return set_ics_exception_dev(exception_runtime_error(), obj, (char*)ss.str().c_str());
        }
        fseek(f, 0, SEEK_END);
        fsize = ftell(f);
        rewind(f);
        data = (unsigned char*) malloc(sizeof(char)*fsize);
        data_size = (int)fread(data, 1, fsize, f);
        fclose(f);
        if (fsize != data_size) {
            return set_ics_exception_dev(exception_runtime_error(), obj, "Readbin file size mismatch");
        }
    } else if (PyTuple_CheckExact(arg_data)) {
        Py_ssize_t tuple_size = PyTuple_Size(arg_data);
        data = (unsigned char*) malloc(sizeof(char)*tuple_size);
        // Move tuple data into array
        for (int i=0; i < tuple_size; ++i) {
            PyObject* value = PyTuple_GET_ITEM(arg_data, i);
            if (!PyLong_CheckExact(value)) {
                return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to convert tuple data. Tuple data must be integer type");
            }
            data[i] = (unsigned char)PyLong_AsLong(PyTuple_GET_ITEM(arg_data, i));
        }
        fsize = tuple_size;
        data_size = fsize;
    } else {
        return set_ics_exception_dev(exception_runtime_error(), obj, "Argument must be filepath or tuple");
    }
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, const unsigned char*, unsigned long, int)> icsneoScriptLoadReadBin(lib, "icsneoScriptLoadReadBin");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoScriptLoadReadBin(handle, data, data_size, location)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoScriptLoadReadBin() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

//void* hObject, unsigned long ulNetworkID, stCM_ISO157652_TxMessage *pMsg, unsigned long ulBlockingTimeout)
PyObject* meth_iso15765_transmit_message(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned long ulNetworkID = 0;
    PyObject* obj_tx_msg = NULL;
    unsigned long ulBlockingTimeout = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OkOk:", __FUNCTION__), &obj, &ulNetworkID, &obj_tx_msg, &ulBlockingTimeout)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    if (!PyCmISO157652TxMessage_Check(obj_tx_msg)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." CM_ISO157652_TX_MESSAGE_OBJECT_NAME);
    }
    cm_iso157652_tx_message_object *temp = (cm_iso157652_tx_message_object*)obj_tx_msg;
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned long, stCM_ISO157652_TxMessage*, unsigned long)> icsneoISO15765_TransmitMessage(lib, "icsneoISO15765_TransmitMessage");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoISO15765_TransmitMessage(handle, ulNetworkID, &temp->s, ulBlockingTimeout)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_TransmitMessage() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("b", true);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

/*

PyObject* obj = NULL;
            if (use_j1850) {
                obj = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            } else {
                obj = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            }

*/
// (void* hObject, unsigned int iIndex, const stCM_ISO157652_RxMessage * pRxMessage)
PyObject* meth_iso15765_receive_message(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned int iIndex = 0;
    PyObject* obj_rx_msg = PyObject_CallObject((PyObject*)&cm_iso157652_rx_message_object_type, NULL);
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &iIndex)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    if (!PyCmISO157652TxMessage_Check(obj_rx_msg)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." CM_ISO157652_RX_MESSAGE_OBJECT_NAME);
    }
    cm_iso157652_rx_message_object *temp = (cm_iso157652_rx_message_object*)obj_rx_msg;
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, stCM_ISO157652_RxMessage*)> icsneoISO15765_ReceiveMessage(lib, "icsneoISO15765_ReceiveMessage");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoISO15765_ReceiveMessage(handle, iIndex, &temp->s)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_ReceiveMessage() Failed");
        }
        Py_END_ALLOW_THREADS
        return obj_rx_msg;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_iso15765_enable_networks(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned long networks = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &networks)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned long)> icsneoISO15765_EnableNetworks(lib, "icsneoISO15765_EnableNetworks");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoISO15765_EnableNetworks(handle, networks)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_EnableNetworks() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_iso15765_disable_networks(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE)> icsneoISO15765_DisableNetworks(lib, "icsneoISO15765_DisableNetworks");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoISO15765_DisableNetworks(handle)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_DisableNetworks() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_active_vnet_channel(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned long channel = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned long*)> icsneoGetActiveVNETChannel(lib, "icsneoGetActiveVNETChannel");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetActiveVNETChannel(handle, &channel)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetActiveVNETChannel() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("i", channel);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_set_active_vnet_channel(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned long channel = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &channel)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, unsigned long)> icsneoSetActiveVNETChannel(lib, "icsneoSetActiveVNETChannel");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetActiveVNETChannel(handle, channel)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoSetActiveVNETChannel() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("i", channel);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_set_bit_rate(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    int bitrate = 0;
    int net_id = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oii:", __FUNCTION__), &obj, &bitrate, &net_id)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, int, int)> icsneoSetBitRate(lib, "icsneoSetBitRate");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetBitRate(handle, bitrate, net_id)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoSetBitRate() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_set_fd_bit_rate(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    int bitrate = 0;
    int net_id = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oii:", __FUNCTION__), &obj, &bitrate, &net_id)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, int, int)> icsneoSetFDBitRate(lib, "icsneoSetFDBitRate");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetFDBitRate(handle, bitrate, net_id)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoSetFDBitRate() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_set_bit_rate_ex(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    int bitrate = 0;
    int net_id = 0;
    int options = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oiii:", __FUNCTION__), &obj, &bitrate, &net_id)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, int, int, int)> icsneoSetBitRateEx(lib, "icsneoSetBitRateEx");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetBitRateEx(handle, bitrate, net_id, options)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoSetBitRateEx() Failed");
        }
        Py_END_ALLOW_THREADS
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_override_library_name(PyObject* self, PyObject* args)
{
    const char* name = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("s:", __FUNCTION__), &name)) {
        return NULL;
    }
    try
    {
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
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_library_path(PyObject* self)
{
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        return Py_BuildValue("s", lib->getPath());
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
