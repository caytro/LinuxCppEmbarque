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
    ///
    /// \brief myParsing
    ///
    myParsing();

    ///
    /// \brief getMyJson
    /// \return
    ///
    const json &getMyJson() const;

    ///
    /// \brief setMyJson
    /// \param newMyJson
    ///
    void setMyJson(const json &newMyJson);

    ///
    /// \brief fromChar
    /// \param str
    /// \return
    ///
    myParsing* fromChar(char* str);

    ///
    /// \brief toString
    /// \return
    ///
    string toString();

    ///
    /// \brief fromFile
    /// \param fileName
    /// \return
    ///
    myParsing* fromFile(string fileName);

    ///
    /// \brief toFile
    /// \param options
    /// \return
    ///
    int toFile(myOptions* options);

    ///
    /// \brief appendToDatas
    /// \param options
    ///
    void appendToDatas(myOptions* options);

    ///
    /// \brief appendFileToDatas
    /// \param fileName
    ///
    void appendFileToDatas(string fileName);

    ///
    /// \brief fromDatasFile
    /// \param options
    /// \return
    ///
    const json fromDatasFile(myOptions *options);
    };

#endif // MYPARSING_H


