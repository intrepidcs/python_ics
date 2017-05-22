#ifndef _OBJECT_ETHERNET_SETTINGS_H_
#define _OBJECT_ETHERNET_SETTINGS_H_

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

#define ETHERNET_SETTINGS_OBJECT_NAME "EthernetSettings"

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
    ETHERNET_SETTINGS s;
} ethernet_settings_object;

static PyMemberDef ethernet_settings_object_members[] = {
    { "duplex", T_UBYTE, offsetof(ethernet_settings_object, s.duplex), 0, ""},
    { "link_speed", T_UBYTE, offsetof(ethernet_settings_object, s.link_speed), 0, ""},
    { "auto_neg", T_UBYTE, offsetof(ethernet_settings_object, s.auto_neg), 0, ""},
    { "led_mode", T_UBYTE, offsetof(ethernet_settings_object, s.led_mode), 0, ""},
    { "rsvd", T_OBJECT_EX, offsetof(ethernet_settings_object, s.rsvd), 0, ""},
    { NULL, 0, 0, 0, 0 },
};

static int ethernet_settings_object_init(ethernet_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

static PyObject* ethernet_settings_object_getattr(PyObject *o, PyObject *attr_name)
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
    if (PyUnicode_CompareWithASCIIString(attr_name, "rsvd") == 0) {
        Py_DECREF(attr_name);
        ethernet_settings_object* obj = (ethernet_settings_object*)o;
        PyObject* temp = Py_BuildValue("(i,i,i,i)",
            obj->s.rsvd[0],
            obj->s.rsvd[1],
            obj->s.rsvd[2],
            obj->s.rsvd[3]);
        PyObject* data = PyTuple_GetSlice(temp, 0, 4);
        Py_DECREF(temp);
        return data;
    }
    else {
        return PyObject_GenericGetAttr(o, attr_name);
    }
}

static int ethernet_settings_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    ethernet_settings_object* obj = (ethernet_settings_object*)o;
    if (PyUnicode_CompareWithASCIIString(name, "rsvd") == 0) {
        // Make sure we are a tuple and len() == 8
        if (!PyTuple_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a tuple",
                MODULE_NAME "." ETHERNET_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        // Get tuple items and place them in array, set as 0 if error.
        for (int i=0; i < 4 && i < PyObject_Length(value); ++i) {
            PyObject* data = PyTuple_GetItem(value, i);
            if (!data && !PyLong_Check(data)) {
                obj->s.rsvd[i] = 0;
            } else {
                obj->s.rsvd[i] = (unsigned char)PyLong_AsLong(data);
            }
        }
        return 0;
    }
    else {
        return PyObject_GenericSetAttr(o, name, value);
    }
}

extern PyTypeObject ethernet_settings_object_type;

// Copied from tupleobject.h
#define PyEthernetSettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyEthernetSettings_CheckExact(op) (Py_TYPE(op) == &ethernet_settings_object_type)

bool setup_ethernet_settings_object(PyObject* module);

#endif // _OBJECT_ETHERNET_SETTINGS_H_