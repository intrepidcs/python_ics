/* No hardware access or external runtime dependencies. */
#ifdef _WIN32
#define API __declspec(dllexport) __stdcall
#else
#define API
#endif
int API icsneoOpenDevice(void* device, void** handle, unsigned char* networks,
                        int config, int options, void* extra, unsigned long reserved)
{
    *handle = (void*)0x1234;
    return 1;
}
int API icsneoClosePort(void* handle, int* errors) { *errors = 0; return 1; }
void API icsneoFreeObject(void* handle) {}
int API icsneoGetDeviceStatus(void* handle, void* status, void* size) { return 1; }
int API icsneoISO15765_ReceiveMessage(void* handle, unsigned int index, void* message) { return 1; }
