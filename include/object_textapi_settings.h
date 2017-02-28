#ifndef _OBJECT_TEXTAPI_SETTINGS_H_
#define _OBJECT_TEXTAPI_SETTINGS_H_

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

#define TEXTAPI_SETTINGS_OBJECT_NAME "TextApiSettings"


typedef struct {
    PyObject_HEAD
    STextAPISettings s;
} textapi_settings_object;

static PyMemberDef textapi_settings_object_members[] = {
    { "can1_tx_id", T_UINT, offsetof(textapi_settings_object, s.can1_tx_id), 0, "Sets or Reads the Arbitration ID for Sending Text API commands" },
    { "can1_rx_id",T_UINT, offsetof(textapi_settings_object, s.can1_rx_id), 0, "Sets or Reads the Arbitration ID for Sending Receiving API commands" },
    { "can1_options", T_UINT, offsetof(textapi_settings_object, s.can1_options), 0, "Sets the length of the Arbitration ID's.  Set to 1 for Extended and 0 for Standard" },
    { "can2_tx_id", T_UINT, offsetof(textapi_settings_object, s.can2_tx_id), 0, "" },
    { "can2_rx_id", T_UINT, offsetof(textapi_settings_object, s.can2_rx_id), 0, "" },
    { "can2_options", T_UINT, offsetof(textapi_settings_object, s.can2_options), 0, "" },
    { "network_enables", T_UINT, offsetof(textapi_settings_object, s.network_enables), 0, "Bitfield telling which netowrk to support Text API." },
    { "can3_tx_id", T_UINT, offsetof(textapi_settings_object, s.can3_tx_id), 0, "" },
    { "can3_rx_id", T_UINT, offsetof(textapi_settings_object, s.can3_rx_id), 0, "" },
    { "can3_options", T_UINT, offsetof(textapi_settings_object, s.can3_options), 0, "" },
    { "can4_tx_id", T_UINT, offsetof(textapi_settings_object, s.can4_tx_id), 0, "" },
    { "can4_rx_id", T_UINT, offsetof(textapi_settings_object, s.can4_rx_id), 0, "" },
    { "can4_options", T_UINT, offsetof(textapi_settings_object, s.can4_options), 0, "" },
    /*
    { "Reserved0", T_INT, offsetof(textapi_settings_object, s.Reserved0), 0, "Not used" },
    { "Reserved1", T_INT, offsetof(textapi_settings_object, s.Reserved1), 0, "Not used" },
    { "Reserved2", T_INT, offsetof(textapi_settings_object, s.Reserved2), 0, "Not used" },
    { "Reserved3", T_INT, offsetof(textapi_settings_object, s.Reserved3), 0, "Not used" },
    { "Reserved4", T_INT, offsetof(textapi_settings_object, s.Reserved3), 0, "Not used" },
    */
    { NULL, 0, 0, 0, 0 },
};

static int textapi_settings_object_init(textapi_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

extern PyTypeObject textapi_settings_object_type;

// Copied from tupleobject.h
#define PyTextApiSettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyTextApiSettings_CheckExact(op) (Py_TYPE(op) == &textapi_settings_object_type)

bool setup_textapi_settings_object(PyObject* module);

#endif // _OBJECT_TEXTAPI_SETTINGS_H_
