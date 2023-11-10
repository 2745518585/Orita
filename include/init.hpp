#pragma once
#ifndef _FILE_INIT
#define _FILE_INIT _FILE_INIT
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

#include<algorithm>
#include<random>
#include<regex>
#include<typeinfo>
#include<functional>

#include<filesystem>

#include<thread>
#include<future>
#include<atomic>
#include<mutex>
#include<condition_variable>

#include<queue>
#include<map>
#define NOMINMAX

#ifdef _WIN32
#include<windows.h>
#include<direct.h>
#endif

#ifdef __linux__
#include<wait.h>
#include<unistd.h>
#include<limits.h>
#include<sys/time.h>
#include<sys/ioctl.h>
#endif

#include"nlohmann/json.hpp"

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

// code
std::string UTF8tosys(const std::string &utf8Text)
{
    #ifdef _WIN32
    int wideCharLength=MultiByteToWideChar(CP_UTF8,0,utf8Text.c_str(),-1,nullptr,0);
    std::wstring wideString(wideCharLength,L'\0');
    MultiByteToWideChar(CP_UTF8,0,utf8Text.c_str(),-1,&wideString[0],wideCharLength);
    int ansiLength=WideCharToMultiByte(CP_ACP,0,wideString.c_str(),-1,nullptr,0,nullptr,nullptr);
    std::string ansiString(ansiLength,'\0');
    WideCharToMultiByte(CP_ACP,0,wideString.c_str(),-1,&ansiString[0],ansiLength,nullptr,nullptr);
    while(ansiString.back()==0) ansiString.pop_back();
    return ansiString;
    #endif
    return utf8Text;
}
std::string systoUTF8(const std::string &systemText)
{
    #ifdef _WIN32
    int wideCharLength=MultiByteToWideChar(CP_ACP,0,systemText.c_str(),-1,nullptr,0);
    std::wstring wideString(wideCharLength,L'\0');
    MultiByteToWideChar(CP_ACP,0,systemText.c_str(),-1,&wideString[0],wideCharLength);
    int utf8Length=WideCharToMultiByte(CP_UTF8,0,wideString.c_str(),-1,nullptr,0,nullptr,nullptr);
    std::string utf8String(utf8Length,'\0');
    WideCharToMultiByte(CP_UTF8,0,wideString.c_str(),-1,&utf8String[0],utf8Length,nullptr,nullptr);
    while(utf8String.back()==0) utf8String.pop_back();
    return utf8String;
    #endif
    return systemText;
}

// os
const std::string os_name=Poco::Environment::osName();
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

// json
using json=nlohmann::json;
void merge(json &a,json b)
{
    if(!a.is_null()&&!b.is_null()&&a.type()!=b.type()) return;
    if(a.is_null()) a=b;
    else if(b.is_object())
    {
        for(auto &i:b.items()) merge(a[i.key()],i.value());
    }
    // else if(b.is_array())
    // {
    //     a.insert(a.end(),b.begin(),b.end());
    // }
    else if(!b.is_null()) a=b;
}
void remove_null(json &a)
{
    if(a.is_object())
    {
        for(auto &i:a) remove_null(i);
        for(auto i=a.begin();i!=a.end();)
        {
            ++i;
            try {if(prev(i)->size()==0) a.erase(prev(i));} catch(...) {}
        }
    }
    else if(a.is_array())
    {
        for(auto &i:a) remove_null(i);
        for(int i=a.size()-1;i>=0;--i)
        {
            try {if(a[i].size()==0) a.erase(i);} catch(...) {}
        }
    }
}

// result
class res
{
  public:
    enum type {NL,AC,SA,SS,WA,RE,TLE_CA,TLE_WA,TLE_O,CE,DA,TO,NF,II,FL};
    type result;
    res():result(type::NL) {}
    res(type _result):result(_result) {}
    bool is(const type target_result) const {return result==target_result;}
    bool is(const std::initializer_list<type> target_result_list) const
    {
        for(auto target_result:target_result_list) if(result==target_result) return true;
        return false;
    }
    bool istrue() const {return is({type::AC,type::SA,type::SS});}
    bool isfalse() const {return is({type::WA,type::RE,type::TLE_CA,type::TLE_WA,type::TLE_O,type::CE,type::DA,type::TO,type::NF,type::II,type::FL});}
    bool isnull() const {return is({type::NL});}
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
    return "0x"+strstream.str();
}
std::string add_quo(const std::string &str)
{
    return "\""+str+"\"";
}
std::string add_squo(const std::string &str)
{
    return "'"+str+"'";
}
std::string add_quo(const std::vector<std::string> &vec)
{
    std::string str;
    for(auto i:vec) str+="\""+i+"\" ";
    return str;
}
std::string add_squo(const std::vector<std::string> &vec)
{
    std::string str;
    for(auto i:vec) str+="'"+i+"' ";
    return str;
}
bool if_pre(std::string str,std::string pre)
{
    return pre.size()<=str.size()&&str.substr(0,pre.size())==pre;
}
template<typename Type> std::enable_if_t<std::is_convertible_v<Type,size_t>,std::string> operator*(const std::string a,Type b)
{
    std::string str="";
    while(b--) str+=a;
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
std::string sgetenv(const std::string &str)
{
    if(!Poco::Environment::has(str)) throw Poco::Exception("empty environment variable");
    return Poco::Environment::get(str);
}
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
    return path.parent();
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
    {"{OS_NAME}",os_name},
};
std::ostream &operator<<(std::ostream &output,pat val)
{
    output<<val.toString();
    return output;
}
std::ostream &operator<<(std::ostream &output,fil val)
{
    output<<val.path();
    return output;
}

// arg
class arg: public Poco::Process::Args
{
  public:
    using Poco::Process::Args::Args;
    arg(const char *str) {push_back((std::string)str);}
    arg(const std::string &str) {push_back(str);}
    arg(const pat &str) {push_back(str.toString());}
    arg(const fil &str) {push_back(str.path());}
};
arg get_arg(const std::string &str)
{
    bool is_quo=false,is_squo=false;
    arg argu;
    std::string tmp;
    for(auto i:str)
    {
        if(i=='\"'&&!is_squo) is_quo=!is_quo;
        else if(i=='\''&&!is_quo) is_squo=!is_squo;
        else if(i==' '&&!is_quo&&!is_squo) argu.push_back(tmp),tmp="";
        else tmp.push_back(i);
    }
    if(tmp!="") argu.push_back(tmp);
    return argu;
}
arg operator+(const arg &a,const arg &b) {arg c=a;c.insert(c.end(),b.begin(),b.end());return c;}
template<typename Type> std::enable_if_t<std::is_convertible_v<Type,arg>,arg> operator+(const arg &a,const Type &b) {return a+(arg)b;}
template<typename Type> std::enable_if_t<std::is_convertible_v<Type,arg>,arg> operator+(const Type &a,const arg &b) {return (arg)a+b;}
template<typename Type> arg &operator+=(arg &a,const Type &b) {return a=a+b;}

// process
class process_handle: public Poco::ProcessHandle
{
  private:
    int exit_code=-1;
  public:
    using Poco::ProcessHandle::ProcessHandle;
    process_handle(Poco::ProcessHandle process):Poco::ProcessHandle(process) {}
    int wait()
    {
        try {exit_code=Poco::ProcessHandle::wait();}
        catch(...) {}
        if(exit_code>=0) return exit_code>>sys_exit_code;
        else return exit_code;
    }
    int tryWait()
    {
        try {exit_code=Poco::ProcessHandle::tryWait();}
        catch(...) {}
        if(exit_code>=0) return exit_code>>sys_exit_code;
        else return exit_code;
    }
};

// pipe
std::istream &operator>>(std::istream &input,const Poco::Pipe &pipe)
{
    Poco::PipeOutputStream pipe_output(pipe);
    Poco::StreamCopier::copyStream(input,pipe_output);
    return input;
}
std::ostream &operator<<(std::ostream &output,const Poco::Pipe &pipe)
{
    Poco::PipeInputStream pipe_input(pipe);
    Poco::StreamCopier::copyStream(pipe_input,output);
    return output;
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
    void init() noexcept
    {
        begin_time=std::chrono::high_resolution_clock::now();
    }
    tim get_time() const noexcept
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

// print
#ifdef _WIN32
const pat system_nul="\\\\.\\nul";
const pat system_con="\\\\.\\con";
#endif
#ifdef __linux__
const pat system_nul="/dev/null";
const pat system_con="/dev/tty";
#endif
std::ostream &operator<<(std::ostream &output,std::any any)
{
    #define out(Type) else if(any.type()==typeid(Type)) output<<std::any_cast<Type>(any);\
    else if(any.type()==typeid(const Type)) output<<std::any_cast<const Type>(any);\
    else if(any.type()==typeid(Type&)) output<<std::any_cast<Type&>(any);\
    else if(any.type()==typeid(const Type&)) output<<std::any_cast<const Type&>(any);\
    else if(any.type()==typeid(Type*)) output<<std::any_cast<Type*>(any);\
    else if(any.type()==typeid(const Type*)) output<<std::any_cast<const Type*>(any)
    if(false);
    out(int);out(unsigned);out(long long);out(unsigned long long);
    out(char);out(bool);
    out(std::string);
    out(tim);out(pat);out(fil);
    #undef out
    else if(any.type()==typeid(std::ostream (*)(std::ostream&))) output<<std::any_cast<std::ostream (*)(std::ostream&)>(any);
    else if(any.type()==typeid(std::ostream &(*)(std::ostream&))) output<<std::any_cast<std::ostream &(*)(std::ostream&)>(any);
    return output;
}
std::string get_any(std::any any)
{
    std::stringstream stream;
    stream<<any;
    return stream.str();
}
class sistream
{
  public:
    std::istream& stream;
    template<typename Type> sistream(Type &_stream):stream(_stream) {}
    template<typename Type> sistream &operator>>(Type &val)
    {
        stream>>val;
        return *this;
    }
}scin(std::cin);
class sostream
{
  public:
    std::ostream &stream;
    template<typename Type> sostream(Type &_stream):stream(_stream) {}
    sostream &operator<<(const std::string &val)
    {
        stream<<UTF8tosys(val);
        return *this;
    }
    template<typename Type> sostream &operator<<(const Type &val)
    {
        stream<<val;
        return *this;
    }
    sostream &operator<<(std::ostream &(*val)(std::ostream&))
    {
        stream<<val;
        return *this;
    }
}scout(std::cout),scerr(std::cerr);
class sifstream: public std::ifstream
{
  public:
    void open(const pat &file,const std::ios_base::openmode &mode=std::ios::in)
    {
        open(file.toString(),mode);
    }
    void open(const fil &file,const std::ios_base::openmode &mode=std::ios::in)
    {
        open(file.path(),mode);
    }
    template<typename Type> void open(const Type &file,const std::ios_base::openmode &mode=std::ios::in)
    {
        std::ifstream::open(UTF8tosys(file),mode);
    }
    template<typename Type> sifstream(const Type &file) {open(file);}
    template<typename Type> sifstream(const Type &file,const std::ios_base::openmode &mode) {open(file,mode);}
};
class sofstream: public std::ofstream
{
  public:
    void open(const pat &file,const std::ios_base::openmode &mode=std::ios::out)
    {
        open(file.toString(),mode);
    }
    void open(const fil &file,const std::ios_base::openmode &mode=std::ios::out)
    {
        open(file.path(),mode);
    }
    template<typename Type> void open(const Type &file,const std::ios_base::openmode &mode=std::ios::out)
    {
        std::ofstream::open(UTF8tosys(file),mode);
    }
    template<typename Type> sofstream(const Type &file) {open(file);}
    template<typename Type> sofstream(const Type &file,const std::ios_base::openmode &mode) {open(file,mode);}
};
namespace ANSI
{
    const std::string hide_cursor="\033[?25l";
    const std::string show_cursor="\033[?25h";
    const std::string move_up="\x1b[A";
};
void hide_cursor() {scout<<ANSI::hide_cursor<<std::flush;}
void show_cursor() {scout<<ANSI::show_cursor<<std::flush;}

// command
int ssystem(const std::string &command)
{
    #ifdef _WIN32
    return system(UTF8tosys("cmd /C "+add_quo(command)).c_str());
    #endif
    #ifdef __linux__
    return system(UTF8tosys(command).c_str());
    #endif
}
size_t get_terminal_width()
{
    #ifdef _WIN32
    HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(console,&csbi)) return csbi.srWindow.Right-csbi.srWindow.Left+1;
    #endif
    #ifdef __linux__
    struct winsize w;
    if(ioctl(0,TIOCGWINSZ,&w)==0) return w.ws_col;
    #endif
    return 0;
}

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
        Init()
        {
            if(os_name!="Windows NT"&&os_name!="Linux")
            {
                throw Poco::Exception("unsupported plateform");
            }
            std::ios_base::sync_with_stdio(false);
            hide_cursor();
        }
        ~Init()
        {
            show_cursor();
        }
    }_Init;
}

#include"env.h"

#endif