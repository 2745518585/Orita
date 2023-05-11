#pragma once
#ifndef _FILE_DATA
#define _FILE_DATA _FILE_DATA
#include"init.hpp"
namespace Data
{
    json data_json;
    void begin()
    {
        std::ifstream file(appdata_path+sPS+"data.json");
        file>>data_json;
        file.close();
    }
    void end()
    {
        std::ofstream file(appdata_path+sPS+"data.json");
        file<<std::setw(4)<<data_json;
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
    void change_compile_argu(std::string para)
    {
        data_json["compile_argu"]=systoUTF8(para);
    }
    std::string get_compile_argu()
    {
        return UTF8tosys(data_json["compile_argu"]);
    }
}
void change_time_limit(int time) {Data::change_time_limit(time);}
int get_time_limit() {return Data::get_time_limit();}
void change_compile_argu(std::string para) {Data::change_compile_argu(para);}
std::string get_compile_argu() {return Data::get_compile_argu();}
#endif