﻿#include "methods.h"
#include "exceptions.h"
#include "dll.h"
#include "defines.h"
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
#include "setup_module_auto_defines.h"

extern PyTypeObject spy_message_object_type;
// __func__, __FUNCTION__ and __PRETTY_FUNCTION__ are not preprocessor macros.
// but MSVC doesn't follow c standard and treats __FUNCTION__ as a string literal macro...
#if (defined(_WIN32) || defined(__WIN32__))
#define arg_parse(a,f) a f
#else
const char* arg_parse(const char* args, const char* func)
{
    static char buffer[128];
    memset(buffer, '\0', sizeof(buffer)/sizeof(buffer[0]));
    strcpy(buffer, args);
    strcat(buffer, func);
    return (const char*)buffer;
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
    case NEODEVICE_UNKNOWN: return "Unknown";
    case NEODEVICE_BLUE: return "neoVI BLUE";
    case NEODEVICE_ECU_AVB: return "neoECU/AVB TSN";
    case NEODEVICE_RADSUPERMOON: return "RADSuperMoon";
    case NEODEVICE_DW_VCAN: return "ValueCAN DW";
    case NEODEVICE_RADMOON2: return "RADMoon2";
    case NEODEVICE_RADGIGALOG: return "RADGigalog";
    case NEODEVICE_VCAN41: return "ValueCAN4-1";
    case NEODEVICE_FIRE: return "neoVI FIRE";
    case NEODEVICE_RADPLUTO: return "RAD-Pluto";
    case NEODEVICE_VCAN42_EL: return "ValueCAN4-1";
    case NEODEVICE_RADIO_CANHUB: return "neoRAD-IO2-CANHUB";
    case NEODEVICE_NEOECU12: return "neoECU12";
    case NEODEVICE_OBD2_LCBADGE: return "neoOBD2-LC BADGE";
    case NEODEVICE_RAD_MOON_DUO: return "RAD-Moon-Duo";
    case NEODEVICE_ONYX: return "neoVI FIRE3";
    case NEODEVICE_VCAN3: return "ValueCAN3";
#if defined(NEODEVICE_JUPITER)
    case NEODEVICE_JUPITER: return "RAD-Jupiter";
#elif defined(NEODEVICE_RADJUPITER)
    case NEODEVICE_RADJUPITER: return "RAD-Jupiter";
#endif
    case NEODEVICE_VCAN4_IND: return "ValueCAN4 Industrial";
    case NEODEVICE_GIGASTAR: return "RAD-GIGAStar";
    case NEODEVICE_RED: return "neoVI RED";
    case NEODEVICE_ECU: return "neoECU";
    case NEODEVICE_IEVB: return "IEVB";
    case NEODEVICE_PENDANT: return "Pendant";
    case NEODEVICE_OBD2_PRO: return "neoOBD2 Pro";
    case NEODEVICE_ECUCHIP_UART: return "ECUCHIP";
    case NEODEVICE_PLASMA: return "neoVI PLASMA";
    case NEODEVICE_NEOANALOG: return "neoAnalog";
    case NEODEVICE_CT_OBD: return "neoOBD CT";
    case NEODEVICE_ION: return "neoVI ION";
    case NEODEVICE_RADSTAR: return "RADStar";
    case NEODEVICE_VCAN44: return "ValueCAN4-4";
    case NEODEVICE_VCAN42: return "ValueCAN4-2";
    case NEODEVICE_CMPROBE: return "CM Probe";
    case NEODEVICE_EEVB: return "EEVB";
    case NEODEVICE_VCANRF: return "ValueCAN.rf";
    case NEODEVICE_FIRE2: return "neoVI FIRE2";
    case NEODEVICE_FLEX: return "neoVI FLEX";
    case NEODEVICE_RADGALAXY: return "RADGalaxy";
    case NEODEVICE_RADSTAR2: return "RADStar2";
    case NEODEVICE_VIVIDCAN: return "VividCAN";
    case NEODEVICE_OBD2_SIM: return "neoOBD2 Sim";
    };
    return "Unknown";
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

// Returns a PyObject from PyObject_CallObject() on success, sets exception and NULL on failure.
PyObject* _getPythonModuleObject(const char* module_name, const char* module_object_name)
{
    // Before we do anything, we need to grab the python s_device_settings ctype.Structure.
    PyObject* module = PyImport_ImportModule(module_name);
    if (!module) 
    {
        return set_ics_exception(exception_runtime_error(), "_getPythonModuleObject(): Failed to import module");
    }
    // Grab the module Dictionary
    PyObject* module_dict = PyModule_GetDict(module);
    if (!module_dict) 
    {
        return set_ics_exception(exception_runtime_error(), "_getPythonModuleObject(): Failed to grab module dict from module");
    }
    // Grab the actual object
    PyObject* module_object = PyDict_GetItemString(module_dict, module_object_name);
    if (!module_object) 
    {
        return set_ics_exception(exception_runtime_error(), "_getPythonModuleObject(): Failed to grab object s_device_settings from module");
    }
    // Call the object so we have our own reference - we are going to return this
    PyObject* object = PyObject_CallObject(module_object, NULL);
    if (!object) 
    {
        return set_ics_exception(exception_runtime_error(), "_getPythonModuleObject(): Failed to call object from module");
    }
    return object;
}

// Returns same as PyObject_IsInstance()
int _isPythonModuleObject_IsInstance(PyObject* object, const char* module_name, const char* module_object_name)
{
    // Before we do anything, we need to grab the python s_device_settings ctype.Structure.
    PyObject* module = PyImport_ImportModule(module_name);
    if (!module) 
    {
        set_ics_exception(exception_runtime_error(), "_isPythonModuleObjectInstanceOf(): Failed to import module");
        return -1;
    }
    // Grab the module Dictionary
    PyObject* module_dict = PyModule_GetDict(module);
    if (!module_dict) 
    {
        set_ics_exception(exception_runtime_error(), "_isPythonModuleObjectInstanceOf(): Failed to grab module dict from module");
        return -1;
    }
    // Grab the actual object
    PyObject* module_object = PyDict_GetItemString(module_dict, module_object_name);
    if (!module_object) 
    {
        set_ics_exception(exception_runtime_error(), "_isPythonModuleObjectInstanceOf(): Failed to grab object s_device_settings from module");
        return -1;
    }
    return PyObject_IsInstance(object, module_object);
}

PyObject* meth_find_devices(PyObject* self, PyObject* args, PyObject* keywords)
{
    PyObject* device_types = NULL;
    int network_id = -1;
    char* kwords[] = { "deviceTypes", "NetworkID", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywords, arg_parse("|Oi:", __FUNCTION__), 
            kwords, &device_types, &network_id)) {
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
    if (device_types && device_types != Py_None)
    {
        std::vector<PyObject*> device_type_vector;
        if (!_convertListOrTupleToArray(device_types, &device_type_vector))
            return NULL;
        device_types_list_size = device_type_vector.size();
        device_types_list.reset((new unsigned int(device_types_list_size)));
        for (unsigned int i=0; i < device_types_list_size; ++i)
            device_types_list[i] = (unsigned int)PyLong_AsLong(device_type_vector[i]);
    }
    // Lets finally call the icsneo40 function
    try
    {
        /*
        int _stdcall icsneoFindDevices(NeoDeviceEx* pNeoDeviceEx,
                                       int* pNumDevices,
                                       unsigned int* deviceTypes,
                                       unsigned int numDeviceTypes,
                                       POptionsFindNeoEx* pOptionsFindNeoEx,
                                       unsigned long reserved​)
        */
        ice::Function<int __stdcall (NeoDeviceEx*, int*, unsigned int*, unsigned int, POptionsFindNeoEx*, unsigned long)> icsneoFindDevices(lib, "icsneoFindDevices");
        NeoDeviceEx devices[255];
        int count = 255;

        // 
        OptionsFindNeoEx opts = {0};
        opts.CANOptions.iNetworkID = network_id;
        POptionsFindNeoEx popts = NULL;
        if (network_id != -1)
            popts = &opts;

        Py_BEGIN_ALLOW_THREADS
        if (!icsneoFindDevices(devices, &count, device_types_list.get(), device_types_list_size, (network_id != -1) ? &popts : NULL, 0)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoFindDevices() Failed");
        }
        Py_END_ALLOW_THREADS

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
            neo_device->dev = devices[i].neoDevice;
            neo_device->name = PyUnicode_FromString(neodevice_to_string(devices[i].neoDevice.DeviceType));
            PyTuple_SetItem(tuple, i, obj);
        }
        return tuple;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_open_device(PyObject* self, PyObject* args, PyObject* keywords)
{
    unsigned long serial_number = 0;
    PyObject* device = NULL;
    PyObject* network_ids = NULL;
    int config_read = 0;
    int options = 0;
    int network_id = -1;
    bool device_need_ref_inc = false;
    char* kwords[] = { "device", "network_ids", "config_read", "options", "network_id", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywords, arg_parse("|OOiii:", __FUNCTION__), 
            kwords, &device, &network_ids, &config_read, &options, &network_id)) {
        return NULL;
    }

    // Grab the library before we start doing anything...
    ice::Library* lib = dll_get_library();
    if (!lib) { 
        char buffer[512];
        return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
    }

    // Verify device type
    if (device && PyLong_CheckExact(device))
    {
        // Device is a serial number in integer format
        serial_number = PyLong_AsLong(device);
    }
    else if (device && PyUnicode_CheckExact(device))
    {
        // Lets convert the base36 string into an integer
        PyObject* module_name = PyUnicode_FromString("builtins");
        PyObject* builtins_module = PyImport_Import(module_name);
        if (!builtins_module)
        {
            return set_ics_exception(exception_runtime_error(),"Failed to import __builtins__ module");
        }
        PyObject* builtin_dict = PyModule_GetDict(builtins_module);
        PyObject *builtin_int = PyDict_GetItemString(builtin_dict, "int");
        if (PyCallable_Check(builtin_int)) 
        {
            PyObject *return_value = PyObject_CallFunction(builtin_int, "Oi", device, 36);
            Py_DECREF(builtins_module);
            if (return_value == NULL) 
            {
                // We failed for some reason...
                PyErr_Print();
                return NULL;
            } 
            else
            {
                serial_number = PyLong_AsLong(return_value);
            }
        }
        else
        {
            return set_ics_exception(exception_runtime_error(),"Failed to convert serial number string to integer.");
        }
    }
    else if (device && !PyNeoDevice_CheckExact(device))
    {
        return set_ics_exception(exception_runtime_error(),"Invalid 'device' parameter object type passed to open_device().");
    }
    else if (device && PyNeoDevice_CheckExact(device))
    {
        // If the user passed in a NeoDevice device we need to increment 
        // the reference counter when we return it since device is a borrowed
        // reference.
        // devs = ics.find_devices()
        // device = ics.open_device(devs[0])
        // del device # This will decrement the reference and crash interp
        device_need_ref_inc = true;
    }

    if ((device && !PyNeoDevice_CheckExact(device)) || !device)
    {
        // We don't have a device parameter so lets find the first one
        try
        {
            ice::Function<int __stdcall (NeoDeviceEx*, int*, unsigned int*, unsigned int, POptionsFindNeoEx*, unsigned long)> icsneoFindDevices(lib, "icsneoFindDevices");
            NeoDeviceEx devices[255];
            int count = 255;

            OptionsFindNeoEx opts = {0};
            opts.CANOptions.iNetworkID = network_id;
            POptionsFindNeoEx popts = NULL;
            if (network_id != -1)
                popts = &opts;

            Py_BEGIN_ALLOW_THREADS
            if (!icsneoFindDevices(devices, &count, NULL, 0, (network_id != -1) ? &popts : NULL, 0)) 
            {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoFindDevices() Failed");
            }
            Py_END_ALLOW_THREADS
            // Find the first free device
            for (int i=0; i < count; ++i)
            {
                // If we are looking for a serial number, check here
                if (serial_number && devices[i].neoDevice.SerialNumber != serial_number)
                    continue;
                if (devices[i].neoDevice.NumberOfClients != 0)
                {
                    return set_ics_exception(exception_runtime_error(), "Found device, but its already open!");
                }
                // We matched a neoDevice, lets allocate it here.
                device = PyObject_CallObject((PyObject*)&neo_device_object_type, NULL);
                PyNeoDevice_GetNeoDevice(device)->dev = devices[i].neoDevice;
                PyNeoDevice_GetNeoDevice(device)->name = PyUnicode_FromString(neodevice_to_string(devices[i].neoDevice.DeviceType));
                break;
            }
            if (!PyNeoDevice_CheckExact(device))
            {
                return set_ics_exception(exception_runtime_error(), "Failed to find a device to open.");
            }
        }
        catch (ice::Exception& ex)
        {
            return set_ics_exception(exception_runtime_error(), (char*)ex.what());
        }
    }

    // We should finally have our device allocated at this point!
    try
    {
        /*
        int _stdcall icsneoOpenDevice(NeoDeviceEx* pNeoDeviceEx,
                                      void** hObject,
                                      unsigned char* bNetworkIDs,
                                      int bConfigRead,
                                      int iOptions,
                                      OptionsOpenNeoEx* stOptionsOpenNeoEx,
                                      unsigned long reserved)
        */
        ice::Function<int __stdcall (NeoDeviceEx*, void**, unsigned char*, int, int, OptionsFindNeoEx*, unsigned long)> icsneoOpenDevice(lib, "icsneoOpenDevice");
        NeoDeviceEx neo_device_ex = {};
        neo_device_ex.neoDevice = PyNeoDevice_GetNeoDevice(device)->dev;
        OptionsFindNeoEx opts = {0};
        opts.CANOptions.iNetworkID = network_id;
        POptionsFindNeoEx popts = NULL;
        if (network_id != -1)
            popts = &opts;

        Py_BEGIN_ALLOW_THREADS
        if (!icsneoOpenDevice(&neo_device_ex, &PyNeoDevice_GetNeoDevice(device)->handle, NULL, config_read, options, (network_id != -1) ? popts : NULL, 0)) 
        {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoOpenDevice() Failed");
        }
        Py_END_ALLOW_THREADS
        
        if (device_need_ref_inc)
        {
            Py_INCREF(device);
        }
        return device;
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
        ice::Function<void __stdcall (ICS_HANDLE)>  icsneoFreeObject(lib, "icsneoFreeObject");
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
        char* file_name = PyUniStr_AsStrOrUTF8(arg_data);
#else
    if (PyString_Check(arg_data)) {
        char* file_name = PyUniStr_AsStrOrUTF8(arg_data);
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
        int count = 0;
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
        Py_BEGIN_ALLOW_THREADS
        for (double i=timeout; i >= 0; --i) {
            count = 20000;
            errors = 0;
            if (!icsneoGetMessages(handle, (icsSpyMessage*)msgs, &count, &errors) && !errors) {
                // We are going to try one more time just incase
                count = 20000;
                errors = 0;
                if (!icsneoGetMessages(handle, (icsSpyMessage*)msgs, &count, &errors)) {
                    Py_BLOCK_THREADS
                    return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoGetMessages() Failed");
                }
            }
            if (count || errors) {
                break;
            }
            // We don't want to sleep, if there isn't a timeout left.
            if (i) {
                Sleep(1);
            }
        }
        Py_END_ALLOW_THREADS
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
        PyObject* list = PyList_New(0);
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
                Py_XDECREF(list);
                return set_ics_exception(exception_runtime_error(), "icsneoGetErrorInfo() Failed");
            }
            Py_END_ALLOW_THREADS
            PyObject* tuple = Py_BuildValue("i, s, s, i, i", errors[i], description_short, description_long, severity, restart_needed);
            
            PyList_Append(list, tuple);
            Py_XDECREF(tuple);
        }
        return list;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

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
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (unsigned long, NeoDevice*, const SReflashChip_t*, unsigned long, unsigned long, unsigned long, unsigned long, void*)> FlashDevice2(lib, "FlashDevice2");
        Py_BEGIN_ALLOW_THREADS
        if (!FlashDevice2(0x3835C256, &(neo_device->dev), rc, reflash_count, 0, 0, 0, &message_callback)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "FlashDevice2() Failed");
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
#endif // _USE_INTERNAL_HEADER_

PyObject* msg_reflash_callback = NULL;
static void message_reflash_callback(const wchar_t* message, unsigned long progress)
{
    // We need to relock the GIL here otherwise we crash
    PyGILState_STATE state = PyGILState_Ensure();
    if (!msg_reflash_callback) {
        PySys_WriteStdout("%s -%d\n", message, progress);
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

PyObject* meth_get_device_settings(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    long device_type_override = -1;
    EPlasmaIonVnetChannel_t vnet_slot = (EPlasmaIonVnetChannel_t)PlasmaIonVnetChannelMain;
    if (!PyArg_ParseTuple(args, arg_parse("O|lk:", __FUNCTION__), &obj, &device_type_override, &vnet_slot)) {
        return NULL;
    }

    // Before we do anything, we need to grab the python s_device_settings ctype.Structure.
    PyObject* settings = _getPythonModuleObject("ics.structures.s_device_settings", "s_device_settings");
    if (!settings)
    {
        return NULL;
    }
    // Grab the buffer out of the newly created object - make sure to call PyBuffer_Release(&settings_buffer) when done.
    Py_buffer settings_buffer = {};
    PyObject_GetBuffer(settings, &settings_buffer, PyBUF_C_CONTIGUOUS | PyBUF_WRITABLE);

    // Verify we have a valid NeoDevice Object - This comes after s_device_settings allocation for testing purposes
    if (!PyNeoDevice_CheckExact(obj)) {
        PyBuffer_Release(&settings_buffer);
        Py_DECREF(settings);
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            PyBuffer_Release(&settings_buffer);
            Py_DECREF(settings);
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // Set/Get the DeviceSettingsType
        Py_BEGIN_ALLOW_THREADS
        EDeviceSettingsType* setting_type = &((SDeviceSettings*)settings_buffer.buf)->DeviceSettingType;
        if (device_type_override == -1)
        {
            // int _stdcall icsneoGetDeviceSettingsType(void* hObject, EPlasmaIonVnetChannel_t vnetSlot, EDeviceSettingsType* pDeviceSettingsType)
            ice::Function<int __stdcall (ICS_HANDLE, EPlasmaIonVnetChannel_t, EDeviceSettingsType*)> icsneoGetDeviceSettingsType(lib, "icsneoGetDeviceSettingsType");
            if (!icsneoGetDeviceSettingsType(handle, vnet_slot, setting_type))
            {
                Py_BLOCK_THREADS
                PyBuffer_Release(&settings_buffer);
                Py_DECREF(settings);
                return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceSettingsType() Failed");
            }
        }
        // int _stdcall icsneoGetDeviceSettings(void* hObject, SDeviceSettings* pSettings, int iNumBytes, EPlasmaIonVnetChannel_t vnetSlot)
        ice::Function<int __stdcall (ICS_HANDLE, SDeviceSettings*, int, EPlasmaIonVnetChannel_t)> icsneoGetDeviceSettings(lib, "icsneoGetDeviceSettings");
        if (!icsneoGetDeviceSettings(handle, (SDeviceSettings*)settings_buffer.buf, settings_buffer.len, vnet_slot))
        {
            Py_BLOCK_THREADS
            PyBuffer_Release(&settings_buffer);
            Py_DECREF(settings);
            return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceSettings() Failed");
        }
        Py_END_ALLOW_THREADS
        PyBuffer_Release(&settings_buffer);
        return settings;
    }
    catch (ice::Exception& ex)
    {
        PyBuffer_Release(&settings_buffer);
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_set_device_settings(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    PyObject* settings = NULL;
    int save_to_eeprom = 1;
    EPlasmaIonVnetChannel_t vnet_slot = PlasmaIonVnetChannelMain;
    if (!PyArg_ParseTuple(args, arg_parse("OO|ik:", __FUNCTION__), &obj, &settings, &save_to_eeprom, &vnet_slot)) {
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
        // int _stdcall icsneoSetDeviceSettings(void* hObject, SDeviceSettings* pSettings, int bSaveToEEPROM, EPlasmaIonVnetChannel_t vnetSlot)
        // int _stdcall icsneoSetDeviceSettings(void* hObject, SDeviceSettings* pSettings, int iNumBytes, int bSaveToEEPROM, EPlasmaIonVnetChannel_t vnetSlot)
        ice::Function<int __stdcall (ICS_HANDLE, SDeviceSettings*, int, int, EPlasmaIonVnetChannel_t)> icsneoSetDeviceSettings(lib, "icsneoSetDeviceSettings");
        Py_buffer settings_buffer = {};
        PyObject_GetBuffer(settings, &settings_buffer, PyBUF_C_CONTIGUOUS | PyBUF_WRITABLE);
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoSetDeviceSettings(handle, (SDeviceSettings*)settings_buffer.buf, settings_buffer.len, save_to_eeprom, vnet_slot)) {
            Py_BLOCK_THREADS
            PyBuffer_Release(&settings_buffer);
            return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoSetDeviceSettings() Failed");
        }
        Py_END_ALLOW_THREADS
        PyBuffer_Release(&settings_buffer);
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
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
        PyObject* info = _getPythonModuleObject("ics.structures.st_api_firmware_info", "st_api_firmware_info");
        if (!info)
        {
            return NULL;
        }
        Py_buffer info_buffer = {};
        PyObject_GetBuffer(info, &info_buffer, PyBUF_SIMPLE);

        
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetHWFirmwareInfo(handle, (stAPIFirmwareInfo*)info_buffer.buf)) {
            Py_BLOCK_THREADS
            PyBuffer_Release(&info_buffer);
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
        PyObject* info = _getPythonModuleObject("ics.structures.st_api_firmware_info", "st_api_firmware_info");
        if (!info)
        {
            return NULL;
        }
        Py_buffer info_buffer = {};
        PyObject_GetBuffer(info, &info_buffer, PyBUF_SIMPLE);
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetDLLFirmwareInfo(handle, (stAPIFirmwareInfo*)info_buffer.buf)) {
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
        char* file_name = PyUniStr_AsStrOrUTF8(arg_data);
#else
    if (PyString_Check(arg_data)) {
        char* file_name = PyUniStr_AsStrOrUTF8(arg_data);
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
    if (_isPythonModuleObject_IsInstance(obj_tx_msg, "ics.structures.st_cm_iso157652_tx_message", "st_cm_iso157652_tx_message") != 1)
    {
        return NULL;
    }
    Py_buffer obj_tx_msg_buffer = {};
    PyObject_GetBuffer(obj_tx_msg, &obj_tx_msg_buffer, PyBUF_SIMPLE);

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
        if (!icsneoISO15765_TransmitMessage(handle, ulNetworkID, (stCM_ISO157652_TxMessage*)obj_tx_msg_buffer.buf, ulBlockingTimeout)) {
            Py_BLOCK_THREADS
            PyBuffer_Release(&obj_tx_msg_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_TransmitMessage() Failed");
        }
        Py_END_ALLOW_THREADS
        PyBuffer_Release(&obj_tx_msg_buffer);
        return Py_BuildValue("b", true);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_iso15765_receive_message(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    PyObject* obj_rx_msg = NULL;
    unsigned int iIndex = 0;
    //PyObject* obj_rx_msg = PyObject_CallObject((PyObject*)&cm_iso157652_rx_message_object_type, NULL);
    if (!PyArg_ParseTuple(args, arg_parse("OiO:", __FUNCTION__), &obj, &iIndex, &obj_rx_msg)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    if (_isPythonModuleObject_IsInstance(obj_rx_msg, "ics.structures.st_cm_iso157652_rx_message", "st_cm_iso157652_rx_message") != 1)
    {
        return NULL;
    }
    Py_buffer obj_rx_msg_buffer = {};
    PyObject_GetBuffer(obj_rx_msg, &obj_rx_msg_buffer, PyBUF_SIMPLE);

    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            PyBuffer_Release(&obj_rx_msg_buffer);
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        //stCM_ISO157652_RxMessage rx_msg_temp = {0};
        //memcpy(&rx_msg_temp, &(temp->s), sizeof(temp->s));
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, stCM_ISO157652_RxMessage*)> icsneoISO15765_ReceiveMessage(lib, "icsneoISO15765_ReceiveMessage");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoISO15765_ReceiveMessage(handle, iIndex, (stCM_ISO157652_RxMessage*)obj_rx_msg_buffer.buf)) {
            Py_BLOCK_THREADS
            PyBuffer_Release(&obj_rx_msg_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_ReceiveMessage() Failed");
        }
        Py_END_ALLOW_THREADS
        PyBuffer_Release(&obj_rx_msg_buffer);
        Py_RETURN_NONE;
    }
    catch (ice::Exception& ex)
    {
        PyBuffer_Release(&obj_rx_msg_buffer);
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

PyObject* meth_get_timestamp_for_msg(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    PyObject* obj_msg = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OO:", __FUNCTION__), &obj, &obj_msg)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    if (!PySpyMessage_CheckExact(obj_msg) && !PySpyMessageJ1850_CheckExact(obj_msg)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    icsSpyMessage* msg = &PySpyMessage_GetObject(obj_msg)->msg;
    try
    {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall (ICS_HANDLE, icsSpyMessage*, double*)> icsneoGetTimeStampForMsg(lib, "icsneoGetTimeStampForMsg");
        double timestamp = 0;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetTimeStampForMsg(handle, msg, &timestamp)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetTimeStampForMsg() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("d", timestamp);
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_device_status(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    int throw_exception_on_size_mismatch = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O|b:", __FUNCTION__), &obj, &throw_exception_on_size_mismatch)) {
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
        PyObject* device_status = _getPythonModuleObject("ics.structures.ics_device_status", "ics_device_status");
        if (!device_status)
        {
            return NULL;
        }
        Py_buffer device_status_buffer = {};
        PyObject_GetBuffer(device_status, &device_status_buffer, PyBUF_SIMPLE);

        size_t device_status_size = device_status_buffer.len;
        ice::Function<int __stdcall (ICS_HANDLE, icsDeviceStatus*, size_t*)> icsneoGetDeviceStatus(lib, "icsneoGetDeviceStatus");
        double timestamp = 0;
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetDeviceStatus(handle, (icsDeviceStatus*)device_status_buffer.buf, &device_status_size)) {
            Py_BLOCK_THREADS
            PyBuffer_Release(&device_status_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceStatus() Failed");
        }
        if (throw_exception_on_size_mismatch)
        {
            if (device_status_size != device_status_buffer.len)
            {
                Py_BLOCK_THREADS
                PyBuffer_Release(&device_status_buffer);
                return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceStatus() API mismatch detected!");
            }
        }
        Py_END_ALLOW_THREADS
        return device_status;
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_enable_network_com(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    bool enable = true; 
    long net_id = -1;
    if (!PyArg_ParseTuple(args, arg_parse("O|bk:", __FUNCTION__), &obj, &enable, &net_id)) {
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
        // int _stdcall icsneoEnableNetworkCom(void* hObject, int iEnable)
        // int _stdcall icsneoEnableNetworkComEx(void* hObject, int iEnable, int iNetId)
        ice::Function<int __stdcall (ICS_HANDLE, int)> icsneoEnableNetworkCom(lib, "icsneoEnableNetworkCom");
        ice::Function<int __stdcall (ICS_HANDLE, int, int)> icsneoEnableNetworkComEx(lib, "icsneoEnableNetworkComEx");
        Py_BEGIN_ALLOW_THREADS
        if (net_id == -1) {
            if (!icsneoEnableNetworkCom(handle, enable)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoEnableNetworkCom() Failed");
            }
        } else {
            if (!icsneoEnableNetworkComEx(handle, enable, net_id)) {
                Py_BLOCK_THREADS
                return set_ics_exception(exception_runtime_error(), "icsneoEnableNetworkComEx() Failed");
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

PyObject* meth_enable_bus_voltage_monitor(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned int enable = 1;
    unsigned int reserved = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O|ii:", __FUNCTION__), &obj, &enable, &reserved)) {
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
        // int _stdcall icsneoEnableBusVoltageMonitor(void* hObject, unsigned int enable, unsigned int reserved)
        ice::Function<int __stdcall (ICS_HANDLE, unsigned int, unsigned int)> icsneoEnableBusVoltageMonitor(lib, "icsneoEnableBusVoltageMonitor");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoEnableBusVoltageMonitor(handle, enable, reserved)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoEnableBusVoltageMonitor() Failed");
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

PyObject* meth_get_bus_voltage(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned int reserved = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O|i:", __FUNCTION__), &obj, &reserved)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try
    {
        unsigned long mV = 0;
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoGetBusVoltage(void* hObject, unsigned long* pVBusVoltage, unsigned int reserved
        ice::Function<int __stdcall (ICS_HANDLE, unsigned long*, unsigned int)> icsneoGetBusVoltage(lib, "icsneoGetBusVoltage");
        Py_BEGIN_ALLOW_THREADS
        if (!icsneoGetBusVoltage(handle, &mV, reserved)) {
            Py_BLOCK_THREADS
            return set_ics_exception(exception_runtime_error(), "icsneoGetBusVoltage() Failed");
        }
        Py_END_ALLOW_THREADS
        return Py_BuildValue("i", mV);
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
        return Py_BuildValue("s", lib->getPath().c_str());
    }
    catch (ice::Exception& ex)
    {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
