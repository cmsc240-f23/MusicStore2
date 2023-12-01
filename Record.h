#ifndef RECORD_H
#define RECORD_H

#include <crow.h>
#include <string>
#include "Album.h"

class Record : public Album 
{
public:
    // Constructor
    Record() {}
    Record(crow::json::rvalue readValueJson);

    // Getters
    std::string getFormat() const { return format; }
    bool getIsUsed() const { return isUsed; }
    int getSize() const { return size; }

    // Setters
    void setFormat(std::string formatParam) { format = formatParam; }
    void setIsUsed(bool isUsedParam) { isUsed = isUsedParam; }
    void setSize(int sizeParam) { size = sizeParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    // The format of the record, e.g., vinyl, CD, etc.
    std::string format; 

    // Whether the record is used or new
    bool isUsed;

    // The size of the record, typically in inches for vinyl records        
    int size;           
};

#endif // RECORD_H
