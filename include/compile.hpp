#pragma once
#ifndef _FILE_COMPILE
#define _FILE_COMPILE _FILE_COMPILE
#include"init.hpp"
#include"log.hpp"
#include"files.hpp"
#include"settings.hpp"
#include"threads.hpp"
class compiler
{
  public:
    const fil file;
    const arg argu;
    bool if_end=false;
    Poco::Pipe in,out,err;
    Poco::ProcessHandle *ph=NULL;
    std::condition_variable wait_end;
    compiler(const fil &_file,const arg &_argu=arg()):file(_file),argu((arg)file+"-o"+replace_extension(file,exe_suf)+compile_argu+_argu) {}
    void wait_for() {ph->wait();}
    void start()
    {
        INFO("compile - start","id: "+to_string_hex(this),"file: "+add_squo(file),"argu: "+add_squo(argu));
        ph=new Poco::ProcessHandle(Poco::Process::launch(compiler_command.path(),argu,&in,&out,&err));
        std::future<void> run_future(std::async(std::launch::async,&compiler::wait_for,this));
        if(run_future.wait_for(runtime_limit)!=std::future_status::ready)
        {
            Poco::Process::kill(*ph);
            run_future.wait();
            WARN("compile - timeout","id: "+to_string_hex(this),"file: "+add_squo(file));
            add();
            return;
        }
        if(ph->wait()) WARN("compile - fail","id: "+to_string_hex(this),"file: "+add_squo(file),"argu: "+add_squo(argu));
        else INFO("compile - success","id: "+to_string_hex(this),"file: "+add_squo(file),"argu: "+add_squo(argu));
        if_end=true;
        wait_end.notify_all();
    }
    int operator()()
    {
        threads::run(std::bind(&compiler::start,this));
        return ph->wait()!=0;
    }
    void add()
    {
        INFO("compile - add","id: "+to_string_hex(this),"file: "+add_squo(file),"argu: "+add_squo(argu));
        threads::add(std::bind(&compiler::start,this));
    }
};
class th_compiler
{
  public:
    std::mutex read_lock;
    std::map<std::string,compiler*> compiler_list;
    void add(const std::string &name,const fil &file,const arg &argu=arg())
    {
        read_lock.lock();
        if(compiler_list.count(name))
        {
            WARN("th_compiler - repeated compiler name","name: ",name);
            return;
        }
        compiler_list[name]=new compiler(file,argu);
        compiler_list[name]->add();
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
        if(!compiler_list.count(name)) throw Poco::Exception("empty compiler name");
        compiler *target=compiler_list[name];
        read_lock.unlock();
        {
            std::mutex wait_end_lock;
            std::unique_lock<std::mutex> lock(wait_end_lock);
            target->wait_end.wait(lock,[&](){return (bool)target->if_end;});
        }
    }
    void wait(const std::initializer_list<std::string> name)
    {
        for(auto i:name) wait(i);
    }
    void wait_all()
    {
        for(auto i:compiler_list) wait(i.first);
    }
    compiler *get(const std::string &name)
    {
        wait(name);
        return compiler_list[name];
    }
    std::pair<std::string,compiler*> get(const std::initializer_list<std::string> name)
    {
        for(auto i:name)
        {
            wait(i);
            if(compiler_list[i]->ph->wait()) return std::make_pair(i,compiler_list[i]);
        }
        return std::make_pair(std::string(""),(compiler*)NULL);
    }
    std::pair<std::string,compiler*> get_all()
    {
        for(auto i:compiler_list)
        {
            wait(i.first);
            if(i.second->ph->wait()) return i;
        }
        return std::make_pair(std::string(""),(compiler*)NULL);
    }
    th_compiler()
    {
        INFO("th_compiler - start","id: "+to_string_hex(this));
    }
    ~th_compiler()
    {
        INFO("th_compiler - end","id: "+to_string_hex(this));
    }
};
#endif