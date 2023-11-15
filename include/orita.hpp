#pragma once
#ifndef _FILE_ORITA
#define _FILE_ORITA _FILE_ORITA
#include"init.hpp"
#include"env.h"
#include"log.hpp"
#include"files.hpp"
#include"settings.hpp"
#include"env.hpp"
#include"process.hpp"
#include"thread.hpp"
#include"compile.hpp"
#include"print.hpp"
#include"judge.hpp"
#include"app.hpp"
void save_config()
{
    Files::save();
    Settings::save();
}
#endif