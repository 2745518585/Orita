#pragma once
#ifndef _FILE_RUN
#define _FILE_RUN _FILE_RUN
#include"name.hpp"
#include"compile.hpp"
#include"data.hpp"
#include"print.hpp"
#include"judge.hpp"
#include"parameter.hpp"
#include"files.hpp"
#include"time.hpp"
void Begin()
{
    Init::begin();
    Judge::begin();
    Name::begin();
    Data::begin();
}
void End()
{
    Init::end();
    Name::end();
    Data::end();
}
#endif