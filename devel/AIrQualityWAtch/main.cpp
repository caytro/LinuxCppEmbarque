#include <iostream>
#include "mycurl.h"

using namespace std;

int main()
{
    myCurl curl;
    curl.setLatitude("43.560537");
    curl.setLongitude("1.404690");
    // chez moi :o)
    curl.setApi_key("b83fcfd7137ff81d96b92a34d3488506b7d3976bda58077cab133e94efd0a240");
    cout << "Go ! \n";
    CURLcode ret=curl.exec();
    char **data = (char**) malloc(sizeof(char*));

    curl.getData(data);
    cout << "Ret : " << ret << endl;
    cout << "Data : " << *data << endl;
    return 0;
}
