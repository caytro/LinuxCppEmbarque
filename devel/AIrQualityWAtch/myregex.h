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

class myRegex
{
public:
    myRegex();
    static updatedAt ambeeDataGetDateTime(string updatedAtField);
    static string toFormatDDMMYY(string updatedAtField);
    static string toFormatHHMM(string updatedAtField);


};

#endif // MYREGEX_H
