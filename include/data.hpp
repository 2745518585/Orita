#ifndef DATA
#define DATA DATA
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
namespace Data
{
    void change_time_limit(int time)
    {
        ofstream file(string(getenv("appdata"))+"\\Orita\\data\\time.txt");
        file<<time;
        file.close();
    }
    int get_time_limit()
    {
        ifstream file(string(getenv("appdata"))+"\\Orita\\data\\time.txt");
        int time;
        file>>time;
        file.close();
        return time;
    }
}
void change_time_limit(int time) {Data::change_time_limit(time);}
int get_time_limit() {return Data::get_time_limit();}
#endif