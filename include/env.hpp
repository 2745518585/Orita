#pragma once
#ifndef _FILE_ENV
#define _FILE_ENV
#include"init.hpp"
#include"files.hpp"
#include"settings.hpp"
std::string get_env(const std::string &str,const pat &dir,const json &args)
{
    INFO("get env","str: "+add_squo(str),"dir: "+add_squo(dir),"args: "+args.dump());
    if(!enviroment_variable[str].is_null()) return (std::string)enviroment_variable[str];
    if(std::regex_match(str,std::regex("^\\*.*$"))) return get_file((file_number)str,dir).path();
    if(std::regex_match(str,std::regex("^\\..*$"))) return get_settings<json>(std::regex_replace(str,std::regex("\\."),"/")).dump();
    if(std::regex_match(str,std::regex("^#.*$")))
    {
        try {return args[str.substr(1)];}
        catch(...) {throw exception("empty environment variable args");}
    }
    if(!Poco::Environment::has(str)) throw exception("empty environment variable");
    return Poco::Environment::get(str);
}
std::string replace_env(const std::string &str,const pat &dir,const json &args)
{
    if(std::regex_match(str,std::regex("^[^%]*(%[^%]*%[^%]*)*%[^%]*$"))) throw exception("inviald environment string");
    size_t laspos=0;
    std::string resstr;
    for(auto it=std::sregex_iterator(str.begin(),str.end(),*new std::regex(std::regex("%[^%]*%")));it!=std::sregex_iterator();++it)
    {
        std::string substr=std::smatch(*it).str();
        resstr+=str.substr(laspos,std::smatch(*it).position()-laspos);
        laspos=std::smatch(*it).position()+std::smatch(*it).length();
        if(std::regex_match(substr,std::regex("^%[^%]+%$")))
        {
            resstr+=get_env(substr.substr(1,substr.size()-2),dir,args);
        }
        else resstr+="%";
    }
    resstr+=str.substr(laspos,str.size()-laspos);
    INFO("replace env","str: "+add_squo(str),"result: "+add_squo(resstr));
    return resstr;
}
template<typename ...others_type> json replace_env(json a,const others_type &...others)
{
    if(a.is_null()) return a;
    if(a.is_string()) return replace_env((std::string)a,others...);
    if(a.is_object())
    {
        for(auto &i:a.items()) a[i.key()]=replace_env(i.value(),others...);
    }
    if(a.is_array())
    {
        for(auto i=0;i<a.size();++i) a[i]=replace_env(a[i],others...);
    }
    return a;
}
namespace Env
{
    class Init
    {
      public:
        Init()
        {
            for(auto ev:enviroment_variable.items())
            {
                if(!ev.value().is_null()) ssetenv(ev.key(),ev.value());
            }
            for(int i=0;i<=_max_file_num;++i)
            {
                if(find_filestr(i)) ssetenv(((file_number)i).str(),get_file((file_number)i).path());
            }
            traverse_json(get_settings_merge(""),[](const std::string &key,const json &value){
                ssetenv(std::regex_replace(key,std::regex("\\/"),"."),value.dump());
            });
        }
        ~Init() {}
    }_Init;
}
#endif