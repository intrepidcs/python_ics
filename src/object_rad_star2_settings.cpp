#include "object_rad_star2_settings.h"

PyTypeObject rad_star2_settings_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." RADSTAR2_SETTINGS_OBJECT_NAME, /* tp_name */
    sizeof(rad_star2_settings_object), /* tp_basicsize */
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
    RADSTAR2_SETTINGS_OBJECT_NAME" object",      /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    rad_star2_settings_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)rad_star2_settings_object_init, /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};


bool setup_rad_star2_settings_object(PyObject* module)
{
    rad_star2_settings_object_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&rad_star2_settings_object_type) < 0) {
        return false;
    }
    Py_INCREF(&rad_star2_settings_object_type);
    PyModule_AddObject(module, RADSTAR2_SETTINGS_OBJECT_NAME, (PyObject*)&rad_star2_settings_object_type);
    return true;
}

void rad_star2_settings_object_update_from_struct(PyObject* settings)
{
    assert(PyRADStar2Settings_CheckExact(settings));
    SRADStar2Settings* s = &((rad_star2_settings_object*)settings)->s;
    rad_star2_settings_object* s_obj = (rad_star2_settings_object*)settings;

    // Since ETH Structures are Python objects, we need to manually update them here.
    ((op_eth_general_settings_object*)s_obj->opEthGen)->s = s->opEthGen;
    ((op_eth_settings_object*)s_obj->opEth1)->s = s->opEth1;
    ((op_eth_settings_object*)s_obj->opEth2)->s = s->opEth2;
    // Since CAN Structures are Python objects, we need to manually update them here.
    ((can_settings_object*)s_obj->can1)->s = s->can1;
    ((can_settings_object*)s_obj->can2)->s = s->can2;
    // Since CAN Structures are Python objects, we need to manually update them here.
    ((canfd_settings_object*)s_obj->canfd1)->s = s->canfd1;
    ((canfd_settings_object*)s_obj->canfd2)->s = s->canfd2;
    // Since LIN Structures are Python objects, we need to manually update them here.
    ((lin_settings_object*)s_obj->lin1)->s = s->lin1;
    // Since TextAPI Structures are Python objects, we need to manually update them here.
    ((textapi_settings_object*)s_obj->textapi)->s = s->text_api;
    // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s = s->iso9141_kwp_settings_1;

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
    // Since Timesync Structures are Python objects, we need to manually update them here.
    ((timesync_settings_object*)s_obj->timesync)->s = s->timeSyncSettings;
    
}

void rad_star2_settings_object_update_from_objects(PyObject* settings)
{
    assert(PyRADStar2Settings_CheckExact(settings));
    rad_star2_settings_object* s_obj = (rad_star2_settings_object*)settings;
    SRADStar2Settings* s = &s_obj->s;

    // Since ETH Structures are Python objects, we need to manually update them here.
    s->opEthGen = ((op_eth_general_settings_object*)s_obj->opEthGen)->s;
    s->opEth1 = ((op_eth_settings_object*)s_obj->opEth1)->s;
    s->opEth2 = ((op_eth_settings_object*)s_obj->opEth2)->s;
    // Since CAN Structures are Python objects, we need to manually update them here.
    s->can1 = ((can_settings_object*)s_obj->can1)->s;
    s->can2 = ((can_settings_object*)s_obj->can2)->s;
    // Since CANFD Structures are Python objects, we need to manually update them here.
    s->canfd1 = ((canfd_settings_object*)s_obj->canfd1)->s;
    s->canfd2 = ((canfd_settings_object*)s_obj->canfd2)->s;
    // Since LIN Structures are Python objects, we need to manually update them here.
    s->lin1 = ((lin_settings_object*)s_obj->lin1)->s;
    // Since TextAPI Structures are Python objects, we need to manually update them here.
    ((textapi_settings_object*)s_obj->textapi)->s = s->text_api; 
    // Since ISO9141Keyword2000 Structures are Python objects, we need to manually update them here.
    s->iso9141_kwp_settings_1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s;
    // Since ISO9141Keyword2000 init Structures are Python tuple objects, we need to manually update them here.
    PyObject* tuple1 = ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->init_steps;
    ((iso9141keyword2000_settings_object*)s_obj->iso9141_kw1)->s.init_step_count = PyTuple_Size(tuple1);
    for (int i=0; i < PyTuple_Size(tuple1); ++i) {
        iso9141keyword2000_init_steps_object* temp = (iso9141keyword2000_init_steps_object*)PyTuple_GetItem(tuple1, i);
        s->iso9141_kwp_settings_1.init_steps[i] = temp->s;
    }
    // Since Timesync Structures are Python objects, we need to manually update them here.
    s->timeSyncSettings = ((timesync_settings_object*)s_obj->timesync)->s;
}