#pragma once
#ifndef _FILE_INIT
#define _FILE_INIT _FILE_INIT
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<string>
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
std::string UTF8tosys(const std::string str) {return UTF8toGB(str);}
std::string systoUTF8(const std::string str) {return GBtoUTF8(str);}
#endif
#ifdef __linux__
std::string UTF8tosys(const std::string str) {return str;}
std::string systoUTF8(const std::string str) {return str;}
#endif

// path
#ifdef _WIN32
char PS='\\';
#endif
#ifdef __linux__
char PS='/';
#endif
std::string makepath(const std::string path) {return path;}
template<typename ...others_type> std::string makepath(const std::string path,const others_type ...others) {return path+PS+makepath(others...);}

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
template<typename T> std::string to_string_len(const T num,const int len)
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
    template<typename ...others_type> void print(const std::string str,const others_type ...others)
    {
        print(str);
        print(others...);
    }
    template<typename ...others_type> void print(const int info,const std::string str)
    {
        read_lock.lock();
        output.open(output_file,std::ios::app);
        if(info==_LOG_INFO) output<<"[Info] "<<str<<":\n";
        if(info==_LOG_WARN) output<<"[Warn] "<<str<<":\n";
        if(info==_LOG_ERROR) output<<"[Error] "<<str<<":\n";
        if(info==_LOG_DEBUG) output<<"[Debug] "<<str<<":\n";
        output.close();
        read_lock.unlock();
    }
    template<typename ...others_type> void print(const int info,const std::string str,const others_type ...others)
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
#define INFO(...) orita_log.print(_LOG_INFO,__VA_ARGS__)
#define WARN(...) orita_log.print(_LOG_WARN,__VA_ARGS__)
#define ERROR(...) orita_log.print(_LOG_ERROR,__VA_ARGS__)
#define DEBUG(...) orita_log.print(_LOG_DEBUG,__VA_ARGS__)

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
std::ostream &operator<<(std::ostream &output,tim str)
{
    return output<<std::to_string(str.count())<<"ms";
}

// print
void hide_cursor() {std::cout<<"\033[?25l"<<std::flush;}
void show_cursor() {std::cout<<"\033[?25h"<<std::flush;}

// command
#ifdef _WIN32
const std::string system_nul="nul";
const std::string system_to_nul=" > nul 2>&1 ";
const std::string system_con="con";
const std::string system_to_con=" > con 2>&1 ";
#endif
#ifdef __linux__
const std::string system_nul="/dev/null";
const std::string system_to_nul=" > /dev/null 2>&1 ";
const std::string system_con="/dev/tty";
const std::string system_to_con=" > /dev/tty 2>&1 ";
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
    if(result) WARN("fail find file","file: "+add_quotation(file));
    else INFO("find file","file: "+add_quotation(file));
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
    if(result) WARN("fail copy file","file: "+add_quotation(file),"copy_path: "+add_quotation(copy_path));
    else INFO("copy file","file: "+add_quotation(file),"copy_path: "+add_quotation(copy_path));
    return result;
}
int make_dir(const std::string dir)
{
    const int result=ssystem("mkdir "+add_quotation(dir)+system_to_nul);
    if(result) WARN("fail make dir","dir: "+add_quotation(dir));
    else INFO("make dir","dir: "+add_quotation(dir));
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
    if(result) WARN("fail remove dir","dir: "+add_quotation(dir));
    else INFO("remove dir","dir: "+add_quotation(dir));
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
    if(result) WARN("fail move file","file: "+add_quotation(file),"move_path: "+add_quotation(move_path));
    else INFO("move file","file: "+add_quotation(file),"move_path: "+add_quotation(move_path));
    return result;
}
int kill_task(const std::string task)
{
    #ifdef _WIN32
    const int result=ssystem("taskkill /f /im "+add_quotation(task)+system_to_nul);
    #endif
    #ifdef __linux__
    const int result=ssystem("killall "+add_quotation(task)+system_to_nul);
    #endif
    if(result) WARN("fail kill task","task: "+add_quotation(task));
    else INFO("kill task","task: "+add_quotation(task));
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
        hide_cursor();
    }
    void end()
    {
        (std::ofstream)(makepath(appdata_path,"settings.json"))<<std::setw(4)<<settings;
        show_cursor();
    }
}
#endif