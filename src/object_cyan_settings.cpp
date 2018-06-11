#include "object_cyan_settings.h"

PyTypeObject cyan_settings_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." CYAN_SETTINGS_OBJECT_NAME, /* tp_name */
    sizeof(cyan_settings_object), /* tp_basicsize */
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
    cyan_settings_object_getattr,   /* tp_getattro */
    cyan_settings_object_setattr,   /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,       /* tp_flags */
    CYAN_SETTINGS_OBJECT_NAME" object",      /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    cyan_settings_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)cyan_settings_object_init, /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};


bool setup_cyan_settings_object(PyObject* module)
{
    cyan_settings_object_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&cyan_settings_object_type) < 0) {
        return false;
    }
    Py_INCREF(&cyan_settings_object_type);
    PyModule_AddObject(module, CYAN_SETTINGS_OBJECT_NAME, (PyObject*)&cyan_settings_object_type);
    return true;
}

void cyan_settings_object_update_from_struct(PyObject* settings)
{
    assert(PyCyanSettings_CheckExact(settings));
    SCyanSettings* s = &((cyan_settings_object*)settings)->s;
    cyan_settings_object* s_obj = (cyan_settings_object*)settings;

    // Since CAN Structures are Python objects, we need to manually update them here.
    ((can_settings_object*)s_obj->can1)->s = s->can1;
    ((can_settings_object*)s_obj->can2)->s = s->can2;
    ((can_settings_object*)s_obj->can3)->s = s->can3;
    ((can_settings_object*)s_obj->can4)->s = s->can4;
    ((can_settings_object*)s_obj->can5)->s = s->can5;
    ((can_settings_object*)s_obj->can6)->s = s->can6;
    ((can_settings_object*)s_obj->can7)->s = s->can7;
    ((can_settings_object*)s_obj->can8)->s = s->can8;
    // Since CAN Structures are Python objects, we need to manually update them here.
    ((canfd_settings_object*)s_obj->canfd1)->s = s->canfd1;
    ((canfd_settings_object*)s_obj->canfd2)->s = s->canfd2;
    ((canfd_settings_object*)s_obj->canfd3)->s = s->canfd3;
    ((canfd_settings_object*)s_obj->canfd4)->s = s->canfd4;
    ((canfd_settings_object*)s_obj->canfd5)->s = s->canfd5;
    ((canfd_settings_object*)s_obj->canfd6)->s = s->canfd6;
    ((canfd_settings_object*)s_obj->canfd7)->s = s->canfd7;
    ((canfd_settings_object*)s_obj->canfd8)->s = s->canfd8;
    ((can_settings_object*)s_obj->lsftcan1)->s = s->lsftcan1;
    ((can_settings_object*)s_obj->lsftcan2)->s = s->lsftcan2;
    ((swcan_settings_object*)s_obj->swcan1)->s = s->swcan1;
    ((swcan_settings_object*)s_obj->swcan2)->s = s->swcan2;
    // Since LIN Structures are Python objects, we need to manually update them here.
    ((lin_settings_object*)s_obj->lin1)->s = s->lin1;
    ((lin_settings_object*)s_obj->lin2)->s = s->lin2;
    ((lin_settings_object*)s_obj->lin3)->s = s->lin3;
    ((lin_settings_object*)s_obj->lin4)->s = s->lin4;
    ((lin_settings_object*)s_obj->lin5)->s = s->lin5;
    ((lin_settings_object*)s_obj->lin6)->s = s->lin6;
    // Since TextAPI Structures are Python objects, we need to manually update them here.
    ((textapi_settings_object*)s_obj->textapi)->s = s->text_api;
    // Since ETHERNET_SETTINGS Structures are Python objects, we need to manually update them here.
    ((ethernet_settings_object*)s_obj->ethernet)->s = s->ethernet;
    // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s = s->iso9141_kwp_settings_1;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s = s->iso9141_kwp_settings_2;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s = s->iso9141_kwp_settings_3;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s = s->iso9141_kwp_settings_4;
    // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
    PyObject* tuple1 = PyTuple_New(s->iso9141_kwp_settings_1.init_step_count);
    for (int i=0; i < PyTuple_Size(tuple1); ++i) {
        iso9141keyword2000_init_steps_object* temp = 
            (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
        temp->s = s->iso9141_kwp_settings_1.init_steps[i];
        PyTuple_SetItem(tuple1, i, (PyObject*)temp);
    }
    Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps);
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple1;

    PyObject* tuple2 = PyTuple_New(s->iso9141_kwp_settings_2.init_step_count);
    for (int i=0; i < PyTuple_Size(tuple2); ++i) {
        iso9141keyword2000_init_steps_object* temp = 
            (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
        temp->s = s->iso9141_kwp_settings_2.init_steps[i];
        PyTuple_SetItem(tuple2, i, (PyObject*)temp);
    }
    Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->init_steps);
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple2;

    PyObject* tuple3 = PyTuple_New(s->iso9141_kwp_settings_3.init_step_count);
    for (int i=0; i < PyTuple_Size(tuple3); ++i) {
        iso9141keyword2000_init_steps_object* temp = 
            (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
        temp->s = s->iso9141_kwp_settings_3.init_steps[i];
        PyTuple_SetItem(tuple3, i, (PyObject*)temp);
    }
    Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->init_steps);
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple3;

    PyObject* tuple4 = PyTuple_New(s->iso9141_kwp_settings_4.init_step_count);
    for (int i=0; i < PyTuple_Size(tuple4); ++i) {
        iso9141keyword2000_init_steps_object* temp = 
            (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
        temp->s = s->iso9141_kwp_settings_4.init_steps[i];
        PyTuple_SetItem(tuple4, i, (PyObject*)temp);
    }
    Py_XDECREF(((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->init_steps);
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps = tuple4;
}

void cyan_settings_object_update_from_objects(PyObject* settings)
{
    assert(PyCyanSettings_CheckExact(settings));
    cyan_settings_object* s_obj = (cyan_settings_object*)settings;
    SCyanSettings* s = &s_obj->s;

    // Since CAN Structures are Python objects, we need to manually update them here.
    s->can1 = ((can_settings_object*)s_obj->can1)->s;
    s->can2 = ((can_settings_object*)s_obj->can2)->s;
    s->can3 = ((can_settings_object*)s_obj->can3)->s;
    s->can4 = ((can_settings_object*)s_obj->can4)->s;
    s->can5 = ((can_settings_object*)s_obj->can5)->s;
    s->can6 = ((can_settings_object*)s_obj->can6)->s;
    s->can7 = ((can_settings_object*)s_obj->can7)->s;
    s->can8 = ((can_settings_object*)s_obj->can8)->s;
    // Since CANFD Structures are Python objects, we need to manually update them here.
    s->canfd1 = ((canfd_settings_object*)s_obj->canfd1)->s;
    s->canfd2 = ((canfd_settings_object*)s_obj->canfd2)->s;
    s->canfd3 = ((canfd_settings_object*)s_obj->canfd3)->s;
    s->canfd4 = ((canfd_settings_object*)s_obj->canfd4)->s;
    s->canfd5 = ((canfd_settings_object*)s_obj->canfd5)->s;
    s->canfd6 = ((canfd_settings_object*)s_obj->canfd6)->s;
    s->canfd7 = ((canfd_settings_object*)s_obj->canfd7)->s;
    s->canfd8 = ((canfd_settings_object*)s_obj->canfd8)->s;

    s->lsftcan1 = ((can_settings_object*)s_obj->lsftcan1)->s;
    s->lsftcan2 = ((can_settings_object*)s_obj->lsftcan2)->s;
    s->swcan1 = ((swcan_settings_object*)s_obj->swcan1)->s;
    s->swcan2 = ((swcan_settings_object*)s_obj->swcan2)->s;
    // Since LIN Structures are Python objects, we need to manually update them here.
    s->lin1 = ((lin_settings_object*)s_obj->lin1)->s;
    s->lin2 = ((lin_settings_object*)s_obj->lin2)->s;
    s->lin3 = ((lin_settings_object*)s_obj->lin3)->s;
    s->lin4 = ((lin_settings_object*)s_obj->lin4)->s;
    s->lin5 = ((lin_settings_object*)s_obj->lin5)->s;
    s->lin6 = ((lin_settings_object*)s_obj->lin6)->s;
    // Since TextAPI Structures are Python objects, we need to manually update them here.
    ((textapi_settings_object*)s_obj->textapi)->s = s->text_api; 
    // Since ETHERNET_SETTINGS Structures are Python objects, we need to manually update them here.
    ((ethernet_settings_object*)s_obj->ethernet)->s = s->ethernet; 
    // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
    s->iso9141_kwp_settings_1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s;
    s->iso9141_kwp_settings_2 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s;
    s->iso9141_kwp_settings_3 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s;
    s->iso9141_kwp_settings_4 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s;
    // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
    PyObject* tuple1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s.init_step_count = PyTuple_Size(tuple1);
    for (int i=0; i < PyTuple_Size(tuple1); ++i) {
        iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple1, i);
        s->iso9141_kwp_settings_1.init_steps[i] = temp->s;
    }
    PyObject* tuple2 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->init_steps;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s.init_step_count = PyTuple_Size(tuple2);
    for (int i=0; i < PyTuple_Size(tuple2); ++i) {
        iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple2, i);
        s->iso9141_kwp_settings_2.init_steps[i] = temp->s;
    }
    PyObject* tuple3 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->init_steps;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s.init_step_count = PyTuple_Size(tuple3);
    for (int i=0; i < PyTuple_Size(tuple3); ++i) {
        iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple3, i);
        s->iso9141_kwp_settings_3.init_steps[i] = temp->s;
    }
    PyObject* tuple4 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->init_steps;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s.init_step_count = PyTuple_Size(tuple4);
    for (int i=0; i < PyTuple_Size(tuple4); ++i) {
        iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple4, i);
        s->iso9141_kwp_settings_4.init_steps[i] = temp->s;
    }
}