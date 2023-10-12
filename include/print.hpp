#pragma once
#ifndef _FILE_PRINT
#define _FILE_PRINT _FILE_PRINT
#include"init.hpp"
#include"log.hpp"
namespace Print
{
    void print_result(const std::string &name,const res result,const tim time,const int exit_code)
    {
        if(name!="") scout<<termcolor::bright_grey<<name<<":\n";
        if(result.is(res::type::SS)) scout<<termcolor::bright_green<<"Success\n";
        if(result.is(res::type::FL)) scout<<termcolor::bright_red<<"Fail\n";
        if(result.is(res::type::AC)) scout<<termcolor::bright_green<<"Accepted\n"<<time<<"\n";
        if(result.is(res::type::WA)) scout<<termcolor::bright_red<<"Wrong Answer\n"<<time<<"\n";
        if(result.is(res::type::RE)) scout<<termcolor::magenta<<"Runtime Error\nexit with code "<<exit_code<<"\n";
        if(result.is(res::type::TLE_CA)) scout<<termcolor::bright_cyan<<"Time Limit Error with Correct Answer\n"<<time<<"\n";
        if(result.is(res::type::TLE_WA)) scout<<termcolor::bright_cyan<<"Time Limit Error with Wrong Answer\n"<<time<<"\n";
        if(result.is(res::type::TLE_O)) scout<<termcolor::bright_cyan<<"Time Limit Error\nover "<<time<<"\n";
        if(result.is(res::type::CE)) scout<<termcolor::bright_yellow<<"Compile Error\n";
        if(result.is(res::type::SA)) scout<<termcolor::bright_green<<"Same Answer\n";
        if(result.is(res::type::DA)) scout<<termcolor::bright_red<<"Different Answer\n";
        if(result.is(res::type::TO)) scout<<termcolor::bright_cyan<<"Timeout\n";
        if(result.is(res::type::NF)) scout<<termcolor::blue<<"No such file\n";
        if(result.is(res::type::II)) scout<<termcolor::blue<<"Invalid input\n";
        scout<<termcolor::reset<<std::flush;
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
    class print_list
    {
        std::vector<std::string> list;
      public:
        print_list(std::initializer_list<std::any> _list)
        {
            for(auto i:_list)
            {
                list.push_back(get_any(i));
            }
        }
        std::string operator[](size_t pos)const {return list[pos];}
        size_t size()const {return list.size();}
    };
    std::string print_type(const print_list &str_back,const std::vector<print_list> &str_list)
    {
        std::string str;
        std::vector<size_t> lens;
        for(int i=0;i<str_back.size();++i)
        {
            size_t len=0;
            for(auto j:str_list)
            {
                if(i<j.size()) len=std::max(len,j[i].size());
            }
            lens.push_back(len);
        }
        for(auto i:str_list)
        {
            for(int j=0;j<str_back.size();++j)
            {
                if(j<i.size())
                {
                    str+=str_back[j]+i[j];
                    for(int k=0;k<lens[j]-i[j].size();++k) str+=" ";
                }
                else
                {
                    str+=str_back[j];
                    for(int k=0;k<lens[j];++k) str+=" ";
                }
            }
        }
        return str;
    }
}
void print_result(const res result=res::type::NL,const tim time=(tim)0,int exit_code=0) {Print::print_result("",result,time,exit_code);}
void print_result(const std::string &name,const res result=res::type::NL,const tim time=(tim)0,int exit_code=0) {Print::print_result(name,result,time,exit_code);}
using Print::get_resultname;
using Print::get_short_resultname;
using Print::print_type;
class printer
{
  public:
    tim interval_time;
    int len;
    std::vector<std::string> str;
    std::atomic<bool> if_end;
    std::mutex wait_lock;
    std::condition_variable wait;
    std::future<void> *print_future;
    void print()
    {
        int pos=0;
        while(!if_end)
        {
            pos=(pos+1)%str.size();
            scout<<str[pos]<<"\r"<<std::flush;
            {
                std::unique_lock<std::mutex> lock(wait_lock);
                wait.wait_for(lock,interval_time,[&](){return (bool)if_end;});
                lock.unlock();
            }
        }
        for(int i=0;i<len;++i) scout<<" ";
        scout<<"\r"<<std::flush;
    }
    void start()
    {
        print_future=new std::future(std::async(std::launch::async,&printer::print,this));
        INFO("printer - start","id: "+to_string_hex(this),"str: "+vec_to_str(str,static_cast<std::string(*)(const std::string&)>(add_squo)),"interval time: "+std::to_string(interval_time.count()));
    }
    void stop()
    {
        if_end=true;
        wait.notify_all();
        print_future->wait();
        INFO("printer - end","id: "+to_string_hex(this));
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