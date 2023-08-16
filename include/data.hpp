#pragma once
#ifndef _FILE_DATA
#define _FILE_DATA _FILE_DATA
#include"init.hpp"
namespace Data
{
    void change_time_limit(const tim time)
    {
        settings["data"]["time"]=time.count();
    }
    tim get_time_limit()
    {
        return (tim)settings["data"]["time"];
    }
    void change_compile_argu(const std::string &argu)
    {
        settings["data"]["compile_argu"]=systoUTF8(argu);
    }
    std::string get_compile_argu()
    {
        return UTF8tosys(settings["data"]["compile_argu"]);
    }
}
void change_time_limit(const tim time) {Data::change_time_limit(time);}
tim get_time_limit() {return Data::get_time_limit();}
void change_compile_argu(const std::string &argu) {Data::change_compile_argu(argu);}
std::string get_compile_argu() {return Data::get_compile_argu();}
const std::string default_checker=(std::string)settings["data"]["default_checker"];
#endif