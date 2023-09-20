#include <iostream>
#include <iostream>
#include <ctime>

#include "../AIrQualityWAtch/myparsing.h"
#include "../AIrQualityWAtch/myoptions.h"

#include "../AIrQualityWAtch/myregex.h"

using namespace std;



int main()
{
    myParsing* p = new myParsing();
    p->fromFile("/home/sylvain/datas/AirQualityWatch.json");
    //cout << p->getMyJson().dump() << endl;
    json j = p->getMyJson();
    int s = j.size();
    json data = j[s-1];
    cout << data["stations"][0]["OZONE"] << endl;
    cout << "size : " << s << endl;
    cout << "Hello World!" << endl;
    return 0;
}
