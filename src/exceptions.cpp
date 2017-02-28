#include "exceptions.h"
#include "defines.h"
#include <sstream>

#include "object_neo_device.h"

static PyObject* IcsArgumentError = NULL;
static PyObject* IcsRuntimeError = NULL;

int initialize_exceptions(PyObject* module)
{
    if (!module && IcsArgumentError && IcsRuntimeError) {
        return 0;
    }
    // ArgumentError
    IcsArgumentError = PyErr_NewException(MODULE_NAME ".ArgumentError", NULL, NULL);
    if (!IcsArgumentError) {
        return 0;
    }
    Py_INCREF(IcsArgumentError);
    PyModule_AddObject(module, "ArgumentError", IcsArgumentError);
    // RuntimeError
    IcsRuntimeError = PyErr_NewException(MODULE_NAME ".RuntimeError", NULL, NULL);
    if (!IcsRuntimeError) {
        return 0;
    }
    Py_INCREF(IcsRuntimeError);
    PyModule_AddObject(module, "RuntimeError", IcsRuntimeError);
    return 1;
}

PyObject* _set_ics_exception(PyObject* exception, char* msg, const char* func_name)
{
    std::stringstream ss;
    std::string function = std::string(func_name);
    int loc = function.find("meth_");
    if (loc != std::string::npos) {
        function.erase(loc, 5);
    }
    ss << "Error: " << function << "(): " << msg;
    if (!exception) {
        PyErr_SetString(PyExc_Exception, ss.str().c_str());
    } else {
        PyErr_SetString(exception, ss.str().c_str());
    }
    return NULL;
}

PyObject* _set_ics_exception_dev(PyObject* exception, PyObject* obj, char* msg, const char* func_name)
{
    std::stringstream ss;
    std::string function = std::string(func_name);
    int loc = function.find("meth_");
    if (loc != std::string::npos) {
        function.erase(loc, 5);
    }
    ss << "Error: " << function << "(): " << msg;
    if (obj && PyNeoDevice_CheckExact(obj)) {
        ss << " (";
        // Grab the String "name" out of the NeoDeviceObject
#if PY_MAJOR_VERSION >= 3
        char* name = PyUnicode_AsUTF8(PyNeoDevice_GetNeoDevice(obj)->name);
#else
        char* name = PyString_AsString(PyNeoDevice_GetNeoDevice(obj)->name);
#endif
        if (name) {
            ss << name << " ";
        }
        ss << PyNeoDevice_GetSerialNumber(obj) << ")";
    }
    if (!exception) {
        PyErr_SetString(PyExc_Exception, ss.str().c_str());
    } else {
        PyErr_SetString(exception, ss.str().c_str());
    }
    return NULL;
}

PyObject* exception_argument_error(void)
{
    return IcsArgumentError;
}

PyObject* exception_runtime_error(void)
{
    return IcsRuntimeError;
}
