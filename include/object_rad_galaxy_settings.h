#ifndef _OBJECT_RADGALAXY_SETTINGS_H_
#define _OBJECT_RADGALAXY_SETTINGS_H_

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
#include "object_canfd_settings.h"
#include "object_op_eth_general_settings.h"
#include "object_op_eth_settings.h"

#define RADGALAXY_SETTINGS_OBJECT_NAME "RadGalaxySettings"

typedef struct {
    PyObject_HEAD
    PyObject* opEthGen;
    PyObject* opEth1;
    PyObject* opEth2;
    PyObject* opEth3;
    PyObject* opEth4;
    PyObject* opEth5;
    PyObject* opEth6;
    PyObject* opEth7;
    PyObject* opEth8;
    PyObject* opEth9;
    PyObject* opEth10;
    PyObject* opEth11;
    PyObject* opEth12;
    PyObject* can1;
    PyObject* can2;
    PyObject* can3;
    PyObject* can4;
    PyObject* can5;
    PyObject* can6;
    PyObject* can7;
    PyObject* can8;
    PyObject* canfd1;
    PyObject* canfd2;
    PyObject* canfd3;
    PyObject* canfd4;
    PyObject* canfd5;
    PyObject* canfd6;
    PyObject* canfd7;
    PyObject* canfd8;
    PyObject* swcan1;
    PyObject* swcan2;
    PyObject* lin1;

    PyObject* iso9141_kw1;

    PyObject* textapi;

    SRADGalaxySettings s;
} rad_galaxy_settings_object;

static PyMemberDef rad_galaxy_settings_object_members[] = {
    { "opEthGen", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEthGen), 0, MODULE_NAME "." OP_ETH_GENERAL_SETTINGS_OBJECT_NAME" Object" },
    { "opEth1", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth1), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth2", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth2), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth3", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth3), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth4", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth4), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth5", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth5), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth6", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth6), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth7", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth7), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth8", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth8), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth9", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth9), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth10", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth10), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth11", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth11), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },
    { "opEth12", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, opEth12), 0, MODULE_NAME "." OP_ETH_SETTINGS_OBJECT_NAME" Object" },

    { "can1", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, can1), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can2", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, can2), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can3", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, can3), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can4", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, can4), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can5", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, can5), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can6", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, can6), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can7", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, can7), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },
    { "can8", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, can8), 0, MODULE_NAME "." CAN_SETTINGS_OBJECT_NAME" Object" },

    { "canfd1", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, canfd1), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd2", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, canfd2), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd3", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, canfd3), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd4", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, canfd4), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd5", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, canfd5), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd6", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, canfd6), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd7", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, canfd7), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },
    { "canfd8", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, canfd8), 0, MODULE_NAME "." CANFD_SETTINGS_OBJECT_NAME" Object" },

    { "lin1", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, lin1), 0, MODULE_NAME "." LIN_SETTINGS_OBJECT_NAME" Object" },

    { "swcan1", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, swcan1), 0, MODULE_NAME "." SWCAN_SETTINGS_OBJECT_NAME" Object" },
    { "swcan2", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, swcan2), 0, MODULE_NAME "." SWCAN_SETTINGS_OBJECT_NAME" Object" },

    { "network_enables", T_USHORT, offsetof(rad_galaxy_settings_object, s.network_enables), 0, "" },
    { "network_enables_2", T_USHORT, offsetof(rad_galaxy_settings_object, s.network_enables_2), 0, "" },
    { "pwr_man_enable", T_USHORT, offsetof(rad_galaxy_settings_object, s.pwr_man_enable), 0, "" },
    { "pwr_man_timeout", T_UINT, offsetof(rad_galaxy_settings_object, s.pwr_man_timeout), 0, "" },
    { "network_enabled_on_boot", T_USHORT, offsetof(rad_galaxy_settings_object, s.network_enabled_on_boot), 0, "" },
    { "misc_io_initial_ddr", T_USHORT, offsetof(rad_galaxy_settings_object, s.misc_io_initial_ddr), 0, "" },
    { "misc_io_initial_latch", T_USHORT, offsetof(rad_galaxy_settings_object, s.misc_io_initial_latch), 0, "" },
    { "misc_io_analog_enable", T_USHORT, offsetof(rad_galaxy_settings_object, s.misc_io_analog_enable), 0, "" },
    { "misc_io_report_period", T_USHORT, offsetof(rad_galaxy_settings_object, s.misc_io_report_period), 0, "" },
    { "misc_io_on_report_events", T_USHORT, offsetof(rad_galaxy_settings_object, s.misc_io_on_report_events), 0, "" },
    { "ain_sample_period", T_USHORT, offsetof(rad_galaxy_settings_object, s.ain_sample_period), 0, "" },
    { "ain_threshold", T_USHORT, offsetof(rad_galaxy_settings_object, s.ain_threshold), 0, "" },
    { "iso15765_separation_time_offset", T_USHORT, offsetof(rad_galaxy_settings_object, s.iso15765_separation_time_offset), 0, "" },
    { "perf_en", T_USHORT, offsetof(rad_galaxy_settings_object, s.perf_en), 0, "" },
    { "network_enables_2", T_USHORT, offsetof(rad_galaxy_settings_object, s.network_enables_2), 0, "" },

    { "iso_parity_1", T_USHORT, offsetof(rad_galaxy_settings_object, s.iso_parity_1), 0, "0 - no parity, 1 - event, 2 - odd" },

    { "iso_msg_termination_1", T_USHORT, offsetof(rad_galaxy_settings_object, s.iso_msg_termination_1), 0, "0 - use inner frame time, 1 - GME CIM-SCL" },

    { "idle_wakeup_network_enables_1", T_USHORT, offsetof(rad_galaxy_settings_object, s.idle_wakeup_network_enables_1), 0, "" },
    { "idle_wakeup_network_enables_2", T_USHORT, offsetof(rad_galaxy_settings_object, s.idle_wakeup_network_enables_2), 0, "" },
    { "idle_wakeup_network_enables_3", T_USHORT, offsetof(rad_galaxy_settings_object, s.idle_wakeup_network_enables_3), 0, "" },

    { "iso9141_kwp_settings_1", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, iso9141_kw1), 0, ISO9141KEYWORD2000_SETTINGS_OBJECT_NAME" Object" },

    { "network_enables_3", T_USHORT, offsetof(rad_galaxy_settings_object, s.network_enables_3), 0, "" },
    { "idle_wakeup_network_enables_3", T_USHORT, offsetof(rad_galaxy_settings_object, s.idle_wakeup_network_enables_3), 0, "" },
    { "can_switch_mode", T_USHORT, offsetof(rad_galaxy_settings_object, s.can_switch_mode), 0, "" },

    { "text_api", T_OBJECT_EX, offsetof(rad_galaxy_settings_object, textapi), 0, MODULE_NAME "." TEXTAPI_SETTINGS_OBJECT_NAME" Object" },
    
    { NULL, 0, 0, 0, 0 },
};

static int rad_galaxy_settings_object_init(rad_galaxy_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    // Initialize Ethernet Objects
    self->opEthGen = PyObject_CallObject((PyObject*)&op_eth_general_settings_object_type, NULL);
    self->opEth1 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth2 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth3 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth4 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth5 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth6 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth7 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth8 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth9 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth10 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth11 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    self->opEth12 = PyObject_CallObject((PyObject*)&op_eth_settings_object_type, NULL);
    // Initialize Can Objects
    self->can1 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can2 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can3 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can4 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can5 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can6 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can7 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->can8 = PyObject_CallObject((PyObject*)&can_settings_object_type, NULL);
    self->canfd1 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd2 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd3 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd4 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd5 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd6 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd7 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    self->canfd8 = PyObject_CallObject((PyObject*)&canfd_settings_object_type, NULL);
    // Initialize SWCan Objects
    self->swcan1 = PyObject_CallObject((PyObject*)&swcan_settings_object_type, NULL);
    self->swcan2 = PyObject_CallObject((PyObject*)&swcan_settings_object_type, NULL);
    // Initialize LIN Objects
    self->lin1 = PyObject_CallObject((PyObject*)&lin_settings_object_type, NULL);
    // Initialize ISO9141Keyword2000 Objects
    self->iso9141_kw1 = PyObject_CallObject((PyObject*)&iso9141keyword2000_settings_object_type, NULL);
    // Initialize TextAPI Objects
    self->textapi = PyObject_CallObject((PyObject*)&textapi_settings_object_type, NULL);
    return 0;
}

extern PyTypeObject rad_galaxy_settings_object_type;

// Copied from tupleobject.h
#define PyRADGalaxySettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyRADGalaxySettings_CheckExact(op) (Py_TYPE(op) == &rad_galaxy_settings_object_type)

bool setup_rad_galaxy_settings_object(PyObject* module);

#endif // _OBJECT_RADGALAXY_SETTINGS_H_
