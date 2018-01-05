#include "dll.h"
#include <cstring>

ice::Library* LIBRARY = NULL;
char ERROR_MESSAGE[512];

bool __initialize(char* name)
{
    if (dll_is_initialized()) {
        return true;
    }
    try
    {
        memset(ERROR_MESSAGE, '\0', sizeof(ERROR_MESSAGE)/sizeof(ERROR_MESSAGE[0]));
        if (!name)
        {
#if (defined(_WIN32) || defined(__WIN32__))
            LIBRARY = new ice::Library("icsneo40.dll");
#else
            LIBRARY = new ice::Library("libicsneoapi.so");
#endif
        }
        else 
        {
            LIBRARY = new ice::Library(name);
        }
    }
    catch (ice::Exception& ex)
    {
        strcpy(ERROR_MESSAGE, ex.whatString().c_str());
        return false;
    }
    return true;
}

bool dll_initialize(char* name)
{
    return __initialize(name);
}

bool dll_is_initialized(void)
{
    return LIBRARY != NULL;
}

void dll_uninitialize(void)
{
    if (!dll_is_initialized()) {
        return;
    }
    delete LIBRARY;
}

bool dll_reinitialize(char* name)
{
    dll_uninitialize();
    return dll_initialize(name);
}

char* dll_get_error(char* error_msg)
{
    strcpy(error_msg, ERROR_MESSAGE);
    return error_msg;
}

ice::Library* dll_get_library(void)
{
    dll_initialize();
    return LIBRARY;
}
