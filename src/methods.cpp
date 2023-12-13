#include "methods.h"
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

#include <memory>

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

// Internal function
char* neodevice_to_string(unsigned long type)
{
    switch (type) {
        case NEODEVICE_UNKNOWN:
            return "Unknown";
        case NEODEVICE_BLUE:
            return "neoVI BLUE";
        case NEODEVICE_ECU_AVB:
            return "neoECU AVB/TSN";
        case NEODEVICE_RADSUPERMOON:
            return "RAD-Supermoon";
        case NEODEVICE_DW_VCAN:
            return "ValueCAN DW";
        case NEODEVICE_RADMOON2:
            return "RAD-Moon 2";
        case NEODEVICE_RADGIGALOG:
            return "RAD-Gigalog";
        case NEODEVICE_VCAN41:
            return "ValueCAN 4-1";
        case NEODEVICE_FIRE:
            return "neoVI FIRE";
        case NEODEVICE_RADPLUTO:
            return "RAD-Pluto";
        case NEODEVICE_VCAN42_EL:
            return "ValueCAN 4-2EL";
        case NEODEVICE_RADIO_CANHUB:
            return "neoRAD-IO2-CANHUB";
        case NEODEVICE_NEOECU12:
            return "neoECU12";
        case NEODEVICE_OBD2_LC:
            return "neoOBD2-LC";
        case NEODEVICE_RAD_MOON_DUO:
            return "RAD-Moon Duo";
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
        case NEODEVICE_FIRE2_REDLINE:
            return "neoVI FIRE 2 Redline";
        case NEODEVICE_ETHER_BADGE:
            return "EtherBADGE";
        case NEODEVICE_RAD_A2B:
            return "RAD-A2B";
        case NEODEVICE_RADEPSILON:
            return "RAD-Epsilon";
        case NEODEVICE_OBD2_SIM_DOIP:
        case NEODEVICE_OBD2_SIM:
            return "neoOBD2-SIM";
        case NEODEVICE_OBD2_DEV:
            return "neoOBD2-DEV";
        case NEODEVICE_ECU22:
            return "neoECU22";
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
        case NEODEVICE_RED:
            return "neoVI RED";
        case NEODEVICE_ECU:
            return "neoECU";
        case NEODEVICE_IEVB: // also NEODEVICE_NEOECUCHIP
            return "IEVB";
        case NEODEVICE_PENDANT:
            return "Pendant";
        case NEODEVICE_OBD2_PRO:
            return "neoOBD2 PRO";
        case NEODEVICE_ECUCHIP_UART:
            return "ECUCHIP";
        case NEODEVICE_PLASMA: // also NEODEVICE_ANY_PLASMA
            return "neoVI PLASMA";
        case NEODEVICE_NEOANALOG:
            return "neoAnalog";
        case NEODEVICE_CT_OBD:
            return "neoOBD CT";
        case NEODEVICE_ION: // also NEODEVICE_ANY_ION
            return "neoVI ION";
        case NEODEVICE_RADSTAR:
            return "RAD-Star";
        case NEODEVICE_VCAN44:
            return "ValueCAN 4-4";
        case NEODEVICE_VCAN42:
            return "ValueCAN 4-2";
        case NEODEVICE_CMPROBE:
            return "CM Probe";
        case NEODEVICE_EEVB:
            return "EEVB";
        case NEODEVICE_VCANRF:
            return "ValueCAN.rf";
        case NEODEVICE_FIRE2:
            return "neoVI FIRE 2";
        case NEODEVICE_FLEX:
            return "neoVI FLEX";
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
        default:
            return "Unknown";
    };
    return "Intrepid Device";
}

bool _convertListOrTupleToArray(PyObject* obj, std::vector<PyObject*>* results)
{
    if (!obj || !results) {
        set_ics_exception(exception_runtime_error(), "_convertListOrTupleToArray() was passed invalid arguments");
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

PyObject* meth_find_devices(PyObject* self, PyObject* args, PyObject* keywords)
{
    PyObject* device_types = NULL;
    int network_id = -1;
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
        device_types_list_size = device_type_vector.size();
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
        NeoDeviceEx devices[255] = { 0 };
        int count = 255;

        //
        OptionsFindNeoEx opts = { 0 };
        opts.CANOptions.iNetworkID = network_id;
        POptionsFindNeoEx popts = NULL;
        if (network_id != -1)
            popts = &opts;

        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoFindDevices(devices,
                               &count,
                               device_types_list.get(),
                               device_types_list_size,
                               (network_id != -1) ? &popts : NULL,
                               0)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoFindDevices() Failed");
        }
        Py_END_ALLOW_THREADS;

        PyObject* tuple = PyTuple_New(count);
        if (!tuple) {
            return NULL;
        }
        for (int i = 0; i < count; ++i) {
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
    } catch (ice::Exception& ex) {
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
    bool use_neovi_server = false;
    bool device_need_ref_inc = false;
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
        network_ids_list_size = network_ids_vector.size();
        network_ids_list.reset((new unsigned char(network_ids_list_size)));
        for (unsigned int i = 0; i < network_ids_list_size; ++i)
            network_ids_list[i] = (unsigned char)PyLong_AsLong(network_ids_vector[i]);
        use_network_ids = true;
    }

    // Verify device type
    if (device && PyLong_CheckExact(device)) {
        // Device is a serial number in integer format
        serial_number = PyLong_AsLong(device);
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
                serial_number = PyLong_AsLong(return_value);
            }
        } else {
            return set_ics_exception(exception_runtime_error(), "Failed to convert serial number string to integer.");
        }
    } else if (device && !PyNeoDevice_CheckExact(device)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Invalid 'device' parameter object type passed to open_device().");
    } else if (device && PyNeoDevice_CheckExact(device)) {
        // If the user passed in a NeoDevice device we need to increment
        // the reference counter when we return it since device is a borrowed
        // reference.
        // devs = ics.find_devices()
        // device = ics.open_device(devs[0])
        // del device # This will decrement the reference and crash interp
        device_need_ref_inc = true;
    }

    if ((device && !PyNeoDevice_CheckExact(device)) || !device) {
        // We don't have a device parameter so lets find the first one
        try {
            ice::Function<int __stdcall(
                NeoDeviceEx*, int*, unsigned int*, unsigned int, POptionsFindNeoEx*, unsigned long)>
                icsneoFindDevices(lib, "icsneoFindDevices");
            NeoDeviceEx devices[255];
            int count = 255;

            OptionsFindNeoEx opts = { 0 };
            opts.CANOptions.iNetworkID = network_id;
            POptionsFindNeoEx popts = NULL;
            if (network_id != -1)
                popts = &opts;

            Py_BEGIN_ALLOW_THREADS;
            if (!icsneoFindDevices(devices, &count, NULL, 0, (network_id != -1) ? &popts : NULL, 0)) {
                Py_BLOCK_THREADS;
                return set_ics_exception(exception_runtime_error(), "icsneoFindDevices() Failed");
            }
            Py_END_ALLOW_THREADS;
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
                device = PyObject_CallObject((PyObject*)&neo_device_object_type, NULL);
                PyNeoDevice_GetNeoDevice(device)->dev = devices[i].neoDevice;
                PyNeoDevice_GetNeoDevice(device)->name =
                    PyUnicode_FromString(neodevice_to_string(devices[i].neoDevice.DeviceType));
                break;
            }
            if (!device || !PyNeoDevice_CheckExact(device)) {
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
        NeoDeviceEx neo_device_ex = {};
        neo_device_ex.neoDevice = PyNeoDevice_GetNeoDevice(device)->dev;
        OptionsFindNeoEx opts = { 0 };
        opts.CANOptions.iNetworkID = network_id;
        POptionsFindNeoEx popts = NULL;
        if (network_id != -1)
            popts = &opts;

        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoOpenDevice(&neo_device_ex,
                              &PyNeoDevice_GetNeoDevice(device)->handle,
                              use_network_ids ? network_ids_list.get() : NULL,
                              config_read,
                              options,
                              (network_id != -1) ? popts : NULL,
                              0)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoOpenDevice() Failed");
        }
        Py_END_ALLOW_THREADS;

        if (device_need_ref_inc) {
            Py_INCREF(device);
        }
        return device;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, int*)> icsneoClosePort(lib, "icsneoClosePort");
        ice::Function<void __stdcall(ICS_HANDLE)> icsneoFreeObject(lib, "icsneoFreeObject");
        int error_count = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoClosePort(PyNeoDevice_GetNeoDevice(obj)->handle, &error_count)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoClosePort() Failed");
        }
        icsneoFreeObject(PyNeoDevice_GetNeoDevice(obj)->handle);
        Py_END_ALLOW_THREADS;
        PyNeoDevice_GetNeoDevice(obj)->handle = 0;
        return Py_BuildValue("i", error_count);
    } catch (ice::Exception& ex) {
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
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    icsSpyTime ics_time;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, icsSpyTime*)> icsneoGetRTC(lib, "icsneoGetRTC");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetRTC(handle, &ics_time)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetRTC() Failed");
        }
        Py_END_ALLOW_THREADS;
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
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
    ics_time.year = PyDateTime_GET_YEAR(datetime_object) % 100;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, icsSpyTime*)> icsneoSetRTC(lib, "icsneoSetRTC");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoSetRTC(handle, &ics_time)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoSetRTC() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
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
        if (!f) {
            std::stringstream ss;
            ss << "Failed to open CoreMini script file: '" << file_name << "'. Please make sure path exists";
            return set_ics_exception_dev(exception_runtime_error(), obj, (char*)ss.str().c_str());
        }
        fseek(f, 0, SEEK_END);
        fsize = ftell(f);
        rewind(f);
        data = (unsigned char*)malloc(sizeof(char) * fsize);
        data_size = (int)fread(data, 1, fsize, f);
        fclose(f);
        if (fsize != data_size) {
            return set_ics_exception_dev(exception_runtime_error(), obj, "CoreMini binary file size mismatch");
        }
    } else if (PyTuple_CheckExact(arg_data)) {
        Py_ssize_t tuple_size = PyTuple_Size(arg_data);
        data = (unsigned char*)malloc(sizeof(char) * tuple_size);
        // Move tuple data into array
        for (int i = 0; i < tuple_size; ++i) {
            PyObject* value = PyTuple_GET_ITEM(arg_data, i);
            if (!PyLong_CheckExact(value)) {
                return set_ics_exception_dev(
                    exception_runtime_error(), obj, "Failed to convert tuple data. Tuple data must be integer type");
            }
            data[i] = (unsigned char)PyLong_AsLong(PyTuple_GET_ITEM(arg_data, i));
        }
        fsize = tuple_size;
        data_size = fsize;
    } else {
        return set_ics_exception_dev(exception_runtime_error(), obj, "Argument must be filepath or tuple");
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, const unsigned char*, unsigned long, int)> icsneoScriptLoad(
            lib, "icsneoScriptLoad");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptLoad(handle, data, data_size, location)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptLoad() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, int)> icsneoScriptStart(lib, "icsneoScriptStart");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptStart(handle, location)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStart() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE)> icsneoScriptStop(lib, "icsneoScriptStop");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptStop(handle)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStop() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, int)> icsneoScriptClear(lib, "icsneoScriptClear");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptClear(handle, location)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptClear() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, int*)> icsneoScriptGetScriptStatus(lib, "icsneoScriptGetScriptStatus");
        int status = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptGetScriptStatus(handle, &status)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptClear() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("b", status == 1);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
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
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, icsSpyMessage*, int, int)> icsneoTxMessages(lib, "icsneoTxMessages");
        const Py_ssize_t TUPLE_COUNT = PyTuple_Size(tuple);
        icsSpyMessage** msgs = new icsSpyMessage*[TUPLE_COUNT]();
        for (int i = 0; i < TUPLE_COUNT; ++i) {
            spy_message_object* obj = (spy_message_object*)PyTuple_GetItem(tuple, i);
            if (!obj) {
                if (created_tuple) {
                    Py_XDECREF(tuple);
                }
                delete[] msgs;
                return set_ics_exception(exception_runtime_error(),
                                         "Tuple item must be of " MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME);
            }
            msgs[i] = &(obj->msg);
        }
        Py_BEGIN_ALLOW_THREADS;
        for (int i = 0; i < TUPLE_COUNT; ++i) {
            if (!icsneoTxMessages(handle, msgs[i], (msgs[i]->NetworkID2 << 8) | msgs[i]->NetworkID, 1)) {
                Py_BLOCK_THREADS;
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
        Py_END_ALLOW_THREADS;
        if (created_tuple) {
            Py_XDECREF(tuple);
        }
        delete[] msgs;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_messages(PyObject* self, PyObject* args)
{
    // Py_RETURN_NONE;
    double timeout = 0.1;
    int use_j1850 = 0;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O|bd:", __FUNCTION__), &obj, &use_j1850, &timeout)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    // Convert timeout to ms
    timeout *= 1000;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int)> icsneoWaitForRxMessagesWithTimeOut(
            lib, "icsneoWaitForRxMessagesWithTimeOut");
        ice::Function<int __stdcall(ICS_HANDLE, icsSpyMessage*, int*, int*)> icsneoGetMessages(lib,
                                                                                               "icsneoGetMessages");
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
            return set_ics_exception_dev(exception_runtime_error(), obj, "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
        }
        Py_BEGIN_ALLOW_THREADS;
        if (timeout == 0 || icsneoWaitForRxMessagesWithTimeOut(handle, (unsigned int)timeout)) {
            if (!icsneoGetMessages(handle, (icsSpyMessage*)msgs, &count, &errors)) {
                Py_BLOCK_THREADS;
                PyMem_Free(msgs);
                return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoGetMessages() Failed");
            }
        } else {
            count = 0;
        }
        Py_END_ALLOW_THREADS;
        PyObject* tuple = PyTuple_New(count);
        for (int i = 0; i < count; ++i) {
            PyObject* obj = NULL;
            if (use_j1850) {
                obj = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            } else {
                obj = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            }
            if (!obj) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception_dev(
                    exception_runtime_error(), obj, "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
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
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);

    unsigned long parameters[255] = { 0 };
    unsigned long parameters_count = 0;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned long*, unsigned long, unsigned long&)>
            icsneoScriptGetScriptStatusEx(lib, "icsneoScriptGetScriptStatusEx");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptGetScriptStatusEx(
                handle, parameters, sizeof(parameters) / sizeof(&parameters[0]), parameters_count)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptGetScriptStatusEx() Failed");
        }
        Py_END_ALLOW_THREADS;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    PyObject* list_object = PyList_New(0);
    for (unsigned long i = 0; i < parameters_count; ++i) {
        PyObject* obj = Py_BuildValue("i", parameters[i]);
        PyList_Append(list_object, obj);
    }
    return list_object;
}

PyObject* meth_get_error_messages(PyObject* self, PyObject* args)
{
    // return PyList_New(0);
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    int errors[600] = { 0 };
    int error_count = 600;

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, int*, int*)> icsneoGetErrorMessages(lib, "icsneoGetErrorMessages");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetErrorMessages(handle, errors, &error_count)) {
            Py_UNBLOCK_THREADS return set_ics_exception(exception_runtime_error(),
                                                        "icsneoScriptGetScriptStatusEx() Failed");
        }
        Py_END_ALLOW_THREADS;
        ice::Function<int __stdcall(int, char*, char*, int*, int*, int*, int*)> icsneoGetErrorInfo(
            lib, "icsneoGetErrorInfo");
        PyObject* list = PyList_New(0);
        for (int i = 0; i < error_count; ++i) {
            char description_short[255] = { 0 };
            char description_long[255] = { 0 };
            int description_short_length = 255;
            int description_long_length = 255;
            int severity = 0, restart_needed = 0;
            Py_BEGIN_ALLOW_THREADS;
            if (!icsneoGetErrorInfo(errors[i],
                                    description_short,
                                    description_long,
                                    &description_short_length,
                                    &description_long_length,
                                    &severity,
                                    &restart_needed)) {
                Py_BLOCK_THREADS;
                Py_XDECREF(list);
                return set_ics_exception(exception_runtime_error(), "icsneoGetErrorInfo() Failed");
            }
            Py_END_ALLOW_THREADS;
            PyObject* tuple = Py_BuildValue(
                "i, s, s, i, i", errors[i], description_short, description_long, severity, restart_needed);

            PyList_Append(list, tuple);
            Py_XDECREF(tuple);
        }
        return list;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "First argument must be of " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME " type");
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
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
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
        Py_BEGIN_ALLOW_THREADS;
        if (!FlashDevice2(0x3835C256, &(neo_device->dev), rc, reflash_count, 0, 0, 0, &message_callback)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "FlashDevice2() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        ice::Function<int __stdcall(void (*)(const wchar_t*, unsigned long))> icsneoSetReflashCallback(
            lib, "icsneoSetReflashCallback");
        Py_BEGIN_ALLOW_THREADS;
        if (callback == Py_None) {
            if (!icsneoSetReflashCallback(NULL)) {
                Py_BLOCK_THREADS;
                return set_ics_exception(exception_runtime_error(), "icsneoSetReflashCallback() Failed");
            }
        } else {
            if (!icsneoSetReflashCallback(&message_reflash_callback)) {
                Py_BLOCK_THREADS;
                return set_ics_exception(exception_runtime_error(), "icsneoSetReflashCallback() Failed");
            }
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
    if (!settings) {
        return NULL;
    }
    // Grab the buffer out of the newly created object - make sure to call PyBuffer_Release(&settings_buffer) when done.
    Py_buffer settings_buffer = {};
    PyObject_GetBuffer(settings, &settings_buffer, PyBUF_C_CONTIGUOUS | PyBUF_WRITABLE);

    // Verify we have a valid NeoDevice Object - This comes after s_device_settings allocation for testing purposes
    if (!PyNeoDevice_CheckExact(obj)) {
        PyBuffer_Release(&settings_buffer);
        Py_DECREF(settings);
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            PyBuffer_Release(&settings_buffer);
            Py_DECREF(settings);
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // Set/Get the DeviceSettingsType
        Py_BEGIN_ALLOW_THREADS;
        EDeviceSettingsType* setting_type = &((SDeviceSettings*)settings_buffer.buf)->DeviceSettingType;
        if (device_type_override == -1) {
            // int _stdcall icsneoGetDeviceSettingsType(void* hObject, EPlasmaIonVnetChannel_t vnetSlot,
            // EDeviceSettingsType* pDeviceSettingsType)
            ice::Function<int __stdcall(ICS_HANDLE, EPlasmaIonVnetChannel_t, EDeviceSettingsType*)>
                icsneoGetDeviceSettingsType(lib, "icsneoGetDeviceSettingsType");
            if (!icsneoGetDeviceSettingsType(handle, vnet_slot, setting_type)) {
                Py_BLOCK_THREADS;
                PyBuffer_Release(&settings_buffer);
                Py_DECREF(settings);
                return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceSettingsType() Failed");
            }
        }
        // int _stdcall icsneoGetDeviceSettings(void* hObject, SDeviceSettings* pSettings, int iNumBytes,
        // EPlasmaIonVnetChannel_t vnetSlot)
        ice::Function<int __stdcall(ICS_HANDLE, SDeviceSettings*, int, EPlasmaIonVnetChannel_t)>
            icsneoGetDeviceSettings(lib, "icsneoGetDeviceSettings");
        if (!icsneoGetDeviceSettings(handle, (SDeviceSettings*)settings_buffer.buf, settings_buffer.len, vnet_slot)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&settings_buffer);
            Py_DECREF(settings);
            return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceSettings() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyBuffer_Release(&settings_buffer);
        return settings;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoSetDeviceSettings(void* hObject, SDeviceSettings* pSettings, int bSaveToEEPROM,
        // EPlasmaIonVnetChannel_t vnetSlot) int _stdcall icsneoSetDeviceSettings(void* hObject, SDeviceSettings*
        // pSettings, int iNumBytes, int bSaveToEEPROM, EPlasmaIonVnetChannel_t vnetSlot)
        ice::Function<int __stdcall(ICS_HANDLE, SDeviceSettings*, int, int, EPlasmaIonVnetChannel_t)>
            icsneoSetDeviceSettings(lib, "icsneoSetDeviceSettings");
        Py_buffer settings_buffer = {};
        PyObject_GetBuffer(settings, &settings_buffer, PyBUF_C_CONTIGUOUS | PyBUF_WRITABLE);
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoSetDeviceSettings(
                handle, (SDeviceSettings*)settings_buffer.buf, settings_buffer.len, save_to_eeprom, vnet_slot)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&settings_buffer);
            return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoSetDeviceSettings() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyBuffer_Release(&settings_buffer);
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    int errors[600] = { 0 };
    int error_count = 600;
    PyObject* list = PyList_New(0);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE)> icsneoLoadDefaultSettings(lib, "icsneoLoadDefaultSettings");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoLoadDefaultSettings(PyNeoDevice_GetNeoDevice(obj)->handle)) {
            Py_BLOCK_THREADS;
            return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoLoadDefaultSettings() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_read_sdcard(PyObject* self,
                           PyObject* args) // icsneoReadSDCard(int hObject,unsigned long iSectorIndex,unsigned char
                                           // *data, unsigned long *bytesRead)
{
    PyObject* obj = NULL;
    unsigned long index = 0;
    unsigned long size = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Ok:", __FUNCTION__), &obj, &index, &size)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    // We only read 512 bytes internally, x4 for future compatibility?
    unsigned char data[2048] = { 0 };
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned long, unsigned char*, unsigned long*)> icsneoReadSDCard(
            lib, "icsneoReadSDCard");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoReadSDCard(PyNeoDevice_GetNeoDevice(obj)->handle, index, data, &size)) {
            Py_BLOCK_THREADS;
            return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoReadSDCard() Failed");
        }
        Py_END_ALLOW_THREADS;
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
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_write_sdcard(
    PyObject* self,
    PyObject* args) // icsneoWriteSDCard(int hObject,unsigned long iSectorIndex,const unsigned char *data)
{
    PyObject* obj = NULL;
    unsigned long index = 0;
    PyObject* ba_obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OkO:", __FUNCTION__), &obj, &index, &ba_obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
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
        ice::Function<int __stdcall(ICS_HANDLE, unsigned long, unsigned char*)> icsneoWriteSDCard(lib,
                                                                                                  "icsneoWriteSDCard");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoWriteSDCard(
                PyNeoDevice_GetNeoDevice(obj)->handle, index, (unsigned char*)PyByteArray_AsString(ba_obj))) {
            Py_BLOCK_THREADS;
            return set_ics_exception_dev(exception_runtime_error(), obj, "icsneoWriteSDCard() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_create_neovi_radio_message(PyObject* self, PyObject* args, PyObject* keywords)
{
    // int PyArg_ParseTupleAndKeywords(PyObject *args, PyObject *kw, const char *format, char *keywords[], ...)
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
    int relay_timeout = 0;
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
    int index;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &index)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int)> icsneoScriptStartFBlock(lib, "icsneoScriptStartFBlock");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptStartFBlock(handle, index)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStartFBlock() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int)> icsneoScriptStopFBlock(lib, "icsneoScriptStopFBlock");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptStopFBlock(handle, index)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptStopFBlock() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, int*)> icsneoScriptGetFBlockStatus(
            lib, "icsneoScriptGetFBlockStatus");
        int status = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptGetFBlockStatus(handle, index, &status)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptGetFBlockStatus() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("b", status == 1);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_read_app_signal(PyObject* self, PyObject* args) // ScriptReadAppSignal
{
    int index;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("Oi:", __FUNCTION__), &obj, &index)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, double*)> icsneoScriptReadAppSignal(
            lib, "icsneoScriptReadAppSignal");
        double value = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptReadAppSignal(handle, index, &value)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptReadAppSignal() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("d", value);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_write_app_signal(PyObject* self, PyObject* args) // ScriptWriteAppSignal
{
    int index;
    PyObject* obj = NULL;
    double value = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oid:", __FUNCTION__), &obj, &index, &value)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, double)> icsneoScriptWriteAppSignal(
            lib, "icsneoScriptWriteAppSignal");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptWriteAppSignal(handle, index, value)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptWriteAppSignal() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_read_tx_message(PyObject* self, PyObject* args) // ScriptReadTxMessage
{
    int index;
    PyObject* obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oi|b:", __FUNCTION__), &obj, &index, &j1850)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, void*)> icsneoScriptReadTxMessage(
            lib, "icsneoScriptReadTxMessage");
        PyObject* msg = NULL;
        if (j1850) {
            msg = PyObject_CallObject((PyObject*)&spy_message_j1850_object_type, NULL);
            if (!msg) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(),
                                         "Failed to allocate " SPY_MESSAGE_J1850_OBJECT_NAME);
            }
            Py_BEGIN_ALLOW_THREADS;
            if (!icsneoScriptReadTxMessage(handle, index, &PySpyMessageJ1850_GetObject(msg)->msg)) {
                Py_BLOCK_THREADS;
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadTxMessage() Failed");
            }
            Py_END_ALLOW_THREADS;
        } else {
            PyObject* msg = PyObject_CallObject((PyObject*)&spy_message_object_type, NULL);
            if (!msg) {
                // This should only happen if we run out of memory (malloc failure)?
                PyErr_Print();
                return set_ics_exception(exception_runtime_error(), "Failed to allocate " SPY_MESSAGE_OBJECT_NAME);
            }
            Py_BEGIN_ALLOW_THREADS;
            if (!icsneoScriptReadTxMessage(handle, index, &PySpyMessage_GetObject(msg)->msg)) {
                Py_BLOCK_THREADS;
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadTxMessage() Failed");
            }
            Py_END_ALLOW_THREADS;
        }
        return msg;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_read_rx_message(PyObject* self, PyObject* args) // ScriptReadRxMessage
{
    int index;
    PyObject* obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oi|b:", __FUNCTION__), &obj, &index, &j1850)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, void*, void*)> icsneoScriptReadRxMessage(
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
            Py_BEGIN_ALLOW_THREADS;
            if (!icsneoScriptReadRxMessage(handle,
                                           index,
                                           &PySpyMessageJ1850_GetObject(msg_mask)->msg,
                                           &PySpyMessageJ1850_GetObject(msg_mask)->msg)) {
                Py_BLOCK_THREADS;
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadRxMessage() Failed");
            }
            Py_END_ALLOW_THREADS;
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
            Py_BEGIN_ALLOW_THREADS;
            if (!icsneoScriptReadRxMessage(
                    handle, index, &PySpyMessage_GetObject(msg)->msg, &PySpyMessage_GetObject(msg_mask)->msg)) {
                Py_BLOCK_THREADS;
                return set_ics_exception(exception_runtime_error(), "icsneoScriptReadRxMessage() Failed");
            }
            Py_END_ALLOW_THREADS;
        }
        return Py_BuildValue("(O,O)", msg, msg_mask);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_write_tx_message(PyObject* self, PyObject* args) // icsneoScriptWriteTxMessage
{
    int index;
    PyObject* obj = NULL;
    PyObject* msg_obj = NULL;
    int j1850 = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OiO|b:", __FUNCTION__), &obj, &index, &msg_obj, &j1850)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    void* msg = NULL;
    void* msg_mask = NULL;
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
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, void*)> icsneoScriptWriteTxMessage(
            lib, "icsneoScriptWriteTxMessage");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptWriteTxMessage(handle, index, msg)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptWriteTxMessage() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_coremini_write_rx_message(PyObject* self, PyObject* args) // icsneoScriptWriteRxMessage
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
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
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, void*, void*)> icsneoScriptWriteRxMessage(
            lib, "icsneoScriptWriteRxMessage");
        if (!icsneoScriptWriteRxMessage(handle, index, msg, msg_mask)) {
            return set_ics_exception(exception_runtime_error(), "icsneoScriptWriteRxMessage() Failed");
        }
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, int*, int*, int*, int*, int*, int*, int*, int*)>
            icsneoGetPerformanceParameters(lib, "icsneoGetPerformanceParameters");
        int buffer_count = 0;
        int buffer_max = 0;
        int overflow_count = 0;
        int reserved1 = 0;
        int reserved2 = 0;
        int reserved3 = 0;
        int reserved4 = 0;
        int reserved5 = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetPerformanceParameters(handle,
                                            &buffer_count,
                                            &buffer_max,
                                            &overflow_count,
                                            &reserved1,
                                            &reserved2,
                                            &reserved3,
                                            &reserved4,
                                            &reserved5)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetPerformanceParameters() Failed");
        }
        Py_END_ALLOW_THREADS;
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
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_validate_hobject(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyLong_CheckExact(obj) && !PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME " or Integer");
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE)> icsneoValidateHObject(lib, "icsneoValidateHObject");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoValidateHObject(handle)) {
            Py_BLOCK_THREADS;
            return Py_BuildValue("b", false);
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetNeoDevice(obj)->handle;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, int*)> icsneoGetLastAPIError(lib, "icsneoGetLastAPIError");
        ice::Function<int __stdcall(int, char*, char*, int*, int*, int*, int*)> icsneoGetErrorInfo(
            lib, "icsneoGetErrorInfo");
        int error = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetLastAPIError(handle, &error)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetLastAPIError() Failed");
        }
        Py_END_ALLOW_THREADS;
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
        return Py_BuildValue("i, s, s, i, i", error, description_short, description_long, severity, restart_needed);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_dll_version(PyObject* self, PyObject* args)
{
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall()> icsneoGetDLLVersion(lib, "icsneoGetDLLVersion");
        int result = 0;
        Py_BEGIN_ALLOW_THREADS;
        result = icsneoGetDLLVersion();
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("i", result);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(void*, unsigned int*)> icsneoGetSerialNumber(lib, "icsneoGetSerialNumber");
        unsigned int serial = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetSerialNumber(handle, &serial)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetSerialNumber() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("i", serial);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, stAPIFirmwareInfo*)> icsneoGetHWFirmwareInfo(lib,
                                                                                             "icsneoGetHWFirmwareInfo");
        PyObject* info = _getPythonModuleObject("ics.structures.st_api_firmware_info", "st_api_firmware_info");
        if (!info) {
            return NULL;
        }
        Py_buffer info_buffer = {};
        PyObject_GetBuffer(info, &info_buffer, PyBUF_SIMPLE);

        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetHWFirmwareInfo(handle, (stAPIFirmwareInfo*)info_buffer.buf)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&info_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoGetHWFirmwareInfo() Failed");
        }
        Py_END_ALLOW_THREADS;
        return info;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_base36enc(PyObject* self, PyObject* args)
{
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
    PyObject* obj = NULL;
    unsigned int timeout_ms = 0;
    unsigned int mode = 0;
    unsigned int reserved = 0;
    if (!PyArg_ParseTuple(args, arg_parse("Oii|i:", __FUNCTION__), &obj, &timeout_ms, &mode, &reserved)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, unsigned int, unsigned int)> icsneoRequestEnterSleepMode(
            lib, "icsneoRequestEnterSleepMode");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoRequestEnterSleepMode(handle, timeout_ms, mode, reserved)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoRequestEnterSleepMode() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = 0;
    if (PyNeoDevice_CheckExact(obj))
        handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE)> icsneoSetContext(lib, "icsneoSetContext");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoSetContext(handle)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoSetContext() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = 0;
    if (PyNeoDevice_CheckExact(obj))
        handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE)> icsneoForceFirmwareUpdate(lib, "icsneoForceFirmwareUpdate");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoForceFirmwareUpdate(handle)) {
            Py_BLOCK_THREADS;
            return Py_BuildValue("b", false);
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = 0;
    if (PyNeoDevice_CheckExact(obj))
        handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE)> icsneoFirmwareUpdateRequired(lib, "icsneoFirmwareUpdateRequired");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoFirmwareUpdateRequired(handle)) {
            Py_BLOCK_THREADS;
            return Py_BuildValue("b", false);
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, stAPIFirmwareInfo*)> icsneoGetDLLFirmwareInfo(
            lib, "icsneoGetDLLFirmwareInfo");
        PyObject* info = _getPythonModuleObject("ics.structures.st_api_firmware_info", "st_api_firmware_info");
        if (!info) {
            return NULL;
        }
        Py_buffer info_buffer = {};
        PyObject_GetBuffer(info, &info_buffer, PyBUF_SIMPLE);
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetDLLFirmwareInfo(handle, (stAPIFirmwareInfo*)info_buffer.buf)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetDLLFirmwareInfo() Failed");
        }
        Py_END_ALLOW_THREADS;
        return info;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int&)> icsneoGetBackupPowerEnabled(
            lib, "icsneoGetBackupPowerEnabled");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetBackupPowerEnabled(handle, enabled)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetBackupPowerEnabled() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("b", enabled);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int)> icsneoSetBackupPowerEnabled(
            lib, "icsneoSetBackupPowerEnabled");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoSetBackupPowerEnabled(handle, enabled)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoSetBackupPowerEnabled() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("b", enabled);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_backup_power_ready(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned int enabled = 0;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int&)> icsneoGetBackupPowerReady(lib,
                                                                                          "icsneoGetBackupPowerReady");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetBackupPowerReady(handle, enabled)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetBackupPowerReady() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("b", enabled);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

// icsneoScriptLoadReadBin
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
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
        if (!f) {
            std::stringstream ss;
            ss << "Failed to open Readbin: '" << file_name << "'. Please make sure path exists";
            return set_ics_exception_dev(exception_runtime_error(), obj, (char*)ss.str().c_str());
        }
        fseek(f, 0, SEEK_END);
        fsize = ftell(f);
        rewind(f);
        data = (unsigned char*)malloc(sizeof(char) * fsize);
        data_size = (int)fread(data, 1, fsize, f);
        fclose(f);
        if (fsize != data_size) {
            return set_ics_exception_dev(exception_runtime_error(), obj, "Readbin file size mismatch");
        }
    } else if (PyTuple_CheckExact(arg_data)) {
        Py_ssize_t tuple_size = PyTuple_Size(arg_data);
        data = (unsigned char*)malloc(sizeof(char) * tuple_size);
        // Move tuple data into array
        for (int i = 0; i < tuple_size; ++i) {
            PyObject* value = PyTuple_GET_ITEM(arg_data, i);
            if (!PyLong_CheckExact(value)) {
                return set_ics_exception_dev(
                    exception_runtime_error(), obj, "Failed to convert tuple data. Tuple data must be integer type");
            }
            data[i] = (unsigned char)PyLong_AsLong(PyTuple_GET_ITEM(arg_data, i));
        }
        fsize = tuple_size;
        data_size = fsize;
    } else {
        return set_ics_exception_dev(exception_runtime_error(), obj, "Argument must be filepath or tuple");
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, const unsigned char*, unsigned long, int)> icsneoScriptLoadReadBin(
            lib, "icsneoScriptLoadReadBin");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoScriptLoadReadBin(handle, data, data_size, location)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoScriptLoadReadBin() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

// void* hObject, unsigned long ulNetworkID, stCM_ISO157652_TxMessage *pMsg, unsigned long ulBlockingTimeout)
PyObject* meth_iso15765_transmit_message(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned long ulNetworkID = 0;
    PyObject* obj_tx_msg = NULL;
    unsigned long ulBlockingTimeout = 0;
    if (!PyArg_ParseTuple(
            args, arg_parse("OkOk:", __FUNCTION__), &obj, &ulNetworkID, &obj_tx_msg, &ulBlockingTimeout)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    if (_isPythonModuleObject_IsInstance(
            obj_tx_msg, "ics.structures.st_cm_iso157652_tx_message", "st_cm_iso157652_tx_message") != 1) {
        return NULL;
    }
    Py_buffer obj_tx_msg_buffer = {};
    PyObject_GetBuffer(obj_tx_msg, &obj_tx_msg_buffer, PyBUF_SIMPLE);

    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned long, stCM_ISO157652_TxMessage*, unsigned long)>
            icsneoISO15765_TransmitMessage(lib, "icsneoISO15765_TransmitMessage");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoISO15765_TransmitMessage(
                handle, ulNetworkID, (stCM_ISO157652_TxMessage*)obj_tx_msg_buffer.buf, ulBlockingTimeout)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&obj_tx_msg_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_TransmitMessage() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyBuffer_Release(&obj_tx_msg_buffer);
        return Py_BuildValue("b", true);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_iso15765_receive_message(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    PyObject* obj_rx_msg = NULL;
    unsigned int iIndex = 0;
    // PyObject* obj_rx_msg = PyObject_CallObject((PyObject*)&cm_iso157652_rx_message_object_type, NULL);
    if (!PyArg_ParseTuple(args, arg_parse("OiO:", __FUNCTION__), &obj, &iIndex, &obj_rx_msg)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    if (_isPythonModuleObject_IsInstance(
            obj_rx_msg, "ics.structures.st_cm_iso157652_rx_message", "st_cm_iso157652_rx_message") != 1) {
        return NULL;
    }
    Py_buffer obj_rx_msg_buffer = {};
    PyObject_GetBuffer(obj_rx_msg, &obj_rx_msg_buffer, PyBUF_SIMPLE);

    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            PyBuffer_Release(&obj_rx_msg_buffer);
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // stCM_ISO157652_RxMessage rx_msg_temp = {0};
        // memcpy(&rx_msg_temp, &(temp->s), sizeof(temp->s));
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, stCM_ISO157652_RxMessage*)> icsneoISO15765_ReceiveMessage(
            lib, "icsneoISO15765_ReceiveMessage");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoISO15765_ReceiveMessage(handle, iIndex, (stCM_ISO157652_RxMessage*)obj_rx_msg_buffer.buf)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&obj_rx_msg_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_ReceiveMessage() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyBuffer_Release(&obj_rx_msg_buffer);
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned long)> icsneoISO15765_EnableNetworks(
            lib, "icsneoISO15765_EnableNetworks");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoISO15765_EnableNetworks(handle, networks)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_EnableNetworks() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE)> icsneoISO15765_DisableNetworks(lib, "icsneoISO15765_DisableNetworks");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoISO15765_DisableNetworks(handle)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoISO15765_DisableNetworks() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned long*)> icsneoGetActiveVNETChannel(
            lib, "icsneoGetActiveVNETChannel");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetActiveVNETChannel(handle, &channel)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetActiveVNETChannel() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("i", channel);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned long)> icsneoSetActiveVNETChannel(
            lib, "icsneoSetActiveVNETChannel");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoSetActiveVNETChannel(handle, channel)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoSetActiveVNETChannel() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("i", channel);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, int, int)> icsneoSetBitRate(lib, "icsneoSetBitRate");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoSetBitRate(handle, bitrate, net_id)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoSetBitRate() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, int, int)> icsneoSetFDBitRate(lib, "icsneoSetFDBitRate");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoSetFDBitRate(handle, bitrate, net_id)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoSetFDBitRate() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, int, int, int)> icsneoSetBitRateEx(lib, "icsneoSetBitRateEx");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoSetBitRateEx(handle, bitrate, net_id, options)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoSetBitRateEx() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    if (!PySpyMessage_CheckExact(obj_msg) && !PySpyMessageJ1850_CheckExact(obj_msg)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    icsSpyMessage* msg = &PySpyMessage_GetObject(obj_msg)->msg;
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, icsSpyMessage*, double*)> icsneoGetTimeStampForMsg(
            lib, "icsneoGetTimeStampForMsg");
        double timestamp = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetTimeStampForMsg(handle, msg, &timestamp)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetTimeStampForMsg() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("d", timestamp);
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
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
        PyObject_GetBuffer(device_status, &device_status_buffer, PyBUF_SIMPLE);

        size_t device_status_size = device_status_buffer.len;
        ice::Function<int __stdcall(ICS_HANDLE, icsDeviceStatus*, size_t*)> icsneoGetDeviceStatus(
            lib, "icsneoGetDeviceStatus");
        double timestamp = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetDeviceStatus(handle, (icsDeviceStatus*)device_status_buffer.buf, &device_status_size)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&device_status_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceStatus() Failed");
        }
        if (throw_exception_on_size_mismatch) {
            if (device_status_size != (size_t)device_status_buffer.len) {
                Py_BLOCK_THREADS;
                PyBuffer_Release(&device_status_buffer);
                return set_ics_exception(exception_runtime_error(), "icsneoGetDeviceStatus() API mismatch detected!");
            }
        }
        Py_END_ALLOW_THREADS;
        return device_status;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoEnableNetworkCom(void* hObject, int iEnable)
        // int _stdcall icsneoEnableNetworkComEx(void* hObject, int iEnable, int iNetId)
        ice::Function<int __stdcall(ICS_HANDLE, int)> icsneoEnableNetworkCom(lib, "icsneoEnableNetworkCom");
        ice::Function<int __stdcall(ICS_HANDLE, int, int)> icsneoEnableNetworkComEx(lib, "icsneoEnableNetworkComEx");
        Py_BEGIN_ALLOW_THREADS;
        if (net_id == -1) {
            if (!icsneoEnableNetworkCom(handle, enable)) {
                Py_BLOCK_THREADS;
                return set_ics_exception(exception_runtime_error(), "icsneoEnableNetworkCom() Failed");
            }
        } else {
            if (!icsneoEnableNetworkComEx(handle, enable, net_id)) {
                Py_BLOCK_THREADS;
                return set_ics_exception(exception_runtime_error(), "icsneoEnableNetworkComEx() Failed");
            }
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoEnableBusVoltageMonitor(void* hObject, unsigned int enable, unsigned int reserved)
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, unsigned int)> icsneoEnableBusVoltageMonitor(
            lib, "icsneoEnableBusVoltageMonitor");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoEnableBusVoltageMonitor(handle, enable, reserved)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoEnableBusVoltageMonitor() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
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
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        unsigned long mV = 0;
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoGetBusVoltage(void* hObject, unsigned long* pVBusVoltage, unsigned int reserved
        ice::Function<int __stdcall(ICS_HANDLE, unsigned long*, unsigned int)> icsneoGetBusVoltage(
            lib, "icsneoGetBusVoltage");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetBusVoltage(handle, &mV, reserved)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetBusVoltage() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("i", mV);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_read_jupiter_firmware(PyObject* self, PyObject* args)
{
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
    int ret_val = PyByteArray_Resize(ba, fileSize);
    // TODO: Documentation doesn't say what return value is.

    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int __stdcall icsneoReadJupiterFirmware(void* hObject, char* fileData, size_t* fileDataSize,
        // EPlasmaIonVnetChannel_t channel)
        ice::Function<int __stdcall(ICS_HANDLE, char*, size_t*, EPlasmaIonVnetChannel_t)> icsneoReadJupiterFirmware(
            lib, "icsneoReadJupiterFirmware");

        // Grab the ByteArray Buffer Object
        Py_buffer ba_buffer = {};
        PyObject_GetBuffer(ba, &ba_buffer, PyBUF_C_CONTIGUOUS | PyBUF_WRITABLE);

        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoReadJupiterFirmware(handle, (char*)ba_buffer.buf, &fileSize, channel)) {

            Py_BLOCK_THREADS;
            PyBuffer_Release(&ba_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoReadJupiterFirmware() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyBuffer_Release(&ba_buffer);
        return Py_BuildValue("Oi", ba, fileSize);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_write_jupiter_firmware(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    PyObject* bytes_obj = NULL;
    EPlasmaIonVnetChannel_t channel = PlasmaIonVnetChannelMain;
    if (!PyArg_ParseTuple(args, arg_parse("OO|i:", __FUNCTION__), &obj, &bytes_obj, &channel)) {
        return NULL;
    }
    if (!PyBytes_CheckExact(bytes_obj)) {
        return set_ics_exception(exception_runtime_error(), "Argument must be of Bytes type ");
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int __stdcall icsneoWriteJupiterFirmware(void* hObject, char* fileData, size_t fileDataSize,
        // EPlasmaIonVnetChannel_t channel)
        ice::Function<int __stdcall(ICS_HANDLE, char*, size_t, EPlasmaIonVnetChannel_t)> icsneoWriteJupiterFirmware(
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

        // Grab the ByteArray Buffer Object
        // Py_buffer bytes_buffer = {};
        // PyObject_GetBuffer(bytes, &bytes_buffer, PyBUF_C_CONTIGUOUS);

        Py_BEGIN_ALLOW_THREADS;
        // if (!icsneoWriteJupiterFirmware(handle, (char*)bytes_buffer.buf, bytes_buffer.len, channel)) {
        if (!icsneoWriteJupiterFirmware(handle, bytes_str, bsize, channel)) {
            Py_BLOCK_THREADS;
            Py_DECREF(bytes);
            // PyBuffer_Release(&bytes_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoWriteJupiterFirmware() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_DECREF(bytes);
        // PyBuffer_Release(&bytes_buffer);
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_flash_accessory_firmware(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    PyObject* parms = NULL;
    bool check_success = true;
    if (!PyArg_ParseTuple(args, arg_parse("OO|b:", __FUNCTION__), &obj, &parms, &check_success)) {
        return NULL;
    }
    /*if (!PyArg_ParseTuple(args, arg_parse("OiO|b:", __FUNCTION__), &obj, &accessory_indx, &bytes_obj, &check_success)) {
        return NULL;
    }*/

    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);

    try {

        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        int function_error = (int)AccessoryOperationError;
        // int __stdcall icsneoFlashAccessoryFirmware(void* hObject, FlashAccessoryFirmwareParams* param, int* errorCode)
        //int __stdcall icsneoFlashPhyFirmware(void* hObject, unsigned char phyIndx, unsigned char* fileData, size_t fileDataSize, int* errorCode)
        ice::Function<int __stdcall(ICS_HANDLE, FlashAccessoryFirmwareParams*, int*)> icsneoFlashAccessoryFirmware(
            lib, "icsneoFlashAccessoryFirmware");

        Py_buffer parms_buffer = {};
        PyObject_GetBuffer(parms, &parms_buffer, PyBUF_C_CONTIGUOUS);

        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoFlashAccessoryFirmware(handle, (FlashAccessoryFirmwareParams*)parms_buffer.buf, &function_error)) {
            Py_BLOCK_THREADS;
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
                case AccessoryParamApiVersionError :
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
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("i", function_error);

    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
}

PyObject* meth_get_accessory_firmware_version(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    char accessory_indx = 0;
    bool check_success = true;
    if (!PyArg_ParseTuple(args, arg_parse("Oi|b:", __FUNCTION__), &obj, &accessory_indx, &check_success)) {
        return NULL;
    }

    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);

    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int __stdcall icsneoGetAccessoryFirmwareVersion(void* hObject, unsigned char index, unsigned int* fwVers, int* errorCode)
        ice::Function<int __stdcall(ICS_HANDLE, unsigned char, unsigned int*, int*)> icsneoGetAccessoryFirmwareVersion(
            lib, "icsneoGetAccessoryFirmwareVersion");

        unsigned int accessory_version = 0;
        int function_error = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetAccessoryFirmwareVersion(handle, accessory_indx, &accessory_version, &function_error)) {
            Py_BLOCK_THREADS return set_ics_exception(exception_runtime_error(), "icsneoGetAccessoryFirmwareVersion() Failed");
        }
        Py_END_ALLOW_THREADS;
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
                case AccessoryParamApiVersionError :
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

PyObject* meth_override_library_name(PyObject* self, PyObject* args)
{
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
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_library_path(PyObject* self)
{
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        bool okay = false;
        auto path = lib->getPath(&okay);
        //auto isLoaded = lib->isLoaded();
        return Py_BuildValue("s", path.c_str());
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_disk_details(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, SDiskDetails*)> icsneoRequestDiskDetails(lib,
                                                                                         "icsneoRequestDiskDetails");

        PyObject* details = _getPythonModuleObject("ics.structures.s_disk_details", "s_disk_details");
        if (!details) {
            return NULL;
        }
        Py_buffer details_buffer = {};
        PyObject_GetBuffer(details, &details_buffer, PyBUF_SIMPLE);

        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoRequestDiskDetails(handle, (SDiskDetails*)details_buffer.buf)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&details_buffer);
            Py_DECREF(details);
            return set_ics_exception(exception_runtime_error(), "icsneoRequestDiskDetails() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyBuffer_Release(&details_buffer);
        return details;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_disk_format(PyObject* self, PyObject* args)
{
    PyObject* details = NULL;
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("OO:", __FUNCTION__), &obj, &details)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        Py_buffer details_buffer = {};
        PyObject_GetBuffer(details, &details_buffer, PyBUF_C_CONTIGUOUS | PyBUF_WRITABLE);
        ice::Function<int __stdcall(ICS_HANDLE, SDiskDetails*)> icsneoRequestDiskFormat(lib, "icsneoRequestDiskFormat");

        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoRequestDiskFormat(handle, (SDiskDetails*)details_buffer.buf)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&details_buffer);
            return set_ics_exception(exception_runtime_error(), "icsneoRequestDiskFormat() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyBuffer_Release(&details_buffer);
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_disk_format_cancel(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE)> icsneoRequestDiskFormatCancel(lib, "icsneoRequestDiskFormatCancel");

        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoRequestDiskFormatCancel(handle)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoRequestDiskFormatCancel() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_disk_format_progress(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, SDiskFormatProgress*)> icsneoRequestDiskFormatProgress(
            lib, "icsneoRequestDiskFormatProgress");

        PyObject* progress = _getPythonModuleObject("ics.structures.s_disk_format_progress", "s_disk_format_progress");
        if (!progress) {
            return NULL;
        }
        Py_buffer progress_buffer = {};
        PyObject_GetBuffer(progress, &progress_buffer, PyBUF_SIMPLE);

        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoRequestDiskFormatProgress(handle, (SDiskFormatProgress*)progress_buffer.buf)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&progress_buffer);
            Py_DECREF(progress);
            return set_ics_exception(exception_runtime_error(), "icsneoRequestDiskFormatProgress() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyBuffer_Release(&progress_buffer);
        return progress;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_enable_doip_line(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    bool enable = false;
    if (!PyArg_ParseTuple(args, arg_parse("O|b:", __FUNCTION__), &obj, &enable)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, bool)> icsneoEnableDOIPLine(lib, "icsneoEnableDOIPLine");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoEnableDOIPLine(handle, enable)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoEnableDOIPLine() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_is_device_feature_supported(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned int feature = 0;
    bool enable = false;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &feature)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        unsigned int supported = 0;
        ice::Function<int __stdcall(ICS_HANDLE, DeviceFeature, unsigned int*)> icsneoIsDeviceFeatureSupported(
            lib, "icsneoIsDeviceFeatureSupported");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoIsDeviceFeatureSupported(handle, (DeviceFeature)feature, &supported)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoIsDeviceFeatureSupported() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("I", supported);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_pcb_serial_number(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    if (!PyArg_ParseTuple(args, arg_parse("O:", __FUNCTION__), &obj)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        char pcbsn[32] = { 0 };
        size_t length = sizeof pcbsn / sizeof pcbsn[0];
        ice::Function<int __stdcall(ICS_HANDLE, char*, size_t*)> icsneoGetPCBSerialNumber(lib,
                                                                                          "icsneoGetPCBSerialNumber");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGetPCBSerialNumber(handle, pcbsn, &length)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGetPCBSerialNumber() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("s", pcbsn);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_set_led_property(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned int led = 0;
    unsigned int prop = 0;
    unsigned int value = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OIII:", __FUNCTION__), &obj, &led, &prop, &value)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int, unsigned int, unsigned int)> icsneoSetLedProperty(
            lib, "icsneoSetLedProperty");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoSetLedProperty(handle, led, prop, value)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoSetLedProperty() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_start_dhcp_server(PyObject* self, PyObject* args)
{
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
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
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
        ice::Function<int __stdcall(ICS_HANDLE,
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
        Py_BEGIN_ALLOW_THREADS;
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
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoStartDHCPServer() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_stop_dhcp_server(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned int NetworkID = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &NetworkID)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, unsigned int)> icsneoStopDHCPServer(lib, "icsneoStopDHCPServer");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoStopDHCPServer(handle, NetworkID)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoStopDHCPServer() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_wbms_manager_write_lock(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    EwBMSManagerPort_t manager = eManagerPortA;
    EwBMSManagerLockState_t lock_state = eLockManager;
    if (!PyArg_ParseTuple(args, arg_parse("OII:", __FUNCTION__), &obj, &manager, &lock_state)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, const EwBMSManagerPort_t, const EwBMSManagerLockState_t)>
            icsneowBMSManagerWriteLock(lib, "icsneowBMSManagerWriteLock");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneowBMSManagerWriteLock(handle, manager, lock_state)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneowBMSManagerWriteLock() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_wbms_manager_reset(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    EwBMSManagerPort_t manager = eManagerPortA;
    if (!PyArg_ParseTuple(args, arg_parse("OI:", __FUNCTION__), &obj, &manager)) {
        return NULL;
    }
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        ice::Function<int __stdcall(ICS_HANDLE, const EwBMSManagerPort_t)> icsneowBMSManagerReset(
            lib, "icsneowBMSManagerReset");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneowBMSManagerReset(handle, manager)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneowBMSManagerReset() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_uart_write(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    EUartPort_t port = eUART0;
    Py_buffer data = {};
    uint8_t flags = 0;
    bool check_size = true;
    if (!PyArg_ParseTuple(args, arg_parse("OIy*|bp:", __FUNCTION__), &obj, &port, &data, &flags, &check_size)) {
        return NULL;
    }

    // Get the device handle
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoUartWrite(void* hObject, const EUartPort_t uart, const void* bData, const size_t
        // bytesToSend, size_t* bytesActuallySent, uint8_t* flags)
        size_t bytesActuallySent = 0;
        ice::Function<int __stdcall(ICS_HANDLE, const EUartPort_t, const void*, const size_t, size_t*, uint8_t*)>
            icsneoUartWrite(lib, "icsneoUartWrite");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoUartWrite(handle, port, data.buf, data.len, &bytesActuallySent, &flags)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoUartWrite() Failed");
        }
        Py_END_ALLOW_THREADS;
        if (check_size && (size_t)data.len != bytesActuallySent) {
            return set_ics_exception(exception_runtime_error(),
                                     "Bytes actually sent didn't match bytes to send length");
        }
        return Py_BuildValue("i", bytesActuallySent);
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_uart_read(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    EUartPort_t port = eUART0;
    unsigned int bytesToRead = 256;
    uint8_t flags = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OI|Is:", __FUNCTION__), &obj, &port, &bytesToRead, &flags)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    uint8_t* buffer = (uint8_t*)malloc(bytesToRead * sizeof(uint8_t));
    if (!buffer) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            free(buffer);
            buffer = NULL;
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        size_t bytesActuallyRead = 0;
        // int _stdcall icsneoUartRead(void* hObject, const EUartPort_t uart, void* bData, const size_t bytesToRead,
        // size_t* bytesActuallyRead, uint8_t* flags)
        ice::Function<int __stdcall(ICS_HANDLE, const EUartPort_t, const void*, const size_t, size_t*, uint8_t*)>
            icsneoUartRead(lib, "icsneoUartRead");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoUartRead(handle, port, (void*)buffer, bytesToRead, &bytesActuallyRead, &flags)) {
            Py_BLOCK_THREADS;
            free(buffer);
            buffer = NULL;
            return set_ics_exception(exception_runtime_error(), "icsneoUartRead() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyObject* ba_result = PyByteArray_FromStringAndSize((const char*)buffer, bytesActuallyRead);
        // PyObject* value = Py_BuildValue("O", ba_result);
        free(buffer);
        buffer = NULL;
        return ba_result;
    } catch (ice::Exception& ex) {
        free(buffer);
        buffer = NULL;
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_uart_set_baudrate(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    EUartPort_t port = eUART0;
    unsigned int baudrate = 0;
    if (!PyArg_ParseTuple(args, arg_parse("OII:", __FUNCTION__), &obj, &port, &baudrate)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // int _stdcall icsneoUartSetBaudrate(void* hObject, const EUartPort_t uart, const uint32_t baudrate)
        ice::Function<int __stdcall(ICS_HANDLE, const EUartPort_t, const uint32_t)> icsneoUartSetBaudrate(
            lib, "icsneoUartSetBaudrate");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoUartSetBaudrate(handle, port, baudrate)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoUartSetBaudrate() Failed");
        }
        Py_END_ALLOW_THREADS;
        Py_RETURN_NONE;

    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_uart_get_baudrate(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    EUartPort_t port = eUART0;
    if (!PyArg_ParseTuple(args, arg_parse("OII:", __FUNCTION__), &obj, &port)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        uint32_t baudrate = 0;
        // int _stdcall icsneoUartGetBaudrate(void* hObject, const EUartPort_t uart, uint32_t* baudrate)
        ice::Function<int __stdcall(ICS_HANDLE, const EUartPort_t, uint32_t*)> icsneoUartGetBaudrate(
            lib, "icsneoUartGetBaudrate");
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoUartGetBaudrate(handle, port, &baudrate)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoUartGetBaudrate() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("I", baudrate);

    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_generic_api_send_command(PyObject* self, PyObject* args)
{
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
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
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
            ICS_HANDLE, unsigned char, unsigned char, unsigned char, void*, unsigned int, unsigned char*)>
            icsneoGenericAPISendCommand(lib, "icsneoGenericAPISendCommand");
        unsigned char functionError = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGenericAPISendCommand(
                handle, apiIndex, instanceIndex, functionIndex, (void*)data.buf, data.len, &functionError)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGenericAPISendCommand() Failed");
        }
        Py_END_ALLOW_THREADS;
        return Py_BuildValue("i", functionError);

    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_generic_api_read_data(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned char apiIndex = 0;
    unsigned char instanceIndex = 0;
    unsigned int length = GENERIC_API_DATA_BUFFER_SIZE;
    if (!PyArg_ParseTuple(args, arg_parse("Obb|I:", __FUNCTION__), &obj, &apiIndex, &instanceIndex, &length)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    unsigned char* buffer = (unsigned char*)malloc(length * sizeof(unsigned char));
    if (!buffer) {
        return NULL;
    }
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            free(buffer);
            buffer = NULL;
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        /*
        int _stdcall icsneoGenericAPIReadData(void* hObject,
            unsigned char apiIndex,
            unsigned char instanceIndex,
            unsigned char* functionIndex,
            unsigned char* bData,
            unsigned int* length)
        */
        ice::Function<int __stdcall(
            ICS_HANDLE, unsigned char, unsigned char, unsigned char*, unsigned char*, unsigned int*)>
            icsneoGenericAPIReadData(lib, "icsneoGenericAPIReadData");
        unsigned char functionIndex = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGenericAPIReadData(handle, apiIndex, instanceIndex, &functionIndex, buffer, &length)) {
            Py_BLOCK_THREADS;
            free(buffer);
            buffer = NULL;
            return set_ics_exception(exception_runtime_error(), "icsneoGenericAPIReadData() Failed");
        }
        Py_END_ALLOW_THREADS;

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
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_generic_api_get_status(PyObject* self, PyObject* args)
{
    PyObject* obj = NULL;
    unsigned char apiIndex = 0;
    unsigned char instanceIndex = 0;

    if (!PyArg_ParseTuple(args, arg_parse("Obb:", __FUNCTION__), &obj, &apiIndex, &instanceIndex)) {
        return NULL;
    }
    // Get the device handle
    if (!PyNeoDevice_CheckExact(obj)) {
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
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
            ICS_HANDLE, unsigned char, unsigned char, unsigned char*, unsigned char*, unsigned char*)>
            icsneoGenericAPIGetStatus(lib, "icsneoGenericAPIGetStatus");
        unsigned char functionIndex = 0;
        unsigned char callbackError = 0;
        unsigned char finishedProcessing = 0;
        Py_BEGIN_ALLOW_THREADS;
        if (!icsneoGenericAPIGetStatus(
                handle, apiIndex, instanceIndex, &functionIndex, &callbackError, &finishedProcessing)) {
            Py_BLOCK_THREADS;
            return set_ics_exception(exception_runtime_error(), "icsneoGenericAPIGetStatus() Failed");
        }
        Py_END_ALLOW_THREADS;

        PyObject* value = Py_BuildValue("III", functionIndex, callbackError, finishedProcessing);
        return value;
    } catch (ice::Exception& ex) {
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

PyObject* meth_get_gptp_status(PyObject* self, PyObject* args)
{
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
    PyObject_GetBuffer(status, &status_buffer, PyBUF_C_CONTIGUOUS | PyBUF_WRITABLE);
    // Verify we have a valid NeoDevice Object - This comes after gptp_status allocation for testing purposes
    if (!PyNeoDevice_CheckExact(obj)) {
        PyBuffer_Release(&status_buffer);
        Py_DECREF(status);
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            PyBuffer_Release(&status_buffer);
            Py_DECREF(status);
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // Get the gptp_status
        Py_BEGIN_ALLOW_THREADS;
        // int _stdcall icsneoGetGPTPStatus(void* hObject, GPTPStatus* gptpStatus)
        ice::Function<int __stdcall(ICS_HANDLE, GPTPStatus*)> icsneoGetGPTPStatus(lib, "icsneoGetGPTPStatus");
        if (!icsneoGetGPTPStatus(handle, (GPTPStatus*)status_buffer.buf)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&status_buffer);
            Py_DECREF(status);
            return set_ics_exception(exception_runtime_error(), "icsneoGetGPTPStatus() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyBuffer_Release(&status_buffer);
        return status;
    } catch (ice::Exception& ex) {
        PyBuffer_Release(&status_buffer);
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}

// int _stdcall icsneoGetAllChipVersions(void* hObject, stChipVersions* pInfo, int ipInfoSize)
PyObject* meth_get_all_chip_versions(PyObject* self, PyObject* args)
{
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
    PyObject_GetBuffer(py_struct, &py_struct_buffer, PyBUF_C_CONTIGUOUS | PyBUF_WRITABLE);
    // Verify we have a valid NeoDevice Object - This comes after ctypes struct allocation for testing purposes
    if (!PyNeoDevice_CheckExact(obj)) {
        PyBuffer_Release(&py_struct_buffer);
        Py_DECREF(py_struct);
        return set_ics_exception(exception_runtime_error(),
                                 "Argument must be of type " MODULE_NAME "." NEO_DEVICE_OBJECT_NAME);
    }
    ICS_HANDLE handle = PyNeoDevice_GetHandle(obj);
    try {
        ice::Library* lib = dll_get_library();
        if (!lib) {
            PyBuffer_Release(&py_struct_buffer);
            Py_DECREF(py_struct);
            char buffer[512];
            return set_ics_exception(exception_runtime_error(), dll_get_error(buffer));
        }
        // Get the struct
        Py_BEGIN_ALLOW_THREADS;
        // int _stdcall icsneoGetAllChipVersions(void* hObject, stChipVersions* pInfo, int ipInfoSize)
        ice::Function<int __stdcall(ICS_HANDLE, stChipVersions*, int)> icsneoGetAllChipVersions(
            lib, "icsneoGetAllChipVersions");
        if (!icsneoGetAllChipVersions(handle, (stChipVersions*)py_struct_buffer.buf, py_struct_buffer.len)) {
            Py_BLOCK_THREADS;
            PyBuffer_Release(&py_struct_buffer);
            Py_DECREF(py_struct);
            return set_ics_exception(exception_runtime_error(), "icsneoGetAllChipVersions() Failed");
        }
        Py_END_ALLOW_THREADS;
        PyBuffer_Release(&py_struct_buffer);
        return py_struct;
    } catch (ice::Exception& ex) {
        PyBuffer_Release(&py_struct_buffer);
        return set_ics_exception(exception_runtime_error(), (char*)ex.what());
    }
    return set_ics_exception(exception_runtime_error(), "This is a bug!");
}
