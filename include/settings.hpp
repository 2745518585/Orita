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
            (sifstream(file_path/"files"/"settings.json",false))>>default_settings;
            try {(sifstream(appdata_path/"settings.json",false))>>settings;} catch(...) {};
        }
        ~Init()
        {
            (sofstream(appdata_path/"settings.json",false))<<std::setw(4)<<settings;
        }
    }_Init;
    template<typename Type> Type get_settings(std::string path)
    {
        if(settings[json::json_pointer(path)].type()!=default_settings[json::json_pointer(path)].type())
        {
            ERROR("get settings - invaild value type",path,settings[json::json_pointer(path)].type_name());
            settings[json::json_pointer(path)]=default_settings[json::json_pointer(path)];
        }
        (Type)settings[json::json_pointer(path)];
        return (Type)settings[json::json_pointer(path)];
    }
}
using Settings::get_settings;
const unsigned max_thread_num=get_settings<unsigned>("/max_thread_num");
const tim runtime_limit=(tim)get_settings<unsigned>("/runtime_limit");
const std::string exe_suf=get_settings<std::string>("/exe_suf");
namespace Settings
{
    void change_time_limit(const tim time)
    {
        settings["data"]["time"]=(unsigned)time.count();
    }
    tim get_time_limit()
    {
        return get_settings<tim>("/data/time");
    }
}
void change_time_limit(const tim time) {Settings::change_time_limit(time);}
tim get_time_limit() {return Settings::get_time_limit();}
const std::string compile_argu=get_settings<std::string>("/data/compile_argu");
fil default_infile=get_file(get_settings<std::string>("/data/infile"),false);
fil default_outfile=get_file(get_settings<std::string>("/data/outfile"),false);
fil default_ansfile=get_file(get_settings<std::string>("/data/ansfile"),false);
fil default_chkfile=get_file(get_settings<std::string>("/data/chkfile"),false);
fil default_data_dir=get_file(get_settings<std::string>("/data/data_dir"),false);
#endif