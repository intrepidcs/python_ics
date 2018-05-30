#ifndef _OBJECT_FIRE2_DEVICE_STATUS_H_
#define _OBJECT_FIRE2_DEVICE_STATUS_H_

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
#include "object_can_settings.h"
#include "object_canfd_settings.h"
#include "object_textapi_settings.h"

#define FIRE2_DEVICE_STATUS_OBJECT_NAME "Fire2DeviceStatus"

#if PY_MAJOR_VERSION < 3
#define PyUnicode_CompareWithASCIIString(uni, string) strcmp(PyString_AsString(uni), string)
#endif


typedef struct {
    PyObject_HEAD
    icsFire2DeviceStatus s;
} fire2_device_status_object;

#if 0
typedef union {
	icsFire2DeviceStatus fire2Status;
	icsVcan4DeviceStatus vcan4Status;
} icsDeviceStatus;

typedef struct
{
	uint8_t ethernetActivationLineEnabled;
} icsVcan4DeviceStatus;

typedef struct
{
	uint8_t backupPowerGood;
	uint8_t backupPowerEnabled;
	uint8_t usbHostPowerEnabled;
	uint8_t ethernetActivationLineEnabled;
} icsFire2DeviceStatus;

#endif
static PyMemberDef fire2_device_status_object_members[] = {
    { "backupPowerGood", T_UBYTE, offsetof(fire2_device_status_object, s.backupPowerGood), 0, "" },

    { "backupPowerEnabled", T_UBYTE, offsetof(fire2_device_status_object, s.backupPowerEnabled), 0, "" },
    { "usbHostPowerEnabled", T_UBYTE, offsetof(fire2_device_status_object, s.usbHostPowerEnabled), 0, "" },

    { "ethernetActivationLineEnabled", T_UBYTE, offsetof(fire2_device_status_object, s.ethernetActivationLineEnabled), 0, "" },
    { NULL, 0, 0, 0, 0 },
};

static int fire2_device_status_object_init(fire2_device_status_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));

    return 0;
}

static PyObject* fire2_device_status_object_getattr(PyObject *o, PyObject *attr_name)
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
    fire2_device_status_object* obj = (fire2_device_status_object*)o;
    if (PyUnicode_CompareWithASCIIString(attr_name, "backupPowerGood") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("i", obj->s.backupPowerGood);
    }
    else if (PyUnicode_CompareWithASCIIString(attr_name, "backupPowerEnabled") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("i", obj->s.backupPowerEnabled);
    }
    else if (PyUnicode_CompareWithASCIIString(attr_name, "usbHostPowerEnabled") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("i", obj->s.usbHostPowerEnabled);
    }
    else if (PyUnicode_CompareWithASCIIString(attr_name, "ethernetActivationLineEnabled") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("i", obj->s.ethernetActivationLineEnabled);
    }
    else {
        return PyObject_GenericGetAttr(o, attr_name);
    }
}

static int fire2_device_status_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    fire2_device_status_object* obj = (fire2_device_status_object*)o;
    return PyObject_GenericSetAttr(o, name, value);
}



extern PyTypeObject fire2_device_status_object_type;


// Copied from tupleobject.h
#define PyFire2DeviceStatus_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyFire2DeviceStatus_CheckExact(op) (Py_TYPE(op) == &fire2_device_status_object_type)

bool setup_fire2_device_status_object(PyObject* module);

#endif // _OBJECT_FIRE2_DEVICE_STATUS_H_
