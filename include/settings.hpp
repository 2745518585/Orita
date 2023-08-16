#pragma once
#ifndef _FILE_SETTINGS
#define _FILE_SETTINGS _FILE_SETTINGS
#include"init.hpp"

json settings;
namespace Settings
{
    class Init
    {
      public:
        Init()
        {
            orita_log.clear();
            (std::ifstream)(makepath(appdata_path,"settings.json"))>>settings;
            hide_cursor();
            INFO("orita start");
        }
        ~Init()
        {
            (std::ofstream)(makepath(appdata_path,"settings.json"))<<std::setw(4)<<settings;
            show_cursor();
            INFO("orita end");
        }
    }_Init;
}

const unsigned max_thread_num=[]()
{
    if(settings["max_thread_num"].type()!=json::value_t::number_unsigned)
    {
        ERROR("invaild thread num");
        class invaild_thread_num {}error;
        throw error;
    }
    return (unsigned)settings["max_thread_num"];
}();

const tim runtime_limit=[]()
{
    if(settings["runtime_limit"].type()!=json::value_t::number_unsigned)
    {
        ERROR("invaild runtime limit");
        class invaild_exe_suf {}error;
        throw error;
    }
    return (tim)settings["runtime_limit"];
}();

const std::string exe_suf=[]()
{
    if(settings["exe_suf"].type()!=json::value_t::string)
    {
        ERROR("invaild exe suf");
        class invaild_exe_suf {}error;
        throw error;
    }
    return (std::string)settings["exe_suf"];
}();

namespace Settings
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
void change_time_limit(const tim time) {Settings::change_time_limit(time);}
tim get_time_limit() {return Settings::get_time_limit();}

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