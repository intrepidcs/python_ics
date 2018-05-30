#ifndef _OBJECT_ICS_DEVICE_STATUS_H_
#define _OBJECT_ICS_DEVICE_STATUS_H_

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
#include "object_fire2_device_status.h"
#include "object_vcan4_device_status.h"

#define ICS_DEVICE_STATUS_OBJECT_NAME "IcsDeviceStatus"

#if PY_MAJOR_VERSION < 3
#define PyUnicode_CompareWithASCIIString(uni, string) strcmp(PyString_AsString(uni), string)
#endif


typedef struct {
    PyObject_HEAD
    PyObject* fire2_status;
#if  (VSPY3_BUILD_VERSION > 802)
    PyObject* vcan4_status;
#endif  // (VSPY3_BUILD_VERSION > 802)
    icsDeviceStatus s;
} ics_device_status_object;

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
static PyMemberDef ics_device_status_object_members[] = {

    { "fire2Status", T_OBJECT_EX, offsetof(ics_device_status_object, fire2_status), 0, MODULE_NAME "." FIRE2_DEVICE_STATUS_OBJECT_NAME" Object" },
#if  (VSPY3_BUILD_VERSION > 802)
    { "vcan4Status", T_OBJECT_EX, offsetof(ics_device_status_object, vcan4_status), 0, MODULE_NAME "." VCAN4_DEVICE_STATUS_OBJECT_NAME" Object" },
#endif  // (VSPY3_BUILD_VERSION > 802)

    { NULL, 0, 0, 0, 0 },
};

static int ics_device_status_object_init(ics_device_status_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));

    self->fire2_status = PyObject_CallObject((PyObject*)&fire2_device_status_object_type, NULL);
#if (VSPY3_BUILD_VERSION > 802)
    self->vcan4_status = PyObject_CallObject((PyObject*)&vcan4_device_status_object_type, NULL);
#endif  // (VSPY3_BUILD_VERSION > 802)

    return 0;
}

static PyObject* ics_device_status_object_getattr(PyObject *o, PyObject *attr_name)
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

static int ics_device_status_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    return PyObject_GenericSetAttr(o, name, value);
}



extern PyTypeObject ics_device_status_object_type;


// Copied from tupleobject.h
#define PyIcsDeviceStatus_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyIcsDeviceStatus_CheckExact(op) (Py_TYPE(op) == &ics_device_status_object_type)

bool setup_ics_device_status_object(PyObject* module);

#endif // _OBJECT_ICS_DEVICE_STATUS_H_
