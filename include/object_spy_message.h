#ifndef _OBJECT_SPY_MESSAGE_H_
#define _OBJECT_SPY_MESSAGE_H_
// http://docs.python.org/3/extending/newtypes.html

#include <Python.h>
#include <structmember.h>
#if (defined(_WIN32) || defined(__WIN32__))
#ifndef USING_STUDIO_8
#define USING_STUDIO_8 1
#endif
#include <icsnVC40.h>
#else
#include <icsnVC40.h>
#endif

#include <vector>

#include "defines.h"

#define SPY_MESSAGE_OBJECT_NAME "SpyMessage"
#define SPY_MESSAGE_J1850_OBJECT_NAME "SpyMessageJ1850"

#if PY_MAJOR_VERSION < 3
#define PyUnicode_CompareWithASCIIString(uni, string) strcmp(PyString_AsString(uni), string)
/*
int PyUnicode_CompareWithASCIIString(PyObject *uni, const char *string)
{
    int result = strcmp(PyString_AsString(uni), string);
    if (result == 0) {
        return 0;
    }
    return result > 0 ? 1 : -1;
}
*/
#endif

#pragma pack(push, 1)
typedef struct
{
    PyObject_HEAD icsSpyMessage msg;
    bool noExtraDataPtrCleanup;
} spy_message_object;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    PyObject_HEAD icsSpyMessageJ1850 msg;
    bool noExtraDataPtrCleanup;
} spy_message_j1850_object;
#pragma pack(pop)


extern PyTypeObject spy_message_object_type;
extern PyTypeObject spy_message_j1850_object_type;

// Copied from tupleobject.h
#define PySpyMessage_Check(op) PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PySpyMessage_CheckExact(op) (Py_TYPE(op) == &spy_message_object_type)
#define PySpyMessageJ1850_CheckExact(op) (Py_TYPE(op) == &spy_message_j1850_object_type)

#define PySpyMessage_GetObject(obj) ((spy_message_object*)obj)
#define PySpyMessageJ1850_GetObject(obj) ((spy_message_j1850_object*)obj)

bool setup_spy_message_object(PyObject* module);

#endif // _OBJECT_SPY_MESSAGE_H_
