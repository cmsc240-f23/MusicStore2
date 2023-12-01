#include <crow.h>
#include <map>
#include <csignal>
#include <string>
#include "Record.h"
#include "Artist.h"
#include "CompactDisc.h"
#include "GenericAPI.h"
#include "Genre.h"
#include "persistence.h"

using namespace std;
using namespace crow;

// Load resources from files.
map<std::string, Genre> genresMap = loadFromFile<Genre>("genres.json");
map<std::string, Artist> artistsMap = loadFromFile<Artist>("artists.json");
map<std::string, Record> recordsMap = loadFromFile<Record>("records.json");
map<std::string, CompactDisc> compactDiscsMap = loadFromFile<CompactDisc>("compactdiscs.json");

int main() 
{
    // Create GenericAPIs to use in the CROW_ROUTES
    GenericAPI<Genre>::resourceMap = genresMap;
    GenericAPI<Artist>::resourceMap = artistsMap;
    GenericAPI<Record>::resourceMap = recordsMap;
    GenericAPI<CompactDisc>::resourceMap = compactDiscsMap;

    // Setup the simple web service.
    SimpleApp app;

    // Define resources:

    // Genres
    CROW_ROUTE(app, "/api/genres").methods("POST"_method)(GenericAPI<Genre>::createResource);
    CROW_ROUTE(app, "/api/genres").methods("GET"_method)(GenericAPI<Genre>::readAllResources);
    CROW_ROUTE(app, "/api/genres/<string>").methods("GET"_method)(GenericAPI<Genre>::readResource);
    CROW_ROUTE(app, "/api/genres/<string>").methods("PUT"_method)(GenericAPI<Genre>::updateResource);
    CROW_ROUTE(app, "/api/genres/<string>").methods("DELETE"_method)(GenericAPI<Genre>::deleteResource);

    // Artist
    CROW_ROUTE(app, "/api/artists").methods("POST"_method)(GenericAPI<Artist>::createResource);
    CROW_ROUTE(app, "/api/artists").methods("GET"_method)(GenericAPI<Artist>::readAllResources);
    CROW_ROUTE(app, "/api/artists/<string>").methods("GET"_method)(GenericAPI<Artist>::readResource);
    CROW_ROUTE(app, "/api/artists/<string>").methods("PUT"_method)(GenericAPI<Artist>::updateResource);
    CROW_ROUTE(app, "/api/artists/<string>").methods("DELETE"_method)(GenericAPI<Artist>::deleteResource);

    // Records
    CROW_ROUTE(app, "/api/records").methods("POST"_method)(GenericAPI<Record>::createResource);
    CROW_ROUTE(app, "/api/records").methods("GET"_method)(GenericAPI<Record>::readAllResources);
    CROW_ROUTE(app, "/api/records/<string>").methods("GET"_method)(GenericAPI<Record>::readResource);
    CROW_ROUTE(app, "/api/records/<string>").methods("PUT"_method)(GenericAPI<Record>::updateResource);
    CROW_ROUTE(app, "/api/records/<string>").methods("DELETE"_method)(GenericAPI<Record>::deleteResource);

    // CompactDiscs
    CROW_ROUTE(app, "/api/compactdiscs").methods("POST"_method)(GenericAPI<CompactDisc>::createResource);
    CROW_ROUTE(app, "/api/compactdiscs").methods("GET"_method)(GenericAPI<CompactDisc>::readAllResources);
    CROW_ROUTE(app, "/api/compactdiscs/<string>").methods("GET"_method)(GenericAPI<CompactDisc>::readResource);
    CROW_ROUTE(app, "/api/compactdiscs/<string>").methods("PUT"_method)(GenericAPI<CompactDisc>::updateResource);
    CROW_ROUTE(app, "/api/compactdiscs/<string>").methods("DELETE"_method)(GenericAPI<CompactDisc>::deleteResource);


    // Run the web service app.
    app.port(18080).run();
        
    // After the web service stops running:

    // Perform persistence of resources
    saveToFile<Genre>(GenericAPI<Genre>::resourceMap, "genres.json");
    saveToFile<Artist>(GenericAPI<Artist>::resourceMap, "artists.json");
    saveToFile<Record>(GenericAPI<Record>::resourceMap, "records.json");
    saveToFile<CompactDisc>(GenericAPI<CompactDisc>::resourceMap, "compactdiscs.json");
}
