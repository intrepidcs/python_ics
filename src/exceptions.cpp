#include "exceptions.h"
#include "defines.h"
#include <sstream>

#include "object_neo_device.h"

static PyObject* IcsArgumentError = NULL;
static PyObject* IcsRuntimeError = NULL;

char *pyics_base36enc(int sn)
{
    char *result = NULL;
#if PY_MAJOR_VERSION >= 3
    PyObject *name = PyUnicode_FromString("ics.ics");
#else
    PyObject *name = PyString_FromString("ics.ics");
#endif
    PyObject *module = PyImport_Import(name);
    PyObject *dict = PyModule_GetDict(module);
    PyObject *base36enc = PyDict_GetItemString(dict, "base36enc");
    if (PyCallable_Check(base36enc)) {
        PyObject *return_value = PyObject_CallFunction(base36enc, "i", sn);
        if (return_value == NULL) {
            // We failed for some reason...
            PyErr_Print();
            Py_DECREF(module);
            Py_DECREF(name);
            return NULL;
        } else {
            return PyUniStr_AsStrOrUTF8(return_value);
        }
    }
    Py_DECREF(module);
    Py_DECREF(name);
    return "";
}

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
        char* name = PyUniStr_AsStrOrUTF8(PyNeoDevice_GetNeoDevice(obj)->name);
        if (name) {
            ss << name << " ";
        }
        char* b36sn = pyics_base36enc(PyNeoDevice_GetSerialNumber(obj));
        ss << PyNeoDevice_GetSerialNumber(obj);
        if (b36sn != NULL && PyNeoDevice_GetSerialNumber(obj) >= 604661760 /* "A0000" */) {
            ss << " - " << b36sn << ")";
        } else {
            ss << ")";
        }
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
