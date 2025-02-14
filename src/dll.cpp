#include "dll.h"
#include <ice/ice.h>
#include <cstring>

#pragma warning(push)
#pragma warning(disable : 4996) // warning C4996: 'strcpy': This function or variable may be unsafe.



bool dll_reinitialize(char* name)
{
    auto& mgr = ice::LibraryManager::instance();
    mgr.add("ics", name, false, true);

    return mgr.exists("ics");
}

char* dll_get_error(char* error_msg)
{
    auto& mgr = ice::LibraryManager::instance();
    if (!mgr.exists("ics")) {
        strcpy(error_msg, "Critical Error: Library isn't loaded!");
        return error_msg;
    }
    strcpy(error_msg, mgr["ics"]->getLastError().c_str());
    return error_msg;
}

ice::Library* dll_get_library(void)
{
    auto& mgr = ice::LibraryManager::instance();
    if (!mgr.exists("ics")) {
        return nullptr;
    }
    return mgr["ics"];
}

#pragma warning(pop)