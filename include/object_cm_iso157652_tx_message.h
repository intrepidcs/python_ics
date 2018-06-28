#ifndef _OBJECT_CM_ISO157652_TX_MESSAGE_H_
#define _OBJECT_CM_ISO157652_TX_MESSAGE_H_

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

#define CM_ISO157652_TX_MESSAGE_OBJECT_NAME "CmISO157652TxMessage"

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
    stCM_ISO157652_TxMessage s;
} cm_iso157652_tx_message_object;

static PyMemberDef cm_iso157652_tx_message_object_members[] = {
    { "vs_netid", T_USHORT, offsetof(cm_iso157652_tx_message_object, s.vs_netid), 0, "The netid of the message (determines which network to transmit on),  not supported"},
    { "padding", T_UBYTE, offsetof(cm_iso157652_tx_message_object, s.padding), 0, "The padding byte to use to fill the unused portion of\n* transmitted CAN frames (single frame, first frame, consecutive frame) *"},
    { "tx_index", T_UBYTE, offsetof(cm_iso157652_tx_message_object, s.tx_index), 0, ""},
    { "id", T_UINT, offsetof(cm_iso157652_tx_message_object, s.id), 0, "arbId of transmitted frames (CAN id to transmit to)"},
    { "fc_id", T_UINT, offsetof(cm_iso157652_tx_message_object, s.fc_id), 0, "flow control arb id filter value (response id from receiver)"},
    { "fc_id_mask", T_UINT, offsetof(cm_iso157652_tx_message_object, s.fc_id_mask), 0, "The flow control arb filter mask (response id from receiver)"},
    { "stMin", T_UBYTE, offsetof(cm_iso157652_tx_message_object, s.stMin), 0, "Overrides the stMin that the receiver reports, see overrideSTmin. Set to J2534's STMIN_TX if <= 0xFF"},
    { "blockSize", T_UBYTE, offsetof(cm_iso157652_tx_message_object, s.blockSize), 0, "Overrides the block size that the receiver reports, see overrideBlockSize.   Set to J2534's BS_TX if <= 0xFF"},
    { "flowControlExtendedAddress", T_UBYTE, offsetof(cm_iso157652_tx_message_object, s.flowControlExtendedAddress), 0, "Expected Extended Address byte of response from receiver.  see fc_ext_address_enable, not supported"},
    { "extendedAddress", T_UBYTE, offsetof(cm_iso157652_tx_message_object, s.extendedAddress), 0, "Extended Address byte of transmitter. see ext_address_enable, not supported"},
    { "fs_timeout", T_USHORT, offsetof(cm_iso157652_tx_message_object, s.fs_timeout), 0, "max timeout (ms) for waiting on flow control respons. Set this to N_BS_MAX's value if J2534"},
    { "fs_wait", T_USHORT, offsetof(cm_iso157652_tx_message_object, s.fs_wait), 0, "max timeout (ms) for waiting on flow control response after receiving flow control\n* with flow status set to WAIT.   Set this to N_BS_MAX's value if J2534."},
    { "data", T_OBJECT_EX, offsetof(cm_iso157652_tx_message_object, s.data), 0, "The data"},
    { "num_bytes", T_UINT, offsetof(cm_iso157652_tx_message_object, s.num_bytes), 0, "Number of data bytes"},
    // TODO: Support bit fields here
    { "flags", T_UINT, offsetof(cm_iso157652_tx_message_object, s.flags), 0, ""},
    { NULL, 0, 0, 0, 0 },
};

static int cm_iso157652_tx_message_object_init(cm_iso157652_tx_message_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

static PyObject* cm_iso157652_tx_message_object_getattr(PyObject *o, PyObject *attr_name)
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
    if (PyUnicode_CompareWithASCIIString(attr_name, "data") == 0) {
        Py_DECREF(attr_name);
        cm_iso157652_tx_message_object* obj = (cm_iso157652_tx_message_object*)o;
        PyObject *tuple = PyTuple_New(sizeof(obj->s.data)/sizeof(obj->s.data[0]));
        for (int i=0; i < sizeof(obj->s.data)/sizeof(obj->s.data[0]); ++i) {
            PyTuple_SET_ITEM(tuple, i, PyLong_FromLong(obj->s.data[i]));
        }
        return tuple;
    }
    else {
        return PyObject_GenericGetAttr(o, attr_name);
    }
}

static int cm_iso157652_tx_message_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    cm_iso157652_tx_message_object* obj = (cm_iso157652_tx_message_object*)o;
    if (PyUnicode_CompareWithASCIIString(name, "data") == 0) {
        // Make sure we are a tuple and len() == 8
        if (!PyTuple_Check(value) && !PyList_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a tuple or list",
                MODULE_NAME "." CM_ISO157652_TX_MESSAGE_OBJECT_NAME, name);
            return -1;
        }
        // Get tuple items and place them in array, set as 0 if error.
        PyObject *container = value;
        if (PyList_Check(value)) {
            container = PyList_AsTuple(value);
        }
        for (int i=0; i < sizeof(obj->s.data)/sizeof(obj->s.data[0]) && i < PyObject_Length(container); ++i) {
            PyObject* data = PyTuple_GetItem(container, i);
            if (!data && !PyLong_Check(data)) {
                obj->s.data[i] = 0;
            } else {
                obj->s.data[i] = (unsigned char)PyLong_AsLong(data);
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

extern PyTypeObject cm_iso157652_tx_message_object_type;

// Copied from tupleobject.h
#define PyCmISO157652TxMessage_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyCmISO157652TxMessage_CheckExact(op) (Py_TYPE(op) == &cm_iso157652_tx_message_object_type)

bool setup_cm_iso157652_tx_message_object(PyObject* module);

#endif // _OBJECT_CM_ISO157652_TX_MESSAGE_H_