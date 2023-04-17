#pragma once
#ifndef _FILE_JUDGE
#define _FILE_JUDGE _FILE_JUDGE
#include"name.hpp"
#include"compile.hpp"
#include"data.hpp"
#include"print.hpp"
namespace Judge
{
    #define _not_end -1
    int result,time,time_limit,exit_code;
    clock_t begin_time;
    bool if_end;
    std::string in_file,out_file,ans_file,chk_file;
    void begin()
    {
        in_file=appdata_address+"\\Orita\\data\\data.in";
        out_file=appdata_address+"\\Orita\\data\\data.out";
        ans_file=appdata_address+"\\Orita\\data\\data.ans";
        chk_file=appdata_address+"\\Orita\\data\\data.txt";
    }
    int compare(std::string file1,std::string file2)
    {
        std::ifstream infile1(file1),infile2(file2);
        std::string str1,str2;
        bool empty1=0,empty2=0;
        while(true)
        {
            bool end1=bool(!getline(infile1,str1)),end2=bool(!getline(infile2,str2));
            if(end1&&end2) break;
            while(str1[str1.size()-1]==' ') str1=str1.substr(0,str1.size()-1);
            while(str2[str2.size()-1]==' ') str2=str2.substr(0,str2.size()-1);
            if(end1||str1.size()==0) empty1=true;
            else empty1=false;
            if(end2||str2.size()==0) empty2=true;
            else empty2=false;
            if(empty1^empty2) return 1;
            if(strcmp(str1.c_str(),str2.c_str())!=0) return 1;
        }
        return 0;
    }
    int check_ans(std::string chk)
    {
        return ssystem("\""+get_address(chk)+"\\"+get_namepre(chk)+".exe\" \""+in_file+"\" \""+ans_file+"\" \""+out_file+"\" 2> \""+chk_file+"\"");
    }
    int judge(std::string ans,std::string chk)
    {
        std::string run_inst="\""+get_address(ans)+"\\"+get_namepre(ans)+".exe\" < \""+in_file+"\" > \""+ans_file+"\"";
        begin_time=clock();
        if(exit_code=ssystem(run_inst))
        {
            if_end=true;
            if(result!=_not_end) return result;
            return result=_RE;
        }
        if_end=true;
        if(result!=_not_end) return result;
        time=(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000;
        std::string check_inst;
        if(check_ans(chk))
        {
            if(time>get_time_limit()) result=_TLE_WA;
            else result=_WA;
        }
        else
        {
            if(time>get_time_limit()) result=_TLE_CA;
            else result=_AC;
        }
        return result;
    }
    int judge_monitor(std::string ans,std::string chk)
    {
        if_end=false;
        result=_not_end;
        time_limit=get_time_limit();
        begin_time=_not_end;
        std::thread(judge,ans,chk).detach();
        while(begin_time==_not_end||(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000<time_limit*2)
        {
            Sleep(5);
            if(if_end)
            {
                while(result==_not_end) Sleep(5);
                return 0;
            }
        }
        result=_TLE_O;
        ssystem("taskkill /f /pid "+get_namepre(ans)+".exe"+system_to_nul);
        while(if_end==false) Sleep(5);
        return 1;
    }
    void running(std::string ans,std::string parameter)
    {
        begin_time=clock();
        exit_code=ssystem(get_address(ans)+"\\"+get_namepre(ans)+".exe "+parameter);
        if_end=true;
    }
    int run_monitor(std::string ans,std::string parameter)
    {
        if_end=false;
        time_limit=get_time_limit();
        begin_time=-1;
        std::thread(running,ans,parameter).detach();
        while(begin_time==-1||(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000<time_limit*2)
        {
            if(if_end) return 0;
        }
        ssystem("taskkill /f /pid "+get_namepre(ans)+".exe"+system_to_nul);
        return 1;
    }
    #undef _not_end
}
int compare(std::string file1,std::string file2) {return Judge::compare(file1,file2);}
int check_ans(std::string chk) {return Judge::check_ans(chk);}
int judge(std::string ans,std::string chk) {return Judge::judge(ans,chk);}
int judge_monitor(std::string ans,std::string chk) {return Judge::judge_monitor(ans,chk);}
int run_monitor(std::string ans,std::string parameter) {return Judge::run_monitor(ans,parameter);}
void print_judge_result() {Print::print_judge_result(Judge::result,Judge::time,Judge::exit_code,Judge::time_limit);}
#endif