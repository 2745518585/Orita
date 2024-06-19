#pragma once
#ifndef _FILE_SETTINGS
#define _FILE_SETTINGS
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
    std::string replace_settings_path(const std::string &str,const pat &dir)
    {
        if(std::regex_match(str,std::regex("^[^%]*(%[^%]*%[^%]*)*%[^%]*$"))) throw exception("inviald environment string");
        size_t laspos=0;
        std::string resstr;
        for(auto it=std::sregex_iterator(str.begin(),str.end(),*new std::regex(std::regex("%[^%]*%")));it!=std::sregex_iterator();++it)
        {
            std::string substr=std::smatch(*it).str();
            resstr+=str.substr(laspos,std::smatch(*it).position()-laspos);
            laspos=std::smatch(*it).position()+std::smatch(*it).length();
            if(substr=="%{SETTINGS_PATH}%") resstr+=dir.toString();
            else resstr+=substr;
        }
        resstr+=str.substr(laspos,str.size()-laspos);
        INFO("replace settings path","str: "+add_squo(str),"result: "+add_squo(resstr));
        return resstr;
    }
    json replace_settings_path(const json &object,const pat &dir)
    {
        if(object.is_object())
        {
            json res=json::parse("{}");
            for(auto i:object.items()) res[i.key()]=replace_settings_path(i.value(),dir);
            return res;
        }
        if(object.is_array())
        {
            json res=json::parse("[]");
            for(int i=0;i<object.size();++i) res[i]=replace_settings_path(object[i],dir);
            return res;
        }
        if(object.is_string()) return replace_settings_path((std::string)object,dir);
        else return object;
    }
    json *get_settings_object(const std::string &key)
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
    template<typename Ty> json *get_settings_object(const std::string &key)
    {
        if(std::is_same_v<Ty,json>) return get_settings_object(key);
        const json::json_pointer pointer=(json::json_pointer)key;
        json *object=NULL;
        try {(Ty)default_settings[pointer];object=&default_settings[pointer];} catch(...) {}
        try {(Ty)global_settings[pointer];object=&global_settings[pointer];} catch(...) {}
        for(auto &i:all_settings)
        {
            try {(Ty)i[pointer];object=&i[pointer];} catch(...) {}
        }
        if(object) INFO("get settings object",add_squo(key),object->dump());
        else INFO("get settings object",add_squo(key),"NULL");
        return object;
    }
    pat get_settings_path(const std::string &key)
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
    template<typename Ty> pat get_settings_path(const std::string &key)
    {
        if(std::is_same_v<Ty,json>) return get_settings_path(key);
        const json::json_pointer pointer=(json::json_pointer)key;
        pat path=running_path;
        for(auto &i:all_settings.items())
        {
            try {(Ty)i.value()[pointer];path=i.key();} catch(...) {}
        }
        INFO("get settings path",add_squo(key),add_squo(path));
        return path;
    }
    json get_settings_merge(const std::string &key)
    {
        const json::json_pointer pointer=(json::json_pointer)key;
        json object=replace_settings_path(default_settings[pointer],file_path);
        merge(object,replace_settings_path(global_settings[pointer],appdata_path));
        for(auto i:all_settings.items()) merge(object,replace_settings_path(i.value()[pointer],i.key()));
        INFO("get settings merge",add_squo(key),object.dump());
        return object;
    }
    template<typename Ty> Ty get_settings(const std::string &key)
    {
        const json::json_pointer pointer=(json::json_pointer)key;
        json *object=get_settings_object<Ty>(key);
        pat path=get_settings_path<Ty>(key);
        if(!object)
        {
            WARN("get settings - null",add_squo(key));
            throw exception("null settings");
        }
        if constexpr(std::is_convertible<Ty,std::string>::value)
        {
            try
            {
                std::string str=replace_env(replace_settings_path((std::string)*object,path));
                INFO("get settings str",add_squo(key),add_squo(str));
                return (Ty)str;
            } catch(...) {WARN("get settings str - fail",add_squo(key),object->dump());}
        }
        else INFO("get settings",add_squo(key),object->dump());
        return (Ty)(replace_settings_path(*object,path));
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
    for(auto i:object) if(i.is_string()) argu+=replace_env((std::string)i);
    return argu;
}();
const arg data_compile_argu=[]()
{
    json object=get_settings_merge("/data/compile_argu");
    arg argu;
    for(auto i:object) if(i.is_string()) argu+=replace_env((std::string)i);
    return argu;
}();
bool if_skip_compiled=get_settings<bool>("/compiler/skip_compiled");
const unsigned compile_try_times=get_settings<unsigned>("/compiler/try_times");
const tim compile_time_limit=get_settings<tim>("/compiler/time_limit");
fil default_infile=get_file(Settings::get_settings<std::string>("/data/infile"));
fil default_outfile=get_file(Settings::get_settings<std::string>("/data/outfile"));
fil default_ansfile=get_file(Settings::get_settings<std::string>("/data/ansfile"));
fil default_chkfile=get_file(Settings::get_settings<std::string>("/data/chkfile"));
fil default_data_dir=get_file(Settings::get_settings<std::string>("/data/data_dir"));
const arg in_args=get_settings<arg>("/data/in_args");
const arg out_args=get_settings<arg>("/data/out_args");
const arg ans_args=get_settings<arg>("/data/ans_args");
const arg chk_args=get_settings<arg>("/data/chk_args");
std::string data_file_str=get_settings<std::string>("/data/data_file");
const std::regex chk_correct_exit_code=(std::regex)get_settings<std::string>("/data/chk_exit_code");
const std::string data_info_pre=get_settings<std::string>("/data/info_pre");
const std::string exefile_str=get_settings<std::string>("/exefile");
pat get_exefile(const pat &file)
{
    return replace_env(exefile_str,running_path,env_args::filenosuf(file));
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