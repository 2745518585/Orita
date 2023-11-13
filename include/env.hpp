#pragma once
#ifndef _FILE_ENV
#define _FILE_ENV _FILE_ENV
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
#endif