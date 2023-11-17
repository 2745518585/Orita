#pragma once
#ifndef _FILE_JUDGE
#define _FILE_JUDGE _FILE_JUDGE
#include"init.hpp"
#include"log.hpp"
#include"files.hpp"
#include"settings.hpp"
#include"print.hpp"
#include"thread.hpp"
class runner
{
  public:
    const fil file;
    const arg argu;
    const tim time_limit;
    int exit_code=-1;
    tim time=(tim)-1;
    timer run_timer;
    bool if_success=false;
    Poco::Pipe in,out,err;
    process_handle *ph=NULL;
    std::istream *in_stream=NULL;
    std::ostream *out_stream=&std::cout,*err_stream=&std::cerr;
    fil in_file,out_file,err_file;
    runner(const fil &_file,const arg &_argu=arg(),const tim _time_limit=runtime_limit):file(get_exefile(_file)),argu(_argu),time_limit(_time_limit) {}
    ~runner() {if(ph!=NULL) delete ph;}
    runner *set_in(const fil &file) {in_file=file;return this;}
    runner *set_in(std::istream *stream) {in_stream=stream;return this;}
    runner *set_out(const fil &file) {out_file=file;return this;}
    runner *set_out(std::ostream *stream) {out_stream=stream;return this;}
    runner *set_err(const fil &file) {err_file=file;return this;}
    runner *set_err(std::ostream *stream) {err_stream=stream;return this;}
    void wait_for() {ph->wait();}
    void start()
    {
        INFO("run - start","id: "+to_string_hex(this),"file: "+add_squo(file),"argu: "+add_squo(argu),"time_limit: "+std::to_string(time_limit.count())+"ms");
        if(in_file!=fil()) in_stream=new sifstream(in_file,std::ios::binary);
        if(out_file!=fil()) out_stream=new sofstream(out_file,std::ios::binary);
        if(err_file!=fil()) err_stream=new sofstream(err_file,std::ios::binary);
        run_timer.init();
        std::future<void> in_future(std::async(std::launch::async,[&](){if(in_stream!=NULL) *in_stream>>in; in.close(Poco::Pipe::CLOSE_WRITE);}));
        std::future<void> out_future(std::async(std::launch::async,[&](){if(out_stream!=NULL) *out_stream<<out<<std::flush;}));
        std::future<void> err_future(std::async(std::launch::async,[&](){if(err_stream!=NULL) *err_stream<<err<<std::flush;}));
        ph=new process_handle(Poco::Process::launch(file.path(),argu,&in,&out,&err));
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
            if_success=true;
            INFO("run - success","id: "+to_string_hex(this),"file: "+add_squo(file),"time: "+std::to_string(time.count())+"ms","exit_code: "+std::to_string(exit_code));
        }
        in_future.wait();out_future.wait();err_future.wait();
        in.close();out.close();err.close();
        if(in_file!=fil()) delete in_stream;
        if(out_file!=fil()) delete out_stream;
        if(err_file!=fil()) delete err_stream;
    }
    int operator()()
    {
        try
        {
            process::run(std::bind(&runner::start,this));
            return if_success!=true;
        }
        catch(...)
        {
            if(ph!=NULL) Poco::Process::kill(*ph);
            wait_for();
            return 1;
        }
    }
};
class judger
{
  public:
    fil in,out,ans,chk,in_file,out_file,ans_file,chk_file;
    const tim time_limit;
    unsigned seed=rnd();
    runner *in_runner=NULL,*out_runner=NULL,*ans_runner=NULL,*chk_runner=NULL;
    res in_result,out_result,result,chk_result;
    tim time=(tim)-1;
    int exit_code=-1;
    bool if_end=false;
    std::condition_variable *wait_end=new std::condition_variable;
    judger(const fil &_ans,const fil &_chk,const fil &_in_file,const fil &_out_file,const fil &_ans_file,const fil &_chk_file,const tim _time_limit=get_time_limit()):ans(_ans),chk(_chk),in_file(_in_file),out_file(_out_file),ans_file(_ans_file),chk_file(_chk_file),time_limit(_time_limit) {}
    ~judger()
    {
        if(in_runner!=NULL) delete in_runner;
        if(out_runner!=NULL) delete out_runner;
        if(ans_runner!=NULL) delete ans_runner;
        if(chk_runner!=NULL) delete chk_runner;
        delete wait_end;
    }
    judger *set_in(const fil &file) {in=file;return this;}
    judger *set_out(const fil &file) {out=file;return this;}
    void judge()
    {
        [&]()
        {
            if(in!=fil()) (in_runner=new runner(in,std::to_string(seed)))->set_out(in_file);
            if(out!=fil()) (out_runner=new runner(out))->set_in(in_file)->set_out(out_file);
            (ans_runner=new runner(ans,arg(),time_limit*2))->set_in(in_file)->set_out(ans_file);
            (chk_runner=new runner(chk,(arg)in_file+out_file+ans_file))->set_out(chk_file);
            if(in_runner!=NULL)
            {
                (in_runner=new runner(in,std::to_string(seed)))->set_out(in_file);
                if((*in_runner)()) {in_result=res::type::TO;return;}
                if(in_runner->exit_code) {in_result=res::type::RE;return;}
            }
            if(out_runner!=NULL)
            {
                (out_runner=new runner(out))->set_in(in_file)->set_out(out_file);
                if((*out_runner)()) {out_result=res::type::TO;return;}
                if(out_runner->exit_code) {out_result=res::type::RE;return;}
            }
            {
                (ans_runner=new runner(ans,arg(),time_limit*2))->set_in(in_file)->set_out(ans_file);
                if((*ans_runner)()) {time=ans_runner->time;exit_code=ans_runner->exit_code;result=res::type::TLE_O;return;}
                time=ans_runner->time;
                exit_code=ans_runner->exit_code;
                if(ans_runner->exit_code) {result=res::type::RE;return;}
            }
            {
                (chk_runner=new runner(chk,(arg)in_file+out_file+ans_file))->set_out(chk_file);
                if((*chk_runner)()) {chk_result=res::type::TO;return;}
                if(chk_runner->exit_code!=0&&!std::regex_match(std::to_string(chk_runner->exit_code),chk_correct_exit_code)) {chk_result=res::type::RE;return;}
            }
            if(ans_runner->time<=time_limit)
            {
                if(chk_runner->exit_code) result=res::type::WA;
                else result=res::type::AC;
            }
            else
            {
                if(chk_runner->exit_code) result=res::type::TLE_WA;
                else result=res::type::TLE_CA;
            }
        }();
        if_end=true;
        wait_end->notify_all();
    }
    void add()
    {
        std::thread(&judger::judge,this).detach();
    }
    void print_result(const std::string &ans_name,const std::string &chk_name)
    {
        if(!chk_result.isnull()) Print::print_result(chk_name,chk_result,chk_runner->time,chk_runner->exit_code);
        else Print::print_result(ans_name,result,ans_runner->time,ans_runner->exit_code);
    }
    void print_result(const std::string &in_name,const std::string &out_name,const std::string &ans_name,const std::string &chk_name)
    {
        if(!in_result.isnull()) Print::print_result(in_name,in_result,in_runner->time,in_runner->exit_code);
        else if(!out_result.isnull()) Print::print_result(out_name,out_result,out_runner->time,out_runner->exit_code);
        else if(!chk_result.isnull()) Print::print_result(chk_name,chk_result,chk_runner->time,chk_runner->exit_code);
        else Print::print_result(ans_name,result,ans_runner->time,ans_runner->exit_code);
    }
};
class th_judger: public thread_mgr<judger>
{
  public:
    std::string class_name() const noexcept override
    {
        return "th_judger";
    }
    th_judger():thread_mgr()
    {
        INFO(class_name()+" - start","id: "+to_string_hex(this));
    }
    ~th_judger()
    {
        INFO(class_name()+" - end","id: "+to_string_hex(this));
    }
};
#endif