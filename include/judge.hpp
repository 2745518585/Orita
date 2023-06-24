#pragma once
#ifndef _FILE_JUDGE
#define _FILE_JUDGE _FILE_JUDGE
#include"files.hpp"
#include"data.hpp"
#include"print.hpp"
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
    const std::string file,argu,in_file,out_file;
    const tim time_limit;
    tim time;
    int exit_code=0;
    timer run_timer;
    std::atomic<bool> if_end;
    std::mutex wait_lock;
    std::condition_variable wait;
    runner(const std::string _file,const std::string _in_file="",const std::string _out_file="",const std::string _argu="",const tim _time_limit=(tim)settings["runtime_limit"]):file(_file),in_file(_in_file),out_file(_out_file),argu(_argu),time_limit(_time_limit) {}
    void run_run()
    {
        const std::string command=""+add_quotation(get_exefile(file))+" "+argu+(in_file!=""?" < "+add_quotation(in_file):"")+(out_file!=""?" > "+add_quotation(out_file):"");
        INFO("run","file: "+add_quotation(get_exefile(file))+"\nargu: "+argu+"\nin_file: "+add_quotation(in_file)+"\nout_file: "+add_quotation(out_file)+"\ncommand: "+command);
        run_timer.init();
        exit_code=ssystem(command)/sys_exit_code;
        time=run_timer.get_time();
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
            WARN("run timeout","file: "+add_quotation(get_exefile(file)));
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
    const std::string ans,chk,in_file,out_file,ans_file,chk_file;
    const tim time_limit;
    tim time,chk_time;
    int exit_code=0,chk_exit_code=0;
    res result,chk_result;
    judger(const std::string _ans,const std::string _chk,const std::string _in_file="",const std::string _out_file="",const std::string _ans_file="",const std::string _chk_file="",const tim _time_limit=get_time_limit()):ans(_ans),chk(_chk),in_file(_in_file==""?makepath(appdata_path,"data","data.in"):_in_file),out_file(_out_file==""?makepath(appdata_path,"data","data.out"):_out_file),ans_file(_ans_file==""?makepath(appdata_path,"data","data.ans"):_ans_file),chk_file(_chk_file==""?makepath(appdata_path,"data","data.txt"):_chk_file),time_limit(_time_limit) {}
    res judge()
    {
        runner ans_runner(ans,in_file,ans_file,"",time_limit*2);
        if(ans_runner.run()) return time=ans_runner.time,result=res::type::TLE_O;
        time=ans_runner.time;
        exit_code=ans_runner.exit_code;
        if(exit_code) return result=res::type::RE;
        runner chk_runner(chk,"",chk_file,""+add_quotation(in_file)+" "+add_quotation(out_file)+" \""+ans_file+"\"");
        if(chk_runner.run()) return chk_time=chk_runner.time,chk_result=res::type::TO,result=res::type::NL;
        chk_time=chk_runner.time;
        chk_exit_code=chk_runner.exit_code;
        if(chk_exit_code!=0&&chk_exit_code!=1) return chk_result=res::type::RE,result=res::type::NL;
        if(time<=time_limit)
        {
            if(chk_exit_code) return result=res::type::WA;
            else return result=res::type::AC;
        }
        else
        {
            if(chk_exit_code) return result=res::type::TLE_WA;
            else return result=res::type::TLE_CA;
        }
    }
    void print_result(const std::string name="",const std::string chk_name="checker")
    {
        if(result.is(res::type::NL)) Print::print_result(chk_name,chk_result,chk_time,chk_exit_code);
        Print::print_result(name,result,time,exit_code);
    }
};
#endif