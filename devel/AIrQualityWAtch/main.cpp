#include <iostream>
#include <ctime>
#include "mycurl.h"
#include "myparsing.h"
#include "myoptions.h"
#include "mygraphics.h"
#include "myregex.h"


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
    options->readFromFile("AIQWA.conf");

    time_t now = time(0);
    cout << "*** " << endl << ctime(&now) << endl << "***" << endl;
    downloadDatas(data, options);

    myParsing* parser = new myParsing();
    parser->fromChar(*data)->toFile(options);

    parser->appendToDatas(options);
    system("./reformDatas");
    json datas = parser->fromDatasFile(options);
    myGraphics *curveChart = new myGraphics();
    curveChart->curveChart(datas, options);
    myGraphics *pieChart = new myGraphics();
    pieChart->pieChart(datas, options);
    free (*data);
    free(data);

    return 0;
}
