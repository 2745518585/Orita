#include<bits/stdc++.h>
#include<windows.h>
#include<direct.h>
#include<sstream>
using namespace std;
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
string appdata_address=getenv("appdata"),file_address;
int system(string inst)
{
    return system(("cmd /C \""+inst+"\"").c_str());
}
string change(string str)
{
    int pos=str.find("\\");
    while(pos!=string::npos)
    {
        str=(pos>0?str.substr(0,pos):"")+"\\\\"+str.substr(pos+1,str.size()-(pos+1));
        pos=str.find("\\",pos+2);
    }
    return str;
}
string get_path()
{
    char path[1001];
    GetModuleFileNameA(NULL,path,MAX_PATH);
    (strrchr(path,'\\'))[0]=0;
    return path;
}
int main()
{
    file_address=get_path();
    system("rmdir /s /Q \"%appdata%\\Orita\" > nul 2>&1");
    system("mkdir \"%appdata%\\Orita\" > nul 2>&1");
    system("mkdir \"%appdata%\\Orita\\data\" > nul 2>&1");
    system("echo 0 > \"%appdata%\\Orita\\data\\data.in\"");
    system("echo 0 > \"%appdata%\\Orita\\data\\data.out\"");
    system("mkdir \"%appdata%\\Orita\\source\" > nul 2>&1");
    system("mkdir \"%appdata%\\Orita\\temp\" > nul 2>&1");
    system("mkdir \"%appdata%\\Orita\\random\" > nul 2>&1");
    system("copy \""+file_address+"\\source\\*\" \"%appdata%\\Orita\" > nul 2>&1");
    system("echo "+change("{\"name100\":\""+GBtoUTF8(appdata_address)+"\\Orita\\0.cpp\",\"name101\":\""+GBtoUTF8(appdata_address)+"\\Orita\\1.cpp\"}")+" > \"%appdata%\\Orita\\name.json\"");
    return 0;
}