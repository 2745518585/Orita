#pragma once
#ifndef _FILE_DATA
#define _FILE_DATA _FILE_DATA
#include"init.hpp"
namespace Data
{
    json data_json;
    void begin()
    {
        std::ifstream file(makepath(appdata_path,"data.json"));
        file>>data_json;
        file.close();
    }
    void end()
    {
        std::ofstream file(makepath(appdata_path,"data.json"));
        file<<std::setw(4)<<data_json;
        file.close();
    }
    void change_time_limit(const tim time)
    {
        data_json["time"]=time.count();
    }
    tim get_time_limit()
    {
        return (tim)data_json["time"];
    }
    void change_compile_argu(const std::string &argu)
    {
        data_json["compile_argu"]=systoUTF8(argu);
    }
    std::string get_compile_argu()
    {
        return UTF8tosys(data_json["compile_argu"]);
    }
}
void change_time_limit(const tim time) {Data::change_time_limit(time);}
tim get_time_limit() {return Data::get_time_limit();}
void change_compile_argu(const std::string &argu) {Data::change_compile_argu(argu);}
std::string get_compile_argu() {return Data::get_compile_argu();}
#endif