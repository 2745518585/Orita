#ifndef NAME
#define NAME NAME
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#define run_run 1
#define check_data_maker 11
#define check_std 12
#define check_run 13
namespace Name
{
    void add_name(int num,string name)
    {
        ofstream file(string(getenv("appdata"))+"\\Orita\\name\\name"+to_string(num)+".txt");
        file<<name;
        file.close();
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
        ofstream file(string(getenv("appdata"))+"\\Orita\\name\\name"+to_string(num)+".txt");
        if(if_name_suf==false) file<<name<<name_suf;
        else file<<name;
        file.close();
    };
    string get_name(int num)
    {
        ifstream file(string(getenv("appdata"))+"\\Orita\\name\\name"+to_string(num)+".txt");
        string name;
        file>>name;
        file.close();
        return name;
    }
    string get_name_pre(int num)
    {
        ifstream file(string(getenv("appdata"))+"\\Orita\\name\\name"+to_string(num)+".txt");
        string name;
        file>>name;
        file.close();
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
        ifstream file(string(getenv("appdata"))+"\\Orita\\name\\name"+to_string(num)+".txt");
        string name;
        file>>name;
        file.close();
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
        ofstream file(string(getenv("appdata"))+"\\Orita\\name\\address"+to_string(num)+".txt");
        file<<address;
        file.close();
    }
    void add_running_address(int num)
    {
        system(("cd > \"%appdata%\\Orita\\name\\address"+to_string(num)+".txt\"").c_str());
    }
    string get_address(int num)
    {
        ifstream file(string(getenv("appdata"))+"\\Orita\\name\\address"+to_string(num)+".txt");
        string address;
        file>>address;
        file.close();
        return address;
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