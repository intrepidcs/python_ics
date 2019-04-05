#ifndef _OBJECT_TIMESYNC_SETTINGS_H_
#define _OBJECT_TIMESYNC_SETTINGS_H_

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

#define TIMESYNC_SETTINGS_OBJECT_NAME "TimesyncSettings"

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
    TIMESYNC_ICSHARDWARE_SETTINGS s;
} timesync_settings_object;

static PyMemberDef timesync_settings_object_members[] = {
    { "MasterEnable", T_UBYTE, offsetof(timesync_settings_object, s.MasterEnable), 0, ""},
    { "SlaveEnable", T_UBYTE, offsetof(timesync_settings_object, s.SlaveEnable), 0, ""},
    { "MasterNetwork", T_UBYTE, offsetof(timesync_settings_object, s.MasterNetwork), 0, ""},
    { "SlaveNetwork", T_UBYTE, offsetof(timesync_settings_object, s.SlaveNetwork), 0, ""},
    { NULL, 0, 0, 0, 0 },
};

static int timesync_settings_object_init(timesync_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

static PyObject* timesync_settings_object_getattr(PyObject *o, PyObject *attr_name)
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
    return PyObject_GenericGetAttr(o, attr_name);
}

static int timesync_settings_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    timesync_settings_object* obj = (timesync_settings_object*)o;
    return PyObject_GenericSetAttr(o, name, value);
}

extern PyTypeObject timesync_settings_object_type;

// Copied from tupleobject.h
#define PyTimesyncSettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyTimesyncSettings_CheckExact(op) (Py_TYPE(op) == &timesync_settings_object_type)

bool setup_timesync_settings_object(PyObject* module);

#endif // _OBJECT_TIMESYNC_SETTINGS_H_