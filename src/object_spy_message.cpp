#include "object_spy_message.h"

PyTypeObject spy_message_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." SPY_MESSAGE_OBJECT_NAME,             /* tp_name */
    sizeof(spy_message_object), /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)spy_message_object_dealloc,/* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    spy_message_object_getattr, /* tp_getattro */
    spy_message_object_setattr, /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /* tp_flags */
    SPY_MESSAGE_OBJECT_NAME" object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    spy_message_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)spy_message_object_alloc, /* tp_init */
};

PyTypeObject spy_message_j1850_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." SPY_MESSAGE_J1850_OBJECT_NAME,             /* tp_name */
    sizeof(spy_message_j1850_object), /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)spy_message_object_dealloc,/* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    spy_message_object_getattr, /* tp_getattro */
    spy_message_object_setattr, /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /* tp_flags */
    SPY_MESSAGE_J1850_OBJECT_NAME" object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    spy_message_j1850_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)spy_message_object_alloc, /* tp_init */
};

bool setup_spy_message_object(PyObject* module)
{
    //spy_message_object_type.ob_type = &PyType_Type;
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