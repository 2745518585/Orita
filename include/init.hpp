#ifndef _FILE_INIT
#define _FILE_INIT _FILE_INIT
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<windows.h>
#include<direct.h>
#include<sstream>
#include<thread>
#include"nlohmann/json.hpp"
using namespace std;
using json=nlohmann::json;
string UTF8toGB(const string &utf8)
{
    if(utf8.empty()) return "";
    stringstream ss;
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
string GBtoUTF8(const string &gb2312)
{
    if(gb2312.empty()) return "";
    stringstream ss;
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
string system_to_nul=" > nul 2>&1 ";
int system(string inst)
{
    return system(("cmd /C \""+inst+"\"").c_str());
}
template<typename T>
string to_string(T num,int len)
{
    string str=to_string(num);
    if(str.size()>len) return str;
    return string(len-str.size(),'0')+str;
}
json settings;
namespace Init
{
    string get_running_address()
    {
        char address[1001];
        getcwd(address,1000);
        return address;
    }
    string get_file_address()
    {
        string address=__FILE__;
        int len=address.size();
        while(address[len-1]!='/'&&address[len-1]!='\\') --len;
        --len;
        while(address[len-1]!='/'&&address[len-1]!='\\') --len;
        --len;
        address=address.substr(0,len);
        for(int i=0;i<len;++i)
        {
            if(address[i]=='/'||address[len-1]=='\\') address[i]='\\';
        }
        return address;
    }
}
string running_address=Init::get_running_address(),file_address=Init::get_file_address(),appdata_address=getenv("appdata");
namespace Init
{
    void begin()
    {
        system("del /Q "+appdata_address+"\\Orita\\source\\*"+system_to_nul);
        system("del /Q "+appdata_address+"\\Orita\\temp\\*"+system_to_nul);
        (ifstream)(appdata_address+"\\Orita\\settings.json")>>settings;
    }
    void end()
    {
        (ofstream)(appdata_address+"\\Orita\\settings.json")<<setw(4)<<settings;
    }
}
#endif