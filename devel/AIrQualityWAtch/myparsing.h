#ifndef MYPARSING_H
#define MYPARSING_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include "myoptions.h"

using namespace  std;
using json = nlohmann::json;

///
/// \brief The myParsing class
/// \details shortcut methods based on <nlohmann/json.hpp> library
///
class myParsing
{
    json myJson;



public:
    ///
    /// \brief myParsing
    /// \details Constructor
    ///
    myParsing();

    ///
    /// \brief getMyJson
    /// \return const json &
    ///
    const json &getMyJson() const;

    ///
    /// \brief setMyJson
    /// \param const json &newMyJson
    ///
    void setMyJson(const json &newMyJson);

    ///
    /// \brief fromChar
    /// \param char* str
    /// \return myParsing*
    /// \details Generate json from char *data read from API returned by curl
    ///
    myParsing* fromChar(string str);

    ///
    /// \brief toString
    /// \return string
    /// \details return json dump, for debug purpose
    ///
    string toString();

    ///
    /// \brief fromFile
    /// \param string fileName
    /// \return myParsing*
    /// \details Read file in json format, parse it and strores data in myJson
    ///
    myParsing* fromFile(string fileName);

    ///
    /// \brief toFile
    /// \param myOptions* options
    /// \return int
    /// \details stores myJson to fileName returned by options->getFullDataFileName
    /// \details an updatedAt tag is appended to fileName
    ///
    int toFile(myOptions* options);

    ///
    /// \brief appendToDatas
    /// \param myOptions* options
    /// \details Append current latest downloaded data to file _options->getFullDataFileName().json_
    ///
    void appendToDatas(myOptions* options);

    ///
    /// \brief appendFileToDatas
    /// \param string fileName
    /// \details Append current latest downloaded data to file _fileName_
    ///
    void appendFileToDatas(string fileName);

    ///
    /// \brief fromDatasFile
    /// \param myOptions *options
    /// \return const json
    /// \details returns json content of _options->getFullDataFileName().json"
    /// \details the file is json array containing previously stored datasets
    ///
    const json fromDatasFile(myOptions *options);
    };

#endif // MYPARSING_H


