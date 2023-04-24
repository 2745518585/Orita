#pragma once
#ifndef _FILE_TIME
#define _FILE_TIME _FILE_TIME
#include"init.hpp"
struct stime
{
    #ifdef _WIN32
    LARGE_INTEGER begin_time;
    void init()
    {
        QueryPerformanceCounter(&begin_time);
    }
    int get_time()
    {
        LARGE_INTEGER now_time,time_per_sec;
        QueryPerformanceFrequency(&time_per_sec);
        QueryPerformanceCounter(&now_time);
        return (int)((double)(now_time.QuadPart-begin_time.QuadPart)*1000/(double)time_per_sec.QuadPart);
    }
    #endif
    #ifdef __linux__
    timeval begin_time;
    void init()
    {
        gettimeofday(&begin_time,NULL);
    }
    int get_time()
    {
        timeval now_time;
        gettimeofday(&now_time,NULL);
        return (now_time.tv_sec-begin_time.tv_sec)*1000+(now_time.tv_usec-begin_time.tv_usec)/1000;
    }
    #endif
};
#endif