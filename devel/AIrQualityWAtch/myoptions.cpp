#include "myoptions.h"

myOptions::myOptions()
{

}

void myOptions::readFromFile(string fileName)
{
    //cout << "entering " << __func__ << "... " << endl;
    ifstream f(fileName);
    options = json::parse(f);


}

string myOptions::getFullUrl()
{
    //cout << "entering " << __func__ << "... " << endl;
    string url = options["curlopts"]["url"];
    string lat = options["curlopts"]["urlParams"]["lat"];
    string lng = options["curlopts"]["urlParams"]["lng"];
    string fullUrl = url.append("?lat=").append(lat).append("&lng=").append(lng);
    return fullUrl;
}

string myOptions::getApiKeyHeader()
{
    //cout << "entering " << __func__ << "... " << endl;
    string apiKeyHeader = options["curlopts"]["api-key"];
    return apiKeyHeader;
}

string myOptions::getFilesOwner()
{
    //cout << "entering " << __func__ << "... " << endl;
    string owner = options["filesOwner"];
    return owner;
}

string myOptions::getFullLogFileName()
{
    //cout << "entering " << __func__ << "... " << endl;
    string path = options["logPath"];
    string baseName = options["logFileName"];
    string fullName = path.append("/").append(baseName);
    return fullName;
}

string myOptions::getFullDataFileName()
{
    //cout << "entering " << __func__ << "... " << endl;
    string path = options["dataPath"];
    string baseName = options["dataFileName"];
    string fullName = path.append("/").append(baseName);
    return fullName;
}

string myOptions::getFullDataCurveChartFileName()
{
    //cout << "entering " << __func__ << "... " << endl;
    string path = options["chartPath"];
    string baseName = options["curveChartFileName"];
    string fullName = path.append("/").append(baseName);
    return fullName;

}

string myOptions::getFullHistoChartFileName()
{
    //cout << "entering " << __func__ << "... " << endl;
    string path = options["chartPath"];
    string baseName = options["histo.png"];
    string fullName = path.append("/").append(baseName);
    return fullName;
}

string myOptions::getFullPieChartFileName()
{
    //cout << "entering " << __func__ << "... " << endl;
    string path = options["chartPath"];
    string baseName = options["pie.png"];
    string fullName = path.append("/").append(baseName);
    return fullName;
}

bool myOptions::isDisplay()
{
    return options["display"];
}

