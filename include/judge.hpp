#pragma once
#ifndef _FILE_JUDGE
#define _FILE_JUDGE _FILE_JUDGE
#include"files.hpp"
#include"data.hpp"
#include"print.hpp"
#include"time.hpp"
namespace Judge
{
    int compare(const std::string file1,const std::string file2)
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
int compare(const std::string file1,const std::string file2) {return Judge::compare(file1,file2);}
class runner
{
  public:
    int time,exit_code,time_limit;
    stime timer;
    std::atomic<bool> if_end;
    std::string file,argu,in_file,out_file;
    std::mutex wait_lock;
    std::condition_variable wait;
    runner(const std::string _file,const std::string _in_file="",const std::string _out_file="",const std::string _argu="",const int _time_limit=settings["runtime_limit"])
    {
        file=_file,in_file=_in_file,out_file=_out_file,argu=_argu,time_limit=_time_limit;
        time=exit_code=0;
    }
    void run_run()
    {
        const std::string command=""+add_quotation(get_exefile(file))+" "+argu+(in_file!=""?" < "+add_quotation(in_file):"")+(out_file!=""?" > "+add_quotation(out_file):"");
        orita_log.print(_LOG_INFO,"run","file: "+add_quotation(get_exefile(file))+"\nargu: "+argu+"\nin_file: "+add_quotation(in_file)+"\nout_file: "+add_quotation(out_file)+"\ncommand: "+command);
        timer.init();
        exit_code=ssystem(command)/sys_exit_code;
        time=timer.get_time();
        if_end=true;
        wait.notify_all();
    }
    int run()
    {
        if_end=false;
        std::thread(&runner::run_run,this).detach();
        {
            std::unique_lock<std::mutex> lock(wait_lock);
            wait.wait_for(lock,std::chrono::milliseconds(time_limit),[&](){return (bool)if_end;});
            lock.unlock();
        }
        if(!if_end)
        {
            orita_log.print(_LOG_WARN,"run timeout","file: "+add_quotation(get_exefile(file)));
            ssystem("taskkill /f /pid "+get_exefilename(file)+system_to_nul);
            {
                std::unique_lock<std::mutex> lock(wait_lock);
                wait.wait(lock,[&](){return (bool)if_end;});
                lock.unlock();
            }
            time=time_limit;
            return 1;
        }
        return 0;
    }
};
class judger
{
  public:
    int time,exit_code,chk_time,chk_exit_code,time_limit;
    res result,chk_result;
    std::string ans,chk,in_file,out_file,ans_file,chk_file;
    judger(const std::string _ans,const std::string _chk,const std::string _in_file="",const std::string _out_file="",const std::string _ans_file="",const std::string _chk_file="",const int _time_limit=get_time_limit())
    {
        ans=_ans,chk=_chk;
        if(_in_file!="") in_file=_in_file;
        else in_file=makepath(appdata_path,"data","data.in");
        if(_out_file!="") out_file=_out_file;
        else out_file=makepath(appdata_path,"data","data.out");
        if(_ans_file!="") ans_file=_ans_file;
        else ans_file=makepath(appdata_path,"data","data.ans");
        if(_chk_file!="") chk_file=_chk_file;
        else chk_file=makepath(appdata_path,"data","data.txt");
        time_limit=_time_limit;
        time=0,exit_code=0,chk_time=0,chk_exit_code=0;
    }
    res judge()
    {
        runner ans_runner(ans,in_file,ans_file,"",time_limit*2);
        if(ans_runner.run()) return time=ans_runner.time,result=_TLE_O;
        time=ans_runner.time;
        exit_code=ans_runner.exit_code;
        if(exit_code) return result=_RE;
        runner chk_runner(chk,"",chk_file,""+add_quotation(in_file)+" "+add_quotation(out_file)+" \""+ans_file+"\"");
        if(chk_runner.run()) return chk_time=chk_runner.time,chk_result=_TO,result=_NL;
        chk_time=chk_runner.time;
        chk_exit_code=chk_runner.exit_code;
        if(chk_exit_code!=0&&chk_exit_code!=1) return chk_result=_RE,result=_NL;
        if(time<=time_limit)
        {
            if(chk_exit_code) return result=_WA;
            else return result=_AC;
        }
        else
        {
            if(chk_exit_code) return result=_TLE_WA;
            else return result=_TLE_CA;
        }
    }
    void print_result(const std::string name="",const std::string chk_name="checker")
    {
        if(result.is(_NL)) Print::print_result(chk_name,chk_result,chk_time,chk_exit_code);
        Print::print_result(name,result,time,exit_code);
    }
};
#endif