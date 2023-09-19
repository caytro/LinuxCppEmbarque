#include <iostream>
#include <regex>
#include <string>
#include <iterator>

using namespace std;

int main()
{
    string s = "2023-09-16T18:00:00.000Z";
    //s="2023-09";
    regex re("([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2}).*+");
    cmatch m;
    regex_match(s.c_str(),m, re );
    for (auto item:m){
        cout << item << endl;
    }
    cout << "year : " << m.format("[$1]") << endl;
    cout << "month : " << m.format("[$2]") << endl;
    cout << "day : " << m.format("[$3]") << endl;
    cout << "hour : " << m.format("[$4]") << endl;
    cout << "minute : " << m.format("[$5]") << endl;
    cout << "second : " << m.format("[$6]") << endl;



    cout << "Hello World!" << endl;
    return 0;
}
