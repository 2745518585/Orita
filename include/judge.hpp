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
    const pat file,in_file,out_file;
    std::string argu;
    const tim time_limit;
    tim time;
    int exit_code=0;
    timer run_timer;
    std::atomic<bool> if_end;
    std::mutex wait_lock;
    std::condition_variable wait;
    runner(const pat &_file,const pat &_in_file,const pat &_out_file,const std::string &_argu="",const tim _time_limit=runtime_limit):file(_file),in_file(_in_file),out_file(_out_file),argu(_argu),time_limit(_time_limit) {}
    void run_run()
    {
        const std::string command=add_quo(replace_extension(file,exe_suf))+" "+argu+" "+(in_file!=""?" < "+add_quo(in_file):"")+(out_file!=""?" > "+add_quo(out_file):"");
        INFO("start run","id: "+to_string_hex(this),"file: "+add_squo(replace_extension(file,exe_suf)),"argu: "+add_squo(argu),"in_file: "+add_squo(in_file),"out_file: "+add_squo(out_file),"command: "+add_squo(command));
        run_timer.init();
        show_cursor();
        exit_code=ssystem(command)>>sys_exit_code;
        hide_cursor();
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
            WARN("run timeout","id: "+to_string_hex(this),"file: "+add_squo(replace_extension(file,exe_suf)));
            kill_task(replace_extension(file.filename(),exe_suf));
            {
                std::unique_lock<std::mutex> lock(wait_lock);
                wait.wait(lock,[&](){return (bool)if_end;});
                lock.unlock();
            }
            time=time_limit;
            return 1;
        }
        INFO("success run","id: "+to_string_hex(this),"file: "+add_squo(replace_extension(file,exe_suf)));
        return 0;
    }
};
class judger
{
  public:
    const pat ans,chk,in_file,out_file,ans_file,chk_file;
    const tim time_limit;
    tim time,chk_time;
    int exit_code=0,chk_exit_code=0;
    res result,chk_result;
    judger(const pat &_ans,const pat &_chk,const pat &_in_file,const pat &_out_file,const pat &_ans_file,const pat &_chk_file,const tim _time_limit=get_time_limit()):ans(_ans),chk(_chk),in_file(_in_file),out_file(_out_file),ans_file(_ans_file),chk_file(_chk_file),time_limit(_time_limit) {}
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
        Print::print_result(name,result,time,exit_code);
    }
};
#endif