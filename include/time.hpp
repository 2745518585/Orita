#pragma once
#ifndef _FILE_TIME
#define _FILE_TIME _FILE_TIME
#include"init.hpp"
class stime
{
  public:
    std::chrono::_V2::system_clock::time_point begin_time;
    void init()
    {
        begin_time=std::chrono::high_resolution_clock::now();
    }
    int get_time()
    {
        auto end_time=std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time=end_time-begin_time;
        return time.count()*1000;
    }
};
#endif