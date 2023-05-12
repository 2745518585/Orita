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
#endif
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

#ifdef _WIN32
char PS='\\';
std::string sPS="\\";
#endif
#ifdef __linux__
char PS='/';
std::string sPS="/";
#endif
std::string fullpath(std::string path)
{
    #ifdef _WIN32
    char abspath[4096]={0};
    _fullpath(abspath,path.c_str(),4096);
    #else
    char abspath[40960]={0};
    realpath(path.c_str(),abspath);
    #endif
    return abspath;
}
#ifdef _WIN32
std::string exe_suf=".exe";
#endif
#ifdef __linux__
std::string exe_suf="";
#endif

void ssleep(const unsigned time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

#ifdef _WIN32
std::string system_to_nul=" > nul 2>&1 ";
#endif
#ifdef __linux__
std::string system_to_nul=" > /dev/null 2>&1 ";
#endif
#ifdef _WIN32
int sys_exit_code=1;
#endif
#ifdef __linux__
int sys_exit_code=256;
#endif

int ssystem(const std::string command)
{
    #ifdef _WIN32
    return system(("cmd /C \""+command+"\"").c_str());
    #endif
    #ifdef __linux__
    return system(command.c_str());
    #endif
}

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
  public:
    int result;
    res():result(_NL){}
    res(int _result):result(_result){}
    bool is(int _result)
    {
        return result==_result;
    }
    bool isnull()
    {
        return result==0;
    }
    bool istrue()
    {
        return result>0;
    }
    bool isfalse()
    {
        return result<0;
    }
};

bool verify_result(int result)
{
    return result>0;
}

template<typename T>
std::string to_string_len(const T num,const int len)
{
    std::string str=std::to_string(num);
    if(str.size()>len) return str;
    return std::string(len-str.size(),'0')+str;
}

json settings;
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
        return getenv("appdata")+sPS+"Orita";
        #endif
        #ifdef __linux__
        return getenv("HOME")+sPS+".Orita";
        #endif
    }
}
std::string running_path=Init::get_running_path(),file_path=Init::get_file_path(),appdata_path=Init::get_appdata_path();
namespace Init
{
    void begin()
    {
        (std::ifstream)(appdata_path+sPS+"settings.json")>>settings;
    }
    void end()
    {
        (std::ofstream)(appdata_path+sPS+"settings.json")<<std::setw(4)<<settings;
    }
}
#endif