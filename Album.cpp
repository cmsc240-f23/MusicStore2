#include "Album.h"

using namespace std;
using namespace crow;

extern map<std::string, Genre> genresMap;
extern map<std::string, Artist> artistsMap;

Album::Album(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Album::convertToJson() 
{
    json::wvalue writeJson;
    writeJson["id"] = id;
    writeJson["title"] = title;
    writeJson["cost"] = cost;
    writeJson["mediaType"] = mediaType;
    writeJson["linkToCoverArt"] = linkToCoverArt;

    // Include the full json for each artist.
    int index = 0;
    for (Artist artist : artists) 
    {
        writeJson["artists"][index] = artist.convertToJson();
        index++;
    }

    // Include full Genre.
    writeJson["genre"] = genre.convertToJson();
 
    return writeJson;
}

// Update from JSON
void Album::updateFromJson(json::rvalue readValueJson) 
{
    id = readValueJson["id"].s();
    title = readValueJson["title"].s();
    cost = readValueJson["cost"].d();
    mediaType = readValueJson["mediaType"].s();
    linkToCoverArt = readValueJson["linkToCoverArt"].s();
    
    // Setting artists
    for (json::rvalue artistReadValueJson: readValueJson["artists"])
    {
        artists.push_back(Artist{artistReadValueJson});
    }

    // Setting genre
    json::rvalue genreReadValueJson = readValueJson["genre"];
    genre = Genre{genreReadValueJson};
}
