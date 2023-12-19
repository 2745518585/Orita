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
    json in_args(const fil &in_file,const fil &out_file,const fil &ans_file,const std::string &testcase_name,const unsigned &seed)
    {
        return {{"infile",in_file.path()},{"outfile",out_file.path()},{"ansfile",ans_file.path()},{"testcase_name",testcase_name},{"seed",std::to_string(seed)}};
    }
    json out_args(const fil &in_file,const fil &out_file,const fil &ans_file)
    {
        return {{"infile",in_file.path()},{"outfile",out_file.path()},{"ansfile",ans_file.path()}};
    }
    json ans_args(const fil &in_file,const fil &out_file,const fil &ans_file)
    {
        return {{"infile",in_file.path()},{"outfile",out_file.path()},{"ansfile",ans_file.path()}};
    }
    json chk_args(const fil &in_file,const fil &out_file,const fil &ans_file)
    {
        return {{"infile",in_file.path()},{"outfile",out_file.path()},{"ansfile",ans_file.path()}};
    }
}
#endif