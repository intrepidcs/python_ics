#ifndef _DEFINES_H_
#define _DEFINES_H_
#include <Python.h>

#define MODULE_NAME "ics.ics"
#define MODULE_DESCRIPTION "Copyright Intrepid Control Systems, Inc."
#define VSPY3_BUILD_VERSION 901

// https://bugs.python.org/issue28769
// 2.x     = char* PyString_AsString(return_value);
// 3.0-3.6 = char* PyUnicode_AsUTF8(value);
// 3.7     = const char* PyUnicode_AsUTF8(value);
#if (PY_MAJOR_VERSION >= 3) && (PY_MINOR_VERSION >= 7)
#define PyUniStr_AsStrOrUTF8(obj) (char*)PyUnicode_AsUTF8(obj)
#elif (PY_MAJOR_VERSION >= 3)
#define PyUniStr_AsStrOrUTF8(obj) PyUnicode_AsUTF8(obj)
#elif (PY_MAJOR_VERSION == 2)
#define PyUniStr_AsStrOrUTF8(obj) PyString_AsString(obj)
#else
#error Failed to suppport PyUnicode_AsUTF8
#endif

#ifdef _cplusplus
extern "C"
{
#endif

    int setup_module_defines(PyObject* module);

#ifdef _cplusplus
}
#endif // extern "C" {

#endif