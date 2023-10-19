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
    process_handle *ph=NULL;
    std::ostream *out_stream=&std::cout,*err_stream=&std::cerr;
    std::vector<sofstream*> close_list;
    runner(const fil &_file,const arg &_argu=arg(),const tim _time_limit=runtime_limit):file(replace_extension(_file,exe_suf)),argu(_argu),time_limit(_time_limit) {}
    ~runner() {delete ph;}
    runner *set_in(const fil &file) {sifstream(file,std::ios::binary)>>in;return this;}
    runner *set_in(std::istream *stream) {*stream>>in;return this;}
    runner *set_out(const fil &file) {auto stream=new sofstream(file,std::ios::binary);out_stream=stream;close_list.push_back(stream);return this;}
    runner *set_out(std::ostream *stream) {out_stream=stream;return this;}
    runner *set_err(const fil &file) {auto stream=new sofstream(file,std::ios::binary);err_stream=stream;close_list.push_back(stream);return this;}
    runner *set_err(std::ostream *stream) {err_stream=stream;return this;}
    void wait_for() {ph->wait();}
    void start()
    {
        INFO("run - start","id: "+to_string_hex(this),"file: "+add_squo(file),"argu: "+add_squo(argu),"time: "+std::to_string(time_limit.count())+"ms");
        run_timer.init();
        ph=new process_handle(Poco::Process::launch(file.path(),argu,&in,&out,&err));
        in.close();
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
        if(out_stream!=NULL) *out_stream<<out;
        if(err_stream!=NULL) *err_stream<<err;
        out_stream->flush();
        err_stream->flush();
        for(auto i:close_list) delete i;
    }
    int operator()()
    {
        process::run(std::bind(&runner::start,this));
        return if_end!=true;
    }
};
class judger
{
  public:
    fil in,out,ans,chk,in_file,out_file,ans_file,chk_file;
    const tim time_limit;
    int seed=rnd();
    runner *in_runner,*out_runner,*ans_runner,*chk_runner;
    res in_result,out_result,result,chk_result;
    tim time;
    int exit_code;
    bool if_end=false;
    std::condition_variable *wait_end=new std::condition_variable;
    judger(const fil &_ans,const fil &_chk,const fil &_in_file,const fil &_out_file,const fil &_ans_file,const fil &_chk_file,const tim _time_limit=get_time_limit()):ans(_ans),chk(_chk),in_file(_in_file),out_file(_out_file),ans_file(_ans_file),chk_file(_chk_file),time_limit(_time_limit) {}
    ~judger() {delete in_runner;delete out_runner;delete ans_runner;delete chk_runner;delete wait_end;}
    judger *set_in(const fil &file) {in=file;return this;}
    judger *set_out(const fil &file) {out=file;return this;}
    void judge()
    {
        if(in!=fil())
        {
            (in_runner=new runner(in,std::to_string(seed)))->set_out(in_file);
            if((*in_runner)()) {in_result=res::type::TO;return;}
            if(in_runner->exit_code) {in_result=res::type::RE;return;}
        }
        if(out!=fil())
        {
            (out_runner=new runner(out))->set_in(in_file)->set_out(out_file);
            if((*out_runner)()) {out_result=res::type::TO;return;}
            if(out_runner->exit_code) {out_result=res::type::RE;return;}
        }
        {
            (ans_runner=new runner(ans,arg(),time_limit*2))->set_in(in_file)->set_out(ans_file);
            time=ans_runner->time;
            exit_code=ans_runner->exit_code;
            if((*ans_runner)()) {result=res::type::TLE_O;return;}
            if(ans_runner->exit_code) {result=res::type::RE;return;}
        }
        {
            (chk_runner=new runner(chk,(arg)in_file+out_file+ans_file))->set_out(chk_file);
            if((*chk_runner)()) {chk_result=res::type::TO;return;}
            if(chk_runner->exit_code!=0&&chk_runner->exit_code!=1) {chk_result=res::type::RE;return;}
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
        if_end=true;
        wait_end->notify_all();
    }
    void add()
    {
        std::thread(&judger::judge,this).detach();
    }
    void print_result(const std::string &ans_name,const std::string &chk_name)
    {
        if(!in_result.isnull()) Print::print_result(chk_name,chk_result,chk_runner->time,chk_runner->exit_code);
        else Print::print_result(ans_name,result,ans_runner->time,ans_runner->exit_code);
    }
    void print_result(const std::string &in_name,const std::string &out_name,const std::string &ans_name,const std::string &chk_name)
    {
        if(!in_result.isnull()) Print::print_result(in_name,in_result,in_runner->time,in_runner->exit_code);
        if(!out_result.isnull()) Print::print_result(out_name,out_result,out_runner->time,out_runner->exit_code);
        if(!chk_result.isnull()) Print::print_result(chk_name,chk_result,chk_runner->time,chk_runner->exit_code);
        else Print::print_result(ans_name,result,ans_runner->time,ans_runner->exit_code);
    }
};
class th_judger
{
  public:
    std::mutex read_lock;
    std::map<std::string,judger*> list;
    std::queue<std::string> new_que;
    std::condition_variable wait_que;
    std::atomic<size_t> running_sum;
    void monitor(const std::string &name)
    {
        judger *target=list[name];
        {
            std::mutex wait_end_lock;
            std::unique_lock<std::mutex> lock(wait_end_lock);
            target->wait_end->wait(lock,[&](){return (bool)target->if_end;});
        }
        read_lock.lock();
        new_que.push(name);
        --running_sum;
        wait_que.notify_all();
        read_lock.unlock();
    }
    void add(const std::string &name,judger *object)
    {
        read_lock.lock();
        if(list.count(name))
        {
            WARN("th_judger - repeated judger name","name: ",name);
            return;
        }
        list[name]=object;
        list[name]->add();
        ++running_sum;
        std::thread(&th_judger::monitor,this,name).detach();
        INFO("th_judger - add judge task","id: "+to_string_hex(this),"name: "+add_squo(name));
        read_lock.unlock();
    }
    void add(const std::initializer_list<std::pair<std::string,judger*>> object)
    {
        for(auto i:object) add(i.first,i.second);
    }
    void wait(const std::string &name)
    {
        read_lock.lock();
        if(!list.count(name)) throw Poco::Exception("empty judger name");
        judger *target=list[name];
        read_lock.unlock();
        {
            std::mutex wait_end_lock;
            std::unique_lock<std::mutex> lock(wait_end_lock);
            target->wait_end->wait(lock,[&](){return (bool)target->if_end;});
        }
    }
    void wait(const std::initializer_list<std::string> name)
    {
        for(auto i:name) wait(i);
    }
    void wait_all()
    {
        {
            std::mutex wait_que_lock;
            std::unique_lock<std::mutex> lock(wait_que_lock);
            wait_que.wait(lock,[&](){return running_sum==0;});
        }
    }
    std::string get(const std::initializer_list<std::string> name)
    {
        for(auto i:name)
        {
            wait(i);
            if(list[i]->exit_code) return i;
        }
        return "";
    }
    std::string get_one()
    {
        while(true)
        {
            {
                std::mutex wait_que_lock;
                std::unique_lock<std::mutex> lock(wait_que_lock);
                wait_que.wait(lock,[&](){return !new_que.empty()||running_sum==0;});
            }
            read_lock.lock();
            if(new_que.empty())
            {
                read_lock.unlock();
                if(running_sum==0) return "";
                continue;
            }
            std::string name=new_que.front();
            new_que.pop();
            read_lock.unlock();
            return name;
        }
    }
    std::string get_all()
    {
        wait_all();
        read_lock.lock();
        for(auto i:list)
        {
            if(i.second->exit_code)
            {
                read_lock.unlock();
                return i.first;
            }
        }
        read_lock.unlock();
        return "";
    }
    void remove(const std::string &name)
    {
        read_lock.lock();
        delete list[name];
        list.erase(name);
        read_lock.unlock();
    }
    th_judger()
    {
        INFO("th_judger - start","id: "+to_string_hex(this));
    }
    ~th_judger()
    {
        for(auto i:list) delete i.second;
        INFO("th_judger - end","id: "+to_string_hex(this));
    }
};
#endif