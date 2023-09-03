#pragma once
#ifndef _FILE_INIT
#define _FILE_INIT _FILE_INIT
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<string>
#include<filesystem>
#include<typeinfo>
#include<regex>
#include<sstream>
#include<thread>
#include<atomic>
#include<mutex>
#include<condition_variable>
#define NOMINMAX

#ifdef _WIN32
#include<windows.h>
#include<direct.h>
#endif

#ifdef __linux__
#include<unistd.h>
#include<limits.h>
#include<sys/time.h>
#endif

#include"nlohmann/json.hpp"
using json=nlohmann::json;
#include"termcolor/termcolor.hpp"
#include"spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

// code
#ifdef _WIN32
std::string UTF8toGB(const std::string &utf8)
{
    if(utf8.empty()) return "";
    std::stringstream ss;
    int len=MultiByteToWideChar(CP_UTF8,0,utf8.c_str(),-1,NULL,0);
    wchar_t*wstr=new wchar_t[len+1];
    memset(wstr,0,len+1);
    MultiByteToWideChar(CP_UTF8,0,utf8.c_str(),-1,wstr,len);
    len=WideCharToMultiByte(CP_ACP,0,wstr,-1,NULL,0,NULL,NULL);
    char *str=new char[len+1];
    memset(str,0,len+1);
    WideCharToMultiByte(CP_ACP,0,wstr,-1,str,len,NULL,NULL);
    ss<<str;
    delete []wstr;
    delete []str;
    return ss.str();
}
std::string GBtoUTF8(const std::string &gb2312)
{
    if(gb2312.empty()) return "";
    std::stringstream ss;
    int len=MultiByteToWideChar(CP_ACP,0,gb2312.c_str(),-1,NULL,0);
    wchar_t*wstr=new wchar_t[len+1];
    memset(wstr,0,len+1);
    MultiByteToWideChar(CP_ACP,0,gb2312.c_str(),-1,wstr,len);
    len=WideCharToMultiByte(CP_UTF8,0,wstr,-1,NULL,0,NULL,NULL);
    char *str=new char[len+1];
    memset(str,0,len+1);
    WideCharToMultiByte(CP_UTF8,0,wstr,-1,str,len,NULL,NULL);
    ss<<str;
    delete []wstr;
    delete []str;
    return ss.str();
}
const UINT codepage=GetACP();
std::string UTF8tosys(const std::string &str)
{
    if(codepage==936) return UTF8toGB(str);
    else return str;
}
std::string systoUTF8(const std::string &str)
{
    if(codepage==936) return GBtoUTF8(str);
    else return str;
}
#endif
#ifdef __linux__
const UINT codepage=65001;
std::string UTF8tosys(const std::string &str)
{
    return str;
}
std::string systoUTF8(const std::string &str)
{
    return str;
}
#endif
std::string sgetenv(const std::string &str)
{
    return systoUTF8(getenv(str.c_str()));
}

// result
class res
{
  public:
    enum type {NL,AC,SA,SS,WA,RE,TLE_CA,TLE_WA,TLE_O,CE,DA,TO,NF,II,FL};
    type result;
    res():result(type::NL) {}
    res(type _result):result(_result) {}
    bool is(const type target_result)const {return result==target_result;}
    bool is(const std::initializer_list<type> target_result_list)const
    {
        for(auto target_result:target_result_list) if(result==target_result) return true;
        return false;
    }
    bool istrue()const {return is({type::AC,type::SA,type::SS});}
    bool isfalse()const {return is({type::WA,type::RE,type::TLE_CA,type::TLE_WA,type::TLE_O,type::CE,type::DA,type::TO,type::NF,type::II,type::FL});}
    bool isnull()const {return is({type::NL});}
};

// string
template<typename num_type> std::string to_string_len(const num_type num,const size_t len)
{
    std::string str=std::to_string(num);
    if(str.size()>len) return str;
    return std::string(len-str.size(),'0')+str;
}
template<typename num_type> std::string to_string_hex(const num_type num)
{
    std::stringstream strstream;
    strstream<<std::hex<<num;
    return strstream.str();
}
std::string add_quo(const std::string &str)
{
    return "\""+str+"\"";
}
std::string add_squo(const std::string &str)
{
    return "'"+str+"'";
}

// path
using pat=std::filesystem::path;
const char path_separator=std::filesystem::path::preferred_separator;
std::string add_quo(const pat &path)
{
    return "\""+path.string()+"\"";
}
std::string add_squo(const pat &path)
{
    return "'"+path.string()+"'";
}
pat replace_extension(pat file,const pat suf=pat())
{
    return file.replace_extension(suf);
}
const pat running_path=[]()
{
    char path[1001];
    getcwd(path,1000);
    return (pat)(systoUTF8(path));
}();
const pat file_path=[]()
{
    char tmp[10001];
    #ifdef _WIN32
    GetModuleFileNameA(NULL,tmp,MAX_PATH);
    #endif
    #ifdef __linux__
    realpath("/proc/self/exe",tmp);
    #endif
    pat path=systoUTF8(tmp);
    return path.parent_path().parent_path();
}();
const pat appdata_path=[]()
{
    #ifdef _WIN32
    return pat(sgetenv("APPDATA"))/"Orita";
    #endif
    #ifdef __linux__
    return pat(sgetenv("HOME"))/".Orita";
    #endif
}();

// time
using tim=std::chrono::milliseconds;
void ssleep(const tim time)
{
    std::this_thread::sleep_for(time);
}
class timer
{
  public:
    std::chrono::_V2::system_clock::time_point begin_time;
    void init()
    {
        begin_time=std::chrono::high_resolution_clock::now();
    }
    tim get_time()
    {
        auto end_time=std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<tim>(end_time-begin_time);
    }
};
std::ofstream &operator<<(std::ofstream &output,tim str)
{
    output<<std::to_string(str.count())<<"ms";
    return output;
}
// print
#ifdef _WIN32
const pat system_nul="nul";
const pat system_con="con";
#endif
#ifdef __linux__
const pat system_nul="/dev/null";
const pat system_con="/dev/tty";
#endif
class sifstream
{
  public:
    std::ifstream stream;
    bool if_sys;
    template<typename Type> void open(const Type &file,const std::ios_base::openmode &mode=std::ios::out)
    {
        if constexpr(std::is_convertible<Type,pat>::value) stream.open(UTF8tosys(pat(file).string()));
        else if constexpr(std::is_convertible<Type,std::ifstream>::value) stream.open(file);
    }
    sifstream() {}
    template<typename Type> sifstream(const Type &file,const bool _if_sys=true):if_sys(_if_sys) {open(file);}
    template<typename Type> sifstream(const Type &file,const std::ios_base::openmode &mode,const bool _if_sys=true):if_sys(_if_sys) {open(file,mode);}
    void close() {stream.close();}
    template<typename Type> sifstream &operator>>(Type &val)
    {
        stream>>val;
        return *this;
    }
    sifstream &operator>>(std::string &str)
    {
        stream>>str;
        if(if_sys) str=systoUTF8(str);
        return *this;
    }
};
class sofstream
{
  public:
    std::ofstream stream;
    bool if_sys;
    template<typename Type> void open(const Type &file,const std::ios_base::openmode &mode=std::ios::out)
    {
        stream.close();
        if constexpr(std::is_convertible<Type,pat>::value) stream.open(UTF8tosys(pat(file).string()),mode);
        else if constexpr(std::is_convertible<Type,std::ofstream>::value) stream.open(file,mode);
    }
    sofstream() {}
    template<typename Type> sofstream(const Type &file,const bool _if_sys=true):if_sys(_if_sys) {open(file);}
    template<typename Type> sofstream(const Type &file,const std::ios_base::openmode &mode,const bool _if_sys=true):if_sys(_if_sys) {open(file,mode);}
    void close() {stream.close();}
    void flush() {stream.flush();}
    template<typename Type> sofstream &operator<<(const Type &val)
    {
        stream<<val;
        return *this;
    }
    sofstream &operator<<(std::ostream &(*manipulator)(std::ostream&))
    {
        stream<<manipulator;
        return *this;
    }
    sofstream &operator<<(const std::string &str)
    {
        if(if_sys) stream<<UTF8tosys(str);
        else stream<<str;
        return *this;
    }
};
class sostream
{
  public:
    std::ostream &stream;
    bool if_sys;
    template<typename Type> sostream(Type &_stream,bool _if_sys=true):stream(_stream),if_sys(_if_sys) {}
    void flush() {stream.flush();}
    template<typename Type> sostream &operator<<(const Type &val)
    {
        stream<<val;
        return *this;
    }
    sostream &operator<<(std::ostream &(*manipulator)(std::ostream&))
    {
        stream<<manipulator;
        return *this;
    }
    sostream &operator<<(const std::string &str)
    {
        if(if_sys) stream<<UTF8tosys(str);
        else stream<<str;
        return *this;
    }
}scout(std::cout);
FILE *sfopen(const std::string &file,const std::string mode)
{
    return fopen(UTF8tosys(file).c_str(),mode.c_str());
}
int sfclose(FILE *file)
{
    return fclose(file);
}
void hide_cursor() {scout<<"\033[?25l"<<std::flush;}
void show_cursor() {scout<<"\033[?25h"<<std::flush;}


// log
class logger
{
    #define _LOG_INFO 1
    #define _LOG_WARN 2
    #define _LOG_ERROR 3
    #define _LOG_DEBUG 4
  private:
    const pat output_file;
    const std::string name;
    std::mutex read_lock;
    std::shared_ptr<spdlog::logger> output;
  public:
    logger(const pat &_output_file=appdata_path/"Orita.log",const std::string _name="Orita LOG"):output_file(_output_file),name(_name) {}
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
        read_lock.lock();
        if(info==_LOG_INFO) output->info(str);
        if(info==_LOG_WARN) output->warn(str);
        if(info==_LOG_ERROR) output->error(str);
        if(info==_LOG_DEBUG) output->debug(str);
        read_lock.unlock();
    }
    template<typename ...others_type> void print(const int info,const std::string &pre_str,const others_type ...others)
    {
        read_lock.lock();
        const std::string str=pre_str+":"+get_str(others...);
        if(info==_LOG_INFO) output->info(str);
        if(info==_LOG_WARN) output->warn(str);
        if(info==_LOG_ERROR) output->error(str);
        if(info==_LOG_DEBUG) output->debug(str);
        read_lock.unlock();
    }
    void clear()
    {
        read_lock.lock();
        (sofstream)(output_file)<<"Orita LOG\n";
        output=spdlog::basic_logger_mt(name,UTF8tosys(output_file.string()));
        output->set_level(spdlog::level::debug);
        output->flush_on(spdlog::level::trace);
        read_lock.unlock();
    }
}orita_log;
#define INFO(...) orita_log.print(_LOG_INFO,__VA_ARGS__)
#define WARN(...) orita_log.print(_LOG_WARN,__VA_ARGS__)
#define ERROR(...) orita_log.print(_LOG_ERROR,__VA_ARGS__)
#define DEBUG(...) orita_log.print(_LOG_DEBUG,__VA_ARGS__)

// command
#ifdef _WIN32
const std::string system_to_nul=" > nul 2>&1 ";
const std::string system_to_con=" > con 2>&1 ";
const int sys_exit_code=0;
#endif
#ifdef __linux__
const std::string system_to_nul=" > /dev/null 2>&1 ";
const std::string system_to_con=" > /dev/tty 2>&1 ";
const int sys_exit_code=8;
#endif
int ssystem(const std::string &command)
{
    #ifdef _WIN32
    return system(("cmd /C "+add_quo(UTF8tosys(command))).c_str());
    #endif
    #ifdef __linux__
    return system(UTF8tosys(command).c_str());
    #endif
}
int kill_task(const pat &task)
{
    #ifdef _WIN32
    const int result=ssystem("taskkill /f /im "+add_quo(task)+system_to_nul);
    #endif
    #ifdef __linux__
    const int result=ssystem("killall "+add_quo(task)+system_to_nul);
    #endif
    if(result) WARN("fail kill task","task: "+add_squo(task));
    else INFO("kill task","task: "+add_squo(task));
    return result;
}
#endif

namespace Init
{
    class Init
    {
      public:
        Init()
        {
            orita_log.clear();
            INFO("running_path","path: "+add_squo(running_path));
            INFO("appdata_path","path: "+add_squo(appdata_path));
            INFO("file_path","path: "+add_squo(file_path));
            hide_cursor();
        }
        ~Init()
        {
            show_cursor();
        }
    }_Init;
}