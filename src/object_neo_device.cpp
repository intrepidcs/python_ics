#include "object_neo_device.h"

PyTypeObject neo_device_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." NEO_DEVICE_OBJECT_NAME,             /* tp_name */
    sizeof(neo_device_object), /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)neo_device_object_dealloc,/* tp_dealloc */
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
    neo_device_object_getattr, /* tp_getattro */
    neo_device_object_setattr, /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /* tp_flags */
    NEO_DEVICE_OBJECT_NAME" object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    neo_device_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)neo_device_object_alloc, /* tp_init */
};

bool setup_neo_device_object(PyObject* module)
{
    //neo_device_object_type.ob_type = &PyType_Type;
    neo_device_object_type.tp_new = PyType_GenericNew;
    neo_device_object_type.tp_dictoffset = offsetof(neo_device_object, dict);
    if (PyType_Ready(&neo_device_object_type) < 0) {
        return false;
    }
    Py_INCREF(&neo_device_object_type);
    PyModule_AddObject(module, NEO_DEVICE_OBJECT_NAME, (PyObject*)&neo_device_object_type);
    return true;
}