#ifndef _FILE_DATA
#define _FILE_DATA _FILE_DATA
#include"init.hpp"
namespace Data
{
    json data_json;
    void begin()
    {
        ifstream file(UTF8toGB(appdata_address+"\\Orita\\data.json"));
        file>>data_json;
        file.close();
    }
    void end()
    {
        ofstream file((UTF8toGB(appdata_address+"\\Orita\\data.json")));
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
    void change_compile_parameter(string para)
    {
        data_json["compile_parameter"]=para;
    }
    string get_compile_parameter()
    {
        return data_json["compile_parameter"];
    }
}
void change_time_limit(int time) {Data::change_time_limit(time);}
int get_time_limit() {return Data::get_time_limit();}
void change_compile_parameter(string para) {Data::change_compile_parameter(para);}
string get_compile_parameter() {return Data::get_compile_parameter();}
#endif