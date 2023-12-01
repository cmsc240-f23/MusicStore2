#ifndef ALBUM_H
#define ALBUM_H

#include <crow.h>
#include <string>
#include <vector>
#include "Artist.h"
#include "Genre.h"

class Album
{
public:
    // Constructors
    Album() {}
    Album(crow::json::rvalue readValueJson);

    // Getters
    std::string getId() const { return id; }
    std::vector<Artist> getArtists() const { return artists; }
    Genre getGenre() const { return genre; }
    std::string getTitle() const { return title; }
    float getCost() const { return cost; }
    std::string getMediaType() const { return mediaType; }
    std::string setLinkToCoverArt() const { return linkToCoverArt; }

    // Setters
    void setId(std::string idParam) { id = idParam; }
    void setArtists(std::vector<Artist>& artistsParam) { artists = artistsParam; }
    void setGenre(Genre& genreParam) { genre = genreParam; }
    void setTitle(std::string titleParam) { title = titleParam; }
    void setCost(float costParam) { cost = costParam; }
    void setMediaType(std::string mediaTypeParam) { mediaType = mediaTypeParam; }
    void setLinkToCoverArt(std::string linkToCoverArtParam) { linkToCoverArt = linkToCoverArtParam; }

    // Convert to JSON.
    virtual crow::json::wvalue convertToJson();

    // Update from JSON.
    virtual void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string id;
    std::vector<Artist> artists;
    Genre genre;
    std::string title;
    float cost;
    std::string mediaType;
    std::string linkToCoverArt;
};

#endif // ALBUM_H
