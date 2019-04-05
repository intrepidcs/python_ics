#include "object_device_settings.h"

PyTypeObject device_settings_object_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    MODULE_NAME "." DEVICE_SETTINGS_OBJECT_NAME, /* tp_name */
    sizeof(device_settings_object), /* tp_basicsize */
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
    DEVICE_SETTINGS_OBJECT_NAME" object",      /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    device_settings_object_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)device_settings_object_init, /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};

bool setup_device_settings_object(PyObject* module)
{
    device_settings_object_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&device_settings_object_type) < 0) {
        return false;
    }
    Py_INCREF(&device_settings_object_type);
    PyModule_AddObject(module, DEVICE_SETTINGS_OBJECT_NAME, (PyObject*)&device_settings_object_type);
    return true;
}

void device_settings_object_update_from_struct(PyObject* settings)
{
    assert(PyDeviceSettings_CheckExact(settings));
    device_settings_object* s_obj = (device_settings_object*)settings;
    SDeviceSettings* s = &s_obj->s;

    // Update fire object
    ((fire_settings_object*)s_obj->fire)->s = s->Settings.fire;
    fire_settings_object_update_from_struct(s_obj->fire);
#if 0
    // Update firevnet object
    ((firevnet_settings_object*)s_obj->firevnet)->s = s->Settings.firevnet;
    firevnet_settings_object_update_from_struct(s_obj->firevnet);
#endif
    // Update cyan object
    ((cyan_settings_object*)s_obj->cyan)->s = s->Settings.cyan;
    cyan_settings_object_update_from_struct(s_obj->cyan);
    // Update vcan3 object
    ((vcan3_settings_object*)s_obj->vcan3)->s = s->Settings.vcan3;
    vcan3_settings_object_update_from_struct(s_obj->vcan3);
    // Update radgalaxy object
    ((rad_galaxy_settings_object*)s_obj->radgalaxy)->s = s->Settings.radgalaxy;
    rad_galaxy_settings_object_update_from_struct(s_obj->radgalaxy);
#if VSPY3_BUILD_VERSION >= 803
    // Update radstar2 object
    ((rad_star2_settings_object*)s_obj->radstar2)->s = s->Settings.radstar2;
    rad_star2_settings_object_update_from_struct(s_obj->radstar2);
#endif
    // Update vcan4 object
    ((vcan4_settings_object*)s_obj->vcan4)->s = s->Settings.vcan4;
    vcan4_settings_object_update_from_struct(s_obj->vcan4);

    // Update vcan4_12 object
    ((vcan412_settings_object*)s_obj->vcan4_12)->s = s->Settings.vcan4_12;
    vcan412_settings_object_update_from_struct(s_obj->vcan4_12);
    // Update vividcan object
    ((vividcan_settings_object*)s_obj->vividcan)->s = s->Settings.vividcan;
    vividcan_settings_object_update_from_struct(s_obj->vividcan);

}
void device_settings_object_update_from_objects(PyObject* settings)
{
    assert(PyDeviceSettings_CheckExact(settings));
    device_settings_object* s_obj = (device_settings_object*)settings;
    SDeviceSettings* s = &s_obj->s;

    switch (s_obj->s.DeviceSettingType)
    {
    case DeviceFireSettingsType:
    {
        fire_settings_object_update_from_objects(s_obj->fire);
        s->Settings.fire = ((fire_settings_object*)s_obj->fire)->s;
        break;
    }
#if 0
    case DeviceFireVnetSettingsType:
    {
        firevnet_settings_object_update_from_objects(s_obj->firevnet);
        s->Settings.firevnet = ((firevnet_settings_object*)s_obj->firevnet)->s;
        break;
    }
#endif
    case DeviceFire2SettingsType:
    {
        cyan_settings_object_update_from_objects(s_obj->cyan);
        s->Settings.cyan = ((cyan_settings_object*)s_obj->cyan)->s;
        break;
    }
    case DeviceVCAN3SettingsType:
    {
        vcan3_settings_object_update_from_objects(s_obj->vcan3);
        s->Settings.vcan3 = ((vcan3_settings_object*)s_obj->vcan3)->s;
        break;
    }
    case DeviceRADGalaxySettingsType:
    {
        rad_galaxy_settings_object_update_from_objects(s_obj->radgalaxy);
        s->Settings.radgalaxy = ((rad_galaxy_settings_object*)s_obj->radgalaxy)->s;
        break;
    }
#if 0
    case DeviceRADStar2SettingsType:
    {
        rad_star2_settings_object_update_from_objects(s_obj->radstar2);
        s->Settings.radstar2 = ((rad_star2_settings_object*)s_obj->radstar2)->s;
        break;
    }
#endif
    case DeviceVCAN4SettingsType:
    {
        vcan4_settings_object_update_from_objects(s_obj->vcan4);
        s->Settings.vcan4 = ((vcan4_settings_object*)s_obj->vcan4)->s;
        break;
    }
    case DeviceVCAN412SettingsType:
    {
        vcan412_settings_object_update_from_objects(s_obj->vcan4_12);
        s->Settings.vcan4_12 = ((vcan412_settings_object*)s_obj->vcan4_12)->s;
        break;
    }
    case DeviceVividCANSettingsType:
    {
        vividcan_settings_object_update_from_objects(s_obj->vividcan);
        s->Settings.vividcan = ((vividcan_settings_object*)s_obj->vividcan)->s;
        break;
    }
    };
}
