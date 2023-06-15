#pragma once
#ifndef _FILE_INIT
#define _FILE_INIT _FILE_INIT
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<string>
#include<sstream>
#include<thread>
#include<atomic>
#include<mutex>
#include<condition_variable>
#include"nlohmann/json.hpp"
using json=nlohmann::json;

#ifdef _WIN32
#include<windows.h>
#include<direct.h>
#endif

#ifdef __linux__
#include<unistd.h>
#include<limits.h>
#include<sys/time.h>
#endif

// code
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
std::string UTF8tosys(const std::string str)
{
    #ifdef _WIN32
    return UTF8toGB(str);
    #endif
    #ifdef __linux__
    return str;
    #endif
}
std::string systoUTF8(const std::string str)
{
    #ifdef _WIN32
    return GBtoUTF8(str);
    #endif
    #ifdef __linux__
    return str;
    #endif
}

// path
#ifdef _WIN32
char PS='\\';
#endif
#ifdef __linux__
char PS='/';
#endif
std::string makepath(const std::string path)
{
    return path;
}
template<typename ...others_type>
std::string makepath(const std::string path,const others_type ...others)
{
    return path+PS+makepath(others...);
}

// result
#define _NL 0
#define _AC 1
#define _SA 2
#define _SS 3
#define _WA -1
#define _RE -2
#define _TLE_CA -3
#define _TLE_WA -4
#define _TLE_O -5
#define _CE -6
#define _DA -7
#define _TO -8
#define _NF -9
#define _II -10
#define _FL -11
class res
{
  private:
    int result;
  public:
    res():result(_NL){}
    res(const int _result):result(_result){}
    bool is(const int _result)const
    {
        return result==_result;
    }
    bool isnull()const
    {
        return result==0;
    }
    bool istrue()const
    {
        return result>0;
    }
    bool isfalse()const
    {
        return result<0;
    }
};

// string
template<typename T>
std::string to_string_len(const T num,const int len)
{
    std::string str=std::to_string(num);
    if(str.size()>len) return str;
    return std::string(len-str.size(),'0')+str;
}
std::string add_quotation(const std::string str)
{
    return "\""+str+"\"";
}

// local path
namespace Init
{
    std::string get_running_path()
    {
        char path[1001];
        getcwd(path,1000);
        return path;
    }
    std::string get_file_path()
    {
        char tmp[10001];
        #ifdef _WIN32
        GetModuleFileNameA(NULL,tmp,MAX_PATH);
        #endif
        #ifdef __linux__
        realpath("/proc/self/exe",tmp);
        #endif
        std::string path=tmp;
        return path.substr(0,path.find_last_of(PS,path.find_last_of(PS)-1));
    }
    std::string get_appdata_path()
    {
        #ifdef _WIN32
        return makepath(getenv("appdata"),"Orita");
        #endif
        #ifdef __linux__
        return makepath(getenv("HOME"),".Orita");
        #endif
    }
}
const std::string running_path=Init::get_running_path(),file_path=Init::get_file_path(),appdata_path=Init::get_appdata_path();

// log
class Log
{
    #define _LOG_INFO 1
    #define _LOG_WARN 2
    #define _LOG_ERROR 3
    #define _LOG_DEBUG 4
  private:
    std::string output_file;
    std::mutex read_lock;
    std::ofstream output;
  public:
    Log()
    {
        output_file=makepath(appdata_path,"Orita.log");
    }
    void print(const std::string str)
    {
        output<<str<<"\n";
    }
    template<typename ...others_type>
    void print(const std::string str,const others_type ...others)
    {
        print(str);
        print(others...);
    }
    template<typename ...others_type>
    void print(const int info,const std::string str,const others_type ...others)
    {
        read_lock.lock();
        output.open(output_file,std::ios::app);
        if(info==_LOG_INFO) output<<"[Info] "<<str<<":\n";
        if(info==_LOG_WARN) output<<"[Warn] "<<str<<":\n";
        if(info==_LOG_ERROR) output<<"[Error] "<<str<<":\n";
        if(info==_LOG_DEBUG) output<<"[Debug] "<<str<<":\n";
        print(others...);
        output.close();
        read_lock.unlock();
    }
    void clear()
    {
        read_lock.lock();
        (std::ofstream)(output_file)<<"Orita LOG\n";
        read_lock.unlock();
        print(_LOG_INFO,"running_path","path: "+add_quotation(running_path));
        print(_LOG_INFO,"appdata_path","path: "+add_quotation(appdata_path));
        print(_LOG_INFO,"file_path","path: "+add_quotation(file_path));
    }
}orita_log;

// time
void ssleep(const unsigned time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}
class stime
{
  public:
    std::chrono::_V2::system_clock::time_point begin_time;
    void init()
    {
        begin_time=std::chrono::high_resolution_clock::now();
    }
    int get_time()
    {
        auto end_time=std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time=end_time-begin_time;
        return time.count()*1000;
    }
};

// command
#ifdef _WIN32
const std::string system_to_nul=" > nul 2>&1 ";
#endif
#ifdef __linux__
const std::string system_to_nul=" > /dev/null 2>&1 ";
#endif
#ifdef _WIN32
const int sys_exit_code=1;
#endif
#ifdef __linux__
const int sys_exit_code=256;
#endif
int ssystem(const std::string command)
{
    #ifdef _WIN32
    return system(("cmd /C "+add_quotation(command)).c_str());
    #endif
    #ifdef __linux__
    return system(command.c_str());
    #endif
}
int find_file(const std::string file)
{
    const int result=ssystem("dir "+add_quotation(file)+system_to_nul);
    if(result) orita_log.print(_LOG_WARN,"fail find file","file: "+add_quotation(file));
    else orita_log.print(_LOG_INFO,"find file","file: "+add_quotation(file));
    return result;
}
int copy_file(const std::string file,const std::string copy_path)
{
    #ifdef _WIN32
    const int result=ssystem("copy "+add_quotation(file)+" "+add_quotation(copy_path)+system_to_nul);
    #endif
    #ifdef __linux__
    const int result=ssystem("cp "+add_quotation(file)+" "+add_quotation(copy_path)+system_to_nul);
    #endif
    if(result) orita_log.print(_LOG_WARN,"fail copy file","file: "+add_quotation(file),"copy_path: "+add_quotation(copy_path));
    else orita_log.print(_LOG_INFO,"copy file","file: "+add_quotation(file),"copy_path: "+add_quotation(copy_path));
    return result;
}
int make_dir(const std::string dir)
{
    const int result=ssystem("mkdir "+add_quotation(dir)+system_to_nul);
    if(result) orita_log.print(_LOG_WARN,"fail make dir","dir: "+add_quotation(dir));
    else orita_log.print(_LOG_INFO,"make dir","dir: "+add_quotation(dir));
    return result;
}
int remove_dir(const std::string dir)
{
    #ifdef _WIN32
    const int result=ssystem("rmdir /S /Q "+add_quotation(dir)+system_to_nul);
    #endif
    #ifdef __linux__
    const int result=ssystem("rm -r "+add_quotation(dir)+system_to_nul);
    #endif
    if(result) orita_log.print(_LOG_WARN,"fail remove dir","dir: "+add_quotation(dir));
    else orita_log.print(_LOG_INFO,"remove dir","dir: "+add_quotation(dir));
    return result;
}
int move_file(const std::string file,const std::string move_path)
{
    #ifdef _WIN32
    const int result=ssystem("move "+add_quotation(file)+" "+add_quotation(move_path)+system_to_nul);
    #endif
    #ifdef __linux__
    const int result=ssystem("mv -f "+add_quotation(file)+" "+add_quotation(move_path)+system_to_nul);
    #endif
    if(result) orita_log.print(_LOG_WARN,"fail move file","file: "+add_quotation(file),"move_path: "+add_quotation(move_path));
    else orita_log.print(_LOG_INFO,"move file","file: "+add_quotation(file),"move_path: "+add_quotation(move_path));
    return result;
}

// settings
json settings;
namespace Init
{
    void begin()
    {
        orita_log.clear();
        (std::ifstream)(makepath(appdata_path,"settings.json"))>>settings;
    }
    void end()
    {
        (std::ofstream)(makepath(appdata_path,"settings.json"))<<std::setw(4)<<settings;
    }
}
#endif