#pragma once
#ifndef _FILE_THREADS
#define _FILE_THREADS _FILE_THREADS
#include"init.hpp"
#include"settings.hpp"
namespace threads
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
                wait_que.wait(lock,[&](){return running_thread_num<max_thread_num;});
                lock.unlock();
            }
            read_lock.lock();
            if(running_thread_num>=max_thread_num)
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
        std::thread(threads::run,func).detach();
    }
}
#endif