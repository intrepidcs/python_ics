#include "object_cm_iso157652_tx_message.h"

PyTypeObject cm_iso157652_tx_message_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." CM_ISO157652_TX_MESSAGE_OBJECT_NAME, /* tp_name */
    sizeof(cm_iso157652_tx_message_object), /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)0,             /* tp_dealloc */
    0,                         /* tp_print */
    0, /* tp_getattr */
    0, /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */ 
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    cm_iso157652_tx_message_object_getattr,   /* tp_getattro */
    cm_iso157652_tx_message_object_setattr,   /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,       /* tp_flags */
    CM_ISO157652_TX_MESSAGE_OBJECT_NAME" object",      /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    cm_iso157652_tx_message_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)cm_iso157652_tx_message_object_init, /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};

bool setup_cm_iso157652_tx_message_object(PyObject* module)
{
    cm_iso157652_tx_message_object_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&cm_iso157652_tx_message_object_type) < 0) {
        return false;
    }
    Py_INCREF(&cm_iso157652_tx_message_object_type);
    PyModule_AddObject(module, CM_ISO157652_TX_MESSAGE_OBJECT_NAME, (PyObject*)&cm_iso157652_tx_message_object_type);
    return true;
}