#ifndef MYOPTIONS_H
#define MYOPTIONS_H
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

using namespace std;
using json = nlohmann::json;


class myOptions
{
    json options;
public:
    myOptions();

    void readFromFile(string fileName);
    string getFullUrl();
    string getApiKeyHeader();
    string getFilesOwner();
    string getFullLogFileName();
    string getFullDataFileName();
    string getFullCurveChartFileName();
    string getFullHistoChartFileName();
    string getFullPieChartFileName();
    bool isDisplay();
};

#endif // MYOPTIONS_H
