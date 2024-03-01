#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include <Python.h>

#ifdef _cplusplus
extern "C"
{
#endif

    int initialize_exceptions(PyObject* module);
    PyObject* _set_ics_exception(PyObject* exception, char* msg, const char* func_name);
#define set_ics_exception(exception, msg) _set_ics_exception(exception, msg, __FUNCTION__);

    PyObject* exception_argument_error(void);
    PyObject* exception_runtime_error(void);

#ifdef _cplusplus
}
#endif // extern "C" {

#endif // _EXCEPTIONS_H_
