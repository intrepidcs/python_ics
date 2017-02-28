/**
 * Ice multiplatform dynamic library loader.
 *
 * @copyright 2011 David Rebbe
 */

#ifndef __ICE_FUNCTIONS_H__
#define __ICE_FUNCTIONS_H__

#include "ice_library.h"
#include "ice_exception.h"
#include <string>
#include <sstream>

namespace ice
{
template <class Signature>
class Function;
}

template <class Signature>
class ice::Function
{
    ice::Library* m_lib;

public:
    Function(ice::Library* library, std::string name)
        : m_name(name)
    {
        m_lib = library;
        if (library == NULL)
        {
            std::stringstream ss;
            ss << "Library is NULL, can't call function: '" <<
                  name << "'";
            throw ice::Exception(ss.str());
        }
#if (defined(_WIN32) || defined(__WIN32__))
        m_func = reinterpret_cast<Signature*>(
                    GetProcAddress(library->_library(), name.c_str()));
        if (m_func == NULL)
        {
            std::stringstream err;
            err << "Failed to Retrieve address of function '" << name <<
                   "': Windows Error #" << GetLastError() << " for library '" <<
                   library->name() << "'";
            throw ice::Exception(err.str());
        }
#else
        m_func = reinterpret_cast<Signature*>(
                    dlsym(library->_library(), name.c_str()));
        if (m_func == NULL)
        {
            std::stringstream err;
            err << "Failed to Retrieve address of function '" << name <<
                   "': " << dlerror() << " for library '" <<
                   library->name() << "'";
            throw ice::Exception(err.str());
        }
#endif
    }
    operator Signature *() const
    {
        if (m_func == NULL)
        {
            std::stringstream ss;
            ss << "Function address '" << m_name + "' isn't resolved for library: '" <<
                  m_lib->name() << "'";
            throw ice::Exception(ss.str());
        }
        return m_func;
    }
    bool isValid() const { return m_func != NULL; }
    std::string name() const { return m_name; }

protected:
    Signature* m_func;
    const std::string m_name;
};

#endif // ice_function.h
