#ifndef _OBJECT_CANFD_SETTINGS_H_
#define _OBJECT_CANFD_SETTINGS_H_

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

#define CANFD_SETTINGS_OBJECT_NAME "CanFdSettings"


typedef struct {
    PyObject_HEAD
    CANFD_SETTINGS s;
} canfd_settings_object;

static PyMemberDef canfd_settings_object_members[] = {
    { "FDMode", T_UBYTE, offsetof(canfd_settings_object, s.FDMode), 0, ""},
    { "FDBaudrate", T_UBYTE, offsetof(canfd_settings_object, s.FDBaudrate), 0, ""},
    { "FDTqSeg1", T_UBYTE, offsetof(canfd_settings_object, s.FDTqSeg1), 0, ""},
    { "FDTqSeg2", T_UBYTE, offsetof(canfd_settings_object, s.FDTqSeg2), 0, ""},
    { "FDTqProp", T_UBYTE, offsetof(canfd_settings_object, s.FDTqProp), 0, ""},
    { "FDTqSync", T_UBYTE, offsetof(canfd_settings_object, s.FDTqSync), 0, ""},
    { "FDBRP", T_USHORT, offsetof(canfd_settings_object, s.FDBRP), 0, ""},
    { NULL, 0, 0, 0, 0 },
};

static int canfd_settings_object_init(canfd_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

extern PyTypeObject canfd_settings_object_type;

// Copied from tupleobject.h
#define PyCanfdSettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyCanfdSettings_CheckExact(op) (Py_TYPE(op) == &canfd_settings_object_type)

bool setup_canfd_settings_object(PyObject* module);

#endif // _OBJECT_CANFD_SETTINGS_H_