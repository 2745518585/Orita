#pragma once
#ifndef _FILE_SETTINGS
#define _FILE_SETTINGS _FILE_SETTINGS
#include"init.hpp"
#include"log.hpp"
json settings;
namespace Settings
{
    class Init
    {
      public:
        Init()
        {
            (sifstream(appdata_path/"settings.json",false))>>settings;
        }
        ~Init()
        {
            (sofstream(appdata_path/"settings.json",false))<<std::setw(4)<<settings;
        }
    }_Init;
}
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
const unsigned max_thread_num=get_settings<unsigned>("/max_thread_num",json::value_t::number_unsigned);
const tim runtime_limit=get_settings<tim>("/runtime_limit",json::value_t::number_unsigned);
const pat exe_suf=get_settings<pat>("/exe_suf",json::value_t::string);
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
const pat default_checker=get_settings<std::string>("/data/default_checker",json::value_t::string);
const pat default_infile=get_settings<std::string>("/data/default_infile",json::value_t::string);
const pat default_outfile=get_settings<std::string>("/data/default_outfile",json::value_t::string);
const pat default_ansfile=get_settings<std::string>("/data/default_ansfile",json::value_t::string);
const pat default_chkfile=get_settings<std::string>("/data/default_chkfile",json::value_t::string);
#endif