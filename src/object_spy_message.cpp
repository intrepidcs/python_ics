#include "object_spy_message.h"

static int spy_message_object_alloc(spy_message_object* self, PyObject* args, PyObject* kwds)
{
    (void)args;
    (void)kwds;
    memset(&self->msg, 0, sizeof(self->msg));
    self->noExtraDataPtrCleanup = false;
    return 0;
}

static void spy_message_object_dealloc(spy_message_object* self)
{
    if ((!self->noExtraDataPtrCleanup && self->msg.ExtraDataPtrEnabled && self->msg.ExtraDataPtr != NULL) ||
        (!self->noExtraDataPtrCleanup && self->msg.Protocol == SPY_PROTOCOL_ETHERNET &&
         self->msg.ExtraDataPtr != NULL)) {
        // Clean up the ExtraDataPtr if we can
        // Ethernet protocol uses the ExtraDataPtrEnabled reversed internally so do a double check here
        delete[] (unsigned char*)self->msg.ExtraDataPtr;
        self->msg.ExtraDataPtr = NULL;
        self->msg.ExtraDataPtrEnabled = 0;
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

// Validates that value is a tuple of at most max_length ints and copies the
// elements into dest. Returns the tuple length, or -1 with an exception set.
// dest is only written on success.
static Py_ssize_t _copy_byte_tuple(PyObject* value, PyObject* attr_name, unsigned char* dest, Py_ssize_t max_length)
{
    if (!PyTuple_Check(value)) {
        PyErr_Format(PyExc_AttributeError,
                     "'%.50s' object attribute '%U' needs to be a tuple",
                     MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME,
                     attr_name);
        return -1;
    }
    Py_ssize_t length = PyTuple_Size(value);
    if (length > max_length) {
        PyErr_Format(
            PyExc_ValueError, "'%U' accepts at most %zd bytes (got %zd)", attr_name, max_length, length);
        return -1;
    }
    unsigned char temp[8] = { 0 };
    for (Py_ssize_t i = 0; i < length; ++i) {
        PyObject* item = PyTuple_GetItem(value, i);
        if (!item)
            return -1;
        long byte = PyLong_AsLong(item);
        if (byte == -1 && PyErr_Occurred())
            return -1;
        temp[i] = (unsigned char)byte;
    }
    memcpy(dest, temp, (size_t)length);
    return length;
}

static PyObject* spy_message_object_getattr(PyObject* o, PyObject* attr_name)
{
#if PY_MAJOR_VERSION >= 3
    if (!PyUnicode_Check(attr_name)) {
#else
    if (!PyString_Check(attr_name)) {
#endif
        PyErr_Format(PyExc_TypeError, "attribute name must be string, not '%.200s'", attr_name->ob_type->tp_name);
        return NULL;
    } else {
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
    } else if (PyUnicode_CompareWithASCIIString(attr_name, "AckBytes") == 0) {
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
    } else if (PyUnicode_CompareWithASCIIString(attr_name, "Header") == 0) {
        Py_DECREF(attr_name);
        spy_message_j1850_object* obj = (spy_message_j1850_object*)o;
        PyObject* temp =
            Py_BuildValue("(i,i,i,i)", obj->msg.Header[0], obj->msg.Header[1], obj->msg.Header[2], obj->msg.Header[3]);
        PyObject* data = PyTuple_GetSlice(temp, 0, obj->msg.NumberBytesHeader);
        Py_DECREF(temp);
        return data;
    } else if (PyUnicode_CompareWithASCIIString(attr_name, "ExtraDataPtr") == 0) {
        Py_DECREF(attr_name);
        spy_message_j1850_object* obj = (spy_message_j1850_object*)o;
        unsigned char* ExtraDataPtr = (unsigned char*)obj->msg.ExtraDataPtr;
        bool extra_data_ptr_enabled = obj->msg.ExtraDataPtrEnabled != 0;
        // Ethernet protocol uses the ExtraDataPtrEnabled reversed internally
        if ((obj->msg.Protocol == SPY_PROTOCOL_ETHERNET || 
             obj->msg.Protocol == SPY_PROTOCOL_SPI || 
             obj->msg.Protocol == SPY_PROTOCOL_WBMS) 
            && obj->msg.ExtraDataPtr != NULL) {
            extra_data_ptr_enabled = true;
        }
        int actual_size = 0;
        // Some newer protocols are packing the length into NumberBytesHeader also so lets handle it here...
        if (obj->msg.Protocol == SPY_PROTOCOL_A2B || obj->msg.Protocol == SPY_PROTOCOL_ETHERNET || 
            obj->msg.Protocol == SPY_PROTOCOL_SPI || obj->msg.Protocol == SPY_PROTOCOL_WBMS) {
            actual_size = (obj->msg.NumberBytesHeader << 8) | obj->msg.NumberBytesData;
        } else {
            actual_size = obj->msg.NumberBytesData;
        }
        if (extra_data_ptr_enabled && actual_size && obj->msg.ExtraDataPtr) {
            PyObject* tuple = PyTuple_New(actual_size);
            for (int i = 0; i < actual_size; ++i) {
                PyTuple_SET_ITEM(tuple, i, PyLong_FromLong(ExtraDataPtr[i]));
            }
            return tuple;
        } else {
            Py_RETURN_NONE;
        }
    } else {
        return PyObject_GenericGetAttr(o, attr_name);
    }
}

static int spy_message_object_setattr(PyObject* o, PyObject* name, PyObject* value)
{
    spy_message_object* obj = (spy_message_object*)o;
    if (PyUnicode_CompareWithASCIIString(name, "Data") == 0) {
        Py_ssize_t length = _copy_byte_tuple(value, name, obj->msg.Data, sizeof(obj->msg.Data));
        if (length < 0)
            return -1;
        obj->msg.NumberBytesData = static_cast<uint8_t>(length);
        return 0;
    } else if (PyUnicode_CompareWithASCIIString(name, "AckBytes") == 0) {
        if (_copy_byte_tuple(value, name, obj->msg.AckBytes, sizeof(obj->msg.AckBytes)) < 0)
            return -1;
        return 0;
    } else if (PyUnicode_CompareWithASCIIString(name, "Header") == 0) {
        spy_message_j1850_object* j1850_obj = (spy_message_j1850_object*)obj;
        Py_ssize_t length = _copy_byte_tuple(value, name, j1850_obj->msg.Header, sizeof(j1850_obj->msg.Header));
        if (length < 0)
            return -1;
        obj->msg.NumberBytesHeader = static_cast<uint8_t>(length);
        return 0;
    } else if (PyUnicode_CompareWithASCIIString(name, "Protocol") == 0) {
        // Ethernet behavior is backward to CAN and will crash if enabled.
        long protocol = PyLong_AsLong(value);
        if (protocol == -1 && PyErr_Occurred())
            PyErr_Clear(); // let PyObject_GenericSetAttr report the type error
        else if (protocol == SPY_PROTOCOL_ETHERNET)
            obj->msg.ExtraDataPtrEnabled = 0;
        return PyObject_GenericSetAttr(o, name, value);
    } else if (PyUnicode_CompareWithASCIIString(name, "ExtraDataPtr") == 0) {
        if (!PyTuple_Check(value)) {
            PyErr_Format(PyExc_AttributeError,
                         "'%.50s' object attribute '%U' needs to be a tuple",
                         MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME,
                         name);
            return -1;
        }
        // Some newer protocols are packing the length into NumberBytesHeader also so lets handle it here...
        bool packs_length = obj->msg.Protocol == SPY_PROTOCOL_A2B || obj->msg.Protocol == SPY_PROTOCOL_ETHERNET ||
            obj->msg.Protocol == SPY_PROTOCOL_SPI || obj->msg.Protocol == SPY_PROTOCOL_WBMS;
        Py_ssize_t length = PyTuple_Size(value);
        Py_ssize_t max_length = packs_length ? 0xFFFF : 0xFF;
        if (length > max_length) {
            PyErr_Format(PyExc_ValueError,
                         "'%U' accepts at most %zd bytes for this protocol (got %zd)",
                         name,
                         max_length,
                         length);
            return -1;
        }
        // Validate and copy into a fresh buffer before touching the message.
        unsigned char* buffer = new unsigned char[length > 0 ? (size_t)length : 1];
        for (Py_ssize_t i = 0; i < length; ++i) {
            PyObject* data = PyTuple_GetItem(value, i);
            long byte = data ? PyLong_AsLong(data) : -1;
            if (!data || (byte == -1 && PyErr_Occurred())) {
                delete[] buffer;
                return -1;
            }
            buffer[i] = (unsigned char)byte;
        }
        // Never delete[] a buffer this extension didn't allocate (e.g. DLL-owned
        // pointers on received messages flagged with noExtraDataPtrCleanup).
        if (obj->msg.ExtraDataPtr != NULL && !obj->noExtraDataPtrCleanup)
            delete[] (unsigned char*)obj->msg.ExtraDataPtr;
        obj->msg.ExtraDataPtr = buffer;
        if (packs_length)
            obj->msg.NumberBytesHeader = static_cast<uint8_t>(length >> 8);
        obj->msg.NumberBytesData = static_cast<uint8_t>(length & 0xFF);
        if (obj->msg.Protocol != SPY_PROTOCOL_ETHERNET)
            obj->msg.ExtraDataPtrEnabled = 1;
        obj->noExtraDataPtrCleanup = false;
        return 0;
    } else if (PyUnicode_CompareWithASCIIString(name, "ExtraDataPtrEnabled") == 0) {
        long enabled = PyLong_AsLong(value);
        if (enabled == -1 && PyErr_Occurred()) {
            PyErr_Clear(); // let PyObject_GenericSetAttr report the type error
            return PyObject_GenericSetAttr(o, name, value);
        }
        // Make sure we clean up here so we don't memory leak
        if ((!obj->noExtraDataPtrCleanup && enabled != 1 && obj->msg.ExtraDataPtrEnabled == 1) ||
            (!obj->noExtraDataPtrCleanup && enabled != 1 && obj->msg.Protocol == SPY_PROTOCOL_ETHERNET)) {
            if (obj->msg.ExtraDataPtr != NULL) {
                delete[] (unsigned char*)obj->msg.ExtraDataPtr;
                obj->msg.ExtraDataPtr = NULL;
            }
        } else if (enabled != 0 && obj->msg.Protocol == SPY_PROTOCOL_ETHERNET) {
            // Ethernet always needs to be set to 0
            return 0;
        }
        return PyObject_GenericSetAttr(o, name, value);
    } else {
        return PyObject_GenericSetAttr(o, name, value);
    }
}

static PyMemberDef spy_message_object_members[] = {
    { "StatusBitField", T_UINT, offsetof(spy_message_object, msg.StatusBitField), 0, "StatusBitField" },
    { "StatusBitField2", T_UINT, offsetof(spy_message_object, msg.StatusBitField2), 0, "StatusBitField2" },
    { "TimeHardware",
      T_UINT,
      offsetof(spy_message_object, msg.TimeHardware),
      0,
      "Hardware time stamp. The TimeStamp is reset on device open" },
    { "TimeHardware2",
      T_UINT,
      offsetof(spy_message_object, msg.TimeHardware2),
      0,
      "Hardware time stamp. The TimeStamp is reset on device open" },
    { "TimeSystem",
      T_UINT,
      offsetof(spy_message_object, msg.TimeSystem),
      0,
      "TimeSystem is loaded with the value received from the timeGetTime call in the WIN32 multimedia API." },
    { "TimeSystem2",
      T_UINT,
      offsetof(spy_message_object, msg.TimeSystem2),
      0,
      "TimeSystem is loaded with the value received from the timeGetTime call in the WIN32 multimedia API." },
    { "TimeStampHardwareID",
      T_UBYTE,
      offsetof(spy_message_object, msg.TimeStampHardwareID),
      0,
      "This is an identifier of what type of hardware timestamp is used. Since neoVI's timestamp is always the same, "
      "this doesn't change." },
    { "TimeStampSystemID",
      T_UBYTE,
      offsetof(spy_message_object, msg.TimeStampSystemID),
      0,
      "This is an identifier of what type of system timestamp is used. Since WIN32 neoVI's timestamp is always the "
      "same, "
      "from the timeGetTime API, this doesn't change." },
    { "NetworkID",
      T_UBYTE,
      offsetof(spy_message_object, msg.NetworkID),
      0,
      "This value is used to identify which network this message was received on." },
    { "NodeID", T_UBYTE, offsetof(spy_message_object, msg.NodeID), 0, "Not Used" },
    { "Protocol",
      T_UBYTE,
      offsetof(spy_message_object, msg.Protocol),
      0,
      "Valid values are SPY_PROTOCOL_CAN, SPY_PROTOCOL_J1850VPW, and SPY_PROTOCOL_ISO9141." },
    { "MessagePieceID", T_UBYTE, offsetof(spy_message_object, msg.MessagePieceID), 0, "Not Used" },
    { "ExtraDataPtrEnabled", T_UBYTE, offsetof(spy_message_object, msg.ExtraDataPtrEnabled), 0, "" },
    { "NumberBytesHeader",
      T_UBYTE,
      offsetof(spy_message_object, msg.NumberBytesHeader),
      0,
      "     Used for J1850/ISO messages. It indicates how many bytes are stored in the Header(1 to 4) array." },
    { "NumberBytesData",
      T_UBYTE,
      offsetof(spy_message_object, msg.NumberBytesData),
      0,
      "Holds the number of bytes in the Data(1 to 8) array or the number of bytes in a CAN remote frame (The DLC)." },
    { "NetworkID2",
      T_UBYTE,
      offsetof(spy_message_object, msg.NetworkID2),
      0,
      "This value is used to identify which network this message was received on." },
    { "DescriptionID", T_SHORT, offsetof(spy_message_object, msg.DescriptionID), 0, "Not Used" },
    { "ArbIDOrHeader", T_UINT, offsetof(spy_message_object, msg.ArbIDOrHeader), 0, "" },
    // Data, AckBytes and ExtraDataPtr are handled by tp_getattro/tp_setattro;
    // a member entry here would expose a descriptor that reinterprets raw
    // struct memory as a PyObject*.
    { "StatusBitField3", T_UINT, offsetof(spy_message_object, msg.StatusBitField3), 0, "StatusBitField3" },
    { "StatusBitField4", T_UINT, offsetof(spy_message_object, msg.StatusBitField4), 0, "StatusBitField4" },
    { "MiscData", T_UBYTE, offsetof(spy_message_object, msg.MiscData), 0, "" },
    { "noExtraDataPtrCleanup",
      T_BOOL,
      offsetof(spy_message_object, noExtraDataPtrCleanup),
      0,
      "Tells Python to not clean up ExtraDataPtrMemory, If this is enabled. Ignore, if unsure." },
    { NULL, 0, 0, 0, NULL },
};

static PyMemberDef spy_message_j1850_object_members[] = {
    { "StatusBitField", T_UINT, offsetof(spy_message_j1850_object, msg.StatusBitField), 0, "StatusBitField" },
    { "StatusBitField2", T_UINT, offsetof(spy_message_j1850_object, msg.StatusBitField2), 0, "StatusBitField2" },
    { "TimeHardware",
      T_UINT,
      offsetof(spy_message_j1850_object, msg.TimeHardware),
      0,
      "Hardware time stamp. The TimeStamp is reset on device open" },
    { "TimeHardware2",
      T_UINT,
      offsetof(spy_message_j1850_object, msg.TimeHardware2),
      0,
      "Hardware time stamp. The TimeStamp is reset on device open" },
    { "TimeSystem",
      T_UINT,
      offsetof(spy_message_j1850_object, msg.TimeSystem),
      0,
      "TimeSystem is loaded with the value received from the timeGetTime call in the WIN32 multimedia API." },
    { "TimeSystem2",
      T_UINT,
      offsetof(spy_message_j1850_object, msg.TimeSystem2),
      0,
      "TimeSystem is loaded with the value received from the timeGetTime call in the WIN32 multimedia API." },
    { "TimeStampHardwareID",
      T_UBYTE,
      offsetof(spy_message_j1850_object, msg.TimeStampHardwareID),
      0,
      "This is an identifier of what type of hardware timestamp is used. Since neoVI's timestamp is always the same, "
      "this doesn't change." },
    { "TimeStampSystemID",
      T_UBYTE,
      offsetof(spy_message_j1850_object, msg.TimeStampSystemID),
      0,
      "This is an identifier of what type of system timestamp is used. Since WIN32 neoVI's timestamp is always the "
      "same, "
      "from the timeGetTime API, this doesn't change." },
    { "NetworkID",
      T_UBYTE,
      offsetof(spy_message_j1850_object, msg.NetworkID),
      0,
      "This value is used to identify which network this message was received on." },
    { "NodeID", T_UBYTE, offsetof(spy_message_j1850_object, msg.NodeID), 0, "Not Used" },
    { "Protocol",
      T_UBYTE,
      offsetof(spy_message_j1850_object, msg.Protocol),
      0,
      "Valid values are SPY_PROTOCOL_CAN, SPY_PROTOCOL_J1850VPW, and SPY_PROTOCOL_ISO9141." },
    { "MessagePieceID", T_UBYTE, offsetof(spy_message_j1850_object, msg.MessagePieceID), 0, "Not Used" },
    { "ExtraDataPtrEnabled", T_UBYTE, offsetof(spy_message_j1850_object, msg.ExtraDataPtrEnabled), 0, "" },
    { "NumberBytesHeader",
      T_UBYTE,
      offsetof(spy_message_j1850_object, msg.NumberBytesHeader),
      0,
      "     Used for J1850/ISO messages. It indicates how many bytes are stored in the Header(1 to 4) array." },
    { "NumberBytesData",
      T_UBYTE,
      offsetof(spy_message_j1850_object, msg.NumberBytesData),
      0,
      "Holds the number of bytes in the Data(1 to 8) array or the number of bytes in a CAN remote frame (The DLC)." },
    { "NetworkID2",
      T_UBYTE,
      offsetof(spy_message_j1850_object, msg.NetworkID2),
      0,
      "This value is used to identify which network this message was received on." },
    { "DescriptionID", T_SHORT, offsetof(spy_message_j1850_object, msg.DescriptionID), 0, "Not Used" },
    // Header, Data, AckBytes and ExtraDataPtr are handled by
    // tp_getattro/tp_setattro; a member entry here would expose a descriptor
    // that reinterprets raw struct memory as a PyObject*.
    { "StatusBitField3", T_UINT, offsetof(spy_message_j1850_object, msg.StatusBitField3), 0, "StatusBitField3" },
    { "StatusBitField4", T_UINT, offsetof(spy_message_j1850_object, msg.StatusBitField4), 0, "StatusBitField4" },
    { "MiscData", T_UBYTE, offsetof(spy_message_j1850_object, msg.MiscData), 0, "" },
    { "noExtraDataPtrCleanup",
      T_BOOL,
      offsetof(spy_message_j1850_object, noExtraDataPtrCleanup),
      0,
      "Tells Python to not clean up ExtraDataPtrMemory, If this is enabled. Ignore, if unsure." },
    { NULL, 0, 0, 0, NULL },
};


PyTypeObject spy_message_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0) MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME, /* tp_name */
    sizeof(spy_message_object),                                             /* tp_basicsize */
    0,                                                                      /* tp_itemsize */
    (destructor)spy_message_object_dealloc,                                 /* tp_dealloc */
    0,                                                                      /* tp_print */
    0,                                                                      /* tp_getattr */
    0,                                                                      /* tp_setattr */
    0,                                                                      /* tp_reserved */
    0,                                                                      /* tp_repr */
    0,                                                                      /* tp_as_number */
    0,                                                                      /* tp_as_sequence */
    0,                                                                      /* tp_as_mapping */
    0,                                                                      /* tp_hash  */
    0,                                                                      /* tp_call */
    0,                                                                      /* tp_str */
    spy_message_object_getattr,                                             /* tp_getattro */
    spy_message_object_setattr,                                             /* tp_setattro */
    0,                                                                      /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                               /* tp_flags */
    SPY_MESSAGE_OBJECT_NAME " object",                                      /* tp_doc */
    0,                                                                      /* tp_traverse */
    0,                                                                      /* tp_clear */
    0,                                                                      /* tp_richcompare */
    0,                                                                      /* tp_weaklistoffset */
    0,                                                                      /* tp_iter */
    0,                                                                      /* tp_iternext */
    0,                                                                      /* tp_methods */
    spy_message_object_members,                                             /* tp_members */
    0,                                                                      /* tp_getset */
    0,                                                                      /* tp_base */
    0,                                                                      /* tp_dict */
    0,                                                                      /* tp_descr_get */
    0,                                                                      /* tp_descr_set */
    0,                                                                      /* tp_dictoffset */
    (initproc)spy_message_object_alloc,                                     /* tp_init */
};

PyTypeObject spy_message_j1850_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0) MODULE_NAME "." SPY_MESSAGE_J1850_OBJECT_NAME, /* tp_name */
    sizeof(spy_message_j1850_object),                                             /* tp_basicsize */
    0,                                                                            /* tp_itemsize */
    (destructor)spy_message_object_dealloc,                                       /* tp_dealloc */
    0,                                                                            /* tp_print */
    0,                                                                            /* tp_getattr */
    0,                                                                            /* tp_setattr */
    0,                                                                            /* tp_reserved */
    0,                                                                            /* tp_repr */
    0,                                                                            /* tp_as_number */
    0,                                                                            /* tp_as_sequence */
    0,                                                                            /* tp_as_mapping */
    0,                                                                            /* tp_hash  */
    0,                                                                            /* tp_call */
    0,                                                                            /* tp_str */
    spy_message_object_getattr,                                                   /* tp_getattro */
    spy_message_object_setattr,                                                   /* tp_setattro */
    0,                                                                            /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                                     /* tp_flags */
    SPY_MESSAGE_J1850_OBJECT_NAME " object",                                      /* tp_doc */
    0,                                                                            /* tp_traverse */
    0,                                                                            /* tp_clear */
    0,                                                                            /* tp_richcompare */
    0,                                                                            /* tp_weaklistoffset */
    0,                                                                            /* tp_iter */
    0,                                                                            /* tp_iternext */
    0,                                                                            /* tp_methods */
    spy_message_j1850_object_members,                                             /* tp_members */
    0,                                                                            /* tp_getset */
    0,                                                                            /* tp_base */
    0,                                                                            /* tp_dict */
    0,                                                                            /* tp_descr_get */
    0,                                                                            /* tp_descr_set */
    0,                                                                            /* tp_dictoffset */
    (initproc)spy_message_object_alloc,                                           /* tp_init */
};

bool setup_spy_message_object(PyObject* module)
{
    // spy_message_object_type.ob_type = &PyType_Type;
    spy_message_object_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&spy_message_object_type) < 0) {
        return false;
    }
    Py_INCREF(&spy_message_object_type);
    PyModule_AddObject(module, SPY_MESSAGE_OBJECT_NAME, (PyObject*)&spy_message_object_type);

    spy_message_j1850_object_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&spy_message_j1850_object_type) < 0) {
        return false;
    }
    Py_INCREF(&spy_message_j1850_object_type);
    PyModule_AddObject(module, SPY_MESSAGE_J1850_OBJECT_NAME, (PyObject*)&spy_message_j1850_object_type);
    return true;
}