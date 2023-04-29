#pragma once
#ifndef _FILE_INIT
#define _FILE_INIT _FILE_INIT
#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <sstream>
#include <thread>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#endif

#ifdef __linux__
#include <unistd.h>
#include <sys/time.h>
#endif

#ifdef _WIN32
std::string UTF8toGB(const std::string &utf8)
{
    if (utf8.empty())
        return "";
    std::stringstream ss;
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
    wchar_t *wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char *str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    ss << str;
    delete[] wstr;
    delete[] str;
    return ss.str();
}
std::string GBtoUTF8(const std::string &gb2312)
{
    if (gb2312.empty())
        return "";
    std::stringstream ss;
    int len = MultiByteToWideChar(CP_ACP, 0, gb2312.c_str(), -1, NULL, 0);
    wchar_t *wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, gb2312.c_str(), -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char *str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    ss << str;
    delete[] wstr;
    delete[] str;
    return ss.str();
}
#endif
std::string UTF8tosys(const std::string str)
{
#ifdef _WIN32
    return UTF8toGB(str);
#endif
#ifdef __linux__
    return str;
#endif
}
std::string systoUTF8(const std::string str)
{
#ifdef _WIN32
    return GBtoUTF8(str);
#endif
#ifdef __linux__
    return str;
#endif
}

#ifdef _WIN32
char PATH_SE = '\\';
std::string sPATH_SE = "\\";
#define _PATH_SE "\\"
#endif
#ifdef __linux__
char PATH_SE = '/';
std::string sPATH_SE = "/";
#define _PATH_SE "/"
#endif
std::string fullpath(std::string path)
{
#ifdef _WIN32
    char abspath[4096] = {0};
    _fullpath(abspath, path.c_str(), 4096);
#else
    char abspath[40960] = {0};
    realpath(path.c_str(), abspath);
#endif
    return abspath;
}

void ssleep(const unsigned time)
{
#ifdef _WIN32
    Sleep(time);
#endif
#ifdef __linux__
    usleep(time * 1000);
#endif
}

#ifdef _WIN32
std::string system_to_nul = " > nul 2>&1 ";
#endif
#ifdef __linux__
std::string system_to_nul = " > /dev/null 2>&1 ";
#endif
int ssystem(const std::string command)
{
#ifdef _WIN32
    return system(("cmd /C \"" + command + "\"").c_str());
#endif
#ifdef __linux__
    return system(command.c_str());
#endif
}

template <typename T>
std::string to_string_len(const T num, const int len)
{
    std::string str = std::to_string(num);
    if (str.size() > len)
        return str;
    return std::string(len - str.size(), '0') + str;
}
json settings;
namespace Init
{
    std::string get_running_path()
    {
        char path[1001];
        getcwd(path, 1000);
        return path;
    }
    std::string get_file_path()
    {
        std::string path = __FILE__;
        int len = path.size();
        for (int i = 0; i < len; ++i)
        {
            if (path[i] == '/' || path[i] == '\\')
                path[i] = PATH_SE;
        }
        while (path[len - 1] != PATH_SE)
            --len;
        --len;
        while (path[len - 1] != PATH_SE)
            --len;
        --len;
        path = path.substr(0, len);
        return path;
    }
    std::string get_appdata_path()
    {
#ifdef _WIN32
        return getenv("appdata") + sPATH_SE + "Orita";
#endif
#ifdef __linux__
        return getenv("HOME") + sPATH_SE + ".Orita";
#endif
    }
}
std::string running_path = Init::get_running_path(), file_path = Init::get_file_path(), appdata_path = Init::get_appdata_path();
namespace Init
{
    void begin()
    {
#ifdef _WIN32
        ssystem("del /Q " + appdata_path + _PATH_SE + "source" + _PATH_SE + "*" + system_to_nul);
        ssystem("del /Q " + appdata_path + _PATH_SE + "temp" + _PATH_SE + "*" + system_to_nul);
#endif
#ifdef __linux__
        ssystem("rm -r " + appdata_path + "/source/*" + system_to_nul);
        ssystem("rm -r " + appdata_path + "/temp/*" + system_to_nul);
#endif
        (std::ifstream)(appdata_path + _PATH_SE + "settings.json") >> settings;
    }
    void end()
    {
        (std::ofstream)(appdata_path + _PATH_SE + "settings.json") << std::setw(4) << settings;
    }
}
#endif