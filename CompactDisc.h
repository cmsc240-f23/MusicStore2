#ifndef COMPACT_DISC_H
#define COMPACT_DISC_H

#include <crow.h>
#include <string>
#include "Album.h"

class CompactDisc : public Album 
{
public:
    // Constructor
    CompactDisc() {}
    CompactDisc(crow::json::rvalue readValueJson);

    // Getters
    bool getIsMultiDiscSet() const { return isMultiDiscSet; }

    // Setters
    void setIsMultiDiscSet(bool isMultiDiscSetParam) { isMultiDiscSet = isMultiDiscSetParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    // Whether this is a multi disc set.
    bool isMultiDiscSet;         
};

#endif // COMPACT_DISC_H
