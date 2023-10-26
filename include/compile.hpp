#pragma once
#ifndef _FILE_COMPILE
#define _FILE_COMPILE _FILE_COMPILE
#include"init.hpp"
#include"log.hpp"
#include"files.hpp"
#include"settings.hpp"
#include"process.hpp"
class compiler
{
  public:
    const fil file;
    const arg argu;
    int exit_code;
    Poco::Pipe in,out,err;
    process_handle *ph=NULL;
    bool if_end=false;
    std::condition_variable *wait_end=new std::condition_variable;
    compiler(const fil &_file,const arg &_argu=arg()):file(_file),argu((arg)file+"-o"+replace_extension(file,exe_suf)+compile_argu+_argu) {}
    ~compiler() {delete ph;delete wait_end;}
    void wait_for() {try {ph->wait();} catch(...) {}}
    void start()
    {
        INFO("compile - start","id: "+to_string_hex(this),"argu: "+add_squo(argu));
        ph=new process_handle(Poco::Process::launch(compiler_command.path(),argu,&in,&out,&err));
        std::future<void> run_future(std::async(std::launch::async,&compiler::wait_for,this));
        if(run_future.wait_for(compile_time_limit)!=std::future_status::ready)
        {
            Poco::Process::kill(*ph);
            run_future.wait();
            WARN("compile - timeout","id: "+to_string_hex(this));
            add();
            return;
        }
        if(exit_code=ph->wait()) WARN("compile - fail","id: "+to_string_hex(this),"argu: "+add_squo(argu));
        else INFO("compile - success","id: "+to_string_hex(this),"argu: "+add_squo(argu));
        if_end=true;
        wait_end->notify_all();
    }
    int operator()()
    {
        process::run(std::bind(&compiler::start,this));
        return ph->wait()!=0;
    }
    void add()
    {
        INFO("compile - add","id: "+to_string_hex(this),"argu: "+add_squo(argu));
        process::add(std::bind(&compiler::start,this));
    }
};
class th_compiler
{
  public:
    std::mutex read_lock;
    std::map<std::string,compiler*> list;
    std::queue<std::string> new_que;
    std::condition_variable wait_que;
    std::atomic<size_t> running_sum;
    void monitor(const std::string &name)
    {
        compiler *target=list[name];
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
    void add(const std::string &name,const fil &file,const arg &argu=arg())
    {
        read_lock.lock();
        if(list.count(name))
        {
            WARN("th_compiler - repeated compiler name","name: ",name);
            return;
        }
        list[name]=new compiler(file,argu);
        list[name]->add();
        ++running_sum;
        std::thread(&th_compiler::monitor,this,name).detach();
        INFO("th_compiler - add compile task","id: "+to_string_hex(this),"name: "+add_squo(name),"file: "+add_squo(file),"argu: "+add_squo(argu));
        read_lock.unlock();
    }
    void add(const std::initializer_list<std::pair<std::string,fil>> file,const arg &argu=arg())
    {
        for(auto i:file) add(i.first,i.second,argu);
    }
    void wait(const std::string &name)
    {
        read_lock.lock();
        if(!list.count(name)) throw Poco::Exception("empty compiler name");
        compiler *target=list[name];
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
            if(running_sum==0) return "";
            read_lock.lock();
            if(new_que.empty())
            {
                read_lock.unlock();
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
    th_compiler()
    {
        INFO("th_compiler - start","id: "+to_string_hex(this));
    }
    ~th_compiler()
    {
        for(auto i:list) delete i.second;
        INFO("th_compiler - end","id: "+to_string_hex(this));
    }
};
#endif