#ifndef _OBJECT_ISO9141KEYWORD2000_SETTINGS_H_
#define _OBJECT_ISO9141KEYWORD2000_SETTINGS_H_

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

#include "object_iso9141_keyword2000_init_steps.h"
#include "object_spy_message.h"

#define ISO9141KEYWORD2000_SETTINGS_OBJECT_NAME "Iso9141Keyword2000Settings"


typedef struct {
    PyObject_HEAD
    ISO9141_KEYWORD2000_SETTINGS s;
    PyObject* init_steps;
} iso9141keyword2000_settings_object;

static PyMemberDef iso9141keyword2000_settings_object_members[] = {
    { "Baudrate", T_UINT, offsetof(iso9141keyword2000_settings_object, s.Baudrate), 0, "" },
    { "spbrg", T_USHORT, offsetof(iso9141keyword2000_settings_object, s.spbrg), 0, "" },
    { "brgh", T_USHORT, offsetof(iso9141keyword2000_settings_object, s.brgh), 0, "" },
    { "init_steps", T_OBJECT_EX, offsetof(iso9141keyword2000_settings_object, init_steps), 0, "Tuple of " ISO9141KEYWORD2000_INIT_STEPS_OBJECT_NAME },
    //{ "init_step_count", T_UBYTE, offsetof(iso9141keyword2000_settings_object, s.init_step_count), 0, "Should be set to len(init_steps)" },
    { "p2_500us", T_USHORT, offsetof(iso9141keyword2000_settings_object, s.p2_500us), 0, "" },
    { "p3_500us", T_USHORT, offsetof(iso9141keyword2000_settings_object, s.p3_500us), 0, "" },
    { "p4_500us", T_USHORT, offsetof(iso9141keyword2000_settings_object, s.p4_500us), 0, "" },
    { "chksum_enabled", T_USHORT, offsetof(iso9141keyword2000_settings_object, s.chksum_enabled), 0, "" },
    { NULL, 0, 0, 0, 0 },
};

static int iso9141keyword2000_settings_object_init(PyObject* s, PyObject* args, PyObject* kwds)
{
    iso9141keyword2000_settings_object* self = (iso9141keyword2000_settings_object*)s;
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    // Initialize Tuple so its not null
    self->init_steps = PyTuple_New(0);
    /* We don't want to initalize this to anything...
    size_t size = sizeof(self->s.init_steps)/sizeof(self->s.init_steps[0]);
    self->init_steps = PyTuple_New(size);
    for (int i=0; i < PyTuple_Size(self->init_steps); ++i) {
        PyObject* obj = PyObject_CallObject((PyObject*)&iso9141keyword2000_init_steps_object_type, NULL);
        if (!obj) {
            continue;
        }
        PyTuple_SET_ITEM(self->init_steps, i, obj);
    }
    */
    return 0;
}

static PyObject* iso9141keyword2000_settings_object_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    iso9141keyword2000_settings_object* self;
    self = (iso9141keyword2000_settings_object*)type->tp_alloc(type, 0);
    if (!self) {
        return (PyObject*)self;
    }
    
    return (PyObject*)self;
}

extern PyTypeObject iso9141keyword2000_settings_object_type;


// Copied from tupleobject.h
#define PyIso9141Keyword2000Settings_Check(op) \
    PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyIso9141Keyword2000Settings_CheckExact(op) (Py_TYPE(op) == &iso9141keyword2000_settings_object_type)

bool setup_iso9141keyword2000_settings_object(PyObject* module);

#endif // _OBJECT_ISO9141KEYWORD2000_SETTINGS_H_
