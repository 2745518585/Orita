#pragma once
#ifndef _FILE_JUDGE
#define _FILE_JUDGE _FILE_JUDGE
#include"init.hpp"
#include"log.hpp"
#include"files.hpp"
#include"settings.hpp"
#include"print.hpp"
class runner
{
  public:
    const fil file,in_file,out_file;
    std::string argu;
    const tim time_limit;
    tim time;
    int exit_code=0;
    timer run_timer;
    runner(const fil &_file,const fil &_in_file,const fil &_out_file,const std::string &_argu="",const tim _time_limit=runtime_limit):file(_file),in_file(_in_file),out_file(_out_file),argu(_argu),time_limit(_time_limit) {}
    void run_run()
    {
        const std::string command=add_quo(replace_extension(file,exe_suf))+" "+argu+" "+(in_file!=fil()?" < "+add_quo(in_file):"")+(out_file!=fil()?" > "+add_quo(out_file):"");
        INFO("run - start","id: "+to_string_hex(this),"file: "+add_squo(replace_extension(file,exe_suf)),"argu: "+add_squo(argu),"in_file: "+add_squo(in_file),"out_file: "+add_squo(out_file),"command: "+add_squo(command));
        run_timer.init();
        show_cursor();
        exit_code=ssystem(command)>>sys_exit_code;
        hide_cursor();
        time=run_timer.get_time();
    }
    int run()
    {
        std::future<void> run_future(std::async(std::launch::async,&runner::run_run,this));
        if(run_future.wait_for(time_limit)!=std::future_status::ready)
        {
            WARN("run - timeout","id: "+to_string_hex(this),"file: "+add_squo(replace_extension(file,exe_suf)));
            kill_task(replace_extension(file,exe_suf).getFileName());
            run_future.wait();
            time=time_limit;
            return 1;
        }
        INFO("run - success","id: "+to_string_hex(this),"file: "+add_squo(replace_extension(file,exe_suf)));
        return 0;
    }
};
class judger
{
  public:
    const fil ans,chk,in_file,out_file,ans_file,chk_file;
    const tim time_limit;
    tim time,chk_time;
    int exit_code=0,chk_exit_code=0;
    res result,chk_result;
    judger(const fil &_ans,const fil &_chk,const fil &_in_file,const fil &_out_file,const fil &_ans_file,const fil &_chk_file,const tim _time_limit=get_time_limit()):ans(_ans),chk(_chk),in_file(_in_file),out_file(_out_file),ans_file(_ans_file),chk_file(_chk_file),time_limit(_time_limit) {}
    res judge()
    {
        runner ans_runner(ans,in_file,ans_file,"",time_limit*2);
        if(ans_runner.run()) return time=ans_runner.time,result=res::type::TLE_O;
        time=ans_runner.time;
        exit_code=ans_runner.exit_code;
        if(exit_code) return result=res::type::RE;
        runner chk_runner(chk,system_nul,chk_file,add_quo(in_file)+" "+add_quo(out_file)+" "+add_quo(ans_file));
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
    void print_result(const std::string &name="",const std::string &chk_name="checker")
    {
        if(result.is(res::type::NL)) Print::print_result(chk_name,chk_result,chk_time,chk_exit_code);
        else Print::print_result(name,result,time,exit_code);
    }
};
#endif