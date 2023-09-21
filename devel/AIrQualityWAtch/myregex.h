#ifndef MYREGEX_H
#define MYREGEX_H

#include <iostream>
#include <string>
#include <iterator>
#include <regex>

using namespace std;

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} updatedAt;

///
/// \brief The myRegex class
/// \details Regex  helpers to display dates and times
///
class myRegex
{
public:
    ///
    /// \brief myRegex
    ///
    myRegex();

    ///
    /// \brief ambeeDataGetDateTime
    /// \param updatedAtField
    /// \return
    ///
    static updatedAt ambeeDataGetDateTime(string updatedAtField);

    ///
    /// \brief toFormatDDMMYY
    /// \param updatedAtField
    /// \return
    ///
    static string toFormatDDMMYY(string updatedAtField);

    ///
    /// \brief toFormatHHMM
    /// \param updatedAtField
    /// \return
    ///
    static string toFormatHHMM(string updatedAtField);

    ///
    /// \brief toFormatDDMMYYHHMM
    /// \param updatedAtField
    /// \return
    ///
    static string toFormatDDMMYYHHMM(string updatedAtField);

};

#endif // MYREGEX_H
