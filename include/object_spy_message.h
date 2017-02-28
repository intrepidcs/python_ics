#ifndef _OBJECT_SPY_MESSAGE_H_
#define _OBJECT_SPY_MESSAGE_H_
//http://docs.python.org/3/extending/newtypes.html

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

#include <vector>

#include "defines.h"

#define SPY_MESSAGE_OBJECT_NAME "SpyMessage"
#define SPY_MESSAGE_J1850_OBJECT_NAME "SpyMessageJ1850"

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
    icsSpyMessage msg;
    std::vector<unsigned char> ExtraDataBuffer;
} spy_message_object;

typedef struct {
    PyObject_HEAD
    icsSpyMessageJ1850 msg;
    std::vector<unsigned char> ExtraDataBuffer;
} spy_message_j1850_object;

static PyMemberDef spy_message_object_members[] = {
    { "StatusBitField", T_ULONG, offsetof(spy_message_object, msg.StatusBitField), 0, "StatusBitField" },
    { "StatusBitField2", T_ULONG, offsetof(spy_message_object, msg.StatusBitField2), 0, "StatusBitField2" },
    { "TimeHardware", T_ULONG, offsetof(spy_message_object, msg.TimeHardware), 0, "Hardware time stamp. The TimeStamp is reset on device open" },
    { "TimeHardware2", T_ULONG, offsetof(spy_message_object, msg.TimeHardware2), 0, "Hardware time stamp. The TimeStamp is reset on device open" },
    { "TimeSystem", T_ULONG, offsetof(spy_message_object, msg.TimeSystem), 0, "TimeSystem is loaded with the value received from the timeGetTime call in the WIN32 multimedia API." },
    { "TimeSystem2", T_ULONG, offsetof(spy_message_object, msg.TimeSystem2), 0, "TimeSystem is loaded with the value received from the timeGetTime call in the WIN32 multimedia API." },
    { "TimeStampHardwareID", T_UBYTE, offsetof(spy_message_object, msg.TimeStampHardwareID), 0, "This is an identifier of what type of hardware timestamp is used. Since neoVI's timestamp is always the same, this doesn't change." },
    { "TimeStampSystemID", T_UBYTE, offsetof(spy_message_object, msg.TimeStampSystemID), 0, "This is an identifier of what type of system timestamp is used. Since WIN32 neoVI's timestamp is always the same, from the timeGetTime API, this doesn't change." },
    { "NetworkID", T_UBYTE, offsetof(spy_message_object, msg.NetworkID), 0, "This value is used to identify which network this message was received on." },
    { "NodeID", T_UBYTE, offsetof(spy_message_object, msg.NodeID), 0, "Not Used" },
    { "Protocol", T_UBYTE, offsetof(spy_message_object, msg.Protocol), 0, "Valid values are SPY_PROTOCOL_CAN, SPY_PROTOCOL_J1850VPW, and SPY_PROTOCOL_ISO9141." },
    { "MessagePieceID", T_UBYTE, offsetof(spy_message_object, msg.MessagePieceID), 0, "Not Used" },
    { "ExtraDataPtrEnabled", T_UBYTE, offsetof(spy_message_object, msg.ExtraDataPtrEnabled), 0, "" },
    { "NumberBytesHeader", T_UBYTE, offsetof(spy_message_object, msg.NumberBytesHeader), 0, "     Used for J1850/ISO messages. It indicates how many bytes are stored in the Header(1 to 4) array." },
    { "NumberBytesData", T_UBYTE, offsetof(spy_message_object, msg.NumberBytesData), 0, "Holds the number of bytes in the Data(1 to 8) array or the number of bytes in a CAN remote frame (The DLC)." },
    { "DescriptionID", T_SHORT, offsetof(spy_message_object, msg.DescriptionID), 0, "Not Used" },
    { "ArbIDOrHeader", T_LONG, offsetof(spy_message_object, msg.ArbIDOrHeader), 0, "" },
    { "Data", T_OBJECT_EX, NULL, 0, "" },
    { "StatusBitField3", T_ULONG, offsetof(spy_message_object, msg.StatusBitField3), 0, "StatusBitField3" },
    { "StatusBitField4", T_ULONG, offsetof(spy_message_object, msg.StatusBitField4), 0, "StatusBitField4" },
    { "AckBytes", T_OBJECT_EX, NULL, 0, "" },
    { "ExtraDataPtr", T_OBJECT_EX, offsetof(spy_message_object, msg.ExtraDataPtr), 0, "" },
    { "MiscData", T_UBYTE, offsetof(spy_message_object, msg.MiscData), 0, "" },
    { NULL, 0, 0, 0, 0 },
};

static PyMemberDef spy_message_j1850_object_members[] = {
    { "StatusBitField", T_ULONG, offsetof(spy_message_j1850_object, msg.StatusBitField), 0, "StatusBitField" },
    { "StatusBitField2", T_ULONG, offsetof(spy_message_j1850_object, msg.StatusBitField2), 0, "StatusBitField2" },
    { "TimeHardware", T_ULONG, offsetof(spy_message_j1850_object, msg.TimeHardware), 0, "Hardware time stamp. The TimeStamp is reset on device open" },
    { "TimeHardware2", T_ULONG, offsetof(spy_message_j1850_object, msg.TimeHardware2), 0, "Hardware time stamp. The TimeStamp is reset on device open" },
    { "TimeSystem", T_ULONG, offsetof(spy_message_j1850_object, msg.TimeSystem), 0, "TimeSystem is loaded with the value received from the timeGetTime call in the WIN32 multimedia API." },
    { "TimeSystem2", T_ULONG, offsetof(spy_message_j1850_object, msg.TimeSystem2), 0, "TimeSystem is loaded with the value received from the timeGetTime call in the WIN32 multimedia API." },
    { "TimeStampHardwareID", T_UBYTE, offsetof(spy_message_j1850_object, msg.TimeStampHardwareID), 0, "This is an identifier of what type of hardware timestamp is used. Since neoVI's timestamp is always the same, this doesn't change." },
    { "TimeStampSystemID", T_UBYTE, offsetof(spy_message_j1850_object, msg.TimeStampSystemID), 0, "This is an identifier of what type of system timestamp is used. Since WIN32 neoVI's timestamp is always the same, from the timeGetTime API, this doesn't change." },
    { "NetworkID", T_UBYTE, offsetof(spy_message_j1850_object, msg.NetworkID), 0, "This value is used to identify which network this message was received on." },
    { "NodeID", T_UBYTE, offsetof(spy_message_j1850_object, msg.NodeID), 0, "Not Used" },
    { "Protocol", T_UBYTE, offsetof(spy_message_j1850_object, msg.Protocol), 0, "Valid values are SPY_PROTOCOL_CAN, SPY_PROTOCOL_J1850VPW, and SPY_PROTOCOL_ISO9141." },
    { "MessagePieceID", T_UBYTE, offsetof(spy_message_j1850_object, msg.MessagePieceID), 0, "Not Used" },
    { "ExtraDataPtrEnabled", T_UBYTE, offsetof(spy_message_j1850_object, msg.ExtraDataPtrEnabled), 0, "" },
    { "NumberBytesHeader", T_UBYTE, offsetof(spy_message_j1850_object, msg.NumberBytesHeader), 0, "     Used for J1850/ISO messages. It indicates how many bytes are stored in the Header(1 to 4) array." },
    { "NumberBytesData", T_UBYTE, offsetof(spy_message_j1850_object, msg.NumberBytesData), 0, "Holds the number of bytes in the Data(1 to 8) array or the number of bytes in a CAN remote frame (The DLC)." },
    { "DescriptionID", T_SHORT, offsetof(spy_message_j1850_object, msg.DescriptionID), 0, "Not Used" },
    { "Header", T_OBJECT_EX, NULL, 0, "" },
    { "Data", T_OBJECT_EX, NULL, 0, "" },
    { "StatusBitField3", T_ULONG, offsetof(spy_message_j1850_object, msg.StatusBitField3), 0, "StatusBitField3" },
    { "StatusBitField4", T_ULONG, offsetof(spy_message_j1850_object, msg.StatusBitField4), 0, "StatusBitField4" },
    { "AckBytes", T_OBJECT_EX, NULL, 0, "" },
    { "ExtraDataPtr", T_OBJECT_EX, offsetof(spy_message_j1850_object, msg.ExtraDataPtr), 0, "" },
    { "MiscData", T_UBYTE, offsetof(spy_message_j1850_object, msg.MiscData), 0, "" },
    { NULL, 0, 0, 0, 0 },
};

static void spy_message_object_dealloc(spy_message_object* self)
{
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* spy_message_object_getattr(PyObject *o, PyObject *attr_name)
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
    if (PyUnicode_CompareWithASCIIString(attr_name, "Data") == 0) {
        Py_DECREF(attr_name);
        spy_message_object* obj = (spy_message_object*)o;
        PyObject* temp = Py_BuildValue("(i,i,i,i,i,i,i,i)",
            obj->msg.Data[0],
            obj->msg.Data[1],
            obj->msg.Data[2],
            obj->msg.Data[3],
            obj->msg.Data[4],
            obj->msg.Data[5],
            obj->msg.Data[6],
            obj->msg.Data[7]);
        PyObject* data = PyTuple_GetSlice(temp, 0, obj->msg.NumberBytesData);
        Py_DECREF(temp);
        return data;
    }
    else if (PyUnicode_CompareWithASCIIString(attr_name, "AckBytes") == 0) {
        Py_DECREF(attr_name);
        spy_message_object* obj = (spy_message_object*)o;
        return Py_BuildValue("(i,i,i,i,i,i,i,i)",
            obj->msg.AckBytes[0],
            obj->msg.AckBytes[1],
            obj->msg.AckBytes[2],
            obj->msg.AckBytes[3],
            obj->msg.AckBytes[4],
            obj->msg.AckBytes[5],
            obj->msg.AckBytes[6],
            obj->msg.AckBytes[7]);
    }
    else if (PyUnicode_CompareWithASCIIString(attr_name, "Header") == 0) {
        Py_DECREF(attr_name);
        spy_message_j1850_object* obj = (spy_message_j1850_object*)o;
        PyObject* temp = Py_BuildValue("(i,i,i,i)",
            obj->msg.Header[0],
            obj->msg.Header[1],
            obj->msg.Header[2],
            obj->msg.Header[3]);
        PyObject* data = PyTuple_GetSlice(temp, 0, obj->msg.NumberBytesHeader);
        Py_DECREF(temp);
        return data;
    }
    else if (PyUnicode_CompareWithASCIIString(attr_name, "ExtraDataPtr") == 0) {
        Py_DECREF(attr_name);
        spy_message_j1850_object* obj = (spy_message_j1850_object*)o;
        PyObject* tuple = PyTuple_New(obj->ExtraDataBuffer.size());
        std::vector<unsigned char>::iterator it = obj->ExtraDataBuffer.begin();
        for (int i=0; it != obj->ExtraDataBuffer.end(); ++it,++i) {
            PyTuple_SET_ITEM(tuple, i, PyLong_FromLong(*it));
        }
        return tuple;
    }
    else {
        return PyObject_GenericGetAttr(o, attr_name);
    }
}

static int spy_message_object_setattr(PyObject *o, PyObject *name, PyObject *value)
{
    spy_message_object* obj = (spy_message_object*)o;
    if (PyUnicode_CompareWithASCIIString(name, "Data") == 0) {
        // Make sure we are a tuple and len() == 8
        if (!PyTuple_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a tuple",
                MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME, name);
            return -1;
        }
        // Get tuple items and place them in array, set as 0 if error.
        for (int i=0; i < 8 && i < PyObject_Length(value); ++i) {
            PyObject* data = PyTuple_GetItem(value, i);
            if (!data && !PyLong_Check(data)) {
                obj->msg.Data[i] = 0;
            } else {
                obj->msg.Data[i] = (unsigned char)PyLong_AsLong(data);
            }
        }
        obj->msg.NumberBytesData = PyObject_Length(value);
        return 0;
    }
    else if (PyUnicode_CompareWithASCIIString(name, "AckBytes") == 0) {
        // Make sure we are a tuple and len() == 8
        if (!PyTuple_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a tuple",
                MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME, name);
            return -1;
        }
        // Get tuple items and place them in array, set as 0 if error.
        for (int i=0; i < 8 && i < PyObject_Length(value); ++i) {
            PyObject* data = PyTuple_GetItem(value, i);
            if (!data && !PyLong_Check(data)) {
                obj->msg.AckBytes[i] = 0;
            } else {
                obj->msg.AckBytes[i] = (unsigned char)PyLong_AsLong(data);
            }
        }
        return 0;
    }
    else if (PyUnicode_CompareWithASCIIString(name, "Header") == 0) {
        // Make sure we are a tuple and len() == 8
        if (!PyTuple_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a tuple",
                MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME, name);
            return -1;
        }
        // Get tuple items and place them in array, set as 0 if error.
        for (int i=0; i < 8 && i < PyObject_Length(value); ++i) {
            PyObject* data = PyTuple_GetItem(value, i);
            if (!data && !PyLong_Check(data)) {
                ((spy_message_j1850_object*)obj)->msg.Header[i] = 0;
            } else {
                ((spy_message_j1850_object*)obj)->msg.Header[i] = (unsigned char)PyLong_AsLong(data);
            }
            obj->msg.NumberBytesHeader = PyObject_Length(value);
        }
        return 0;
    }
    else if (PyUnicode_CompareWithASCIIString(name, "ExtraDataPtr") == 0) {

        // Make sure we are a tuple and len() == 8
        if (!PyTuple_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                "'%.50s' object attribute '%.400s' needs to be a tuple",
                MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME, name);
            return -1;
        }

        // Get tuple items and place them in array, set as 0 if error.
        Py_ssize_t length = PyObject_Length(value);
        ((spy_message_j1850_object*)obj)->ExtraDataBuffer.clear();
        for (int i=0; i < PyObject_Length(value); ++i) {
            PyObject* data = PyTuple_GetItem(value, i);
            if (!data && !PyLong_Check(data)) {
                obj->ExtraDataBuffer.push_back(0);
            } else {
                obj->ExtraDataBuffer.push_back((unsigned char)PyLong_AsLong(data));
            }
            obj->msg.NumberBytesHeader = PyObject_Length(value);
        }
        return 0;
    }
    else {
        return PyObject_GenericSetAttr(o, name, value);
    }
}

extern PyTypeObject spy_message_object_type;
extern PyTypeObject spy_message_j1850_object_type;

// Copied from tupleobject.h
#define PySpyMessage_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PySpyMessage_CheckExact(op) (Py_TYPE(op) == &spy_message_object_type)
#define PySpyMessageJ1850_CheckExact(op) (Py_TYPE(op) == &spy_message_j1850_object_type)

#define PySpyMessage_GetObject(obj) ((spy_message_object*)obj)
#define PySpyMessageJ1850_GetObject(obj) ((spy_message_j1850_object*)obj)

bool setup_spy_message_object(PyObject* module);

#endif // _OBJECT_SPY_MESSAGE_H_