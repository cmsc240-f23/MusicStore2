#ifndef GENRE_H
#define GENRE_H

#include <crow.h>
#include <string>


class Genre 
{
public:
    // Constructors
    Genre() {}
    Genre(crow::json::rvalue readValueJson);

    // Getters
    std::string getId() const { return id; }
    std::string getGenre() const { return genre; }

    // Setters
    void setId(std::string idParam) { id = idParam; }
    void setGenre(std::string genreParam) { genre = genreParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);
    
private:
    std::string id;
    std::string genre;
};

#endif // GENRE_H
