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
    const fil file;
    const arg argu;
    const tim time_limit;
    int exit_code=-1;
    tim time;
    timer run_timer;
    bool if_end=false;
    Poco::Pipe in,out,err;
    Poco::ProcessHandle *ph=NULL;
    std::ostream *out_stream=&std::cout,*err_stream=&std::cerr;
    runner(const fil &_file,const arg &_argu=arg(),const tim _time_limit=runtime_limit):file(replace_extension(_file,exe_suf)),argu(_argu),time_limit(_time_limit) {}
    runner &set_in(const fil &file) {sifstream(file,std::ios::binary)>>in;return *this;}
    runner &set_out(std::istream *stream) {*stream>>in;return *this;}
    runner &set_out(const fil &file) {out_stream=new sofstream(file,std::ios::binary);return *this;}
    runner &set_out(std::ostream *stream) {out_stream=stream;return *this;}
    runner &set_err(const fil &file) {err_stream=new sofstream(file,std::ios::binary);return *this;}
    runner &set_err(std::ostream *stream) {err_stream=stream;return *this;}
    void wait_for() {ph->wait();}
    void start()
    {
        INFO("run - start","id: "+to_string_hex(this),"file: "+add_squo(file),"argu: "+add_squo(argu),"time: "+std::to_string(time_limit.count())+"ms");
        show_cursor();
        run_timer.init();
        in.close();
        ph=new Poco::ProcessHandle(Poco::Process::launch(file.path(),argu,&in,&out,&err));
        std::future<void> run_future(std::async(std::launch::async,&runner::wait_for,this));
        if(run_future.wait_for(time_limit)!=std::future_status::ready)
        {
            Poco::Process::kill(*ph);
            run_future.wait();
            time=time_limit;
            WARN("run - timeout","id: "+to_string_hex(this),"file: "+add_squo(file));
        }
        else
        {
            time=run_timer.get_time();
            exit_code=ph->wait();
            if_end=true;
            INFO("run - success","id: "+to_string_hex(this),"file: "+add_squo(file),"time: "+std::to_string(time.count())+"ms","exit_code: "+std::to_string(exit_code));
        }
        hide_cursor();
        if(out_stream!=NULL) *out_stream<<out;
        if(err_stream!=NULL) *err_stream<<err;
        out_stream->flush();
        err_stream->flush();
    }
    int operator()()
    {
        threads::run(std::bind(&runner::start,this));
        return if_end!=true;
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
        runner ans_runner=runner(ans,arg(),time_limit*2).set_in(in_file).set_out(ans_file);
        if(ans_runner()) return time=ans_runner.time,result=res::type::TLE_O;
        time=ans_runner.time;
        exit_code=ans_runner.exit_code;
        if(exit_code) return result=res::type::RE;
        runner chk_runner=runner(chk,(arg)in_file+out_file+ans_file).set_out(chk_file);
        if(chk_runner()) return chk_time=chk_runner.time,chk_result=res::type::TO,result=res::type::NL;
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