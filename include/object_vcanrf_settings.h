#ifndef _OBJECT_VCANRF_SETTINGS_H_
#define _OBJECT_VCANRF_SETTINGS_H_

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
#include "object_lin_settings.h"
#include "object_iso9141_keyword2000_settings.h"

#define VCANRF_SETTINGS_OBJECT_NAME "VcanRFSettings"


typedef struct {
    PyObject_HEAD
    PyObject* can1;
    PyObject* can2;
    PyObject* can3;
    PyObject* can4;
    PyObject* lin1;
    PyObject* lin2;
    PyObject* iso9141_kwp;
    PyObject* iso9141_kwp2;
    SVCANRFSettings s;
} vcanrf_settings_object;

static PyMemberDef vcanrf_settings_object_members[] = {
    { "can1", T_OBJECT_EX, offsetof(vcanrf_settings_object, can1), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME " Object" },
    { "can2", T_OBJECT_EX, offsetof(vcanrf_settings_object, can2), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME " Object" },
    { "can3", T_OBJECT_EX, offsetof(vcanrf_settings_object, can3), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME " Object" },
    { "can4", T_OBJECT_EX, offsetof(vcanrf_settings_object, can4), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME " Object" },
    { "lin1", T_OBJECT_EX, offsetof(vcanrf_settings_object, lin1), 0, MODULE_NAME "." LIN_SETTINGS_OBJECT_NAME " Object" },
    { "lin2", T_OBJECT_EX, offsetof(vcanrf_settings_object, lin2), 0, MODULE_NAME "." LIN_SETTINGS_OBJECT_NAME " Object" },
    { "network_enables", T_USHORT, offsetof(vcanrf_settings_object, s.network_enables), 0, "" },
    { "network_enabled_on_boot", T_USHORT, offsetof(vcanrf_settings_object, s.network_enabled_on_boot), 0, "" },
    { "pwr_man_timeout", T_UINT, offsetof(vcanrf_settings_object, s.pwr_man_timeout), 0, "" },
    { "pwr_man_enable", T_USHORT, offsetof(vcanrf_settings_object, s.perf_en), 0, "0 - off, 1 - sleep enabled, 2- idle enabled (fast wakeup)" },
    { "misc_io_initial_ddr", T_USHORT, offsetof(vcanrf_settings_object, s.misc_io_initial_ddr), 0, "" },
    { "misc_io_initial_latch", T_USHORT, offsetof(vcanrf_settings_object, s.misc_io_initial_latch), 0, "" },
    { "misc_io_analog_enable", T_USHORT, offsetof(vcanrf_settings_object, s.misc_io_analog_enable), 0, "" },
    { "misc_io_report_period", T_USHORT, offsetof(vcanrf_settings_object, s.misc_io_report_period), 0, "" },
    { "misc_io_on_report_events", T_USHORT, offsetof(vcanrf_settings_object, s.misc_io_on_report_events), 0, "" },
    { "iso15765_separation_time_offset", T_USHORT, offsetof(vcanrf_settings_object, s.iso15765_separation_time_offset), 0, "" },
    { "iso9141_kwp_enable_reserved", T_USHORT, offsetof(vcanrf_settings_object, s.iso9141_kwp_enable_reserved), 0, "" },
    { "iso9141_kwp_settings", T_OBJECT_EX, offsetof(vcanrf_settings_object, iso9141_kwp), 0, MODULE_NAME "." ISO9141KEYWORD2000_SETTINGS_OBJECT_NAME " Object" },
    { "perf_en", T_USHORT, offsetof(vcanrf_settings_object, s.perf_en), 0, "" },
    { "iso_parity", T_USHORT, offsetof(vcanrf_settings_object, s.iso_parity), 0, "0 - no parity, 1 - event, 2 - odd" },
    { "iso_msg_termination", T_USHORT, offsetof(vcanrf_settings_object, s.iso_msg_termination), 0, "0 - use inner frame time, 1 - GME CIM-SCL" },
    { "iso_tester_pullup_enable", T_USHORT, offsetof(vcanrf_settings_object, s.iso_tester_pullup_enable), 0, "" },
    { "network_enables_2", T_USHORT, offsetof(vcanrf_settings_object, s.network_enables_2), 0, "" },
    { "iso9141_kwp_settings_2", T_OBJECT_EX, offsetof(vcanrf_settings_object, iso9141_kwp2), 0, MODULE_NAME "." ISO9141KEYWORD2000_SETTINGS_OBJECT_NAME " Object" },
    { "iso_parity_2", T_USHORT, offsetof(vcanrf_settings_object, s.iso_parity_2), 0, "0 - no parity, 1 - event, 2 - odd" },
    { "iso_msg_termination_2", T_USHORT, offsetof(vcanrf_settings_object, s.iso_msg_termination_2), 0, "0 - use inner frame time, 1 - GME CIM-SCL" },
    { "idle_wakeup_network_enables_1", T_USHORT, offsetof(vcanrf_settings_object, s.idle_wakeup_network_enables_1), 0, "" },
    { "idle_wakeup_network_enables_2", T_USHORT, offsetof(vcanrf_settings_object, s.idle_wakeup_network_enables_2), 0, "" },
    //{ "reservedZero", T_USHORT, offsetof(vcanrf_settings_object, s.reservedZero), 0, "" },
    { NULL, 0, 0, 0, 0 },
};

static int vcanrf_settings_object_init(vcanrf_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    // Initialize Can Objects
    self->can1 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can2 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can3 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can4 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    // Initialize LIN Objects
    self->lin1 = PyObject_CallObject((PyObject*)&lin_settings_object_type, NULL);
    self->lin2 = PyObject_CallObject((PyObject*)&lin_settings_object_type, NULL);
    // Initialize ISO9141Keyword2000 Objects
    self->iso9141_kwp = PyObject_CallObject((PyObject*)&iso9141keyword2000_settings_object_type, NULL);
    self->iso9141_kwp2 = PyObject_CallObject((PyObject*)&iso9141keyword2000_settings_object_type, NULL);
    return 0;
}

extern PyTypeObject vcanrf_settings_object_type;


// Copied from tupleobject.h
#define PyVcanRFSettings_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyVcanRFSettings_CheckExact(op) (Py_TYPE(op) == &vcanrf_settings_object_type)

bool setup_vcanrf_settings_object(PyObject* module);

#endif // _OBJECT_VCANRF_SETTINGS_H_
