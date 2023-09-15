#include <iostream>
#include "mycurl.h"
#include "myparsing.h"


using namespace std;

int main()
{
    myCurl *curl = new myCurl();


    curl->setLatitude("43.560537");
    curl->setLongitude("1.404690");
    // chez moi :o)
    curl->setApi_key("b83fcfd7137ff81d96b92a34d3488506b7d3976bda58077cab133e94efd0a240");
    cout << "Go ! \n";
    CURLcode ret=curl->exec();
    if (ret!=0) {
        cout << "Code erreur : " << ret << endl;
        return ret;
    }
    char **data = (char**) malloc(sizeof(char*));
    curl->getData(data);
    myParsing* parser = new myParsing();
    parser->fromChar(*data);
    string fileName="/tmp/AirQualityWatch-";
    fileName.append(parser->getMyJson()["stations"][0]["updatedAt"]);
    fileName.append(".json");
    parser->toFile(fileName);


    return 0;
}
