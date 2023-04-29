#pragma once
#ifndef _FILE_NAME
#define _FILE_NAME _FILE_NAME
#include "init.hpp"
#define _run_ans 1
#define _run_chk 2
#define _check_in 11
#define _check_out 12
#define _check_ans 13
#define _check_chk 14
const int _custom_start = 100, _custom_tot = 100;
namespace Name
{
    const int name_len = 3;
    json name_json;
    void begin()
    {
        (std::ifstream)(appdata_path + sPATH_SE + "name.json") >> name_json;
    }
    void end()
    {
        (std::ofstream)(appdata_path + sPATH_SE + "name.json") << std::setw(4) << name_json;
    }
    int find_name(int num)
    {
        return (int)name_json["name" + to_string_len(num, name_len)].type() != 3;
    }
    void add_name(int num, std::string name)
    {
        name_json["name" + to_string_len(num, name_len)] = systoUTF8(name);
    }
    std::string get_name(int num)
    {
        return UTF8tosys(name_json["name" + to_string_len(num, name_len)]);
    }
    std::string get_filename(std::string name)
    {
        int len = name.size();
        for (int i = len - 1; i >= 0; --i)
            if (name[i] == PATH_SE)
                return name.substr(i + 1, len - (i + 1));
        return name;
    }
    std::string get_filename(int num)
    {
        std::string name = get_name(num);
        int len = name.size();
        for (int i = len - 1; i >= 0; --i)
            if (name[i] == PATH_SE)
                return name.substr(i + 1, len - (i + 1));
        return name;
    }
    std::string get_path(std::string name)
    {
        int len = name.size();
        for (int i = len - 1; i >= 0; --i)
            if (name[i] == PATH_SE)
                return name.substr(0, i);
        return name;
    }
    std::string get_path(int num)
    {
        return get_path(get_name(num));
    }
    std::string get_namepre(std::string name)
    {
        name = get_filename(name);
        int len = name.size();
        for (int i = len - 1; i >= 0; --i)
            if (name[i] == '.')
                return name.substr(0, i);
        return name;
    }
    std::string get_namepre(int num)
    {
        return get_namepre(get_name(num));
    }
    std::string get_namesuf(std::string name)
    {
        name = get_filename(name);
        int len = name.size();
        for (int i = len - 1; i >= 0; --i)
            if (name[i] == '.')
                return name.substr(i, len - i);
        return "";
    }
    std::string get_namesuf(int num)
    {
        return get_namesuf(get_name(num));
    }
    int get_custom_num(std::string name)
    {
        return stoi(name.substr(1, name.size() - 1)) + _custom_start;
    }
    void add_file(int num, std::string name)
    {
        if (name[0] == '<')
        {
            add_name(num, name);
            return;
        }
        while (name[0] == '"' && name[name.size() - 1] == '"')
            name = name.substr(1, name.size() - 2);
        if (name[0] == ':')
        {
            add_name(num, get_name(get_custom_num(name)));
            return;
        }
        add_name(num, fullpath(name));
    }
    std::string get_file(std::string name)
    {
        if (name[0] == '<')
            return name;
        while (name[0] == '"' && name[name.size() - 1] == '"')
            name = name.substr(1, name.size() - 2);
        if (name[0] == ':')
            return get_name(get_custom_num(name));
        return fullpath(name);
    }
    std::string add_namesuf(std::string name, std::string namesuf)
    {
        if (name[0] == '<')
            return name;
        if (name.size() < namesuf.size() || name.substr(name.size() - namesuf.size(), namesuf.size()) != namesuf)
            return name + namesuf;
        return name;
    }
}
int find_name(int num) { return Name::find_name(num); }
void add_name(int num, std::string name) { return Name::add_name(num, name); }
std::string get_name(int num) { return Name::get_name(num); }
std::string get_filename(std::string name) { return Name::get_filename(name); }
std::string get_filename(int num) { return Name::get_filename(num); }
std::string get_path(std::string name) { return Name::get_path(name); }
std::string get_path(int num) { return Name::get_path(num); }
std::string get_namepre(std::string name) { return Name::get_namepre(name); }
std::string get_namepre(int num) { return Name::get_namepre(num); }
std::string get_namesuf(std::string name) { return Name::get_namesuf(name); }
std::string get_namesuf(int num) { return Name::get_namesuf(num); }
int get_custom_num(std::string name) { return Name::get_custom_num(name); }
void add_file(int num, std::string name) { return Name::add_file(num, name); }
std::string get_file(std::string name) { return Name::get_file(name); }
std::string add_namesuf(std::string name, std::string namesuf) { return Name::add_namesuf(name, namesuf); }
#endif