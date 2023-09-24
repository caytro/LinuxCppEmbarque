#include <iostream>
#include <ctime>
#include "mycurl.h"
#include "myparsing.h"
#include "myoptions.h"
#include "mygraphics.h"
#include "myregex.h"


using namespace std;

int downloadDatas(char** data, myOptions* options){
    myCurl mc;
    CURLcode ret=mc.exec(options, data);
//    if (ret!=0) {
//        cout << "Code erreur : " << ret << endl;
//        return ret;
//    }

    return ret;
}



int main()
{
    char** data = (char**) malloc(sizeof(char*));


    myOptions* options = new(myOptions);
    options->readFromFile("AIQWA.conf");
    downloadDatas(data, options);

    myParsing* parser = new myParsing();
    string jsonData = string(*data);
    parser->fromChar(jsonData);
    parser->toFile(options);
    parser->appendToDatas(options);
    system("./reformDatas");
    json datas = parser->fromDatasFile(options);
    myGraphics *curveChart = new myGraphics();
    curveChart->curveChart(datas, options);
    myGraphics *pieChart = new myGraphics();
    pieChart->pieChart(datas, options);
    free (*data);
    free(data);
    delete(options);
    delete(parser);
    delete(curveChart);
    delete(pieChart);
    return 0;
}
