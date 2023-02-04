#ifndef _FILE_DATA
#define _FILE_DATA _FILE_DATA
#include"init.hpp"
namespace Data
{
    json data_json;
    void begin()
    {
        ifstream file(UTF8toGB(appdata_address+"\\Orita\\data\\data.json"));
        file>>data_json;
        file.close();
    }
    void end()
    {
        ofstream file((UTF8toGB(appdata_address+"\\Orita\\data\\data.json")));
        file<<setw(4)<<data_json;
        file.close();
    }
    void change_time_limit(int time)
    {
        data_json["time"]=time;
    }
    int get_time_limit()
    {
        return data_json["time"];
    }
}
void change_time_limit(int time) {Data::change_time_limit(time);}
int get_time_limit() {return Data::get_time_limit();}
#endif