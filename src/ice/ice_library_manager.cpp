#include "ice_library_manager.h"
#include <sstream>
#include "ice_exception.h"

using namespace ice;

LibraryManager::LibraryManager()
{
    
}

LibraryManager::~LibraryManager()
{
    Libraries::iterator iter = m_libs.begin();
    for (; iter != m_libs.end(); iter = m_libs.begin())
        this->remove(iter->first);
}

void LibraryManager::add(std::string name, std::string path)
{
    m_libs[name] = new ice::Library(path);
}

void LibraryManager::remove(std::string name)
{
    if (m_libs.find(name) == m_libs.end())
        return;
    ice::Library* lib = m_libs[name];
    delete lib;
    lib = NULL;
    m_libs.erase(name);
}

std::vector<std::string> LibraryManager::getLibraryNames() const
{
    std::vector<std::string> names;
    names.reserve(m_libs.size());
    Libraries::const_iterator iter = m_libs.begin();
    for (; iter != m_libs.end(); ++iter)
        names.push_back(iter->first);
    return names;
}

ice::Library& LibraryManager::operator[](std::string name)
{
    if (m_libs.find(name) == m_libs.end())
    {
        std::stringstream ss;
        ss << "LibraryManager Failed to retreive '" << name << "' From loaded library list!";
        throw Exception(ss.str());
    }
    return *m_libs[name];
}
