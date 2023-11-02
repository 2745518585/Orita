#pragma once
#ifndef _FILE_COMPILE
#define _FILE_COMPILE _FILE_COMPILE
#include"init.hpp"
#include"log.hpp"
#include"files.hpp"
#include"settings.hpp"
#include"process.hpp"
#include"thread.hpp"
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
class th_compiler: public thread_mgr<compiler>
{
  public:
    std::string class_name() const noexcept override
    {
        return "th_compiler";
    }
    void add(const std::string &name,const fil &file,const arg &argu=arg())
    {
        thread_mgr::add(name,new compiler(file,argu));
    }
    void add(const std::initializer_list<std::pair<std::string,fil>> file,const arg &argu=arg())
    {
        for(auto i:file) add(i.first,i.second,argu);
    }
    th_compiler():thread_mgr()
    {
        INFO(class_name()+" - start","id: "+to_string_hex(this));
    }
    ~th_compiler()
    {
        INFO(class_name()+" - end","id: "+to_string_hex(this));
    }
};
#endif