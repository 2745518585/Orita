#ifndef NAME
#define NAME NAME
#include<bits/stdc++.h>
#include<windows.h>
#include<direct.h>
#include"nlohmann/json.hpp"
using namespace std;
using json=nlohmann::json;
#define run_run 1
#define check_data_maker 11
#define check_std 12
#define check_run 13
namespace Name
{
    json name_list;
    void begin()
    {
        ifstream file(string(getenv("appdata"))+"\\Orita\\name\\name.json");
        file>>name_list;
    }
    void end()
    {
        ofstream file(string(getenv("appdata"))+"\\Orita\\name\\name.json");
        file<<setw(4)<<name_list;
    }
    void add_name(int num,string name)
    {
        name_list["name"+to_string(num)]=name;
    }
    void add_name(int num,string name,string name_suf)
    {
        int length_name=name.size(),length_name_suf=name_suf.size();
        bool if_name_suf=true;
        for(int i=0;i<length_name_suf;++i)
        {
            if(name[length_name-i-1]!=name_suf[length_name_suf-i-1])
            {
                if_name_suf=false;
                break;
            }
        }
        if(if_name_suf==false) name+=name_suf;
        name_list["name"+to_string(num)]=name;
    };
    string get_name(int num)
    {
        return name_list["name"+to_string(num)];
    }
    string get_name_pre(int num)
    {
        string name=name_list["name"+to_string(num)];
        int length=name.size();
        for(int i=length-1;i>=0;--i)
        {
            if(name[i]=='.')
            {
                name=name.substr(0,i);
                break;
            }
        }
        return name;
    }
    string get_name_suf(int num)
    {
        string name=name_list["name"+to_string(num)];
        int length=name.size();
        bool if_find=false;
        for(int i=length-1;i>=0;--i)
        {
            if(name[i]=='.')
            {
                name=name.substr(i,length-i);
                break;
            }
        }
        if(if_find==false) name.substr(0,0);
        return name;
    }
    void add_address(int num,string address)
    {
        name_list["address"+to_string(num)]=address;
    }
    void add_running_address(int num)
    {
        char address[1001];
        getcwd(address,1000);
        name_list["address"+to_string(num)]=address;
    }
    string get_address(int num)
    {
        return name_list["address"+to_string(num)];
    }
}
void add_name(int num,string name) {Name::add_name(num,name);}
void add_name(int num,string name,string name_suf) {Name::add_name(num,name,name_suf);}
string get_name(int num) {return Name::get_name(num);}
string get_name_pre(int num) {return Name::get_name_pre(num);}
string get_name_suf(int num) {return Name::get_name_suf(num);}
void add_address(int num,string address) {Name::add_address(num,address);}
void add_running_address(int num) {Name::add_running_address(num);}
string get_address(int num) {return Name::get_address(num);}
#endif