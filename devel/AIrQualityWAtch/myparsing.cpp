#include "myparsing.h"


const json &myParsing::getMyJson() const
{
    return myJson;
}

void myParsing::setMyJson(const json &newMyJson)
{
    myJson = newMyJson;
}

myParsing* myParsing::fromChar(char *str)
{
    myJson = json::parse(str);
    return this;
}

string myParsing::toString()
{
    return myJson.dump();
}

myParsing* myParsing::fromFile(string fileName)
{
    ifstream f(fileName);
    myJson = json::parse(f);
    return this;
}

int myParsing::toFile(string fileName)
{
    std::ofstream o(fileName);
    o << setw(4) << myJson << endl;
    return 0;
}

myParsing::myParsing()
{

}
