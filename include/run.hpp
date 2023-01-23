#ifndef RUN
#define RUN RUN
#include"name.hpp"
#include"compile.hpp"
#include"data.hpp"
#include"print.hpp"
#include"judge.hpp"
#include"parameter.hpp"
#include"files.hpp"
void Begin()
{
    Name::begin();
    Data::begin();
}
void End()
{
    Name::end();
    Data::end();
}
#endif