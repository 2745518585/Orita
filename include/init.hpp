#ifndef _FILE_INIT
#define _FILE_INIT _FILE_INIT
#include<bits/stdc++.h>
#include<windows.h>
#include<direct.h>
#include<sstream>
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
string system_to_nul=" > nul 2>&1";
int system(string inst)
{
    return system(UTF8toGB("cmd /C \""+inst+"\"").c_str());
}
string running_address,appdata_address;
void init()
{
    char temp[1001];
    getcwd(temp,1000);
    running_address=GBtoUTF8(temp);
    appdata_address=GBtoUTF8(getenv("appdata"));
}
#endif