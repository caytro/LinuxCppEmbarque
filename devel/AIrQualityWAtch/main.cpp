#include <iostream>
#include <ctime>
#include "mycurl.h"
#include "myparsing.h"
#include "myoptions.h"
#include "mygraphics.h"


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
    char **data = (char**) malloc(sizeof(char*));
    *data=nullptr;

    myOptions* options = new(myOptions);
    options->readFromFile("/home/sylvain/AIQWA.config");

    time_t now = time(0);
    cout << "*** " << endl << ctime(&now) << endl << "***" << endl;
//    downloadDatas(data, options);

    myParsing* parser = new myParsing();
//    parser->fromChar(*data)->toFile(options);
//    parser->appendToDatas(options);
    json datas = parser->fromDatasFile(options);
    myGraphics *curveChart = new myGraphics();
    curveChart->curveChart(datas, options);
    free (*data);
    free(data);

    return 0;
}
