#pragma once
#ifndef _FILE_RUN
#define _FILE_RUN _FILE_RUN
#include"files.hpp"
#include"compile.hpp"
#include"data.hpp"
#include"print.hpp"
#include"judge.hpp"
#include"argu.hpp"
#include"files.hpp"
#include"time.hpp"
namespace Run
{
    class Init_run
    {
      public:
        Init_run()
        {
            Init::begin();
            Files::begin();
            Data::begin();
        }
        ~Init_run()
        {
            Init::end();
            Files::end();
            Data::end();
        }
    }_Init_run;
}
#endif