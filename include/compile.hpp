#pragma once
#ifndef _FILE_COMPILE
#define _FILE_COMPILE _FILE_COMPILE
#include"name.hpp"
#include"data.hpp"
#include"print.hpp"
#include"time.hpp"
namespace Compile
{
    int compile(std::string ans,std::string compile_argu,bool if_print)
    {
        if(get_namesuf(ans)!=".cpp") return -1;
        return ssystem("g++ \""+ans+"\" -o \""+get_exefile(ans)+"\" "+get_compile_argu()+" "+compile_argu+" "+(if_print?"":system_to_nul))!=0;
    }
}
int compile(std::string ans,std::string compile_argu="",bool if_print=true) {return Compile::compile(ans,compile_argu,if_print);}
class compiler
{
  public:
    std::atomic<int> running_sum;
    std::atomic<bool> if_end;
    std::mutex wait_que_lock,wait_end_lock,wait_result_lock;
    std::condition_variable wait_que,wait_end,wait_result;
    class comp_file
    {
      public:
        comp_file(){}
        comp_file(std::string name,std::string file,std::string argu):name(name),file(file),argu(argu){}
        std::string name,file,argu;
    };
    std::queue<comp_file> compile_que;
    std::map<std::string,int> results;
    int compile(std::string file,std::string compile_argu)
    {
        if(get_namesuf(file)!=".cpp") return -1;
        return ssystem("g++ \""+file+"\" -o \""+get_exefile(file)+"\" "+get_compile_argu()+" "+compile_argu+system_to_nul)!=0;
    }
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
            static std::mutex read_lock1;
            read_lock1.lock();
            if(if_end)
            {
                --running_sum;
                ssleep(10);
                if(running_sum==0) wait_end.notify_all();
                read_lock1.unlock();
                break;
            }
            if(compile_que.empty()) continue;
            comp_file file=compile_que.front();
            compile_que.pop();
            read_lock1.unlock();
            int result=compile(file.file,file.argu);
            static std::mutex read_lock2;
            read_lock2.lock();
            results[file.name]=result;
            wait_result.notify_all();
            read_lock2.unlock();
        }
    }
    compiler(int thread_sum)
    {
        thread_sum=std::min(thread_sum,(int)settings["max_thread_num"]);
        running_sum=0;
        if_end=false;
        for(int i=1;i<=thread_sum;++i) std::thread(&compiler::auto_compile,this).detach();
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
        ssleep(10);
    }
    void add(std::string name,std::string file,std::string argu="")
    {
        compile_que.push(comp_file(name,file,argu));
        wait_que.notify_one();
    }
    void add(std::initializer_list<std::initializer_list<std::string>> file,std::string argu="")
    {
        for(auto i:file)
        {
            if(i.size()!=2) continue;
            add(*i.begin(),*next(i.begin()));
        }
    }
    void wait(std::initializer_list<std::string> name)
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
    std::pair<int,std::string> get(std::initializer_list<std::string> name)
    {
        for(auto i:name)
        {
            if(!results.count(i)||results[i]) return std::make_pair(1,i);
        }
        return std::make_pair(0,"");
    }
};
#endif