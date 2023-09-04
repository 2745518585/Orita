#pragma once
#ifndef _FILE_COMPILE
#define _FILE_COMPILE _FILE_COMPILE
#include"init.hpp"
#include"log.hpp"
#include"files.hpp"
#include"settings.hpp"
namespace Compile
{
    int compile(pat file,const std::string &compile_argu="",const bool if_print=true)
    {
        if(file.extension()!=".cpp")
        {
            WARN("compile - invaild file","file: "+add_quo(file));
            return -1;
        }
        const std::string command="g++ "+add_quo(file)+" -o "+add_quo(replace_extension(file,exe_suf))+" "+compile_argu+" "+(if_print?"":system_to_nul);
        INFO("compile - start","file: "+add_squo(file),"argu: "+add_squo(compile_argu),"command: "+add_squo(command));
        int result=ssystem(command);
        if(result) WARN("compile - fail","file: "+add_squo(file),"argu: "+add_squo(compile_argu),"command: "+add_squo(command));
        else INFO("compile - success","file: "+add_squo(file),"argu: "+add_squo(compile_argu),"command: "+add_squo(command));
        return result!=0;
    }
}
int compile(const pat &file) {return Compile::compile(file);}
int compile(const pat &file,const std::string &compile_argu) {return Compile::compile(file,compile_argu);}
int compile(const pat &file,const std::string &compile_argu,const bool if_print) {return Compile::compile(file,compile_argu,if_print);}
class compiler
{
  public:
    std::atomic<int> running_sum;
    std::atomic<bool> if_end;
    std::mutex wait_que_lock,wait_end_lock,wait_result_lock,read_lock1,read_lock2;
    std::condition_variable wait_que,wait_end,wait_result;
    class comp_file
    {
      public:
        std::string name,argu;
        pat file;
        comp_file(){}
        comp_file(const std::string &name,const pat &file,const std::string &argu):name(name),file(file),argu(argu){}
    };
    std::queue<comp_file> compile_que;
    std::map<std::string,int> results;
    void auto_compile()
    {
        ++running_sum;
        while(true)
        {
            {
                std::unique_lock<std::mutex> lock(wait_que_lock);
                wait_que.wait(lock,[&](){return !compile_que.empty()||if_end;});
                lock.unlock();
            }
            read_lock1.lock();
            if(if_end)
            {
                --running_sum;
                ssleep((tim)10);
                if(running_sum==0) wait_end.notify_all();
                read_lock1.unlock();
                break;
            }
            if(compile_que.empty()) continue;
            comp_file file=compile_que.front();
            compile_que.pop();
            read_lock1.unlock();
            int result=compile(file.file,file.argu,false);
            read_lock2.lock();
            results[file.name]=result;
            wait_result.notify_all();
            read_lock2.unlock();
        }
    }
    compiler(unsigned thread_sum)
    {
        thread_sum=std::min(thread_sum,max_thread_num);
        running_sum=0;
        if_end=false;
        for(unsigned i=1;i<=thread_sum;++i) std::thread(&compiler::auto_compile,this).detach();
        INFO("compiler - start","id: "+to_string_hex(this),"thread sum: "+std::to_string(thread_sum));
    }
    ~compiler()
    {
        if_end=true;
        wait_que.notify_all();
        {
            std::unique_lock<std::mutex> lock(wait_end_lock);
            wait_end.wait(lock,[&](){return running_sum==0;});
            lock.unlock();
        }
        ssleep((tim)10);
        INFO("compiler - end","id: "+to_string_hex(this));
    }
    void add(const std::string &name,const pat &file,const std::string &argu="")
    {
        compile_que.push(comp_file(name,file,argu));
        wait_que.notify_one();
        INFO("compiler - add compile task","id: "+to_string_hex(this),"name: "+add_squo(name),"file: "+add_squo(file),"argu: "+add_squo(argu));
    }
    void add(const std::initializer_list<std::pair<std::string,pat>> file,const std::string &argu="")
    {
        for(auto i:file)
        {
            add(i.first,i.second,argu);
        }
    }
    void wait(const std::initializer_list<std::string> name)
    {
        auto check=[&]()
        {
            for(auto i:name) if(!results.count(i)) return false;
            return true;
        };
        std::unique_lock<std::mutex> lock(wait_result_lock);
        wait_result.wait(lock,check);
        lock.unlock();
    }
    std::pair<int,std::string> get(const std::initializer_list<std::string> name)
    {
        for(auto i:name)
        {
            if(!results.count(i)||results[i]) return std::make_pair(1,i);
        }
        return std::make_pair(0,std::string(""));
    }
};
#endif