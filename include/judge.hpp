#pragma once
#ifndef _FILE_JUDGE
#define _FILE_JUDGE _FILE_JUDGE
#include"name.hpp"
#include"compile.hpp"
#include"data.hpp"
#include"print.hpp"
namespace Judge
{
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
}
class judger
{
  public:
    int result,time,exit_code;
    stime run_time;
    std::string ans,chk,in_file,out_file,ans_file,chk_file;
    judger(std::string _ans,std::string _chk)
    {
        ans=_ans,chk=_chk;
        in_file=appdata_path+sPS+"data"+sPS+"data.in";
        out_file=appdata_path+sPS+"data"+sPS+"data.out";
        ans_file=appdata_path+sPS+"data"+sPS+"data.ans";
        chk_file=appdata_path+sPS+"data"+sPS+"data.txt";
    }
    judger(std::string _ans,std::string _chk,std::string _in_file,std::string _out_file,std::string _ans_file,std::string _chk_file)
    {
        ans=_ans,chk=_chk;
        if(_in_file!="") in_file=_in_file;
        else in_file=appdata_path+sPS+"data"+sPS+"data.in";
        if(_out_file!="") out_file=_out_file;
        else out_file=appdata_path+sPS+"data"+sPS+"data.out";
        if(_ans_file!="") ans_file=_ans_file;
        else ans_file=appdata_path+sPS+"data"+sPS+"data.ans";
        if(_chk_file!="") chk_file=_chk_file;
        else chk_file=appdata_path+sPS+"data"+sPS+"data.txt";
    }
    int judge()
    {
        std::string run_command="\""+get_exefile(ans)+"\" < \""+in_file+"\" > \""+ans_file+"\"";
        run_time.init();
        if(exit_code=ssystem(run_command)) return result=_RE;
        time=run_time.get_time();
        if(ssystem("\""+get_exefile(chk)+"\" \""+in_file+"\" \""+ans_file+"\" \""+out_file+"\" 2> \""+chk_file+"\""))
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
    void print_result()
    {
        Print::print_judge_result(result,time,exit_code);
    }
};
class monitor_judger
{
  public:
    #define _not_end -1
    int result,time,exit_code;
    stime run_time;
    bool if_begin,if_end;
    std::string ans,chk,in_file,out_file,ans_file,chk_file;
    monitor_judger(std::string _ans,std::string _chk)
    {
        ans=_ans,chk=_chk;
        in_file=appdata_path+sPS+"data"+sPS+"data.in";
        out_file=appdata_path+sPS+"data"+sPS+"data.out";
        ans_file=appdata_path+sPS+"data"+sPS+"data.ans";
        chk_file=appdata_path+sPS+"data"+sPS+"data.txt";
    }
    monitor_judger(std::string _ans,std::string _chk,std::string _in_file,std::string _out_file,std::string _ans_file,std::string _chk_file)
    {
        ans=_ans,chk=_chk;
        if(_in_file!="") in_file=_in_file;
        else in_file=appdata_path+sPS+"data"+sPS+"data.in";
        if(_out_file!="") out_file=_out_file;
        else out_file=appdata_path+sPS+"data"+sPS+"data.out";
        if(_ans_file!="") ans_file=_ans_file;
        else ans_file=appdata_path+sPS+"data"+sPS+"data.ans";
        if(_chk_file!="") chk_file=_chk_file;
        else chk_file=appdata_path+sPS+"data"+sPS+"data.txt";
    }
    int run_judge()
    {
        std::string run_command="\""+get_exefile(ans)+"\" < \""+in_file+"\" > \""+ans_file+"\"";
        run_time.init();
        if_begin=true;
        if(exit_code=ssystem(run_command))
        {
            if_end=true;
            if(result!=_not_end) return result;
            return result=_RE;
        }
        if_end=true;
        if(result!=_not_end) return result;
        time=run_time.get_time();
        std::string check_command;
        if(ssystem("\""+get_exefile(chk)+"\" \""+in_file+"\" \""+ans_file+"\" \""+out_file+"\" 2> \""+chk_file+"\""))
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
    int judge()
    {
        int time_limit=get_time_limit();
        result=_not_end;
        if_begin=if_end=false;
        std::thread(&monitor_judger::run_judge,this).detach();
        while(if_begin==false||run_time.get_time()<time_limit*2)
        {
            ssleep(5);
            if(if_end)
            {
                while(result==_not_end) ssleep(5);
                return 0;
            }
        }
        result=_TLE_O;
        time=get_time_limit()*2;
        ssystem("taskkill /f /pid "+get_exename(ans)+system_to_nul);
        while(if_end==false) ssleep(5);
        return 1;
    }
    void print_result()
    {
        Print::print_judge_result(result,time,exit_code);
    }
};
class monitor_runner
{
  public:
    int exit_code;
    stime run_time;
    bool if_begin,if_end;
    std::string ans,argu;
    monitor_runner(std::string _ans,std::string _argu)
    {
        ans=_ans,argu=_argu;
    }
    void run_run()
    {
        run_time.init();
        if_begin=true;
        exit_code=ssystem(get_exefile(ans)+" "+argu);
        if_end=true;
    }
    int run()
    {
        int time_limit=get_time_limit();
        if_begin=if_end=false;
        std::thread(&monitor_runner::run_run,this).detach();
        while(if_begin==false||run_time.get_time()<time_limit*2)
        {
            if(if_end) return 0;
        }
        ssystem("taskkill /f /pid "+get_exename(ans)+system_to_nul);
        return 1;
    }
};
int compare(std::string file1,std::string file2) {return Judge::compare(file1,file2);}
#endif