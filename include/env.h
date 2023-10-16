#pragma once
#ifndef _FILE_ENV_PRE
#define _FILE_ENV_PRE _FILE_ENV_PRE
#include"init.hpp"
std::string get_env(const std::string &str,const pat &dir=running_path);
std::string replace_env(const std::string &str,const pat &dir=running_path);
#endif