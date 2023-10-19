#pragma once
#ifndef _FILE_PROCESS
#define _FILE_PROCESS _FILE_PROCESS
#include"init.hpp"
#include"settings.hpp"
namespace process
{
    std::atomic<unsigned> running_thread_num;
    std::mutex wait_que_lock,read_lock;
    std::condition_variable wait_que;
    void run(std::function<void()> func)
    {
        while(true)
        {
            {
                std::unique_lock<std::mutex> lock(wait_que_lock);
                wait_que.wait(lock,[&](){return running_thread_num<max_process_num;});
                lock.unlock();
            }
            read_lock.lock();
            if(running_thread_num>=max_process_num)
            {
                read_lock.unlock();
                continue;
            }
            ++running_thread_num;
            read_lock.unlock();
            func();
            read_lock.lock();
            --running_thread_num;
            wait_que.notify_one();
            read_lock.unlock();
            return;
        }
    }
    void add(std::function<void()> func)
    {
        std::thread(process::run,func).detach();
    }
}
#endif