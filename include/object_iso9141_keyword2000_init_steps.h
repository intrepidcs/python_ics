#ifndef _OBJECT_ISO9141KEYWORD2000_INIT_STEPS_H_
#define _OBJECT_ISO9141KEYWORD2000_INIT_STEPS_H_

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

#define ISO9141KEYWORD2000_INIT_STEPS_OBJECT_NAME "Iso9141Keyword2000InitSteps"


typedef struct {
    PyObject_HEAD
    ISO9141_KEYWORD2000__INIT_STEP s;
} iso9141keyword2000_init_steps_object;

static PyMemberDef iso9141keyword2000_init_steps_object_members[] = {

    { "time_500us", T_USHORT, offsetof(iso9141keyword2000_init_steps_object, s.time_500us), 0, "" },
    { "k", T_USHORT, offsetof(iso9141keyword2000_init_steps_object, s.k), 0, "" },
    { "l", T_USHORT, offsetof(iso9141keyword2000_init_steps_object, s.l), 0, "" },
    { NULL, 0, 0, 0, 0 },
};

static int iso9141keyword2000_init_steps_object_init(iso9141keyword2000_init_steps_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

extern PyTypeObject iso9141keyword2000_init_steps_object_type;

// Copied from tupleobject.h
#define PyIso9141Keyword2000InitSteps_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyIso9141Keyword2000InitSteps_CheckExact(op) (Py_TYPE(op) == &iso9141keyword2000_init_steps_object_type)

bool setup_iso9141keyword2000_init_steps_object(PyObject* module);

#endif // _OBJECT_ISO9141KEYWORD2000_INIT_STEPS_H_
