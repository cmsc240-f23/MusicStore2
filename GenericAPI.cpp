
/**
 * @file GenericAPI.cpp
 * @brief Implementation of the Generic API for RESTful services.
 *
 * This file provides the implementation for a generic API that can be
 * specialized for different types of resources in a RESTful service.
 */

#include <stdexcept>
#include "Artist.h"
#include "CompactDisc.h"
#include "GenericAPI.h"
#include "Genre.h"
#include "Record.h"

using namespace std;
using namespace crow;


template<typename T> 
map<string, T> GenericAPI<T>::resourceMap;

/**
 * @brief Create a new resource.
 * 
 * This method handles the creation of a new resource based on the data
 * received in the request body.
 * 
 * @param req The HTTP request object.
 * @return res The HTTP response object.
 */
template<typename T> 
response GenericAPI<T>::createResource(request req) 
{
    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = json::load(req.body);

    // If there was a problem converting the body text to JSON return an error.
    // 400 Bad Request: The server cannot or will not process the request due to something
    // that is perceived to be a client error (e.g., malformed request syntax, invalid 
    // request message framing, or deceptive request routing).
    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    // Create a new resource.
    T resource{readValueJson};

    // Add the new resource to the map.
    resourceMap[resource.getId()] = resource;

    // Return the create resource as a JSON string.
    // 201 Created: The request succeeded, and a new resource was created as a result.
    // This is typically the response sent after POST requests, or some PUT requests.
    return response(201, resource.convertToJson().dump());
}

/**
 * @brief Read a specific resource.
 * 
 * This method retrieves a resource identified by a unique ID.
 * 
 * @param id The unique identifier of the resource.
 * @return res The HTTP response object.
 */
template<typename T> 
response GenericAPI<T>::readResource(string id) 
{
    try 
    {
        // Get the resource from the resource map.
        T resource = resourceMap.at(id);

        // Return the resource as a JSON string.
        return response(resource.convertToJson().dump());
    } 
    catch (out_of_range& exception) 
    {
        // If the resource was not found in the map return a 404 not found error.
        // 404 Not Found: The server cannot find the requested resource.
        return response(404, "Resource Not Found");
    }
}

/**
 * @brief Read all resources.
 * 
 * This method retrieves a resource identified by a unique ID.
 * 
 * @return res The HTTP response object.
 */
template<typename T> 
response GenericAPI<T>::readAllResources() 
{
    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each resource in the map, convert the resource to JSON and add to the write value.
    int index = 0;
    for (pair<string, T> keyValuePair : resourceMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = keyValuePair.second.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

/**
 * @brief Update a specific resource.
 * 
 * This method updates the data of a resource identified by a unique ID.
 * 
 * @param req The HTTP request object.
 * @param res The HTTP response object.
 * @param id The unique identifier of the resource.
 */
template<typename T> 
void GenericAPI<T>::updateResource(request req, response& res, string id) 
{
    try 
    {
        // Get the resource from the resource map.
        T resource = resourceMap.at(id);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON return an error.
        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the resource.
        resource.updateFromJson(readValueJson);
        resourceMap[id] = resource;

        // Return the updated resource as a JSON string.
        // 200 OK: The request succeeded.
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(resource.convertToJson().dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        // If the resource was not found in the map return a 404 not found error.
        res.code = 404;
        res.end("Resource Not Found");
    }
}

/**
 * @brief Delete a specific resource.
 * 
 * This method deletes a resource identified by a unique ID.
 * 
 * @param id The unique identifier of the resource.
 * @return res The HTTP response object.
 */
template<typename T> 
response GenericAPI<T>::deleteResource(string id) 
{
    try 
    {
        // Get the resource from the resource map.
        T resource = resourceMap.at(id);

        // Remove the resource from the resource map.
        resourceMap.erase(id);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        // If the resource was not found in the map return a 404 not found error.
        return response(404, "Resource Not Found");
    }
}

// Explicit template instantiation
template class GenericAPI<Genre>;
template class GenericAPI<Artist>;
template class GenericAPI<Record>;
template class GenericAPI<CompactDisc>;