#ifndef _OBJECT_SWCAN_SETTINGS_H_
#define _OBJECT_SWCAN_SETTINGS_H_

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

#define SWCAN_SETTINGS_OBJECT_NAME "SWCanSettings"


typedef struct {
    PyObject_HEAD
    SWCAN_SETTINGS s;
} swcan_settings_object;

static PyMemberDef swcan_settings_object_members[] = {
    { "Mode", T_UBYTE, offsetof(swcan_settings_object, s.Mode), 0, "CAN controller mode when the neoVI device goes online or runs a CoreMini script.\n\tNormal=0\n\tDisabled=1\n\tListen Only=3\n\tListen All=7\n" },
    { "SetBaudrate", T_UBYTE, offsetof(swcan_settings_object, s.SetBaudrate), 0, "The bit rate of a CAN channel can be selected one of two ways. It can either be selected from a list of common bit rates (SetBaudrate=1) or the user can specify the CAN timing parameters (SetBaudrate=0) " },
    { "Baudrate", T_UBYTE, offsetof(swcan_settings_object, s.Baudrate), 0, "The bit rate of a CAN channel can be selected from a list of common bit rates Write the correct enumeration for the desired bit rate and ensure that SetBaudrate is 1(auto)" },
    { "transceiver_mode", T_UBYTE, offsetof(swcan_settings_object, s.transceiver_mode), 0, "Currently Not used." },
    { "TqSeg1", T_UBYTE, offsetof(swcan_settings_object, s.TqSeg1), 0, "Phase 1 segment" },
    { "TqSeg2", T_UBYTE, offsetof(swcan_settings_object, s.TqSeg2), 0, "Phase 2 segment" },
    { "TqProp", T_UBYTE, offsetof(swcan_settings_object, s.TqProp), 0, "Propagation delay" },
    { "TqSync", T_UBYTE, offsetof(swcan_settings_object, s.TqSync), 0, "Syncro jump width" },
    { "BRP", T_USHORT, offsetof(swcan_settings_object, s.BRP), 0, "" },
    { "high_speed_auto_switch", T_USHORT, offsetof(swcan_settings_object, s.high_speed_auto_switch), 0, "" },
    { "auto_baud", T_USHORT, offsetof(swcan_settings_object, s.auto_baud), 0, "Enables the auto bitrate feature. 1 = enable, 0 = disable." },
    { "RESERVED", T_UBYTE, offsetof(swcan_settings_object, s.RESERVED), 0, "RESERVED" },
    { NULL, 0, 0, 0, 0 },
};

static PyObject* swcan_settings_object_getattr(swcan_settings_object* obj, char* name)
{
    if (strcmp(name, "Mode") == 0) {
        return PyLong_FromLong(obj->s.Mode);
    }
    if (strcmp(name, "SetBaudrate") == 0) {
        return PyLong_FromLong(obj->s.SetBaudrate);
    }
    if (strcmp(name, "Baudrate") == 0) {
        return PyLong_FromLong(obj->s.Baudrate);
    }
    if (strcmp(name, "transceiver_mode") == 0) {
        return PyLong_FromLong(obj->s.transceiver_mode);
    }
    if (strcmp(name, "TqSeg1") == 0) {
        return PyLong_FromLong(obj->s.TqSeg1);
    }
    if (strcmp(name, "TqSeg2") == 0) {
        return PyLong_FromLong(obj->s.TqSeg2);
    }
    if (strcmp(name, "TqProp") == 0) {
        return PyLong_FromLong(obj->s.TqProp);
    }
    if (strcmp(name, "TqSync") == 0) {
        return PyLong_FromLong(obj->s.TqSync);
    }
    if (strcmp(name, "BRP") == 0) {
        return PyLong_FromLong(obj->s.BRP);
    }
    if (strcmp(name, "high_speed_auto_switch") == 0) {
        return PyLong_FromLong(obj->s.high_speed_auto_switch);
    }
    if (strcmp(name, "auto_baud") == 0) {
        return PyLong_FromLong(obj->s.auto_baud);
    }
    if (strcmp(name, "RESERVED") == 0) {
        return PyLong_FromLong(obj->s.RESERVED);
    }
    PyErr_Format(PyExc_AttributeError,
        "'%.50s' object has no attribute '%.400s'",
        MODULE_NAME "." SWCAN_SETTINGS_OBJECT_NAME, name);
    return NULL;
}

static int swcan_settings_object_setattr(swcan_settings_object* obj, char* name, PyObject* v)
{
    if (!v) {
        return 0;
    }
    unsigned long value = 0;
    if (PyLong_Check(v)) {
        // We have some values that are not compatible with int type.
        value = (unsigned long)PyLong_AsLong(v);
    }
    if (strcmp(name, "Mode") == 0) {
        obj->s.Mode = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "SetBaudrate") == 0) {
        obj->s.SetBaudrate = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "Baudrate") == 0) {
        obj->s.Baudrate = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "transceiver_mode") == 0) {
        obj->s.transceiver_mode = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "TqSeg1") == 0) {
        obj->s.TqSeg1 = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "TqSeg2") == 0) {
        obj->s.TqSeg2 = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "TqProp") == 0) {
        obj->s.TqProp = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "TqSync") == 0) {
        obj->s.TqSync = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "BRP") == 0) {
        obj->s.BRP = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "auto_baud") == 0) {
        obj->s.auto_baud = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "high_speed_auto_switch") == 0) {
        obj->s.high_speed_auto_switch = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "RESERVED") == 0) {
        obj->s.RESERVED = (unsigned char)value;
        return 0;
    }

    PyErr_Format(PyExc_AttributeError,
        "'%.50s' object has no attribute '%.400s'",
        MODULE_NAME "." SWCAN_SETTINGS_OBJECT_NAME, name);
    return -1;
}

static int swcan_settings_object_init(swcan_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

extern PyTypeObject swcan_settings_object_type;

// Copied from tupleobject.h
#define PySwCanSettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PySwCanSettings_CheckExact(op) (Py_TYPE(op) == &swcan_settings_object_type)

bool setup_swcan_settings_object(PyObject* module);

#endif // _OBJECT_SWCAN_SETTINGS_H_
