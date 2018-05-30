#ifndef _OBJECT_VCAN4_SETTINGS_H_
#define _OBJECT_VCAN4_SETTINGS_H_

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
#include "object_lin_settings.h"
#include "object_uart_settings.h"
#include "object_iso9141_keyword2000_settings.h"
#include "object_ethernet_settings.h"

#define VCAN4_SETTINGS_OBJECT_NAME "Vcan4Settings"

#if PY_MAJOR_VERSION < 3
#define PyUnicode_CompareWithASCIIString(uni, string) strcmp(PyString_AsString(uni), string)
#endif


typedef struct {
    PyObject_HEAD
    PyObject* can1;
    PyObject* can2;
    PyObject* can3;
    PyObject* can4;
    PyObject* canfd1;
    PyObject* canfd2;
    PyObject* canfd3;
    PyObject* canfd4;
    PyObject* lin1;
    PyObject* iso9141_kw1;
    PyObject* ethernet;
    PyObject* textapi;
    SVCAN4Settings s;
} vcan4_settings_object;

#if 0
typedef struct _SVCAN4Settings
{
	uint16_t perf_en;
	CAN_SETTINGS can1;
	CANFD_SETTINGS canfd1;
	CAN_SETTINGS can2;
	CANFD_SETTINGS canfd2;
	CAN_SETTINGS can3;
	CANFD_SETTINGS canfd3;
	CAN_SETTINGS can4;
	CANFD_SETTINGS canfd4;
	uint16_t network_enables;
	uint16_t network_enables_2;
	LIN_SETTINGS lin1;
	uint16_t network_enabled_on_boot;
	int16_t iso15765_separation_time_offset;
	uint16_t iso_9141_kwp_enable_reserved;
	ISO9141_KEYWORD2000_SETTINGS iso9141_kwp_settings_1;
	uint16_t iso_parity_1;
	uint16_t iso_msg_termination_1;
	uint16_t network_enables_3;
	STextAPISettings text_api;
	uint64_t termination_enables;
	ETHERNET_SETTINGS ethernet;
	struct
	{
		uint32_t enableLatencyTest : 1;
		uint32_t enablePcEthernetComm : 1;
		uint32_t reserved : 30;
	} flags;
	uint16_t pwr_man_enable;
	uint16_t pwr_man_timeout;
} SVCAN4Settings;
#endif
static PyMemberDef vcan4_settings_object_members[] = {
    { "perf_en", T_USHORT, offsetof(vcan4_settings_object, s.perf_en), 0, "" },

    { "can1", T_OBJECT_EX, offsetof(vcan4_settings_object, can1), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can2", T_OBJECT_EX, offsetof(vcan4_settings_object, can2), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can3", T_OBJECT_EX, offsetof(vcan4_settings_object, can3), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can4", T_OBJECT_EX, offsetof(vcan4_settings_object, can4), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "canfd1", T_OBJECT_EX, offsetof(vcan4_settings_object, canfd1), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd2", T_OBJECT_EX, offsetof(vcan4_settings_object, canfd2), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd3", T_OBJECT_EX, offsetof(vcan4_settings_object, canfd3), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd4", T_OBJECT_EX, offsetof(vcan4_settings_object, canfd4), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },

    { "network_enables", T_USHORT, offsetof(vcan4_settings_object, s.network_enables), 0, "" },
    { "network_enables_2", T_USHORT, offsetof(vcan4_settings_object, s.network_enables_2), 0, "" },

    { "lin1", T_OBJECT_EX, offsetof(vcan4_settings_object, lin1), 0, MODULE_NAME "." LIN_SETTINGS_OBJECT_NAME" Object" },

    { "network_enabled_on_boot", T_USHORT, offsetof(vcan4_settings_object, s.network_enabled_on_boot), 0, "" },
    { "iso15765_separation_time_offset", T_USHORT, offsetof(vcan4_settings_object, s.iso15765_separation_time_offset), 0, "" },
    { "iso_9141_kwp_enable_reserved", T_USHORT, offsetof(vcan4_settings_object, s.iso_9141_kwp_enable_reserved), 0, "" },
    { "iso9141_kwp_settings_1", T_OBJECT_EX, offsetof(vcan4_settings_object, iso9141_kw1), 0, ISO9141KEYWORD2000_SETTINGS_OBJECT_NAME" Object" },

    { "iso_parity_1", T_USHORT, offsetof(vcan4_settings_object, s.iso_parity_1), 0, "" },
    { "iso_msg_termination_1", T_USHORT, offsetof(vcan4_settings_object, s.iso_msg_termination_1), 0, "" },
    { "network_enables_3", T_USHORT, offsetof(vcan4_settings_object, s.network_enables_3), 0, "" },

    { "text_api", T_OBJECT_EX, offsetof(vcan4_settings_object, textapi), 0, MODULE_NAME "." TEXTAPI_SETTINGS_OBJECT_NAME" Object" },
    { "termination_enables", T_ULONGLONG, offsetof(vcan4_settings_object, s.termination_enables), 0, "" },
    
    { "ethernet", T_OBJECT_EX, offsetof(vcan4_settings_object, ethernet), 0, MODULE_NAME "." ETHERNET_SETTINGS_OBJECT_NAME" Object" },

    { "enableLatencyTest", T_OBJECT_EX, NULL, 0, "flags"},
    { "enablePcEthernetComm", T_OBJECT_EX, NULL, 0, "flags"},
    { "reserved", T_OBJECT_EX, NULL, 0, "flags"},

    { "pwr_man_enable", T_USHORT, offsetof(vcan4_settings_object, s.pwr_man_enable), 0, "" },
    { "pwr_man_timeout", T_USHORT, offsetof(vcan4_settings_object, s.pwr_man_timeout), 0, "" },

    { NULL, 0, 0, 0, 0 },
};

static int vcan4_settings_object_init(vcan4_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));

    self->can1 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can2 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can3 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can4 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);

    self->canfd1 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd2 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd3 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd4 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);

    self->lin1 = PyObject_CallObject((PyObject*)&lin_settings_object_type, NULL);

    self->iso9141_kw1 = PyObject_CallObject((PyObject*)&iso9141keyword2000_settings_object_type, NULL);

    self->ethernet = PyObject_CallObject((PyObject*)&ethernet_settings_object_type, NULL);

    // Initialize TextAPI Objects
    self->textapi = PyObject_CallObject((PyObject*)&textapi_settings_object_type, NULL);

    return 0;
}

static PyObject* vcan4_settings_object_getattr(PyObject *o, PyObject *attr_name)
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
    vcan4_settings_object* obj = (vcan4_settings_object*)o;
    if (PyUnicode_CompareWithASCIIString(attr_name, "enableLatencyTest") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("b", obj->s.flags.enableLatencyTest);
    }
    else if (PyUnicode_CompareWithASCIIString(attr_name, "enablePcEthernetComm") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("b", obj->s.flags.enablePcEthernetComm);
    }
    else if (PyUnicode_CompareWithASCIIString(attr_name, "reserved") == 0) {
        Py_DECREF(attr_name);
        return Py_BuildValue("i", obj->s.flags.reserved);
    }
    else {
        return PyObject_GenericGetAttr(o, attr_name);
    }
}

static int vcan4_settings_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    vcan4_settings_object* obj = (vcan4_settings_object*)o;
    if (PyUnicode_CompareWithASCIIString(name, "enableLatencyTest") == 0) {
        if (!PyBool_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a boolean",
                MODULE_NAME "." VCAN4_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        obj->s.flags.enableLatencyTest = PyLong_AsLong(value);
        return 0;
    }
    else if (PyUnicode_CompareWithASCIIString(name, "enablePcEthernetComm") == 0) {
        if (!PyBool_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a boolean",
                MODULE_NAME "." VCAN4_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        obj->s.flags.enablePcEthernetComm = PyLong_AsLong(value);
        return 0;
    }
    else if (PyUnicode_CompareWithASCIIString(name, "reserved") == 0) {
        if (!PyLong_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be an integer",
                MODULE_NAME "." VCAN4_SETTINGS_OBJECT_NAME, name);
            return -1;
        }
        obj->s.flags.reserved = PyLong_AsLong(value);
        return 0;
    }
    else {
        return PyObject_GenericSetAttr(o, name, value);
    }
}



extern PyTypeObject vcan4_settings_object_type;


// Copied from tupleobject.h
#define PyVcan4Settings_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyVcan4Settings_CheckExact(op) (Py_TYPE(op) == &vcan4_settings_object_type)

bool setup_vcan4_settings_object(PyObject* module);

#endif // _OBJECT_VCAN4_SETTINGS_H_