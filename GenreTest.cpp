#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include <string>
#include "Genre.h"

using namespace std;  
using namespace crow;  



TEST_CASE("Testing Genre Class") 
{
    // Testing Genre constructor
    SUBCASE("Testing the Genre Constructor") 
    {
        // Create a new Genre class from json.
        Genre testGenre(json::load(R"({"genre":"Rock","id":"1"})"));

        // Check that the constructor properly loaded the values.
        CHECK(testGenre.getId() == "1");
        CHECK(testGenre.getGenre() == "Rock");
    }

    // Testing convertToJson method
    SUBCASE("Testing the convertToJson Method") 
    {
        // Create a new Genre class from json.
        Genre testGenre(json::load(R"({"genre":"Rock","id":"1"})"));

        // Convert the Genre class to json using the convertToJson method.
        json::wvalue jsonOutput = testGenre.convertToJson();

        // Convert back to a json read value for testing.
        json::rvalue jsonReadValue = json::load(jsonOutput.dump());

        // Check the values.
        CHECK(jsonReadValue["id"].s() == "1");
        CHECK(jsonReadValue["genre"].s() == "Rock");
    }

    // Testing updateFromJson method
    SUBCASE("Testing updateFromJson Method") 
    {
        // Create a new Genre class from json.
        Genre testGenre(json::load(R"({"genre":"Rock","id":"1"})"));

        // Create the update json.
        json::rvalue updateJson = json::load(R"({"genre":"Jazz","id":"2"})");

        // Update the Genre with the updateFromJson method. 
        testGenre.updateFromJson(updateJson);

        // Check the updated values.
        CHECK(testGenre.getId() == "2");
        CHECK(testGenre.getGenre() == "Jazz");
    }
}
