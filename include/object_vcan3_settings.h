#ifndef _OBJECT_VCAN3_SETTINGS_H_
#define _OBJECT_VCAN3_SETTINGS_H_

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
#include "object_can_settings.h"

#define VCAN3_SETTINGS_OBJECT_NAME "Vcan3Settings"


typedef struct {
    PyObject_HEAD
    PyObject* can1;
    PyObject* can2;
    SVCAN3Settings s;
} vcan3_settings_object;

static PyMemberDef vcan3_settings_object_members[] = {
    { "can1", T_OBJECT_EX, offsetof(vcan3_settings_object, can1), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME " Object" },
    { "can2", T_OBJECT_EX, offsetof(vcan3_settings_object, can1), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME " Object" },
    { "network_enables", T_USHORT, offsetof(vcan3_settings_object, s.network_enables), 0, "" },
    { "network_enabled_on_boot", T_USHORT, offsetof(vcan3_settings_object, s.network_enabled_on_boot), 0, "" },
    { "iso15765_separation_time_offset", T_USHORT, offsetof(vcan3_settings_object, s.iso15765_separation_time_offset), 0, "" },
    { "perf_en", T_USHORT, offsetof(vcan3_settings_object, s.perf_en), 0, "" },
    { "misc_io_initial_ddr", T_USHORT, offsetof(vcan3_settings_object, s.misc_io_initial_ddr), 0, "" },
    { "misc_io_initial_latch", T_USHORT, offsetof(vcan3_settings_object, s.misc_io_initial_latch), 0, "" },
    { "misc_io_report_period", T_USHORT, offsetof(vcan3_settings_object, s.misc_io_report_period), 0, "" },
    { "misc_io_on_report_events", T_USHORT, offsetof(vcan3_settings_object, s.misc_io_on_report_events), 0, "" },
    { NULL, 0, 0, 0, 0 },
};

static int vcan3_settings_object_init(vcan3_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));

    self->can1 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL); //(PyObject*)PyObject_New(can_settings_object, &can_settings_object_type);
    self->can2 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);

    return 0;
}

extern PyTypeObject vcan3_settings_object_type;


// Copied from tupleobject.h
#define PyVcan3Settings_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyVcan3Settings_CheckExact(op) (Py_TYPE(op) == &vcan3_settings_object_type)

bool setup_vcan3_settings_object(PyObject* module);

#endif // _OBJECT_VCAN3_SETTINGS_H_
