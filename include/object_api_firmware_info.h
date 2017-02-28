#ifndef _OBJECT_API_FIRMWARE_INFO_H_
#define _OBJECT_API_FIRMWARE_INFO_H_

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

#define API_FIRMWARE_INFO_OBJECT_NAME "ApiFirmwareInfo"

typedef struct {
    PyObject_HEAD
    stAPIFirmwareInfo s;
} api_firmware_info_object;

static PyMemberDef api_firmware_info_object_members[] = {
    { "iType", T_INT, offsetof(api_firmware_info_object, s.iType), 0, "" },

    { "iMainFirmDateDay", T_INT, offsetof(api_firmware_info_object, s.iMainFirmDateDay), 0, "" },
    { "iMainFirmDateMonth", T_INT, offsetof(api_firmware_info_object, s.iMainFirmDateMonth), 0, "" },
    { "iMainFirmDateYear", T_INT, offsetof(api_firmware_info_object, s.iMainFirmDateYear), 0, "" },
    { "iMainFirmDateHour", T_INT, offsetof(api_firmware_info_object, s.iMainFirmDateHour), 0, "" },
    { "iMainFirmDateMin", T_INT, offsetof(api_firmware_info_object, s.iMainFirmDateMin), 0, "" },
    { "iMainFirmDateSecond", T_INT, offsetof(api_firmware_info_object, s.iMainFirmDateSecond), 0, "" },
    { "iMainFirmChkSum", T_INT, offsetof(api_firmware_info_object, s.iMainFirmChkSum), 0, "" },

    { "iAppMajor", T_UBYTE, offsetof(api_firmware_info_object, s.iAppMajor), 0, "" },
    { "iAppMinor", T_UBYTE, offsetof(api_firmware_info_object, s.iAppMinor), 0, "" },

    { "iManufactureDay", T_UBYTE, offsetof(api_firmware_info_object, s.iManufactureDay), 0, "" },
    { "iManufactureMonth", T_UBYTE, offsetof(api_firmware_info_object, s.iManufactureMonth), 0, "" },
    { "iManufactureYear", T_USHORT, offsetof(api_firmware_info_object, s.iManufactureYear), 0, "" },

    { "iBoardRevMajor", T_UBYTE, offsetof(api_firmware_info_object, s.iBoardRevMajor), 0, "" },
    { "iBoardRevMinor", T_UBYTE, offsetof(api_firmware_info_object, s.iBoardRevMinor), 0, "" },

    { "iBoardRevMajor", T_UBYTE, offsetof(api_firmware_info_object, s.iBoardRevMajor), 0, "" },
    { "iBoardRevMinor", T_UBYTE, offsetof(api_firmware_info_object, s.iBoardRevMinor), 0, "" },

    { "iBootLoaderVersionMajor", T_UBYTE, offsetof(api_firmware_info_object, s.iBootLoaderVersionMajor), 0, "" },
    { "iBootLoaderVersionMinor", T_UBYTE, offsetof(api_firmware_info_object, s.iBootLoaderVersionMinor), 0, "" },
    { "iMainVnetHWrevMajor", T_UBYTE, offsetof(api_firmware_info_object, s.iMainVnetHWrevMajor), 0, "" },
    { "iMainVnetHWrevMinor", T_UBYTE, offsetof(api_firmware_info_object, s.iMainVnetHWrevMinor), 0, "" },
    { "iMainVnetSRAMSize", T_UBYTE, offsetof(api_firmware_info_object, s.iMainVnetSRAMSize), 0, "" },

    { NULL, 0, 0, 0, 0 },
};

static int api_firmware_info_object_init(api_firmware_info_object* self, PyObject* args, PyObject* kwds)
{
    // Initialize all struct values to 0
    memset(&(self->s), 0, sizeof(self->s));
    return 0;
}

extern PyTypeObject api_firmware_info_object_type;

// Copied from tupleobject.h
#define PyApiFirmwareInfo_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BASETYPE)
#define PyApiFirmwareInfo_CheckExact(op) (Py_TYPE(op) == &api_firmware_info_object_type)
#define PyApiFirmwareInfo_GetApiFirmwareInfo(op) ((api_firmware_info_object*)op)

bool setup_api_firmware_info_object(PyObject* module);

#endif // _OBJECT_API_FIRMWARE_INFO_H_
