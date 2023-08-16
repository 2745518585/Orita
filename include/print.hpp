#pragma once
#ifndef _FILE_PRINT
#define _FILE_PRINT _FILE_PRINT
#include"init.hpp"
namespace Print
{
    void print_result(const std::string &name,const res result,const tim time,const int exit_code)
    {
        if(name!="") std::cout<<termcolor::bright_grey<<name<<":\n";
        if(result.is(res::type::SS)) std::cout<<termcolor::bright_green<<"Success\n";
        if(result.is(res::type::FL)) std::cout<<termcolor::bright_red<<"Fail\n";
        if(result.is(res::type::AC)) std::cout<<termcolor::bright_green<<"Accepted\n"<<time<<"\n";
        if(result.is(res::type::WA)) std::cout<<termcolor::bright_red<<"Wrong Answer\n"<<time<<"\n";
        if(result.is(res::type::RE)) std::cout<<termcolor::magenta<<"Runtime Error\nexit with code "<<exit_code<<"\n";
        if(result.is(res::type::TLE_CA)) std::cout<<termcolor::bright_cyan<<"Time Limit Error with Correct Answer\n"<<time<<"\n";
        if(result.is(res::type::TLE_WA)) std::cout<<termcolor::bright_cyan<<"Time Limit Error with Wrong Answer\n"<<time<<"\n";
        if(result.is(res::type::TLE_O)) std::cout<<termcolor::bright_cyan<<"Time Limit Error\nover "<<time<<"\n";
        if(result.is(res::type::CE)) std::cout<<termcolor::bright_yellow<<"Compile Error\n";
        if(result.is(res::type::SA)) std::cout<<termcolor::bright_green<<"Same Answer\n";
        if(result.is(res::type::DA)) std::cout<<termcolor::bright_red<<"Different Answer\n";
        if(result.is(res::type::TO)) std::cout<<termcolor::bright_cyan<<"Timeout\n";
        if(result.is(res::type::NF)) std::cout<<termcolor::blue<<"No such file\n";
        if(result.is(res::type::II)) std::cout<<termcolor::blue<<"Invalid input\n";
        std::cout<<termcolor::reset;
        std::cout.flush();
    }
    std::string get_resultname(const res result)
    {
        if(result.is(res::type::NL)) return "NULL";
        if(result.is(res::type::NF)) return "No such file";
        if(result.is(res::type::AC)) return "Accepted";
        if(result.is(res::type::WA)) return "Wrong Answer";
        if(result.is(res::type::RE)) return "Runtime Error";
        if(result.is(res::type::TLE_CA)) return "Time Limit Error with Correct Answer";
        if(result.is(res::type::TLE_WA)) return "Time Limit Error with Wrong Answer";
        if(result.is(res::type::TLE_O)) return "Time Limit Error";
        if(result.is(res::type::CE)) return "Compile Error";
        if(result.is(res::type::SA)) return "Same Answer";
        if(result.is(res::type::DA)) return "Different Answer";
        if(result.is(res::type::II)) return "Invalid input";
        if(result.is(res::type::TO)) return "Timeout";
        if(result.is(res::type::SS)) return "Success";
        if(result.is(res::type::FL)) return "Fail";
        return "";
    }
    std::string get_short_resultname(const res result)
    {
        if(result.is(res::type::NL)) return "NL";
        if(result.is(res::type::NF)) return "NF";
        if(result.is(res::type::AC)) return "AC";
        if(result.is(res::type::WA)) return "WA";
        if(result.is(res::type::RE)) return "RE";
        if(result.is(res::type::TLE_CA)) return "TLE_CA";
        if(result.is(res::type::TLE_WA)) return "TLE_WA";
        if(result.is(res::type::TLE_O)) return "TLE_O";
        if(result.is(res::type::CE)) return "CE";
        if(result.is(res::type::SA)) return "SA";
        if(result.is(res::type::DA)) return "DA";
        if(result.is(res::type::II)) return "II";
        if(result.is(res::type::TO)) return "TO";
        if(result.is(res::type::SS)) return "SS";
        if(result.is(res::type::FL)) return "FL";
        return "";
    }
}
void print_result(const res result=res::type::NL,const tim time=(tim)0,int exit_code=0) {Print::print_result("",result,time,exit_code);}
void print_result(const std::string &name,const res result=res::type::NL,const tim time=(tim)0,int exit_code=0) {Print::print_result(name,result,time,exit_code);}
std::string get_resultname(const res result) {return Print::get_resultname(result);}
std::string get_short_resultname(const res result) {return Print::get_short_resultname(result);}
class printer
{
  public:
    tim interval_time;
    int len;
    std::vector<std::string> str;
    std::atomic<bool> if_end;
    std::mutex wait_lock;
    std::condition_variable wait;
    void print()
    {
        int pos=0;
        while(!if_end)
        {
            pos=(pos+1)%str.size();
            std::cout<<str[pos]<<"\r"<<std::flush;
            {
                std::unique_lock<std::mutex> lock(wait_lock);
                wait.wait_for(lock,interval_time,[&](){return (bool)if_end;});
                lock.unlock();
            }
        }
        for(int i=0;i<len;++i) std::cout<<" ";
        std::cout<<"\r"<<std::flush;
    }
    void start()
    {
        std::thread(&printer::print,this).detach();
    }
    void stop()
    {
        if_end=true;
        wait.notify_all();
        ssleep((tim)10);
    }
    printer(const std::initializer_list<std::string> _str,const tim _interval_time)
    {
        if_end=false;
        len=0;
        interval_time=_interval_time;
        for(auto i:_str) str.push_back(i),len=std::max(len,(int)i.size());
        for(int i=0;i<str.size();++i)
        {
            while(str[i].size()<len) str[i]+=" ";
        }
    }
    ~printer() {stop();}
};
#endif