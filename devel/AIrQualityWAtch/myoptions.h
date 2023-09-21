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
///
class myOptions
{
    ///
    /// \brief options
    ///
    json options;
public:
    ///
    /// \brief myOptions
    ///
    myOptions();

    ///
    /// \brief readFromFile
    /// \param fileName
    ///
    void readFromFile(string fileName);

    ///
    /// \brief getFullUrl
    /// \return
    ///
    string getFullUrl();

    ///
    /// \brief getApiKeyHeader
    /// \return
    ///
    string getApiKeyHeader();

    ///
    /// \brief getFilesOwner
    /// \return
    ///
    string getFilesOwner();

    ///
    /// \brief getFullLogFileName
    /// \return
    ///
    string getFullLogFileName();

    ///
    /// \brief getFullDataFileName
    /// \return
    ///
    string getFullDataFileName();

    ///
    /// \brief getDataPathName();
    /// \return
    ///
    string getDataPathName();
    ///
    /// \brief getFullCurveChartFileName
    /// \return
    ///
    string getFullCurveChartFileName();

    ///
    /// \brief getFullHistoChartFileName
    /// \return
    ///
    string getFullHistoChartFileName();

    ///
    /// \brief getFullPieChartFileName
    /// \return
    ///
    string getFullPieChartFileName();

    ///
    /// \brief isDisplay
    /// \return
    ///
    bool isDisplay();
};

#endif // MYOPTIONS_H
