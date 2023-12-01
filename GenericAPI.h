#ifndef GENERIC_API_H
#define GENERIC_API_H

#include <crow.h>
#include <map>
#include <string>

template<typename T> 
class GenericAPI 
{
public:
    static std::map<std::string, T> resourceMap;
    static crow::response createResource(crow::request req);
    static crow::response readResource(std::string id); 
    static crow::response readAllResources();
    static void updateResource(crow::request req, crow::response& res, std::string id); 
    static crow::response deleteResource(std::string id); 
};

#endif // GENERIC_API_H