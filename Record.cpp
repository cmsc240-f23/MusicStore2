#include "Record.h"

using namespace std;
using namespace crow;


Record::Record(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}


// Convert to JSON
json::wvalue Record::convertToJson() 
{
    // Convert the base Album part
    json::wvalue writeJson = Album::convertToJson();

    // Add Record-specific details
    writeJson["format"] = format;
    writeJson["isUsed"] = isUsed;
    writeJson["size"] = size;

    return writeJson;
}

// Update from JSON
void Record::updateFromJson(json::rvalue readValueJson) 
{
    // Update the base Album part
    Album::updateFromJson(readValueJson); 

    // Update Record-specific details
    format = readValueJson["format"].s();
    isUsed = readValueJson["isUsed"].b();
    size = readValueJson["size"].i();
}
