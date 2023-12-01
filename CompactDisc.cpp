#include "CompactDisc.h"

using namespace std;
using namespace crow;


CompactDisc::CompactDisc(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}


// Convert to JSON
json::wvalue CompactDisc::convertToJson() 
{
    // Convert the base Album part
    json::wvalue writeJson = Album::convertToJson();

    // Add CompactDisc-specific details
    writeJson["isMultiDiscSet"] = isMultiDiscSet;

    return writeJson;
}

// Update from JSON
void CompactDisc::updateFromJson(json::rvalue readValueJson) 
{
    // Update the base Album part
    Album::updateFromJson(readValueJson); 

    // Update CompactDisc-specific details
    isMultiDiscSet = readValueJson["isMultiDiscSet"].b();
}
