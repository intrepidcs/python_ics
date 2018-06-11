#ifndef _DEFINES_H_
#define _DEFINES_H_
#include <Python.h>

#define MODULE_NAME "ics"
#define MODULE_DESCRIPTION "Copyright Intrepid Control Systems, Inc."
#define VSPY3_BUILD_VERSION 802

// Enable use of generic device settings object in 803 or newer.
#if !defined(USE_GENERIC_DEVICE_SETTINGS) && (VSPY3_BUILD_VERSION >= 803)
#define USE_GENERIC_DEVICE_SETTINGS
#endif

#ifdef _cplusplus
extern "C" {
#endif

int setup_module_defines(PyObject* module);

#ifdef _cplusplus
}
#endif // extern "C" {

#endif