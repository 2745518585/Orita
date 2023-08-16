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
        if(settings["data"]["time"].type()!=json::value_t::number_unsigned)
        {
            ERROR("invaild time limit");
            class invaild_time_limit {}error;
            throw error;
        }
        return (tim)settings["data"]["time"];
    }
}
void change_time_limit(const tim time) {Data::change_time_limit(time);}
tim get_time_limit() {return Data::get_time_limit();}
const std::string compile_argu=[]()
{
    if(settings["data"]["compile_argu"].type()!=json::value_t::string)
    {
        ERROR("invaild compile argu");
        class invaild_compile_argu {}error;
        throw error;
    }
    return UTF8tosys(settings["data"]["compile_argu"]);
}();
const std::string default_checker=[]()
{
    if(settings["data"]["default_checker"].type()!=json::value_t::string)
    {
        ERROR("invaild default checker");
        class invaild_default_checker {}error;
        throw error;
    }
    return UTF8tosys(settings["data"]["default_checker"]);
}();
#endif