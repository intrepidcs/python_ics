#ifndef _OBJECT_VIVIDCAN_SETTINGS_H_
#define _OBJECT_VIVIDCAN_SETTINGS_H_

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

#define VIVIDCAN_SETTINGS_OBJECT_NAME "VividCANSettings"

#if PY_MAJOR_VERSION < 3
#define PyUnicode_CompareWithASCIIString(uni, string) strcmp(PyString_AsString(uni), string)
#endif

typedef struct {
    PyObject_HEAD
    PyObject* can1;
	PyObject* swcan1;
	PyObject* lsftcan1;
    SVividCANSettings s;
} vividcan_settings_object;

#if 0
	uint32_t ecu_id;

	CAN_SETTINGS can1;// 12 bytes
	SWCAN_SETTINGS swcan1;// 14 bytes
	CAN_SETTINGS lsftcan1;// 12 bytes

	uint16_t network_enables;
	uint16_t network_enabled_on_boot;

	uint16_t iso15765_separation_time_offset;

	uint16_t perf_en;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t can_switch_mode;
	uint16_t termination_enables;

	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t reserved : 30;
	} flags;
#endif
static PyMemberDef vividcan_settings_object_members[] = {
	{ "ecu_id", T_UINT, offsetof(vividcan_settings_object, s.ecu_id), 0, "" },

	{ "can1", T_OBJECT_EX, offsetof(vividcan_settings_object, can1), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
	{ "swcan1", T_OBJECT_EX, offsetof(vividcan_settings_object, swcan1), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
	{ "lsftcan1", T_OBJECT_EX, offsetof(vividcan_settings_object, lsftcan1), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },

	{ "network_enables", T_USHORT, offsetof(vividcan_settings_object, s.network_enables), 0, "" },
	{ "network_enabled_on_boot", T_USHORT, offsetof(vividcan_settings_object, s.network_enabled_on_boot), 0, "" },

	{ "iso15765_separation_time_offset", T_USHORT, offsetof(vividcan_settings_object, s.iso15765_separation_time_offset), 0, "" },

    { "perf_en", T_USHORT, offsetof(vividcan_settings_object, s.perf_en), 0, "" },

    { "pwr_man_timeout", T_UINT, offsetof(vividcan_settings_object, s.pwr_man_timeout), 0, "" },
    { "pwr_man_enable", T_USHORT, offsetof(vividcan_settings_object, s.pwr_man_enable), 0, "" },

    { "can_switch_mode", T_USHORT, offsetof(vividcan_settings_object, s.can_switch_mode), 0, "" },
    { "termination_enables", T_USHORT, offsetof(vividcan_settings_object, s.termination_enables), 0, "" },

    { "disableUsbCheckOnBoot", T_OBJECT_EX, NULL, 0, "flags"},
    { "enableLatencyTest", T_OBJECT_EX, NULL, 0, "flags"},
    { "reserved", T_OBJECT_EX, NULL, 0, "flags"},
    { NULL, 0, 0, 0, 0 },
};

static int vividcan_settings_object_init(vividcan_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));

    self->can1 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->swcan1 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->lsftcan1 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);

    return 0;
}

static PyObject* vividcan_settings_object_getattr(PyObject *o, PyObject *attr_name)
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
    vividcan_settings_object* obj = (vividcan_settings_object*)o;
    if (PyUnicode_CompareWithASCIIString(attr_name, "disableUsbCheckOnBoot") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("b", obj->s.flags.disableUsbCheckOnBoot);
    }
    else if (PyUnicode_CompareWithASCIIString(attr_name, "enableLatencyTest") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("b", obj->s.flags.enableLatencyTest);
    }
    else if (PyUnicode_CompareWithASCIIString(attr_name, "reserved") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("i", obj->s.flags.reserved);
    }
    else {
        return PyObject_GenericGetAttr(o, attr_name);
    }
}

static int vividcan_settings_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    vividcan_settings_object* obj = (vividcan_settings_object*)o;
    if (PyUnicode_CompareWithASCIIString(name, "disableUsbCheckOnBoot") == 0) {
        if (!PyBool_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a boolean",
                MODULE_NAME "." VIVIDCAN_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        obj->s.flags.disableUsbCheckOnBoot = PyLong_AsLong(value);
        return 0;
    }
    else if (PyUnicode_CompareWithASCIIString(name, "enableLatencyTest") == 0) {
        if (!PyBool_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a boolean",
                MODULE_NAME "." VIVIDCAN_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        obj->s.flags.enableLatencyTest = PyLong_AsLong(value);
        return 0;
    }
    else if (PyUnicode_CompareWithASCIIString(name, "reserved") == 0) {
        if (!PyLong_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be an integer",
                MODULE_NAME "." VIVIDCAN_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        obj->s.flags.reserved = PyLong_AsLong(value);
        return 0;
    }
    else {
        return PyObject_GenericSetAttr(o, name, value);
    }
}



extern PyTypeObject vividcan_settings_object_type;


// Copied from tupleobject.h
#define PyVividCANSettings_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyVividCANSettings_CheckExact(op) (Py_TYPE(op) == &vividcan_settings_object_type)

bool setup_vividcan_settings_object(PyObject* module);

#endif // _OBJECT_VIVIDCAN_SETTINGS_H_
