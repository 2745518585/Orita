#pragma once
#ifndef _FILE_SETTINGS
#define _FILE_SETTINGS _FILE_SETTINGS
#include"init.hpp"
#include"log.hpp"
#include"files.hpp"
json all_settings,global_settings,default_settings,if_has_settings;
json::json_pointer others_settings=json::json_pointer("/~0list");
namespace Settings
{
    void read()
    {
        (sifstream(file_path/"files"/"settings.json"))>>default_settings;
        try {(sifstream(appdata_path/"settings.json"))>>global_settings;} catch(...) {}
        pat dir("/");
        dir.setDevice(running_path.getDevice());
        dir.setNode(running_path.getNode());
        for(int i=-1;i<=running_path.depth();++i)
        {
            if(i>=0) dir/=running_path[i];
            try
            {
                (sifstream(dir/".orita/settings.json"))>>all_settings[dir.toString()];
                if_has_settings[dir.toString()]=true;
            } catch(...) {};
        }
    }
    void save()
    {
        remove_null(global_settings);
        (sofstream(appdata_path/"settings.json"))<<global_settings.dump(4,' ',true,json::error_handler_t::ignore);
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
                    remove_null(all_settings[dir.toString()]);
                    (sofstream(dir/".orita/settings.json"))<<all_settings[dir.toString()].dump(4,' ',true,json::error_handler_t::ignore);
                }
            } catch(...) {};
        }
    }
    class Init
    {
      public:
        Init() {read();}
        ~Init() {save();}
    }_Init;
    json *get_settings_object(std::string key)
    {
        const json::json_pointer pointer=(json::json_pointer)key;
        json *object=NULL;
        try {if(!default_settings[pointer].is_null()) object=&default_settings[pointer];} catch(...) {}
        try {if(!global_settings[pointer].is_null()) object=&global_settings[pointer];} catch(...) {}
        for(auto &i:all_settings)
        {
            try {if(!i[pointer].is_null()) object=&i[pointer];} catch(...) {}
        }
        if(object) INFO("get settings object",add_squo(key),object->dump());
        else INFO("get settings object",add_squo(key),"NULL");
        return object;
    }
    template<typename Type> json *get_settings_object(std::string key)
    {
        if(std::is_same_v<Type,json>) return get_settings_object(key);
        const json::json_pointer pointer=(json::json_pointer)key;
        json *object=NULL;
        try {(Type)default_settings[pointer];object=&default_settings[pointer];} catch(...) {}
        try {(Type)global_settings[pointer];object=&global_settings[pointer];} catch(...) {}
        for(auto &i:all_settings)
        {
            try {(Type)i[pointer];object=&i[pointer];} catch(...) {}
        }
        if(object) INFO("get settings object",add_squo(key),object->dump());
        else INFO("get settings object",add_squo(key),"NULL");
        return object;
    }
    pat get_settings_path(std::string key)
    {
        const json::json_pointer pointer=(json::json_pointer)key;
        pat path=running_path;
        for(auto &i:all_settings.items())
        {
            try {if(!i.value()[pointer].is_null()) path=i.key();} catch(...) {}
        }
        INFO("get settings path",add_squo(key),add_squo(path));
        return path;
    }
    template<typename Type> pat get_settings_path(std::string key)
    {
        const json::json_pointer pointer=(json::json_pointer)key;
        pat path=running_path;
        for(auto &i:all_settings.items())
        {
            try {(Type)i.value()[pointer];path=i.key();} catch(...) {}
        }
        INFO("get settings path",add_squo(key),add_squo(path));
        return path;
    }
    json get_settings_merge(std::string key)
    {
        const json::json_pointer pointer=(json::json_pointer)key;
        json object=default_settings[pointer];
        merge(object,global_settings[pointer]);
        for(auto i:all_settings) merge(object,i[pointer]);
        INFO("get settings merge",add_squo(key),object.dump());
        return object;
    }
    template<typename Type> Type get_settings(std::string key)
    {
        const json::json_pointer pointer=(json::json_pointer)key;
        json *object=get_settings_object<Type>(key);
        if(!object)
        {
            WARN("get settings - null",add_squo(key));
            throw exception("null settings");
        }
        if constexpr(std::is_convertible<Type,std::string>::value)
        {
            try
            {
                std::string str=replace_env((std::string)*object);
                INFO("get settings str",add_squo(key),add_squo(str));
                return (Type)str;
            } catch(...) {WARN("get settings str - fail",add_squo(key),object->dump());}
        }
        else INFO("get settings",add_squo(key),object->dump());
        return (Type)(*object);
    }
}
using Settings::get_settings_object;
using Settings::get_settings_path;
using Settings::get_settings_merge;
using Settings::get_settings;
const unsigned max_process_num=get_settings<unsigned>("/max_process_num");
const unsigned max_thread_num=get_settings<unsigned>("/max_thread_num");
const tim runtime_limit=(tim)get_settings<unsigned>("/runtime_limit");
const fil compiler_command=get_settings<std::string>("/compiler/command");
const arg compile_argu=[]()
{
    json object=get_settings_merge("/compiler/argu");
    arg argu;
    for(auto i:object) if(i.is_string()) argu+=(std::string)i;
    return argu;
}();
const arg data_compile_argu=[]()
{
    json object=get_settings_merge("/data/compile_argu");
    arg argu;
    for(auto i:object) if(i.is_string()) argu+=(std::string)i;
    return argu;
}();
const tim compile_time_limit=get_settings<tim>("/compiler/time_limit");
namespace Settings
{
    std::string get_file(std::string key) noexcept
    {
        try {return ::get_file(get_settings<std::string>(key),get_settings_path<std::string>(key)).path();} catch(...) {}
        return "";
    }
}
fil default_infile=Settings::get_file("/data/infile");
fil default_outfile=Settings::get_file("/data/outfile");
fil default_ansfile=Settings::get_file("/data/ansfile");
fil default_chkfile=Settings::get_file("/data/chkfile");
fil default_data_dir=Settings::get_file("/data/data_dir");
const std::regex chk_correct_exit_code=(std::regex)get_settings<std::string>("/data/chk_exit_code");
const std::string exefile_str=Settings::get_settings<std::string>("/exefile");
pat get_exefile(const pat &file)
{
    return replace_env(exefile_str,running_path,{{"file",replace_extension(file,"").toString()},{"filename",replace_extension((pat)file.getFileName(),"").toString()},{"filepath",replace_extension(file.parent(),"").toString()}});
}
pat get_exefile(const fil &file)
{
    return get_exefile((pat)file.path());
}
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
using Settings::change_time_limit;
using Settings::get_time_limit;
bool show_file_info=Settings::get_settings<bool>("/show_file_info");
#endif