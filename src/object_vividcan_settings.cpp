#include "object_vividcan_settings.h"

PyTypeObject vividcan_settings_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." VIVIDCAN_SETTINGS_OBJECT_NAME, /* tp_name */
    sizeof(vividcan_settings_object), /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)0,             /* tp_dealloc */
    0,                         /* tp_print */
    (getattrfunc)PyObject_GenericGetAttr, /* tp_getattr */
    (setattrfunc)PyObject_GenericSetAttr, /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */ 
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    vividcan_settings_object_getattr,   /* tp_getattro */
    vividcan_settings_object_setattr,   /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,       /* tp_flags */
    VIVIDCAN_SETTINGS_OBJECT_NAME" object",      /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    vividcan_settings_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)vividcan_settings_object_init, /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};

bool setup_vividcan_settings_object(PyObject* module)
{
    vividcan_settings_object_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&vividcan_settings_object_type) < 0) {
        return false;
    }
    Py_INCREF(&vividcan_settings_object_type);
    PyModule_AddObject(module, VIVIDCAN_SETTINGS_OBJECT_NAME, (PyObject*)&vividcan_settings_object_type);
    return true;
}

void vividcan_settings_object_update_from_struct(PyObject* settings)
{
    assert(PyVividCANSettings_CheckExact(settings));
    SVividCANSettings* s = &((vividcan_settings_object*)settings)->s;
    vividcan_settings_object* s_obj = (vividcan_settings_object*)settings;

    // Since CAN Structures are Python objects, we need to manually update them here.
    ((can_settings_object*)s_obj->can1)->s = s->can1;
    ((swcan_settings_object*)s_obj->swcan1)->s = s->swcan1;
    ((can_settings_object*)s_obj->lsftcan1)->s = s->lsftcan1;
}


void vividcan_settings_object_update_from_objects(PyObject* settings)
{
    assert(PyVividCANSettings_CheckExact(settings));
    vividcan_settings_object* s_obj = (vividcan_settings_object*)settings;
    SVividCANSettings* s = &s_obj->s;

    // Since CAN Structures are Python objects, we need to manually update them here.
    s->can1 = ((can_settings_object*)s_obj->can1)->s;
    s->swcan1 = ((swcan_settings_object*)s_obj->swcan1)->s;
    s->lsftcan1 = ((can_settings_object*)s_obj->lsftcan1)->s;
}