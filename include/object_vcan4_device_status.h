#ifndef _OBJECT_VCAN4_DEVICE_STATUS_H_
#define _OBJECT_VCAN4_DEVICE_STATUS_H_

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

#if (VSPY3_BUILD_VERSION > 802)

#define VCAN4_DEVICE_STATUS_OBJECT_NAME "Vcan4DeviceStatus"

#if PY_MAJOR_VERSION < 3
#define PyUnicode_CompareWithASCIIString(uni, string) strcmp(PyString_AsString(uni), string)
#endif


typedef struct {
    PyObject_HEAD
    icsVcan4DeviceStatus s;
} vcan4_device_status_object;

#if 0
typedef union {
	icsVcan4DeviceStatus fire2Status;
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
} icsVcan4DeviceStatus;

#endif
static PyMemberDef vcan4_device_status_object_members[] = {
    { "ethernetActivationLineEnabled", T_UBYTE, offsetof(vcan4_device_status_object, s.ethernetActivationLineEnabled), 0, "" },
    { NULL, 0, 0, 0, 0 },
};

static int vcan4_device_status_object_init(vcan4_device_status_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));

    return 0;
}

static PyObject* vcan4_device_status_object_getattr(PyObject *o, PyObject *attr_name)
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
    vcan4_device_status_object* obj = (vcan4_device_status_object*)o;
    if (PyUnicode_CompareWithASCIIString(attr_name, "ethernetActivationLineEnabled") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("i", obj->s.ethernetActivationLineEnabled);
    }
    else {
        return PyObject_GenericGetAttr(o, attr_name);
    }

    return PyObject_GenericGetAttr(o, attr_name);
}

static int vcan4_device_status_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    vcan4_device_status_object* obj = (vcan4_device_status_object*)o;
    return PyObject_GenericSetAttr(o, name, value);
}



extern PyTypeObject vcan4_device_status_object_type;


// Copied from tupleobject.h
#define PyVcan4DeviceStatus_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyVcan4DeviceStatus_CheckExact(op) (Py_TYPE(op) == &vcan4_device_status_object_type)

#endif // (VSPY3_BUILD_VERSION > 802)

bool setup_vcan4_device_status_object(PyObject* module);


#endif // _OBJECT_VCAN4_DEVICE_STATUS_H_
