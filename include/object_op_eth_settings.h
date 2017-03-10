#ifndef _OBJECT_OP_ETH_SETTINGS_H_
#define _OBJECT_OP_ETH_SETTINGS_H_

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

#include "defines.h"

#define OP_ETH_SETTINGS_OBJECT_NAME "OpEthSettings"

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

typedef struct {
    PyObject_HEAD
    OP_ETH_SETTINGS s;
} op_eth_settings_object;

static PyMemberDef op_eth_settings_object_members[] = {
    { "ucConfigMode", T_UBYTE, offsetof(op_eth_settings_object, s.ucConfigMode), 0, ""},
    { "preemption_en", T_UBYTE, offsetof(op_eth_settings_object, s.preemption_en), 0, ""},
    { "reserved0", T_OBJECT_EX, NULL, 0, ""},
    { NULL, 0, 0, 0, 0 },
};

static int op_eth_settings_object_init(op_eth_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

static PyObject* op_eth_settings_object_getattr(PyObject *o, PyObject *attr_name)
{
#if PY_MAJOR_VERSION >= 3
    if (!PyUnicode_Check(attr_name)) {
#else
    if (!PyString_Check(attr_name)) {
#endif
        PyErr_Format(PyExc_TypeError,
                    "attribute name must be string, not '%.200s'",
                    attr_name->ob_type->tp_name);
        return NULL;
    }
    else {
        Py_INCREF(attr_name);
    }
    if (PyUnicode_CompareWithASCIIString(attr_name, "reserved0") == 0) {
        Py_DECREF(attr_name);
        op_eth_settings_object* obj = (op_eth_settings_object*)o;
        PyObject* temp = Py_BuildValue("(i,i,i,i,i,i,i,i,i,i,i,i,i,i)",
            obj->s.reserved0[0],
            obj->s.reserved0[1],
            obj->s.reserved0[2],
            obj->s.reserved0[3],
            obj->s.reserved0[4],
            obj->s.reserved0[5],
            obj->s.reserved0[6],
            obj->s.reserved0[7],
            obj->s.reserved0[8],
            obj->s.reserved0[9],
            obj->s.reserved0[10],
            obj->s.reserved0[11],
            obj->s.reserved0[12],
            obj->s.reserved0[13]);
        PyObject* data = PyTuple_GetSlice(temp, 0, 14);
        Py_DECREF(temp);
        return data;
    }
    else {
        return PyObject_GenericGetAttr(o, attr_name);
    }
}

static int op_eth_settings_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    op_eth_settings_object* obj = (op_eth_settings_object*)o;
    if (PyUnicode_CompareWithASCIIString(name, "reserved0") == 0) {
        // Make sure we are a tuple and len() == 8
        if (!PyTuple_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a tuple",
                MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        // Get tuple items and place them in array, set as 0 if error.
        for (int i=0; i < 15 && i < PyObject_Length(value); ++i) {
            PyObject* data = PyTuple_GetItem(value, i);
            if (!data && !PyLong_Check(data)) {
                obj->s.reserved0[i] = 0;
            } else {
                obj->s.reserved0[i] = (unsigned char)PyLong_AsLong(data);
            }
        }
        return 0;
    }
    else {
        return PyObject_GenericSetAttr(o, name, value);
    }
}

extern PyTypeObject op_eth_settings_object_type;

// Copied from tupleobject.h
#define PyOpEthSettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyOpEthSettings_CheckExact(op) (Py_TYPE(op) == &op_eth_settings_object_type)

bool setup_op_eth_settings_object(PyObject* module);

#endif // _OBJECT_OP_ETH_SETTINGS_H_