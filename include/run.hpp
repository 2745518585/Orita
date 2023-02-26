#ifndef _FILE_RUN
#define _FILE_RUN _FILE_RUN
#include"name.hpp"
#include"compile.hpp"
#include"data.hpp"
#include"print.hpp"
#include"judge.hpp"
#include"parameter.hpp"
#include"files.hpp"
void Begin()
{
    init();
    Judge::begin();
    Name::begin();
    Data::begin();
}
void End()
{
    Name::end();
    Data::end();
}
#endif