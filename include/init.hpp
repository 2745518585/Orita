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
#include<random>
#include<regex>
#include<sstream>
#include<thread>
#include<future>
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
#include"spdlog/sinks/basic_file_sink.h"

#include"Poco/File.h"
#include"Poco/Path.h"
#include"Poco/Environment.h"

#include"Poco/Process.h"
#include"Poco/Pipe.h"
#include"Poco/PipeStream.h"
#include"Poco/StreamCopier.h"

#include"Poco/Util/Application.h"
#include"Poco/Util/Option.h"
#include"Poco/Util/OptionSet.h"
#include"Poco/Util/OptionCallback.h"
#include"Poco/Util/OptionProcessor.h"
#include"Poco/Util/OptionException.h"
#include"Poco/Util/HelpFormatter.h"
#include"Poco/Exception.h"

// os
#ifdef _WIN32
const std::string os_name="windows";
#endif
#ifdef __linux__
const std::string os_name="linux";
#endif

// json
void merge(json &a,json b)
{
    for(auto &i:b.items())
    {
        if(i.value().is_object()) merge(a[i.key()],i.value());
        else if(!i.value().is_null()) a[i.key()]=i.value();
    }
}

// code
std::string UTF8tosys(const std::string &str)
{
    return str;
}
std::string systoUTF8(const std::string &str)
{
    return str;
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
template<typename Type,typename Func> std::string vec_to_str(const std::vector<Type> &vec,Func func)
{
    std::string str;
    for(auto i:vec) str+=func(i)+" ";
    return str;
}

// path
using pat=Poco::Path;
using fil=Poco::File;
const char path_separator=pat::separator();
pat operator/(pat path1,const pat &path2)
{
    return path1.append(path2);
}
pat &operator/=(pat &path1,const pat &path2)
{
    return path1=path1/path2;
}
fil operator/(const fil &path1,const fil &path2)
{
    pat tmp=path1.path();
    return tmp.append(path2.path()).toString();
}
fil &operator/=(fil &path1,const fil &path2)
{
    return path1=path1/path2;
}
bool operator==(const pat &path1,const pat &path2)
{
    return path1.toString()==path2.toString();
}
bool operator!=(const pat &path1,const pat &path2)
{
    return path1.toString()!=path2.toString();
}
std::string add_quo(const pat &path)
{
    return "\""+path.toString()+"\"";
}
std::string add_quo(const fil &path)
{
    return "\""+path.path()+"\"";
}
std::string add_squo(const pat &path)
{
    return "'"+path.toString()+"'";
}
std::string add_squo(const fil &path)
{
    return "'"+path.path()+"'";
}
pat replace_extension(pat file,const std::string suf="")
{
    return file.setExtension(suf);
}
pat replace_extension(fil file,const std::string suf="")
{
    return ((pat)file.path()).setExtension(suf).toString();
}
std::string sgetenv(const std::string &str);
const pat running_path=[]()
{
    return (pat)(pat::current());
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
    pat path=tmp;
    return path.parent().parent().parent();
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
json enviroment_variable={
    {"{RUNNING_PATH}",running_path.toString()},
    {"{FILE_PATH}",file_path.toString()},
    {"{APPDATA_PATH}",appdata_path.toString()},
    {"{OS_NAME}",os_name}
};
std::string sgetenv(const std::string &str)
{
    if(!enviroment_variable[str].is_null()) return (std::string)enviroment_variable[str];
    if(!Poco::Environment::has(str))
    {
        throw Poco::Exception("empty environment variable");
    }
    return Poco::Environment::get(str);
}

// time
using tim=std::chrono::milliseconds;
void ssleep(const tim time)
{
    std::this_thread::sleep_for(time);
}
class timer
{
  public:
    decltype(std::chrono::high_resolution_clock::now()) begin_time;
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
std::ostream &operator<<(std::ostream &output,tim str)
{
    output<<std::to_string(str.count())<<"ms";
    return output;
}
std::ofstream &operator<<(std::ofstream &output,tim str)
{
    output<<std::to_string(str.count())<<"ms";
    return output;
}

// print
#ifdef _WIN32
const pat system_nul="\\\\.\\nul";
const pat system_con="\\\\.\\con";
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
        if constexpr(std::is_convertible<Type,pat>::value) stream.open(pat(file).toString());
        else if constexpr(std::is_convertible<Type,fil>::value) stream.open(fil(file).path());
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
};
class sofstream
{
  public:
    std::ofstream stream;
    bool if_sys;
    template<typename Type> void open(const Type &file,const std::ios_base::openmode &mode=std::ios::out)
    {
        stream.close();
        if constexpr(std::is_convertible<Type,pat>::value) stream.open(pat(file).toString(),mode);
        else if constexpr(std::is_convertible<Type,fil>::value) stream.open(fil(file).path(),mode);
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
}scout(std::cout),scerr(std::cerr);
FILE *sfopen(const std::string &file,const std::string mode)
{
    return fopen(file.c_str(),mode.c_str());
}
int sfclose(FILE *file)
{
    return fclose(file);
}
void hide_cursor() {scout<<"\033[?25l"<<std::flush;}
void show_cursor() {scout<<"\033[?25h"<<std::flush;}

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
    return system(("cmd /C "+add_quo(command)).c_str());
    #endif
    #ifdef __linux__
    return system(command.c_str());
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
    return result;
}
#endif

// random
unsigned rnd()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen();
}

//init
namespace Init
{
    class Init
    {
      public:
        Init() {hide_cursor();}
        ~Init() {show_cursor();}
    }_Init;
}