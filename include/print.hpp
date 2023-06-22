#pragma once
#ifndef _FILE_PRINT
#define _FILE_PRINT _FILE_PRINT
#include"init.hpp"
namespace Print
{
    std::string color_str(const int red,const int green,const int blue)
    {
        return "\e[38;2;"+std::to_string(red)+";"+std::to_string(green)+";"+std::to_string(blue)+"m";
    }
    void change_color(const int red,const int green,const int blue)
    {
        std::cout<<color_str(red,green,blue);
    }
    std::string color_str(const std::string color)
    {
        if(color=="default") return "\033[0m";
        if(settings["colors"][color].type()==json::value_t::null) return "";
        const std::string red=((std::string)settings["colors"][color]).substr(1,2),green=((std::string)settings["colors"][color]).substr(3,2),blue=((std::string)settings["colors"][color]).substr(5,2);
        return "\e[38;2;"+std::to_string(stoi(red,0,16))+";"+std::to_string(stoi(green,0,16))+";"+std::to_string(stoi(blue,0,16))+"m";
    }
    void change_color(const std::string color)
    {
        std::cout<<color_str(color);
    }
    void print_result(const std::string name,const res result,const int time,const int exit_code)
    {
        if(name!="")
        {
            change_color("grey");
            std::cout<<name<<":\n";
            change_color("default");
        }
        if(result.is(res::type::SS))
        {
            change_color("green");
            std::cout<<"Success\n";
            change_color("default");
        }
        if(result.is(res::type::FL))
        {
            change_color("red");
            std::cout<<"Fail\n";
            change_color("default");
        }
        if(result.is(res::type::AC))
        {
            change_color("green");
            std::cout<<"Accepted\n"<<time<<"ms\n";
            change_color("default");
        }
        if(result.is(res::type::WA))
        {
            change_color("red");
            std::cout<<"Wrong Answer\n"<<time<<"ms\n";
            change_color("default");
        }
        if(result.is(res::type::RE))
        {
            change_color("purple");
            std::cout<<"Runtime Error\nexit with code "<<exit_code<<"\n";
            change_color("default");
        }
        if(result.is(res::type::TLE_CA))
        {
            change_color("blue");
            std::cout<<"Time Limit Error with Correct Answer\n"<<time<<"ms\n";
            change_color("default");
        }
        if(result.is(res::type::TLE_WA))
        {
            change_color("blue");
            std::cout<<"Time Limit Error with Wrong Answer\n"<<time<<"ms\n";
            change_color("default");
        }
        if(result.is(res::type::TLE_O))
        {
            change_color("blue");
            std::cout<<"Time Limit Error\nover "<<time<<"ms\n";
            change_color("default");
        }
        if(result.is(res::type::CE))
        {
            change_color("yellow");
            std::cout<<"Compile Error\n";
            change_color("default");
        }
        if(result.is(res::type::SA))
        {
            change_color("green");
            std::cout<<"Same Answer\n";
            change_color("default");
        }
        if(result.is(res::type::DA))
        {
            change_color("red");
            std::cout<<"Different Answer\n";
            change_color("default");
        }
        if(result.is(res::type::TO))
        {
            change_color("blue");
            std::cout<<"Timeout\n";
            change_color("default");
        }
        if(result.is(res::type::NF))
        {
            change_color("orange");
            std::cout<<"No such file\n";
            change_color("default");
        }
        if(result.is(res::type::II))
        {
            change_color("orange");
            std::cout<<"Invalid input\n";
            change_color("default");
        }
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
        if(result.is(res::type::TLE_WA)) return "TLEres::type::WA";
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
void change_color(const int red,const int green,const int blue) {Print::change_color(red,green,blue);}
std::string color_str(const int red,const int green,const int blue) {return Print::color_str(red,green,blue);}
void change_color(const std::string color) {Print::change_color(color);}
std::string color_str(const std::string color) {return Print::color_str(color);}
void print_result(const res result=res::type::NL,const int time=0,int exit_code=0) {Print::print_result("",result,time,exit_code);}
void print_result(const std::string name,const res result=res::type::NL,const int time=0,int exit_code=0) {Print::print_result(name,result,time,exit_code);}
std::string get_resultname(const res result) {return Print::get_resultname(result);}
std::string get_short_resultname(const res result) {return Print::get_short_resultname(result);}
class printer
{
  public:
    int interval_time,len;
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
            std::cout<<str[pos];
            std::cout.flush();
            {
                std::unique_lock<std::mutex> lock(wait_lock);
                wait.wait_for(lock,std::chrono::milliseconds(interval_time),[&](){return (bool)if_end;});
                lock.unlock();
            }
            for(int i=0;i<len;++i) std::cout<<"\b";
            std::cout.flush();
        }
        for(int i=0;i<len;++i) std::cout<<" ";
        for(int i=0;i<len;++i) std::cout<<"\b";
        std::cout.flush();
    }
    void start()
    {
        std::thread(&printer::print,this).detach();
    }
    void stop()
    {
        if_end=true;
        wait.notify_all();
        ssleep(10);
    }
    printer(const std::initializer_list<std::string> _str,const int _interval_time)
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
    ~printer()
    {
        stop();
    }
};
#endif