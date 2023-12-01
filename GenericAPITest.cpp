#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include "Artist.h"
#include "CompactDisc.h"
#include "GenericAPI.h"
#include "Genre.h"
#include "Record.h"

using namespace std;
using namespace crow;

map<string, Genre> genresMap;
map<string, Artist> artistsMap;
map<string, Record> recordsMap;
map<string, CompactDisc> compactDiscsMap;

TEST_CASE("Creating a new Genre resource") 
{
    // Setup resource map to be empty before the test
    GenericAPI<Genre>::resourceMap.clear();

    // Setup request object
    request req;
    req.body = R"({"genre":"Rock","id":"1"})"; 

    // Perform the action
    response res = GenericAPI<Genre>::createResource(req);

    // Check the results
    CHECK(res.code == 201); // Check that the response code is 201 Created
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Genre>::resourceMap.size() == 1); // Ensure the resource was added to the map
    CHECK(GenericAPI<Genre>::resourceMap.at("1").getId() == "1"); // Validate the resource content
    CHECK(GenericAPI<Genre>::resourceMap.at("1").getGenre() == "Rock"); // Validate the resource content
}

TEST_CASE("Reading a Genre resource") 
{
    // Load a resource to read.
    genresMap["1"] = Genre{json::load(R"({"genre":"Rock","id":"1"})")};

    // Setup resource map to be empty before the test
    GenericAPI<Genre>::resourceMap = genresMap;

    // Perform the action
    response res = GenericAPI<Genre>::readResource("1");

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == genresMap["1"].convertToJson().dump()); // Validate the reponse body
    CHECK(GenericAPI<Genre>::resourceMap.size() == 1); // Ensure that no resources were added or removed from the map
}

TEST_CASE("Reading all Genre resources") 
{
    // Load resources to read.
    genresMap["1"] = Genre{json::load(R"({"genre":"Rock","id":"1"})")};
    genresMap["2"] = Genre{json::load(R"({"genre":"Jazz","id":"2"})")};
    genresMap["3"] = Genre{json::load(R"({"genre":"Blues","id":"3"})")};
    genresMap["4"] = Genre{json::load(R"({"genre":"Country","id":"4"})")};

    // Setup resource map to be empty before the test
    GenericAPI<Genre>::resourceMap = genresMap;

    // Perform the action
    response res = GenericAPI<Genre>::readAllResources();

    // Create the expected reponse body
    string expectedResponseBody = R"([{"genre":"Rock","id":"1"},{"id":"2","genre":"Jazz"},{"genre":"Blues","id":"3"},{"genre":"Country","id":"4"}])";

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == expectedResponseBody); // Validate the reponse body
    CHECK(GenericAPI<Genre>::resourceMap.size() == 4); // Ensure that no resources were added or removed from the map
}


TEST_CASE("Updating a Genre resource") 
{
    // Load resources to update.
    genresMap["1"] = Genre{json::load(R"({"genre":"Rock","id":"1"})")};
    genresMap["2"] = Genre{json::load(R"({"genre":"Jazz","id":"2"})")};
    genresMap["3"] = Genre{json::load(R"({"genre":"Blues","id":"3"})")};
    genresMap["4"] = Genre{json::load(R"({"genre":"Country","id":"4"})")};

    // Setup resource map to be empty before the test
    GenericAPI<Genre>::resourceMap = genresMap;

    // Setup request object
    request req;
    req.body = R"({"genre":"Classical","id":"1"})"; 

    // Setup a response object
    response res;

    // Perform the action
    GenericAPI<Genre>::updateResource(req, res, "1");

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Genre>::resourceMap.size() == 4); // Ensure no resource was added or removed from the map
    CHECK(GenericAPI<Genre>::resourceMap.at("1").getId() == "1"); // Validate the resource content
    CHECK(GenericAPI<Genre>::resourceMap.at("1").getGenre() == "Classical"); // Validate the resource content
}


TEST_CASE("Deleting a Genre resource") 
{
    // Load a resources to update.
    genresMap["1"] = Genre{json::load(R"({"genre":"Rock","id":"1"})")};
    genresMap["2"] = Genre{json::load(R"({"genre":"Jazz","id":"2"})")};
    genresMap["3"] = Genre{json::load(R"({"genre":"Blues","id":"3"})")};
    genresMap["4"] = Genre{json::load(R"({"genre":"Country","id":"4"})")};

    // Setup resource map to be empty before the test
    GenericAPI<Genre>::resourceMap = genresMap;

    // Perform the action
    response res = GenericAPI<Genre>::deleteResource("4");

    // Check the results
    CHECK(res.code == 204); // Check that the response code is 204 No Content
    CHECK(res.body == ""); // Validate the reponse body
    CHECK(GenericAPI<Genre>::resourceMap.size() == 3); // Ensure one resource was removed from the map
}