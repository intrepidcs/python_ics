#ifndef _OBJECT_NEO_DEVICE_H_
#define _OBJECT_NEO_DEVICE_H_
// http://docs.python.org/3/extending/newtypes.html

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
#include "exceptions.h"
#include "dll.h"

// Linux specific fixes
#if !(defined(_WIN32) || defined(__WIN32__))

// __int64 is a msvc specific type
#include <inttypes.h>
#define __int64 int64_t

// __stdcall is a windows calling convention
#ifndef __stdcall
#define __stdcall

// Sleep is a windows.h specific function.
#include <unistd.h>
#define Sleep(i) sleep(i)

#endif
#endif

#define NEO_DEVICE_OBJECT_NAME "NeoDevice"

#if ICS_LEGACY_SUPPORT
#define ICS_HANDLE int
#define ICS_HANDLE_PY_TYPE T_INT
#else
#define ICS_HANDLE void*
#define ICS_HANDLE_PY_TYPE T_INT
#endif

typedef struct
{
    PyObject_HEAD NeoDevice dev;
    PyObject* name;
    char auto_cleanup;
    ICS_HANDLE handle;
    PyObject* dict;
} neo_device_object;

static PyMemberDef neo_device_object_members[] = {
    { "Name",
      T_OBJECT_EX,
      offsetof(neo_device_object, name),
      0,
      "String describing DeviceType, extension to Python api only." },
    { "DeviceType", T_UINT, offsetof(neo_device_object, dev.DeviceType), 0, "" },
    { "Handle", T_INT, offsetof(neo_device_object, dev.Handle), 0, "" },
    { "NumberOfClients", T_INT, offsetof(neo_device_object, dev.NumberOfClients), 0, "" },
    { "SerialNumber", T_INT, offsetof(neo_device_object, dev.SerialNumber), 0, "" },
    { "MaxAllowedClients", T_INT, offsetof(neo_device_object, dev.MaxAllowedClients), 0, "" },
    { "AutoHandleClose",
      T_BOOL,
      offsetof(neo_device_object, dev.MaxAllowedClients),
      0,
      "When " NEO_DEVICE_OBJECT_NAME " is freed the handle will automatically be closed, if true." },
    { "_Handle",
      ICS_HANDLE_PY_TYPE,
      offsetof(neo_device_object, handle),
      0,
      "This contains the handle returned from icsneoOpenDevice() API. If uncertain, don't use this." },
    { "IsOpen",
      T_BOOL,
      offsetof(neo_device_object, handle),
      0,
      "This contains the handle returned from icsneoOpenDevice() API. If uncertain, don't use this." },
    { NULL, 0, 0, 0, 0 },
};

static int neo_device_object_alloc(neo_device_object* self, PyObject* args, PyObject* kwds)
{
    self->name = PyUnicode_FromString("");
    self->auto_cleanup = 1;
    self->handle = 0;

    return 0;
}

static void neo_device_object_dealloc(neo_device_object* self)
{
    if (self->auto_cleanup && self->handle) {
        try {
            // Auto clean up device handle if NeoDevice object is going out of scope.
            ice::Library* lib = dll_get_library();
            if (lib) {
                ice::Function<int __stdcall(ICS_HANDLE, int*)> icsneoClosePort(lib, "icsneoClosePort");
                ice::Function<void __stdcall(ICS_HANDLE)> icsneoFreeObject(lib, "icsneoFreeObject");
                int error_count = 0;
                if (icsneoClosePort(self->handle, &error_count)) {
                    icsneoFreeObject(self->handle);
                }
            }
        } catch (...) {
            // return set_ics_exception(exception_runtime_error(), (char*)ex.what());
        }
    }
    Py_XDECREF(self->name);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* neo_device_object_getattr(PyObject* o, PyObject* attr_name)
{
    return PyObject_GenericGetAttr(o, attr_name);
}

static int neo_device_object_setattr(PyObject* o, PyObject* name, PyObject* value)
{
    return PyObject_GenericSetAttr(o, name, value);
}

// Shamelessly copied from base36enc
static PyObject* convert_to_base36(unsigned long value)
{
    char base36[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    /* log(2**64) / log(36) = 12.38 => max 13 char + '\0' */
    char buffer[100];
    unsigned int offset = sizeof(buffer);

    buffer[--offset] = '\0';
    do {
        buffer[--offset] = base36[value % 36];
    } while (value /= 36);
    return PyUnicode_FromString(&buffer[offset]);
}

static PyObject* neo_device_object_tp_repr(PyObject* o)
{
    // example output: <ics.NeoDevice neoVI FIRE2 CY1234>
    neo_device_object* nd = (neo_device_object*)(o);
    // Check range is A00000-ZZZZZZ
    PyObject* sn = NULL;
    uint32_t serial = (uint32_t)nd->dev.SerialNumber;
    if (604661760 <= serial && serial <= 2176782335)
        sn = convert_to_base36(serial);
    else
        sn = PyUnicode_FromFormat("%lu", nd->dev.SerialNumber);
    return PyUnicode_FromFormat("<" MODULE_NAME "." NEO_DEVICE_OBJECT_NAME " %U %U>", nd->name, sn);
}

extern PyTypeObject neo_device_object_type;

// Copied from tupleobject.h
#define PyNeoDevice_Check(op) PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyNeoDevice_CheckExact(op) (Py_TYPE(PyNeoDevice_GetNeoDevice(op)) == &neo_device_object_type)

#define PyNeoDevice_GetNeoDevice(nd) ((neo_device_object*)nd)
#define PyNeoDevice_GetName(nd) (PyNeoDevice_GetNeoDevice(nd)->name)
#define PyNeoDevice_GetSerialNumber(nd) (PyNeoDevice_GetNeoDevice(nd)->dev.SerialNumber)

#define PyNeoDevice_GetHandle(nd) (PyNeoDevice_GetNeoDevice(nd)->handle)
#define PyNeoDevice_SetHandle(nd, hndle) PyNeoDevice_GetNeoDevice(nd)->handle = hndle

bool setup_neo_device_object(PyObject* module);

#endif // _OBJECT_NEO_DEVICE_H_
