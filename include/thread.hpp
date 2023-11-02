#pragma once
#ifndef _FILE_THREAD
#define _FILE_THREAD _FILE_THREAD
#include"init.hpp"
#include"log.hpp"
#include"settings.hpp"
template<typename run_t> class thread_mgr
{
  public:
    std::mutex read_lock;
    std::map<std::string,run_t*> list;
    std::queue<std::string> new_que;
    std::condition_variable wait_que;
    std::atomic<size_t> running_sum;
    virtual std::string class_name() const noexcept
    {
        return "thread_mgr";
    }
    void monitor(const std::string &name)
    {
        run_t *target=list[name];
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
    void add(const std::string &name,run_t *object)
    {
        read_lock.lock();
        if(list.count(name))
        {
            WARN(class_name()+" - repeated name","name: ",name);
            return;
        }
        list[name]=object;
        list[name]->add();
        ++running_sum;
        std::thread(&thread_mgr::monitor,this,name).detach();
        INFO(class_name()+" - add task","id: "+to_string_hex(this),"name: "+add_squo(name));
        read_lock.unlock();
    }
    void add(const std::initializer_list<std::pair<std::string,run_t*>> object)
    {
        for(auto i:object) add(i.first,i.second);
    }
    void wait(const std::string &name)
    {
        read_lock.lock();
        if(!list.count(name)) throw Poco::Exception("empty name");
        run_t *target=list[name];
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
                if(running_sum==0)
                {
                    read_lock.unlock();
                    return "";
                }
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
    thread_mgr()
    {
        INFO(class_name()+" - start","id: "+to_string_hex(this));
    }
    ~thread_mgr()
    {
        for(auto i:list) delete i.second;
        INFO(class_name()+" - end","id: "+to_string_hex(this));
    }
};
#endif