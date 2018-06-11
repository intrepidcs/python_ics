#include "object_fire_settings.h"

PyTypeObject fire_settings_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." FIRE_SETTINGS_OBJECT_NAME, /* tp_name */
    sizeof(fire_settings_object), /* tp_basicsize */
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
    PyObject_GenericGetAttr,   /* tp_getattro */
    PyObject_GenericSetAttr,   /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,       /* tp_flags */
    FIRE_SETTINGS_OBJECT_NAME" object",      /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    fire_settings_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)fire_settings_object_init, /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};


bool setup_fire_settings_object(PyObject* module)
{
    fire_settings_object_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&fire_settings_object_type) < 0) {
        return false;
    }
    Py_INCREF(&fire_settings_object_type);
    PyModule_AddObject(module, FIRE_SETTINGS_OBJECT_NAME, (PyObject*)&fire_settings_object_type);
    return true;
}

void fire_settings_object_update_from_struct(PyObject* settings)
{
    assert(PyFireSettings_CheckExact(settings));
    fire_settings_object* s_obj = (fire_settings_object*)settings;
    SFireSettings* s = &((fire_settings_object*)settings)->s;

    // Since CAN Structures are Python objects, we need to manually update them here.
    ((can_settings_object*)s_obj->can1)->s = s->can1;
    ((can_settings_object*)s_obj->can2)->s = s->can2;
    ((can_settings_object*)s_obj->can3)->s = s->can3;
    ((can_settings_object*)s_obj->can4)->s = s->can4;
    ((can_settings_object*)s_obj->lsftcan)->s = s->lsftcan;
    ((swcan_settings_object*)s_obj->swcan)->s = s->swcan;
    // Since LIN Structures are Python objects, we need to manually update them here.
    ((lin_settings_object*)s_obj->lin1)->s = s->lin1;
    ((lin_settings_object*)s_obj->lin2)->s = s->lin2;
    ((lin_settings_object*)s_obj->lin3)->s = s->lin3;
    ((lin_settings_object*)s_obj->lin4)->s = s->lin4;
    // Since UART Structures are Python objects, we need to manually update them here.
    ((uart_settings_object*)s_obj->uart)->s = s->uart;
    ((uart_settings_object*)s_obj->uart2)->s = s->uart2;
    // Since TextAPI Structures are Python objects, we need to manually update them here.
    ((textapi_settings_object*)s_obj->textapi)->s = s->text_api;
    // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s = s->iso9141_kwp_settings;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s = s->iso9141_kwp_settings_2;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s = s->iso9141_kwp_settings_3;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s = s->iso9141_kwp_settings_4;
    // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
    PyObject* tuple1 = PyTuple_New(s->iso9141_kwp_settings.init_step_count);
    for (int i=0; i < PyTuple_Size(tuple1); ++i) {
        iso9141keyword2000_init_steps_object* temp = 
            (iso9141keyword2000_init_steps_object*)PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
        temp->s = s->iso9141_kwp_settings.init_steps[i];
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

void fire_settings_object_update_from_objects(PyObject* settings)
{
    assert(PyFireSettings_CheckExact(settings));
    fire_settings_object* s_obj = (fire_settings_object*)settings;
    SFireSettings* s = &s_obj->s;

    // Since CAN Structures are Python objects, we need to manually update them here.
    s->can1 = ((can_settings_object*)s_obj->can1)->s;
    s->can2 = ((can_settings_object*)s_obj->can2)->s;
    s->can3 = ((can_settings_object*)s_obj->can3)->s;
    s->can4 = ((can_settings_object*)s_obj->can4)->s;
    s->lsftcan = ((can_settings_object*)s_obj->lsftcan)->s;
    s->swcan = ((swcan_settings_object*)s_obj->swcan)->s;
    // Since LIN Structures are Python objects, we need to manually update them here.
    s->lin1 = ((lin_settings_object*)s_obj->lin1)->s;
    s->lin2 = ((lin_settings_object*)s_obj->lin2)->s;
    s->lin3 = ((lin_settings_object*)s_obj->lin3)->s;
    s->lin4 = ((lin_settings_object*)s_obj->lin4)->s;
    // Since UART Structures are Python objects, we need to manually update them here.
    s->uart = ((uart_settings_object*)s_obj->uart)->s;
    s->uart2 = ((uart_settings_object*)s_obj->uart2)->s;
    // Since TextAPI Structures are Python objects, we need to manually update them here.
    ((textapi_settings_object*)s_obj->textapi)->s = s->text_api; 
    // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
    s->iso9141_kwp_settings = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s;
    s->iso9141_kwp_settings_2 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw2)->s;
    s->iso9141_kwp_settings_3 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw3)->s;
    s->iso9141_kwp_settings_4 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw4)->s;
    // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
    PyObject* tuple1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s.init_step_count = PyTuple_Size(tuple1);
    for (int i=0; i < PyTuple_Size(tuple1); ++i) {
        iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple1, i);
        s->iso9141_kwp_settings.init_steps[i] = temp->s;
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