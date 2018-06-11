#include "object_vcan412_settings.h"

PyTypeObject vcan412_settings_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." VCAN412_SETTINGS_OBJECT_NAME, /* tp_name */
    sizeof(vcan412_settings_object), /* tp_basicsize */
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
    vcan412_settings_object_getattr,   /* tp_getattro */
    vcan412_settings_object_setattr,   /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,       /* tp_flags */
    VCAN412_SETTINGS_OBJECT_NAME" object",      /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    vcan412_settings_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)vcan412_settings_object_init, /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};

bool setup_vcan412_settings_object(PyObject* module)
{
    vcan412_settings_object_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&vcan412_settings_object_type) < 0) {
        return false;
    }
    Py_INCREF(&vcan412_settings_object_type);
    PyModule_AddObject(module, VCAN412_SETTINGS_OBJECT_NAME, (PyObject*)&vcan412_settings_object_type);
    return true;
}

void vcan412_settings_object_update_from_struct(PyObject* settings)
{
    assert(PyVcan412Settings_CheckExact(settings));
    SVCAN412Settings* s = &((vcan412_settings_object*)settings)->s;
    vcan412_settings_object* s_obj = (vcan412_settings_object*)settings;

    // Since CAN Structures are Python objects, we need to manually update them here.
    ((can_settings_object*)s_obj->can1)->s = s->can1;
    ((can_settings_object*)s_obj->can2)->s = s->can2;
    ((canfd_settings_object*)s_obj->canfd1)->s = s->canfd1;
    ((canfd_settings_object*)s_obj->canfd2)->s = s->canfd2;

    // Since TextAPI Structures are Python objects, we need to manually update them here.
    ((textapi_settings_object*)s_obj->textapi)->s = s->text_api;
}

void vcan412_settings_object_update_from_objects(PyObject* settings)
{
    assert(PyVcan412Settings_CheckExact(settings));
    vcan412_settings_object* s_obj = (vcan412_settings_object*)settings;
    SVCAN412Settings* s = &s_obj->s;

    // Since CAN Structures are Python objects, we need to manually update them here.
    s->can1 = ((can_settings_object*)s_obj->can1)->s;
    s->can2 = ((can_settings_object*)s_obj->can2)->s;
    s->canfd1 = ((canfd_settings_object*)s_obj->canfd1)->s;
    s->canfd2 = ((canfd_settings_object*)s_obj->canfd2)->s;
    // Since textapi Structures are Python objects, we need to manually update them here.
    s->text_api = ((textapi_settings_object*)s_obj->textapi)->s;
}