#pragma once
#ifndef _FILE_RUN
#define _FILE_RUN _FILE_RUN
#include"name.hpp"
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
            Name::begin();
            Data::begin();
        }
        ~Init_run()
        {
            Init::end();
            Name::end();
            Data::end();
        }
    }_Init_run;
}
#endif