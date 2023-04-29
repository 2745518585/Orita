#pragma once
#ifndef _FILE_FILES
#define _FILE_FILES _FILE_FILES
#include "name.hpp"
namespace Files
{
    int copy_source(std::string file, std::string copy)
    {
#ifdef _WIN32
        return ssystem("copy \"" + file + "\" \"" + appdata_path + sPATH_SE + copy + "\"" + system_to_nul);
#endif
#ifdef __linux__
        return ssystem("cp \"" + file + "\" \"" + appdata_path + sPATH_SE + copy + "\"" + system_to_nul);
#endif
    }
    int copy_result(std::string file, std::string copy)
    {
#ifdef _WIN32
        return ssystem("copy \"" + appdata_path + sPATH_SE + file + "\" \"" + copy + "\"" + system_to_nul);
#endif
#ifdef __linux__
        return ssystem("cp \"" + appdata_path + sPATH_SE + file + "\" \"" + copy + "\"" + system_to_nul);
#endif
    }
    int find_file(std::string file)
    {
        return ssystem("dir \"" + file + "\"" + system_to_nul);
    }
}
int copy_source(std::string file, std::string copy) { return Files::copy_source(file, copy); }
int copy_result(std::string file, std::string copy) { return Files::copy_result(file, copy); }
int find_file(std::string file) { return Files::find_file(file); }
#endif