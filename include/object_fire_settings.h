#ifndef _OBJECT_FIRE_SETTINGS_H_
#define _OBJECT_FIRE_SETTINGS_H_

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
#include "object_swcan_settings.h"
#include "object_textapi_settings.h"
#include "object_uart_settings.h"
#include "object_iso9141_keyword2000_settings.h"

#define FIRE_SETTINGS_OBJECT_NAME "FireSettings"

typedef struct {
    PyObject_HEAD
    PyObject* can1;
    PyObject* can2;
    PyObject* can3;
    PyObject* can4;
    PyObject* swcan;
    PyObject* lsftcan;
    PyObject* lin1;
    PyObject* lin2;
    PyObject* lin3;
    PyObject* lin4;

    PyObject* iso9141_kw1;
    PyObject* iso9141_kw2;
    PyObject* iso9141_kw3;
    PyObject* iso9141_kw4;

    PyObject* uart;
    PyObject* uart2;
    PyObject* textapi;

    SFireSettings s;
} fire_settings_object;

static PyMemberDef fire_settings_object_members[] = {
    { "can1", T_OBJECT_EX, offsetof(fire_settings_object, can1), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can2", T_OBJECT_EX, offsetof(fire_settings_object, can2), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can3", T_OBJECT_EX, offsetof(fire_settings_object, can3), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can4", T_OBJECT_EX, offsetof(fire_settings_object, can4), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },

    { "lin1", T_OBJECT_EX, offsetof(fire_settings_object, lin1), 0, MODULE_NAME "." LIN_SETTINGS_OBJECT_NAME" Object" },
    { "lin2", T_OBJECT_EX, offsetof(fire_settings_object, lin2), 0, MODULE_NAME "." LIN_SETTINGS_OBJECT_NAME" Object" },
    { "lin3", T_OBJECT_EX, offsetof(fire_settings_object, lin3), 0, MODULE_NAME "." LIN_SETTINGS_OBJECT_NAME" Object" },
    { "lin4", T_OBJECT_EX, offsetof(fire_settings_object, lin4), 0, MODULE_NAME "." LIN_SETTINGS_OBJECT_NAME" Object" },

    { "swcan", T_OBJECT_EX, offsetof(fire_settings_object, swcan), 0, MODULE_NAME "." SWCAN_SETTINGS_OBJECT_NAME" Object" },
    { "lsft", T_OBJECT_EX, offsetof(fire_settings_object, lsftcan), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },

    { "cgi_enable_reserved", T_USHORT, offsetof(fire_settings_object, s.cgi_enable_reserved), 0, "" },
    { "cgi_baud", T_USHORT, offsetof(fire_settings_object, s.cgi_baud), 0, "" },
    { "cgi_tx_ifs_bit_times", T_USHORT, offsetof(fire_settings_object, s.cgi_tx_ifs_bit_times), 0, "" },
    { "cgi_rx_ifs_bit_times", T_USHORT, offsetof(fire_settings_object, s.cgi_rx_ifs_bit_times), 0, "" },
    { "cgi_chksum_enable", T_USHORT, offsetof(fire_settings_object, s.cgi_chksum_enable), 0, "" },
    { "network_enables", T_USHORT, offsetof(fire_settings_object, s.network_enables), 0, "" },
    { "network_enabled_on_boot", T_USHORT, offsetof(fire_settings_object, s.network_enabled_on_boot), 0, "" },
    { "pwm_man_timeout", T_UINT, offsetof(fire_settings_object, s.pwm_man_timeout), 0, "" },
    { "pwr_man_enable", T_USHORT, offsetof(fire_settings_object, s.pwr_man_enable), 0, "" },
    { "misc_io_initial_ddr", T_USHORT, offsetof(fire_settings_object, s.misc_io_initial_ddr), 0, "" },
    { "misc_io_initial_latch", T_USHORT, offsetof(fire_settings_object, s.misc_io_initial_latch), 0, "" },
    { "misc_io_analog_enable", T_USHORT, offsetof(fire_settings_object, s.misc_io_analog_enable), 0, "" },

    { "misc_io_report_period", T_USHORT, offsetof(fire_settings_object, s.misc_io_report_period), 0, "" },
    { "misc_io_on_report_events", T_USHORT, offsetof(fire_settings_object, s.misc_io_on_report_events), 0, "" },
    { "ain_sample_period", T_USHORT, offsetof(fire_settings_object, s.ain_sample_period), 0, "" },
    { "ain_threshold", T_USHORT, offsetof(fire_settings_object, s.ain_threshold), 0, "" },
    { "iso15765_separation_time_offset", T_USHORT, offsetof(fire_settings_object, s.iso15765_separation_time_offset), 0, "" },
    { "iso9141_kwp_enable_reserved", T_USHORT, offsetof(fire_settings_object, s.iso9141_kwp_enable_reserved), 0, "" },
    { "perf_en", T_USHORT, offsetof(fire_settings_object, s.perf_en), 0, "" },
    { "iso_parity", T_USHORT, offsetof(fire_settings_object, s.iso_parity), 0, "0 - no parity, 1 - event, 2 - odd" },
    { "iso_msg_termination", T_USHORT, offsetof(fire_settings_object, s.iso_msg_termination), 0, "0 - use inner frame time, 1 - GME CIM-SCL" },
    { "iso_tester_pullup_enable", T_USHORT, offsetof(fire_settings_object, s.iso_tester_pullup_enable), 0, "" },
    { "network_enables_2", T_USHORT, offsetof(fire_settings_object, s.network_enables_2), 0, "" },
    { "iso_parity_2", T_USHORT, offsetof(fire_settings_object, s.iso_parity_2), 0, "0 - no parity, 1 - event, 2 - odd" },
    { "iso_msg_termination_2", T_USHORT, offsetof(fire_settings_object, s.iso_msg_termination_2), 0, "0 - use inner frame time, 1 - GME CIM-SCL" },

    { "iso_parity_3", T_USHORT, offsetof(fire_settings_object, s.iso_parity_3), 0, "0 - no parity, 1 - event, 2 - odd" },
    { "iso_msg_termination_3", T_USHORT, offsetof(fire_settings_object, s.iso_msg_termination_3), 0, "0 - use inner frame time, 1 - GME CIM-SCL " },
    { "iso_parity_4", T_USHORT, offsetof(fire_settings_object, s.iso_parity_4), 0, "0 - no parity, 1 - event, 2 - odd" },
    { "iso_msg_termination_4", T_USHORT, offsetof(fire_settings_object, s.iso_msg_termination_4), 0, "0 - use inner frame time, 1 - GME CIM-SCL " },
    { "fast_init_network_enables_1", T_USHORT, offsetof(fire_settings_object, s.fast_init_network_enables_1), 0, "" },
    { "fast_init_network_enables_2", T_USHORT, offsetof(fire_settings_object, s.fast_init_network_enables_2), 0, "" },
#ifdef VNETBITS_FEATURE_ANDROID_MSGS
    { "vnetBits", T_USHORT, offsetof(fire_settings_object, s.vnetBits), 0, "" },
#endif //VNETBITS_FEATURE_ANDROID_MSGS
    { "iso9141_kwp_settings", T_OBJECT_EX, offsetof(fire_settings_object, iso9141_kw1), 0, ISO9141KEYWORD2000_SETTINGS_OBJECT_NAME" Object" },
    { "iso9141_kwp_settings_2", T_OBJECT_EX, offsetof(fire_settings_object, iso9141_kw2), 0, ISO9141KEYWORD2000_SETTINGS_OBJECT_NAME" Object" },
    { "iso9141_kwp_settings_3", T_OBJECT_EX, offsetof(fire_settings_object, iso9141_kw3), 0, ISO9141KEYWORD2000_SETTINGS_OBJECT_NAME" Object" },
    { "iso9141_kwp_settings_4", T_OBJECT_EX, offsetof(fire_settings_object, iso9141_kw4), 0, ISO9141KEYWORD2000_SETTINGS_OBJECT_NAME" Object" },

    { "uart", T_OBJECT_EX, offsetof(fire_settings_object, uart), 0, MODULE_NAME "." UART_SETTINGS_OBJECT_NAME " Object" },
    { "uart2", T_OBJECT_EX, offsetof(fire_settings_object, uart2), 0, MODULE_NAME "." UART_SETTINGS_OBJECT_NAME " Object" },
    { "text_api", T_OBJECT_EX, offsetof(fire_settings_object, textapi), 0, MODULE_NAME "." TEXTAPI_SETTINGS_OBJECT_NAME" Object" },
    // TODO: Not supported: SNeoMostGatewaySettings neoMostGateway;
    { NULL, 0, 0, 0, 0 },
};

static int fire_settings_object_init(fire_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    // Initialize Can Objects
    self->can1 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can2 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can3 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can4 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->lsftcan = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    // Initialize SWCan Objects
    self->swcan = PyObject_CallObject((PyObject*)&swcan_settings_object_type, NULL);
    // Initialize LIN Objects
    self->lin1 = PyObject_CallObject((PyObject*)&lin_settings_object_type, NULL);
    self->lin2 = PyObject_CallObject((PyObject*)&lin_settings_object_type, NULL);
    self->lin3 = PyObject_CallObject((PyObject*)&lin_settings_object_type, NULL);
    self->lin4 = PyObject_CallObject((PyObject*)&lin_settings_object_type, NULL);
    // Initialize ISO9141Keyword2000 Objects
    self->iso9141_kw1 = PyObject_CallObject((PyObject*)&iso9141keyword2000_settings_object_type, NULL);
    self->iso9141_kw2 = PyObject_CallObject((PyObject*)&iso9141keyword2000_settings_object_type, NULL);
    self->iso9141_kw3 = PyObject_CallObject((PyObject*)&iso9141keyword2000_settings_object_type, NULL);
    self->iso9141_kw4 = PyObject_CallObject((PyObject*)&iso9141keyword2000_settings_object_type, NULL);
    // Initialize Uart Objects
    PyObject* uarts[] = { self->uart, self->uart2 };
    self->uart = PyObject_CallObject((PyObject*)&uart_settings_object_type, NULL);
    self->uart2 = PyObject_CallObject((PyObject*)&uart_settings_object_type, NULL);
    // Initialize TextAPI Objects
    self->textapi = PyObject_CallObject((PyObject*)&textapi_settings_object_type, NULL);
    return 0;
}

extern PyTypeObject fire_settings_object_type;

// Copied from tupleobject.h
#define PyFireSettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyFireSettings_CheckExact(op) (Py_TYPE(op) == &fire_settings_object_type)

bool setup_fire_settings_object(PyObject* module);

#endif // _OBJECT_FIRE_SETTINGS_H_
