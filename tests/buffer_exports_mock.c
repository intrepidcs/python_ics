#include <stddef.h>

#ifdef _WIN32
#define API __declspec(dllexport)
#define CALL __stdcall
#else
#define API __attribute__((visibility("default")))
#define CALL
#endif

static int mode;
API void set_mode(int value) { mode = value; }

#ifndef OMIT_BUFFER_APIS
/* The loader requests undecorated API names, including on 32-bit Windows. */
#if defined(_WIN32) && defined(_M_IX86)
#pragma comment(linker, "/export:icsneoUartWrite=_icsneoUartWrite@24")
#pragma comment(linker, "/export:icsneoGenericAPISendCommand=_icsneoGenericAPISendCommand@28")
#pragma comment(linker, "/export:icsneoGetDeviceStatus=_icsneoGetDeviceStatus@12")
#pragma comment(linker, "/export:icsneoGetHWFirmwareInfo=_icsneoGetHWFirmwareInfo@8")
#pragma comment(linker, "/export:icsneoGetDLLFirmwareInfo=_icsneoGetDLLFirmwareInfo@8")
#pragma comment(linker, "/export:icsneoFlashAccessoryFirmware=_icsneoFlashAccessoryFirmware@12")
#endif

/* No hardware calls or file access: mode 1 fails, mode 2 reports a mismatch. */
API int CALL icsneoUartWrite(void* h, int port, const void* data, size_t len,
                           size_t* sent, unsigned char* flags)
{
    *sent = mode == 2 ? 0 : len;
    return mode != 1;
}
API int CALL icsneoGenericAPISendCommand(void* h, unsigned char a, unsigned char i,
                                      unsigned char f, void* data, unsigned int len,
                                      unsigned char* error)
{
    *error = 7;
    return mode != 1;
}
API int CALL icsneoGetDeviceStatus(void* h, void* status, size_t* size)
{
    if (mode == 2) *size = 0;
    return mode != 1;
}
API int CALL icsneoGetHWFirmwareInfo(void* h, void* info) { return mode != 1; }
API int CALL icsneoGetDLLFirmwareInfo(void* h, void* info) { return mode != 1; }
API int CALL icsneoFlashAccessoryFirmware(void* h, void* params, int* error)
{
    *error = mode == 2 ? 0 : 1;
    return mode != 1;
}
#endif
