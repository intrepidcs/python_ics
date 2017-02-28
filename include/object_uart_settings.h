#ifndef _OBJECT_UART_SETTINGS_H_
#define _OBJECT_UART_SETTINGS_H_

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

#define UART_SETTINGS_OBJECT_NAME "UartSettings"


typedef struct {
    PyObject_HEAD
    UART_SETTINGS s;
} uart_settings_object;

static PyMemberDef uart_settings_object_members[] = {
    { "Baudrate", T_USHORT, offsetof(uart_settings_object, s.Baudrate), 0, "     Holds the baud rate for the UART Connection.  An example value could be 10417 or 9600" },
    { "spbrg", T_USHORT, offsetof(uart_settings_object, s.spbrg), 0, "" },
    { "brgh", T_USHORT, offsetof(uart_settings_object, s.brgh), 0, "" },
    { "parity", T_USHORT, offsetof(uart_settings_object, s.parity), 0, "Sets the Parity type. Valid values are None=0, Even=1, Odd=2" },
    { "stop_bits", T_USHORT, offsetof(uart_settings_object, s.stop_bits), 0, "Sets the number of stop bits to use. Valid values are One=1, Two=2" },
    { "flow_control", T_UBYTE, offsetof(uart_settings_object, s.flow_control), 0, "Set to 0 for no flow control and 1 for simple CTS RTS" },
    { "reserved_1", T_UBYTE, offsetof(uart_settings_object, s.reserved_1), 0, "" },
    { "bOptions", T_UINT, offsetof(uart_settings_object, s.bOptions), 0, "Bitfield containing UART Options Invert TX=1, Invert RX=2, Half Duplex=4" },
    { NULL, 0, 0, 0, 0 },
};

static PyObject* uart_settings_object_getattr(uart_settings_object* obj, char* name)
{
    if (strcmp(name, "Baudrate") == 0) {
        return PyLong_FromLong(obj->s.Baudrate);
    }
    if (strcmp(name, "spbrg") == 0) {
        return PyLong_FromLong(obj->s.spbrg);
    }
    if (strcmp(name, "brgh") == 0) {
        return PyLong_FromLong(obj->s.brgh);
    }
    if (strcmp(name, "stop_bits") == 0) {
        return PyLong_FromLong(obj->s.stop_bits);
    }
    if (strcmp(name, "flow_control") == 0) {
        return PyLong_FromLong(obj->s.flow_control);
    }
    if (strcmp(name, "reserved_1") == 0) {
        return PyLong_FromLong(obj->s.reserved_1);
    }
    if (strcmp(name, "bOptions") == 0) {
        return PyLong_FromLong(obj->s.bOptions);
    }
    PyErr_Format(PyExc_AttributeError,
        "'%.50s' object has no attribute '%.400s'",
        MODULE_NAME "." UART_SETTINGS_OBJECT_NAME, name);
    return NULL;
}

static int uart_settings_object_setattr(uart_settings_object* obj, char* name, PyObject* v)
{
    if (!v) {
        return 0;
    }
    unsigned long value = 0;
    if (PyLong_Check(v)) {
        // We have some values that are not compatible with int type.
        value = (unsigned long)PyLong_AsLong(v);
    }
    if (strcmp(name, "Baudrate") == 0) {
        obj->s.Baudrate = (unsigned short)value;
        return 0;
    }
    if (strcmp(name, "spbrg") == 0) {
        obj->s.spbrg = (unsigned short)value;
        return 0;
    }
    if (strcmp(name, "brgh") == 0) {
        obj->s.brgh = (unsigned short)value;
        return 0;
    }
    if (strcmp(name, "stop_bits") == 0) {
        obj->s.stop_bits = (unsigned short)value;
        return 0;
    }
    if (strcmp(name, "flow_control") == 0) {
        obj->s.flow_control = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "reserved_1") == 0) {
        obj->s.reserved_1 = (unsigned char)value;
        return 0;
    }
    if (strcmp(name, "bOptions") == 0) {
        obj->s.bOptions = (unsigned int)value;
        return 0;
    }
    PyErr_Format(PyExc_AttributeError,
        "'%.50s' object has no attribute '%.400s'",
        MODULE_NAME "." UART_SETTINGS_OBJECT_NAME, name);
    return -1;
}

static int uart_settings_object_init(uart_settings_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

extern PyTypeObject uart_settings_object_type;

// Copied from tupleobject.h
#define PyUartSettings_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BA)
#define PyUartSettings_CheckExact(op) (Py_TYPE(op) == &uart_settings_object_type)

bool setup_uart_settings_object(PyObject* module);

#endif // _OBJECT_UART_SETTINGS_H_
