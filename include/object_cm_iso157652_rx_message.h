#ifndef _OBJECT_CM_ISO157652_RX_MESSAGE_H_
#define _OBJECT_CM_ISO157652_RX_MESSAGE_H_

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

#define CM_ISO157652_RX_MESSAGE_OBJECT_NAME "CmISO157652RxMessage"

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
    stCM_ISO157652_RxMessage s;
} cm_iso157652_rx_message_object;

static PyMemberDef cm_iso157652_rx_message_object_members[] = {
    { "vs_netid", T_USHORT, offsetof(cm_iso157652_rx_message_object, s.vs_netid), 0, "The netid of the message (determines which network to decode receives),  not supported"},
    { "padding", T_UBYTE, offsetof(cm_iso157652_rx_message_object, s.padding), 0, "The padding byte to use to fill the unused portion of\n* transmitted CAN frames (flow control), see paddingEnable."},
    { "id", T_UINT, offsetof(cm_iso157652_rx_message_object, s.id), 0, "arbId of transmitted frames (CAN id to transmit to)"},
    { "id_mask", T_UINT, offsetof(cm_iso157652_rx_message_object, s.id_mask), 0, "ArbId filter mask for frames from transmitter (from ECU to neoVI)"},
    { "fc_id", T_UINT, offsetof(cm_iso157652_rx_message_object, s.fc_id), 0, "flow control arbId to transmit in flow control (from neoVI to ECU)"},
    { "flowControlExtendedAddress", T_UBYTE, offsetof(cm_iso157652_rx_message_object, s.flowControlExtendedAddress), 0, "Expected Extended Address byte of response from receiver.  see fc_ext_address_enable, not supported"},
    { "extendedAddress", T_UBYTE, offsetof(cm_iso157652_rx_message_object, s.extendedAddress), 0, "Extended Address byte of transmitter. see ext_address_enable, not supported"},
    { "blockSize", T_UBYTE, offsetof(cm_iso157652_rx_message_object, s.blockSize), 0, "Overrides the block size that the receiver reports, see overrideBlockSize.   Set to J2534's BS_TX if <= 0xFF"},
    { "stMin", T_UBYTE, offsetof(cm_iso157652_rx_message_object, s.stMin), 0, "Minimum seperation time (between consecutive frames) to report in flow control response"},
    { "cf_timeout", T_USHORT, offsetof(cm_iso157652_rx_message_object, s.cf_timeout), 0, "max timeout (ms) for waiting on consecutive frame.  Set this to N_CR_MAX's value in J2534"},
    // TODO: Support bit fields here
    { "flags", T_UBYTE, offsetof(cm_iso157652_rx_message_object, s.flags), 0, ""},
    { "reserved", T_OBJECT_EX, offsetof(cm_iso157652_rx_message_object, s.reserved), 0, ""},
    { NULL, 0, 0, 0, 0 },
};


static int cm_iso157652_rx_message_object_init(cm_iso157652_rx_message_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

static PyObject* cm_iso157652_rx_message_object_getattr(PyObject *o, PyObject *attr_name)
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
    if (PyUnicode_CompareWithASCIIString(attr_name, "reserved") == 0) {
        Py_DECREF(attr_name);
        cm_iso157652_rx_message_object* obj = (cm_iso157652_rx_message_object*)o;
        PyObject *tuple = PyTuple_New(sizeof(obj->s.reserved)/sizeof(obj->s.reserved[0]));
        for (int i=0; i < sizeof(obj->s.reserved)/sizeof(obj->s.reserved[0]); ++i) {
            PyTuple_SET_ITEM(tuple, i, PyLong_FromLong(obj->s.reserved[i]));
        }
        return tuple;
    }
    else {
        return PyObject_GenericGetAttr(o, attr_name);
    }
}

static int cm_iso157652_rx_message_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    cm_iso157652_rx_message_object* obj = (cm_iso157652_rx_message_object*)o;
    if (PyUnicode_CompareWithASCIIString(name, "data") == 0) {
        // Make sure we are a tuple and len() == 8
        if (!PyTuple_Check(value) || !PyList_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a tuple or list",
                MODULE_NAME "." CM_ISO157652_RX_MESSAGE_OBJECT_NAME, name);
            return -1;
        }
        // Get tuple items and place them in array, set as 0 if error.
        PyObject *container = value;
        if (PyList_Check(value)) {
            container = PyList_AsTuple(value);
        }
        for (int i=0; i < sizeof(obj->s.reserved)/sizeof(obj->s.reserved[0]) && i < PyObject_Length(container); ++i) {
            PyObject* data = PyTuple_GetItem(container, i);
            if (!data && !PyLong_Check(data)) {
                obj->s.reserved[i] = 0;
            } else {
                obj->s.reserved[i] = (unsigned char)PyLong_AsLong(data);
            }
        }
        if (PyList_Check(value)) {
            Py_DECREF(container);
        }
        return 0;
    }
    else {
        return PyObject_GenericSetAttr(o, name, value);
    }
}

extern PyTypeObject cm_iso157652_rx_message_object_type;

// Copied from tupleobject.h
#define PyCmISO157652RxMessage_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyCmISO157652RxMessage_CheckExact(op) (Py_TYPE(op) == &cm_iso157652_rx_message_object_type)

bool setup_cm_iso157652_rx_message_object(PyObject* module);

#endif // _OBJECT_CM_ISO157652_RX_MESSAGE_H_