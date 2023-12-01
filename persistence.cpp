#include <crow.h>
#include <fstream>
#include "persistence.h"

using namespace std;
using namespace crow;

template <typename T>
void saveToFile(map<string, T> data, string filename)  
{
    // Open the file for writing
    ofstream file(filename);

    if (file.is_open()) 
    {
        // Create a new JSON write value use to write to the file.
        json::wvalue jsonWriteValue;
        
        // For each object in the map, convert the object to JSON and add to the write value.
        int index = 0;
        for (pair<string, T> keyValuePair : data)
        {
            // first: gives you access to the first item in the pair.
            // second: gives you access to the second item in the pair.
            jsonWriteValue[index] = keyValuePair.second.convertToJson();
            index++;
        }

        // Write the JSON to the file.
        file << jsonWriteValue.dump();
        file.close();
    }
}

template <typename T>
map<string, T> loadFromFile(string filename) 
{
    map<string, T> data;
    
    // Open the file for reading.
    ifstream file(filename);

    // If the file is open. 
    if (file.is_open()) 
    {      
        // Create a stream for reading in the file.
        ostringstream stringStreamJson;

        // Read the entire JSON string.
        stringStreamJson << file.rdbuf();

        // Load the string into a JSON read value object.
        json::rvalue jsonReadValue = json::load(stringStreamJson.str());

        // Close the file.
        file.close();

        // For each item in the JSON convert it to an object, 
        // and add it to the data map.
        for (json::rvalue item : jsonReadValue) 
        {
            T object{item};
            data[object.getId()] = object;
        }
    }
    
    return data;
}

