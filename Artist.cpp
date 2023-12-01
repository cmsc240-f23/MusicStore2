#include "Artist.h"

using namespace std;
using namespace crow;


Artist::Artist(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Artist::convertToJson() 
{
    json::wvalue writeJson;
    writeJson["id"] = id;
    writeJson["artist"] = artist;
    return writeJson;
}

// Update from JSON
void Artist::updateFromJson(json::rvalue readValueJson) 
{
    id = readValueJson["id"].s();
    artist = readValueJson["artist"].s();
}

