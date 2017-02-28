#ifndef _OBJECT_CAN_SETTINGS_H_
#define _OBJECT_CAN_SETTINGS_H_

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

#define CAN_SETTINGS_OBJECT_NAME "CanSettings"


typedef struct {
    PyObject_HEAD
    CAN_SETTINGS s;
} can_settings_object;

static PyMemberDef can_settings_object_members[] = {
    { "Mode", T_UBYTE, offsetof(can_settings_object, s.Mode), 0, "CAN controller mode when the neoVI device goes online or runs a CoreMini script.\n\tNormal=0\n\tDisabled=1\n\tListen Only=3\n\tListen All=7\n" },
    { "SetBaudrate", T_UBYTE, offsetof(can_settings_object, s.SetBaudrate), 0, "The bit rate of a CAN channel can be selected one of two ways. It can either be selected from a list of common bit rates (SetBaudrate=1) or the user can specify the CAN timing parameters (SetBaudrate=0) " },
    { "Baudrate", T_UBYTE, offsetof(can_settings_object, s.Baudrate), 0, "The bit rate of a CAN channel can be selected from a list of common bit rates Write the correct enumeration for the desired bit rate and ensure that SetBaudrate is 1(auto)" },
    { "transceiver_mode", T_UBYTE, offsetof(can_settings_object, s.transceiver_mode), 0, "Currently Not used." },
    { "TqSeg1", T_UBYTE, offsetof(can_settings_object, s.TqSeg1), 0, "Phase 1 segment" },
    { "TqSeg2", T_UBYTE, offsetof(can_settings_object, s.TqSeg2), 0, "Phase 2 segment" },
    { "TqProp", T_UBYTE, offsetof(can_settings_object, s.TqProp), 0, "Propagation delay" },
    { "TqSync", T_UBYTE, offsetof(can_settings_object, s.TqSync), 0, "Syncro jump width" },
    { "BRP", T_USHORT, offsetof(can_settings_object, s.BRP), 0, "" },
    { "auto_baud", T_USHORT, offsetof(can_settings_object, s.auto_baud), 0, "Enables the auto bitrate feature. 1 = enable, 0 = disable." },
    { "innerFrameDelay25us", T_USHORT, offsetof(can_settings_object, s.innerFrameDelay25us), 0, "" },
    { NULL, 0, 0, 0, 0 },
};

static int can_settings_object_init(can_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

extern PyTypeObject can_settings_object_type;

// Copied from tupleobject.h
#define PyCanSettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyCanSettings_CheckExact(op) (Py_TYPE(op) == &can_settings_object_type)

bool setup_can_settings_object(PyObject* module);

#endif // _OBJECT_CAN_SETTINGS_H_