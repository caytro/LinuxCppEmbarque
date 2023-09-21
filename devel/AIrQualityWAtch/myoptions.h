#ifndef MYOPTIONS_H
#define MYOPTIONS_H
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

using namespace std;
using json = nlohmann::json;

///
/// \brief The myOptions class
/// \details Manage acces to AIQWA.conf file
/// \details Allows to modify API parameters and local files names and paths
/// \details without the need to recompile
/// \details File Format :
/// \details {
/// \details "curlopts": {
/// \details    "url": "https://api.ambeedata.com/latest/by-lat-lng",
/// \details    "urlParams": {
/// \details        "lat": "43.560537",
/// \details        "lng": "1.404690"
/// \details    },
/// \details    "api-key": "x-api-
/// \details key:b83fcfd7137ff81d96b92a34d3488506b7d3976bda58077cab133e94efd0a240"
/// \details },
/// \details "display":true,
/// \details "filesOwner": "owner",
/// \details "logPath": "logs",
/// \details "logFileName": "AIQWA.log",
/// \details "dataPath": "datas",
/// \details "dataFileName": "AirQualityWatch",
/// \details "chartPath": "charts",
/// \details "curveChartFileName": "curve.png",
/// \details "histoChartFileName": "histo.png",
/// \details "pieChartFileName": "pie.png"
/// \details }

///
class myOptions
{
    ///
    /// \brief options
    /// \details Stores json options
    ///
    json options;
public:
    ///
    /// \brief myOptions
    /// \details Constructor
    ///
    myOptions();

    ///
    /// \brief readFromFile
    /// \param string fileName
    /// \details Read options from file in json format
    ///
    void readFromFile(string fileName);

    ///
    /// \brief getFullUrl
    /// \return string
    /// \details Returns full API Url, including GET params
    ///
    string getFullUrl();

    ///
    /// \brief getApiKeyHeader
    /// \return string
    ///
    string getApiKeyHeader();

    ///
    /// \brief getFilesOwner
    /// \return string
    ///
    string getFilesOwner();

    ///
    /// \brief getFullLogFileName
    /// \return string
    ///
    string getFullLogFileName();

    ///
    /// \brief getFullDataFileName
    /// \return string
    /// \details return datas path/fileName
    ///
    string getFullDataFileName();

    ///
    /// \brief getDataPathName();
    /// \return string
    /// \details return datas path
    ///
    string getDataPathName();
    ///
    /// \brief getFullCurveChartFileName
    /// \return string
    /// \details return path/fileName
    ///
    string getFullCurveChartFileName();

    ///
    /// \brief getFullHistoChartFileName
    /// \return string
    /// \details return path/fileName
    ///
    string getFullHistoChartFileName();

    ///
    /// \brief getFullPieChartFileName
    /// \return string
    /// \details return path/fileName
    ///
    string getFullPieChartFileName();

    ///
    /// \brief isDisplay
    /// \return bool
    /// \details Set false on embedded system
    /// \details Set true on local system to allow system call to _display_
    ///
    bool isDisplay();
};

#endif // MYOPTIONS_H
