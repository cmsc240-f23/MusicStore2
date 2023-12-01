#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include "Genre.h"
#include "persistence.h"

using namespace std;
using namespace crow;


TEST_CASE("Saving to a file and loading from a file.") 
{
    // Load a resources to read.
    map<string, Genre> genresMap;
    genresMap["1"] = Genre{json::load(R"({"genre":"Rock","id":"1"})")};
    genresMap["2"] = Genre{json::load(R"({"genre":"Jazz","id":"2"})")};
    genresMap["3"] = Genre{json::load(R"({"genre":"Blues","id":"3"})")};
    genresMap["4"] = Genre{json::load(R"({"genre":"Country","id":"4"})")};

    // Perform the action
    saveToFile<Genre>(genresMap, "persistenceTest.json");
    map<string, Genre> genresMapLoaded = loadFromFile<Genre>("persistenceTest.json");

    // Check the results
    CHECK(genresMap.size() == genresMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(genresMap.at("1").getId() == genresMapLoaded.at("1").getId()); // Validate the resource content
    CHECK(genresMap.at("1").getGenre() == genresMapLoaded.at("1").getGenre()); // Validate the resource content
    CHECK(genresMap.at("2").getId() == genresMapLoaded.at("2").getId()); // Validate the resource content
    CHECK(genresMap.at("2").getGenre() == genresMapLoaded.at("2").getGenre()); // Validate the resource content
    CHECK(genresMap.at("3").getId() == genresMapLoaded.at("3").getId()); // Validate the resource content
    CHECK(genresMap.at("3").getGenre() == genresMapLoaded.at("3").getGenre()); // Validate the resource content
    CHECK(genresMap.at("4").getId() == genresMapLoaded.at("4").getId()); // Validate the resource content
    CHECK(genresMap.at("4").getGenre() == genresMapLoaded.at("4").getGenre()); // Validate the resource content
}