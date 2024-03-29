#pragma once
#ifndef _FILE_ENV_PRE
#define _FILE_ENV_PRE
#include"init.hpp"
std::string get_env(const std::string &str,const pat &dir=running_path,const json &args=json());
std::string replace_env(const std::string &str,const pat &dir=running_path,const json &args=json());
namespace env_args
{
    json filenosuf(const pat &file)
    {
        return {{"file",replace_extension(file,"").toString()},{"filename",replace_extension((pat)file.getFileName(),"").toString()},{"filepath",replace_extension(file.parent(),"").toString()}};
    }
    json filenosuf(const std::string &file)
    {
        return filenosuf((pat)file);
    }
    json filenosuf(const fil &file)
    {
        return filenosuf((pat)file.path());
    }
}
#endif