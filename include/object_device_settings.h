#ifndef _OBJECT_DEVICE_SETTINGS_H_
#define _OBJECT_DEVICE_SETTINGS_H_

#include <Python.h>
#include <structmember.h>
#if (defined(_WIN32) || defined(__WIN32__))
    #ifndef USING_STUDIO_8
          #define USING_STUDIO_8 1
    #endif
    #include <icsnVC40.h>
#else
    #include <icsnVC40.h>
#endif

#include "defines.h"
#include "object_fire_settings.h"
//#include "object_fire_vnet_settings.h"
#include "object_cyan_settings.h"
#include "object_vcan3_settings.h"
#include "object_rad_galaxy_settings.h"
#include "object_rad_star2_settings.h"
#include "object_vcan4_settings.h"
#include "object_vcan412_settings.h"
//#include "object_neoecu_avb_settings.h"
//#include "object_rad_supermoon_settings.h"
//#include "object_rad_moon2_settings.h"
#include "object_vividcan_settings.h"



#define DEVICE_SETTINGS_OBJECT_NAME "DeviceSettings"

#if PY_MAJOR_VERSION < 3
#define PyUnicode_CompareWithASCIIString(uni, string) strcmp(PyString_AsString(uni), string)
#endif


typedef struct {
    PyObject_HEAD
    PyObject* fire;
    PyObject* firevnet;
    PyObject* cyan;
    PyObject* vcan3;
    PyObject* radgalaxy;
    PyObject* radstar2;
    PyObject* vcan4;
    PyObject* vcan4_12;
    PyObject* vividcan;

    SDeviceSettings s;
} device_settings_object;

#if 0
typedef struct _SDeviceSettings
{
	EDeviceSettingsType DeviceSettingType;
	union {
		SFireSettings fire;
		SFireVnetSettings firevnet;
		SCyanSettings cyan;
		SVCAN3Settings vcan3;
		SRADGalaxySettings radgalaxy;
		SRADStar2Settings radstar2;
		SVCAN4Settings vcan4;
		VCAN412Settings vcan4_12;
		SVividCANSettings vividcan;
		//
		// add new settings type for each new settings structure in the union
		//
	} Settings;
} SDeviceSettings;

#endif
static PyMemberDef device_settings_object_members[] = {
    
    { "DeviceSettingType", T_ULONG, offsetof(device_settings_object, s.DeviceSettingType), 0, "" },
    { "fire", T_OBJECT_EX, offsetof(device_settings_object, fire), 0, MODULE_NAME "." FIRE_SETTINGS_OBJECT_NAME" Object" },
    //{ "firevnet", T_OBJECT_EX, offsetof(device_settings_object, firevnet), 0, MODULE_NAME "." FIREVNET_SETTINGS_OBJECT_NAME" Object" },
    { "cyan", T_OBJECT_EX, offsetof(device_settings_object, cyan), 0, MODULE_NAME "." CYAN_SETTINGS_OBJECT_NAME" Object" },
    { "vcan3", T_OBJECT_EX, offsetof(device_settings_object, vcan3), 0, MODULE_NAME "." VCAN3_SETTINGS_OBJECT_NAME" Object" },
    { "radgalaxy", T_OBJECT_EX, offsetof(device_settings_object, radgalaxy), 0, MODULE_NAME "." RADGALAXY_SETTINGS_OBJECT_NAME" Object" },
    { "radstar2", T_OBJECT_EX, offsetof(device_settings_object, radstar2), 0, MODULE_NAME "." RADSTAR2_SETTINGS_OBJECT_NAME" Object" },
    { "vcan4", T_OBJECT_EX, offsetof(device_settings_object, vcan4), 0, MODULE_NAME "." VCAN4_SETTINGS_OBJECT_NAME" Object" },
    { "vcan4_12", T_OBJECT_EX, offsetof(device_settings_object, vcan4_12), 0, MODULE_NAME "." VCAN412_SETTINGS_OBJECT_NAME" Object" },
    { "vividcan", T_OBJECT_EX, offsetof(device_settings_object, vividcan), 0, MODULE_NAME "." VIVIDCAN_SETTINGS_OBJECT_NAME" Object" },

    { NULL, 0, 0, 0, 0 },
};

static int device_settings_object_init(device_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));

    self->fire = PyObject_CallObject((PyObject*)&fire_settings_object_type, NULL);
    //self->firevnet = PyObject_CallObject((PyObject*)&firevnet_settings_object_type, NULL);
    self->cyan = PyObject_CallObject((PyObject*)&cyan_settings_object_type, NULL);
    self->vcan3 = PyObject_CallObject((PyObject*)&vcan3_settings_object_type, NULL);
    self->radgalaxy = PyObject_CallObject((PyObject*)&rad_galaxy_settings_object_type, NULL);
    self->radstar2 = PyObject_CallObject((PyObject*)&rad_star2_settings_object_type, NULL);
    self->vcan4 = PyObject_CallObject((PyObject*)&vcan4_settings_object_type, NULL);
    self->vcan4_12 = PyObject_CallObject((PyObject*)&vcan412_settings_object_type, NULL);
    self->vividcan = PyObject_CallObject((PyObject*)&vividcan_settings_object_type, NULL);

    return 0;
}



extern PyTypeObject device_settings_object_type;


// Copied from tupleobject.h
#define PyDeviceSettings_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyDeviceSettings_CheckExact(op) (Py_TYPE(op) == &device_settings_object_type)

bool setup_device_settings_object(PyObject* module);

void device_settings_object_update_from_struct(PyObject* settings);
void device_settings_object_update_from_objects(PyObject* settings);

#endif // _OBJECT_DEVICE_SETTINGS_H_
