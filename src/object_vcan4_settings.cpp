#include "object_vcan4_settings.h"

PyTypeObject vcan4_settings_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." VCAN4_SETTINGS_OBJECT_NAME, /* tp_name */
    sizeof(vcan4_settings_object), /* tp_basicsize */
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
    vcan4_settings_object_getattr,   /* tp_getattro */
    vcan4_settings_object_setattr,   /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,       /* tp_flags */
    VCAN4_SETTINGS_OBJECT_NAME" object",      /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    vcan4_settings_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)vcan4_settings_object_init, /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};

bool setup_vcan4_settings_object(PyObject* module)
{
    vcan4_settings_object_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&vcan4_settings_object_type) < 0) {
        return false;
    }
    Py_INCREF(&vcan4_settings_object_type);
    PyModule_AddObject(module, VCAN4_SETTINGS_OBJECT_NAME, (PyObject*)&vcan4_settings_object_type);
    return true;
}

void vcan4_settings_object_update_from_struct(PyObject* settings)
{
    assert(PyVcan4Settings_CheckExact(settings));
    SVCAN4Settings* s = &((vcan4_settings_object*)settings)->s;
    vcan4_settings_object* s_obj = (vcan4_settings_object*)settings;

    // Since CAN Structures are Python objects, we need to manually update them here.
    ((can_settings_object*)s_obj->can1)->s = s->can1;
    ((can_settings_object*)s_obj->can2)->s = s->can2;
    ((can_settings_object*)s_obj->can3)->s = s->can3;
    ((can_settings_object*)s_obj->can4)->s = s->can4;
    ((canfd_settings_object*)s_obj->canfd1)->s = s->canfd1;
    ((canfd_settings_object*)s_obj->canfd2)->s = s->canfd2;
    ((canfd_settings_object*)s_obj->canfd3)->s = s->canfd3;
    ((canfd_settings_object*)s_obj->canfd4)->s = s->canfd4;
    // Since LIN Structures are Python objects, we need to manually update them here.
    ((lin_settings_object*)s_obj->lin1)->s = s->lin1;
    // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
    PyObject* tuple1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s.init_step_count = PyTuple_Size(tuple1);
    for (int i=0; i < PyTuple_Size(tuple1); ++i) {
        iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple1, i);
        s->iso9141_kwp_settings_1.init_steps[i] = temp->s;
    }
    // Since ETHERNET_SETTINGS Structures are Python objects, we need to manually update them here.
    ((ethernet_settings_object*)s_obj->ethernet)->s = s->ethernet;
    // Since TextAPI Structures are Python objects, we need to manually update them here.
    ((textapi_settings_object*)s_obj->textapi)->s = s->text_api;
}

void vcan4_settings_object_update_from_objects(PyObject* settings)
{
    assert(PyVcan4Settings_CheckExact(settings));
    vcan4_settings_object* s_obj = (vcan4_settings_object*)settings;
    SVCAN4Settings* s = &s_obj->s;

    // Since CAN Structures are Python objects, we need to manually update them here.
    s->can1 = ((can_settings_object*)s_obj->can1)->s;
    s->can2 = ((can_settings_object*)s_obj->can2)->s;
    s->can3 = ((can_settings_object*)s_obj->can3)->s;
    s->can4 = ((can_settings_object*)s_obj->can4)->s;
    s->canfd1 = ((canfd_settings_object*)s_obj->canfd1)->s;
    s->canfd2 = ((canfd_settings_object*)s_obj->canfd2)->s;
    s->canfd3 = ((canfd_settings_object*)s_obj->canfd3)->s;
    s->canfd4 = ((canfd_settings_object*)s_obj->canfd4)->s;
    // Since LIN Structures are Python objects, we need to manually update them here.
    s->lin1 = ((lin_settings_object*)s_obj->lin1)->s;
    // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
    s->iso9141_kwp_settings_1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s;
    // Since ETHERNET_SETTINGS Structures are Python objects, we need to manually update them here.
    s->ethernet = ((ethernet_settings_object*)s_obj->ethernet)->s; 
    // Since TextAPI Structures are Python objects, we need to manually update them here.
    s->text_api = ((textapi_settings_object*)s_obj->textapi)->s;
}