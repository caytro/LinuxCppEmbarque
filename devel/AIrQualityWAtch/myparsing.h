#ifndef MYPARSING_H
#define MYPARSING_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include "myoptions.h"

using namespace  std;
using json = nlohmann::json;

class myParsing
{
    json myJson;



public:
    myParsing();

    const json &getMyJson() const;
    void setMyJson(const json &newMyJson);
    myParsing* fromChar(char* str);
    string toString();
    myParsing* fromFile(string fileName);
    int toFile(myOptions* options);
    };

#endif // MYPARSING_H


