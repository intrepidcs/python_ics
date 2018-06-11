#ifndef _OBJECT_VCAN412_SETTINGS_H_
#define _OBJECT_VCAN412_SETTINGS_H_

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

#define VCAN412_SETTINGS_OBJECT_NAME "Vcan412Settings"

#if PY_MAJOR_VERSION < 3
#define PyUnicode_CompareWithASCIIString(uni, string) strcmp(PyString_AsString(uni), string)
#endif


typedef struct {
    PyObject_HEAD
    PyObject* can1;
    PyObject* can2;
    PyObject* canfd1;
    PyObject* canfd2;
    PyObject* textapi;
    SVCAN412Settings s;
} vcan412_settings_object;

#if 0
	/* Performance Test */
	uint16_t perf_en;

	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;

	uint64_t network_enables;
	uint64_t termination_enables;

	uint32_t pwr_man_timeout;
	uint16_t pwr_man_enable;

	uint16_t network_enabled_on_boot;

	/* ISO15765-2 Transport Layer */
	int16_t iso15765_separation_time_offset;

	STextAPISettings text_api;
	struct
	{
		uint32_t disableUsbCheckOnBoot : 1;
		uint32_t enableLatencyTest : 1;
		uint32_t reserved : 30;
	} flags;
#endif
static PyMemberDef vcan412_settings_object_members[] = {
    { "perf_en", T_USHORT, offsetof(vcan412_settings_object, s.perf_en), 0, "" },

    { "can1", T_OBJECT_EX, offsetof(vcan412_settings_object, can1), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can2", T_OBJECT_EX, offsetof(vcan412_settings_object, can2), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },

    { "canfd1", T_OBJECT_EX, offsetof(vcan412_settings_object, canfd1), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd2", T_OBJECT_EX, offsetof(vcan412_settings_object, canfd2), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },

    { "network_enables", T_ULONGLONG, offsetof(vcan412_settings_object, s.network_enables), 0, "" },
    { "termination_enables", T_ULONGLONG, offsetof(vcan412_settings_object, s.termination_enables), 0, "" },

    { "pwr_man_timeout", T_UINT, offsetof(vcan412_settings_object, s.pwr_man_timeout), 0, "" },
    { "pwr_man_enable", T_USHORT, offsetof(vcan412_settings_object, s.pwr_man_enable), 0, "" },

    { "network_enabled_on_boot", T_USHORT, offsetof(vcan412_settings_object, s.network_enabled_on_boot), 0, "" },

    { "iso15765_separation_time_offset", T_USHORT, offsetof(vcan412_settings_object, s.iso15765_separation_time_offset), 0, "" },

    { "text_api", T_OBJECT_EX, offsetof(vcan412_settings_object, textapi), 0, MODULE_NAME "." TEXTAPI_SETTINGS_OBJECT_NAME" Object" },

    { "disableUsbCheckOnBoot", T_OBJECT_EX, NULL, 0, "flags"},
    { "enableLatencyTest", T_OBJECT_EX, NULL, 0, "flags"},
    { "reserved", T_OBJECT_EX, NULL, 0, "flags"},
    { NULL, 0, 0, 0, 0 },
};

static int vcan412_settings_object_init(vcan412_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));

    self->can1 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can2 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);

    self->canfd1 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd2 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);

    // Initialize TextAPI Objects
    self->textapi = PyObject_CallObject((PyObject*)&textapi_settings_object_type, NULL);

    return 0;
}

static PyObject* vcan412_settings_object_getattr(PyObject *o, PyObject *attr_name)
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
    vcan412_settings_object* obj = (vcan412_settings_object*)o;
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

static int vcan412_settings_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    vcan412_settings_object* obj = (vcan412_settings_object*)o;
    if (PyUnicode_CompareWithASCIIString(name, "disableUsbCheckOnBoot") == 0) {
        if (!PyBool_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a boolean",
                MODULE_NAME "." VCAN412_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        obj->s.flags.disableUsbCheckOnBoot = PyLong_AsLong(value);
        return 0;
    }
    else if (PyUnicode_CompareWithASCIIString(name, "enableLatencyTest") == 0) {
        if (!PyBool_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a boolean",
                MODULE_NAME "." VCAN412_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        obj->s.flags.enableLatencyTest = PyLong_AsLong(value);
        return 0;
    }
    else if (PyUnicode_CompareWithASCIIString(name, "reserved") == 0) {
        if (!PyLong_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be an integer",
                MODULE_NAME "." VCAN412_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        obj->s.flags.reserved = PyLong_AsLong(value);
        return 0;
    }
    else {
        return PyObject_GenericSetAttr(o, name, value);
    }
}



extern PyTypeObject vcan412_settings_object_type;


// Copied from tupleobject.h
#define PyVcan412Settings_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyVcan412Settings_CheckExact(op) (Py_TYPE(op) == &vcan412_settings_object_type)

bool setup_vcan412_settings_object(PyObject* module);

void vcan412_settings_object_update_from_struct(PyObject* settings);
void vcan412_settings_object_update_from_objects(PyObject* settings);

#endif // _OBJECT_VCAN412_SETTINGS_H_
