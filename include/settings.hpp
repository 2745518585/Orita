#pragma once
#ifndef _FILE_SETTINGS
#define _FILE_SETTINGS _FILE_SETTINGS
#include"init.hpp"
#include"log.hpp"
#include"files.hpp"
json all_settings,global_settings,default_settings,if_has_settings;
namespace Settings
{
    class Init
    {
      public:
        Init()
        {
            (sifstream(file_path/"files"/os_name/"settings.json",false))>>default_settings;
            try {(sifstream(appdata_path/"settings.json",false))>>global_settings;} catch(...) {}
            pat dir("/");
            dir.setDevice(running_path.getDevice());
            dir.setNode(running_path.getNode());
            for(int i=-1;i<=running_path.depth();++i)
            {
                if(i>=0) dir/=running_path[i];
                try
                {
                    (sifstream(dir/".orita/settings.json",false))>>all_settings[dir.toString()];
                    if_has_settings[dir.toString()]=true;
                } catch(...) {};
            }
        }
        ~Init()
        {
            (sofstream(appdata_path/"settings.json",false))<<global_settings.dump(4,' ',true,json::error_handler_t::ignore);
            pat dir("/");
            dir.setDevice(running_path.getDevice());
            dir.setNode(running_path.getNode());
            for(int i=-1;i<=running_path.depth();++i)
            {
                if(i>=0) dir/=running_path[i];
                try
                {
                    if(!if_has_settings[dir.toString()].is_null())
                    {
                        ((fil)dir/".orita").createDirectory();
                        (sofstream(dir/".orita/settings.json",false))<<all_settings[dir.toString()].dump(4,' ',true,json::error_handler_t::ignore);
                    }
                } catch(...) {};
            }
        }
    }_Init;
    json *get_settings_object(std::string key)
    {
        const json::json_pointer pointer=(json::json_pointer)key;
        json *object=&default_settings[pointer];
        try {if(global_settings[pointer].type()==default_settings[pointer].type()) object=&global_settings[pointer];} catch(...) {}
        for(auto &i:all_settings)
        {
            try {if(i[pointer].type()==default_settings[pointer].type()) object=&i[pointer];} catch(...) {}
        }
        INFO("get settings object",add_squo(key),(*object).dump());
        return object;
    }
    template<typename Type> Type get_settings(std::string key)
    {
        const json::json_pointer pointer=(json::json_pointer)key;
        json *object=get_settings_object(key);
        INFO("get settings",add_squo(key),(*object).dump());
        return (Type)(*object);
    }
    pat get_settings_path(std::string key)
    {
        const json::json_pointer pointer=(json::json_pointer)key;
        pat path=running_path;
        try {if(global_settings[pointer].type()==default_settings[pointer].type()) path=running_path;} catch(...) {}
        for(auto &i:all_settings.items())
        {
            try {if(i.value()[pointer].type()==default_settings[pointer].type()) path=i.key();} catch(...) {}
        }
        INFO("get settings path",add_squo(key),add_squo(path));
        return path;
    }
}
using Settings::get_settings_object;
using Settings::get_settings;
using Settings::get_settings_path;
const unsigned max_thread_num=get_settings<unsigned>("/max_thread_num");
const tim runtime_limit=(tim)get_settings<unsigned>("/runtime_limit");
const std::string exe_suf=get_settings<std::string>("/exe_suf");
const std::string compile_argu=get_settings<std::string>("/data/compile_argu");
fil default_infile=get_file(get_settings<std::string>("/data/infile"),get_settings_path("/data/infile"));
fil default_outfile=get_file(get_settings<std::string>("/data/outfile"),get_settings_path("/data/outfile"));
fil default_ansfile=get_file(get_settings<std::string>("/data/ansfile"),get_settings_path("/data/ansfile"));
fil default_chkfile=get_file(get_settings<std::string>("/data/chkfile"),get_settings_path("/data/chkfile"));
fil default_data_dir=get_file(get_settings<std::string>("/data/data_dir"),get_settings_path("/data/data_dir"));
namespace Settings
{
    void change_time_limit(const tim time)
    {
        (*get_settings_object("/data/time"))=(unsigned)time.count();
    }
    tim get_time_limit()
    {
        return get_settings<tim>("/data/time");
    }
}
void change_time_limit(const tim time) {Settings::change_time_limit(time);}
tim get_time_limit() {return Settings::get_time_limit();}
#endif