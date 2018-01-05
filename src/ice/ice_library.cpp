/**
 * Ice multiplatform dynamic library loader.
 *
 * @copyright 2011 David Rebbe
 */

#include "ice_library.h"
#include "ice_exception.h"
#include <sstream>

using namespace ice;

Library::Library(std::string name)
{
    m_name = name;
#if (defined(_WIN32) || defined(__WIN32__))
#ifdef UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, NULL, 0);
    if (len)
    {
        wchar_t* n = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, n, len);
        m_lib = LoadLibrary(n);
        delete[] n;
    } else m_lib = NULL;
#else
    m_lib = LoadLibrary(name.c_str());
#endif // UNICODE
    if (m_lib == NULL)
    {
        DWORD error = GetLastError();
        std::stringstream err;
        err << "Failed to open library: '" << name <<
               "' with error code: #" << error;
        throw Exception(err.str());
    }
#else
    m_lib = dlopen(name.c_str(), RTLD_NOW);
    if (m_lib == NULL)
    {
        std::stringstream err;
        err << "Failed to open library '" << name <<
               "': " << dlerror();
        throw Exception(err.str());
    }
#endif
}

Library::~Library()
{
    if (this->isLoaded())
    {
#if (defined(_WIN32) || defined(__WIN32__))
        FreeLibrary(m_lib);
#else
        dlclose(m_lib);
#endif
    }
}

bool Library::isLoaded() const
{
    return m_lib != NULL;
}

std::string Library::getPath(bool* okay)
{
    if (okay)
        *okay = false;
    if (!isLoaded())
        return m_name;
#if (defined(_WIN32) || defined(__WIN32__))
    TCHAR buffer[MAX_PATH] = {0};
    int len = GetModuleFileName(m_lib, buffer, MAX_PATH);
    if (!len)
    {
        DWORD error = GetLastError();
        std::stringstream err;
        err << "Failed to get Library path: '" << m_name <<
               "' with error code: #" << error;
        throw Exception(err.str());
    }
#ifdef UNICODE
    int length = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, NULL, 0, NULL, NULL);
    if (length)
    {
        char* temp = new char[MAX_PATH];
        WideCharToMultiByte(CP_UTF8, 0, buffer, -1, temp, length, NULL, NULL);
        std::stringstream ss;
        ss << temp;
        if (okay)
            *okay = true;
        return ss.str();
    }
#else
    std::stringstream ss;
    ss << buffer;
    if (okay)
        *okay = true;
    return ss.str();    
#endif // UNICODE
#else
    // Linux doesn't really have a way to get the library path from the handle and
    // its recommended to use absolute paths when loading with dlopen().
#endif // WIN32
    return m_name;
}

HMODULE const& Library::_library() const
{
    return m_lib;
}
