#ifndef _OBJECT_LIN_SETTINGS_H_
#define _OBJECT_LIN_SETTINGS_H_

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

#define LIN_SETTINGS_OBJECT_NAME "LinSettings"


typedef struct {
    PyObject_HEAD
    LIN_SETTINGS s;
} lin_settings_object;

static PyMemberDef lin_settings_object_members[] = {
    { "Baudrate", T_UINT, offsetof(lin_settings_object, s.Baudrate), 0, "" },
    { "spbrg", T_USHORT, offsetof(lin_settings_object, s.spbrg), 0, "" },
    { "brgh", T_USHORT, offsetof(lin_settings_object, s.brgh), 0, "" },
    { "MasterResistor", T_UBYTE, offsetof(lin_settings_object, s.MasterResistor), 0, "" },
    { "Mode", T_UBYTE, offsetof(lin_settings_object, s.Mode), 0, "" },
    { NULL, 0, 0, 0, 0 },
};

static int lin_settings_object_init(lin_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

extern PyTypeObject lin_settings_object_type;

// Copied from tupleobject.h
#define PyLinSettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyLinSettings_CheckExact(op) (Py_TYPE(op) == &lin_settings_object_type)

bool setup_lin_settings_object(PyObject* module);

#endif // _OBJECT_LIN_SETTINGS_H_
