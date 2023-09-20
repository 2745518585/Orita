#pragma once
#ifndef _FILE_SETTINGS
#define _FILE_SETTINGS _FILE_SETTINGS
#include"init.hpp"
#include"log.hpp"
#include"files.hpp"
json settings,default_settings;
namespace Settings
{
    class Init
    {
      public:
        Init()
        {
            (sifstream(appdata_path/"settings.json",false))>>settings;
            (sifstream(file_path/"files"/"settings.json",false))>>default_settings;
        }
        ~Init()
        {
            (sofstream(appdata_path/"settings.json",false))<<std::setw(4)<<settings;
        }
    }_Init;
    template<typename Type> Type get_settings(std::string path,json::value_t type)
    {
        if(settings[json::json_pointer(path)].type()!=type)
        {
            ERROR("get settings - invaild value type",path,settings[json::json_pointer(path)].type_name());
            class invaild_settings {}error;
            throw error;
        }
        return (Type)settings[json::json_pointer(path)];
    }
    template<typename Type> Type get_default_settings(std::string path,json::value_t type)
    {
        if(settings[json::json_pointer(path)].type()!=type)
        {
            ERROR("get default settings - invaild value type",path,settings[json::json_pointer(path)].type_name());
            class invaild_settings {}error;
            throw error;
        }
        return (Type)settings[json::json_pointer(path)];
    }
}
using Settings::get_settings;
using Settings::get_default_settings;
const unsigned max_thread_num=get_settings<unsigned>("/max_thread_num",json::value_t::number_unsigned);
const tim runtime_limit=(tim)get_settings<unsigned>("/runtime_limit",json::value_t::number_unsigned);
const std::string exe_suf=get_settings<std::string>("/exe_suf",json::value_t::string);
namespace Settings
{
    void change_time_limit(const tim time)
    {
        settings["data"]["time"]=(unsigned)time.count();
    }
    tim get_time_limit()
    {
        return get_settings<tim>("/data/time",json::value_t::number_unsigned);
    }
}
void change_time_limit(const tim time) {Settings::change_time_limit(time);}
tim get_time_limit() {return Settings::get_time_limit();}
const std::string compile_argu=get_settings<std::string>("/data/compile_argu",json::value_t::string);
fil default_infile=get_file(get_settings<std::string>("/data/infile",json::value_t::string));
fil default_outfile=get_file(get_settings<std::string>("/data/outfile",json::value_t::string));
fil default_ansfile=get_file(get_settings<std::string>("/data/ansfile",json::value_t::string));
fil default_chkfile=get_file(get_settings<std::string>("/data/chkfile",json::value_t::string));
fil default_data_dir=get_file(get_settings<std::string>("/data/data_dir",json::value_t::string)).path();
#endif