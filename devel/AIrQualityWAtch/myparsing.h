#ifndef MYPARSING_H
#define MYPARSING_H

#include <iostream>
#include <nlohmann/json.hpp>

using namespace  std;
using json = nlohmann::json;

class myParsing
{
    json myJson;

public:
    myParsing();

};

#endif // MYPARSING_H


/*
 * #include <iostream>
#include <nlohmann/json.hpp>
#include <string>



using namespace std;
using json = nlohmann::json;


int main()
{
    string test="Hello";
    json ex1 = json::parse(R"(
      {
        "pi": 3.141,
        "happy": true
      }
    )");
    json ex2 = json::parse(R"(
      {"message":"success","stations":[{"CO":0.234,"NO2":16.543,"OZONE":12.586,"PM10":12.853,"PM25":2.6,"SO2":0.661,"city":"Toulouse","countryCode":"FR","division":"Haute-Garonne","lat":43.556374,"lng":1.403964,"placeName":"Avenue de Larrieu","postalCode":"31100","state":"Occitanie","updatedAt":"2023-09-14T07:00:00.000Z","AQI":16,"aqiInfo":{"pollutant":"NO2","concentration":16.543,"category":"Good"}}]}
    )");

    cout << ex1["pi"] <<endl;
    cout << ex2["stations"][0]["OZONE"] <<endl;
    return 0;
}
*/
