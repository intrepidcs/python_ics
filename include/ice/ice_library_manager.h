#ifndef __ICE_LIBRARY_MANAGER_H__
#define __ICE_LIBRARY_MANAGER_H__

#include "ice_library.h"
#include <map>
#include <string>
#include <vector>

namespace ice
{
    class LibraryManager;
};

class ice::LibraryManager
{
public:
    LibraryManager();
    ~LibraryManager();
    
    void add(std::string name, std::string path);    
    void remove(std::string name);
    void remove(ice::Library& library);
    
    std::vector<std::string> getLibraryNames() const;
    
    ice::Library& operator[](std::string name);
    
private:
    typedef std::map<std::string, ice::Library*> Libraries;
    Libraries m_libs;
};

#endif // __ICE_LIBRARY_MANAGER_H__