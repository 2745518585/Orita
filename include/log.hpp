#pragma once
#ifndef _FILE_LOG
#define _FILE_LOG _FILE_LOG
#include"init.hpp"
class logger
{
    #define _LOG_INFO 1
    #define _LOG_WARN 2
    #define _LOG_ERROR 3
    #define _LOG_DEBUG 4
  private:
    const fil output_file;
    const std::string name;
    std::shared_ptr<spdlog::logger> output;
  public:
    const std::string get_str(const std::string &str)
    {
        return "\n>> "+str;
    }
    template<typename ...others_type> std::string get_str(const std::string &str,const others_type ...others)
    {
        return get_str(str)+get_str(others...);
    }
    template<typename ...others_type> void print(const int info,const std::string &str)
    {
        if(info==_LOG_INFO) output->info(str);
        if(info==_LOG_WARN) output->warn(str);
        if(info==_LOG_ERROR) output->error(str);
        if(info==_LOG_DEBUG) output->debug(str);
    }
    template<typename ...others_type> void print(const int info,const std::string &pre_str,const others_type ...others)
    {
        const std::string str=pre_str+":"+get_str(others...);
        if(info==_LOG_INFO) output->info(str);
        if(info==_LOG_WARN) output->warn(str);
        if(info==_LOG_ERROR) output->error(str);
        if(info==_LOG_DEBUG) output->debug(str);
    }
    logger(const fil &_output_file=appdata_path/"Orita.log",const std::string _name="Orita LOG"):output_file(_output_file),name(_name)
    {
        (sofstream)(output_file)<<name<<"\n";
        output=spdlog::basic_logger_mt(name,UTF8tosys(output_file.path()));
        output->set_level(spdlog::level::debug);
        output->flush_on(spdlog::level::trace);
        print(_LOG_INFO,"running_path","path: "+add_squo(running_path));
        print(_LOG_INFO,"appdata_path","path: "+add_squo(appdata_path));
        print(_LOG_INFO,"file_path","path: "+add_squo(file_path));
    }
    ~logger()
    {
        spdlog::drop(name);
    }
};
logger *orita_log=new logger;
#define INFO(...) orita_log->print(_LOG_INFO,__VA_ARGS__)
#define WARN(...) orita_log->print(_LOG_WARN,__VA_ARGS__)
#define ERROR(...) orita_log->print(_LOG_ERROR,__VA_ARGS__)
#define DEBUG(...) orita_log->print(_LOG_DEBUG,__VA_ARGS__)
#endif