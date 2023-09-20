#include <iostream>
#include <ctime>
#include "mycurl.h"
#include "myparsing.h"
#include "myoptions.h"
#include "mygraphics.h"
#include "myregex.h"



 // A Compléter !!!

using namespace std;

int downloadDatas(char** data, myOptions* options){
    myCurl *mc = new myCurl();

    CURLcode ret=mc->exec(options);
    if (ret!=0) {
        cout << "Code erreur : " << ret << endl;
        return ret;
    }
    mc->getData(data);
    return ret;
}



int main()
{
    // https://api.ambeedata.com/history/by-lat-lng?lat=12&lng=73&from=2020-07-13 12:16:44&to=2020-07-18 08:16:44

    char **data = (char**) malloc(sizeof(char*));
    *data=nullptr;

    myOptions* options = new(myOptions);
    options->readFromFile("/home/sylvain/AIQWA.config");

    time_t now = time(0);
    cout << "*** " << endl << ctime(&now) << endl << "***" << endl;
    downloadDatas(data, options);

    myParsing* parser = new myParsing();
    parser->fromChar(*data)->toFile(options);
    parser->appendToDatas(options);
    json datas = parser->fromDatasFile(options);
    myGraphics *curveChart = new myGraphics();
    curveChart->curveChart(datas, options);
    free (*data);
    free(data);

    return 0;
}
