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

    ofstream o(fileName);
    o << setw(4) << myJson << endl;
    o.close();
    return 0;
}


void myParsing::appendToDatas(myOptions *options)
{
    string fileName = options->getFullDataFileName().append(".json");
    ifstream f(fileName);
    json previousJson = json::parse(f);
    previousJson.push_back(myJson);
    f.close();
    ofstream o(fileName);
    o << setw(4) << previousJson << endl;
    o.close();
}

void myParsing::appendFileToDatas(string fileName)
{
    ifstream f(fileName);
    json previousJson = json::parse(f);
    previousJson.push_back(myJson);
    f.close();
    ofstream o(fileName);
    o << setw(4) << previousJson << endl;
    o.close();
}

const json myParsing::fromDatasFile(myOptions* options)
{
    ifstream f(options->getFullDataFileName().append(".json"));
    json datas=json::parse(f);
    return datas;
}


myParsing::myParsing()
{

}
