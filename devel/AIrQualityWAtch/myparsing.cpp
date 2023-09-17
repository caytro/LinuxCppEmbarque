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
    f.close();
    return this;
}

int myParsing::toFile(myOptions *options)
{
    string fileName = options->getFullDataFileName().append("-");
    fileName.append(myJson["stations"][0]["updatedAt"]).append(".json");
    cout << "Saving datas to " << fileName << endl;

    std::ofstream o(fileName);
    o << setw(4) << myJson << endl;
    o.close();
    return 0;
}

myParsing::myParsing()
{

}
