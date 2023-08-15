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
namespace Run
{
    class Init_run
    {
      public:
        Init_run()
        {
            Init::begin();
            Files::begin();
        }
        ~Init_run()
        {
            Init::end();
            Files::end();
        }
    }_Init_run;
}
#endif