#ifndef ARTIST_H
#define ARTIST_H

#include <crow.h>
#include <string>

class Artist
{
public:
    // Constructors
    Artist() {}
    Artist(crow::json::rvalue readValueJson);

    // Getters
    std::string getId() const { return id; }
    std::string getArtist() const { return artist; }

    // Setters
    void setId(std::string idParam) { id = idParam; }
    void setArtist(std::string artistParam) { artist = artistParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string id;
    std::string artist;
};

#endif // ARTIST_H
