#include "myregex.h"


myRegex::myRegex()
{

}

updatedAt myRegex::ambeeDataGetDateTime(string updatedAtField)
{
    // Format : "updatedAt": "2023-09-16T18:00:00.000Z"

    regex re("([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2}).*+");
    cmatch m;
    regex_match(updatedAtField.c_str(),m, re );
    updatedAt response;
    response.year = stoi(m.format("$1"));
    response.month = stoi(m.format("$2"));
    response.day = stoi(m.format("$3"));
    response.hour = stoi(m.format("$4"));
    response.minute = stoi(m.format("$5"));
    response.second = stoi(m.format("$6"));

    return response;

}

string myRegex::toFormatDDMMYY(string updatedAtField)
{
    regex re("([0-9]{2})([0-9]{2})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2}).*+");
    cmatch m;
    regex_match(updatedAtField.c_str(),m, re );
    string response = m.format("$4/$3/$2");
    return response;
}

string myRegex::toFormatHHMM(string updatedAtField)
{
    regex re("([0-9]{2})([0-9]{2})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2}).*+");
    cmatch m;
    regex_match(updatedAtField.c_str(),m, re );
    string response = m.format("$5:$6");
    return response;
}
