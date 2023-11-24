#pragma once
#ifndef _FILE_PRINT
#define _FILE_PRINT
#include"init.hpp"
#include"log.hpp"
namespace Print
{
    std::map<res::type,std::string> result_name={
        {res::type::NL,"NULL"},
        {res::type::NF,"No such file"},
        {res::type::AC,"Accepted"},
        {res::type::WA,"Wrong Answer"},
        {res::type::RE,"Runtime Error"},
        {res::type::TLE_CA,"Time Limit Exceed with Correct Answer"},
        {res::type::TLE_WA,"Time Limit Exceed with Wrong Answer"},
        {res::type::TLE_O,"Time Limit Exceed"},
        {res::type::CE,"Compile Error"},
        {res::type::SA,"Same Answer"},
        {res::type::DA,"Different Answer"},
        {res::type::II,"Invalid input"},
        {res::type::TO,"Timeout"},
        {res::type::SS,"Success"},
        {res::type::FL,"Fail"},
    };
    std::map<res::type,std::string> short_result_name={
        {res::type::NL,"NL"},
        {res::type::NF,"NF"},
        {res::type::AC,"AC"},
        {res::type::WA,"WA"},
        {res::type::RE,"RE"},
        {res::type::TLE_CA,"TLE_CA"},
        {res::type::TLE_WA,"TLE_WA"},
        {res::type::TLE_O,"TLE_O"},
        {res::type::CE,"CE"},
        {res::type::SA,"SA"},
        {res::type::DA,"DA"},
        {res::type::II,"II"},
        {res::type::TO,"TO"},
        {res::type::SS,"SS"},
        {res::type::FL,"FL"},
    };
    std::map<res::type,std::ostream &(*)(std::ostream&)> result_color={
        {res::type::NL,termcolor::reset},
        {res::type::NF,termcolor::blue},
        {res::type::AC,termcolor::bright_green},
        {res::type::WA,termcolor::bright_red},
        {res::type::RE,termcolor::magenta},
        {res::type::TLE_CA,termcolor::bright_cyan},
        {res::type::TLE_WA,termcolor::bright_cyan},
        {res::type::TLE_O,termcolor::bright_cyan},
        {res::type::CE,termcolor::bright_yellow},
        {res::type::SA,termcolor::bright_green},
        {res::type::DA,termcolor::bright_red},
        {res::type::II,termcolor::blue},
        {res::type::TO,termcolor::bright_cyan},
        {res::type::SS,termcolor::bright_green},
        {res::type::FL,termcolor::bright_red},
    };
    void print_result(const std::string &name,const res result,const tim time,const int exit_code)
    {
        if(name!="") scout<<termcolor::bright_grey<<name<<":\n";
        scout<<result_color[result.result]<<result_name[result.result]<<"\n";
        if(result.is({res::type::AC,res::type::WA,res::type::TLE_CA,res::type::TLE_WA})) scout<<time<<"\n";
        if(result.is(res::type::RE)) scout<<"exit with code "<<exit_code<<"\n";
        if(result.is(res::type::TLE_O)) scout<<"over "<<time<<"\n";
        scout<<termcolor::reset<<std::flush;
    }
    std::string get_resultname(const res result)
    {
        return result_name[result.result];
    }
    std::string get_short_resultname(const res result)
    {
        return short_result_name[result.result];
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
        const std::string operator[](size_t pos) const {return list[pos];}
        const size_t size() const {return list.size();}
    };
    std::string print_type(const print_list &str_back,const std::vector<print_list> &str_list,bool if_right=false)
    {
        std::string str;
        std::vector<size_t> lens;
        size_t tot_len=0;
        for(unsigned i=0;i<str_back.size();++i)
        {
            size_t len=0;
            for(auto j:str_list) if(i<j.size()) len=std::max(len,j[i].size());
            lens.push_back(len);
            tot_len+=str_back[i].size()+len;
        }
        std::string pre;
        if(if_right) pre=std::string(" ")*(get_terminal_width()-tot_len);
        for(auto i:str_list)
        {
            str+=pre;
            for(unsigned j=0;j<str_back.size();++j)
            {
                if(j<i.size()) str+=str_back[j]+i[j]+std::string(" ")*(lens[j]-i[j].size());
                else str+=str_back[j]+std::string("")*lens[j];
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
std::ostream &operator<<(std::ostream &output,res res)
{
    output<<get_resultname(res);
    return output;
}
std::ostream &print_right(std::ostream &stream)
{
    stream<<std::setw(get_terminal_width())<<std::right;
    return stream;
}
class printer
{
  public:
    tim interval_time;
    size_t len;
    std::vector<std::string> str;
    std::atomic<bool> if_end;
    std::mutex wait_lock;
    std::condition_variable wait;
    std::future<void> *print_future;
    void print()
    {
        size_t pos=0;
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
        for(size_t i=0;i<len;++i) scout<<" ";
        scout<<"\r"<<std::flush;
    }
    void start()
    {
        print_future=new std::future(std::async(std::launch::async,&printer::print,this));
        INFO("printer - start","id: "+to_string_hex(this),"str: "+add_squo(str),"interval time: "+std::to_string(interval_time.count()));
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
        for(auto i:_str) str.push_back(i),len=std::max(len,i.size());
        for(size_t i=0;i<str.size();++i)
        {
            while(str[i].size()<len) str[i]+=" ";
        }
    }
    ~printer() {stop();}
};
#endif