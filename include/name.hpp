#ifndef NAME
#define NAME NAME
#include"init.hpp"
#define run_run 1
#define check_data_maker 11
#define check_std 12
#define check_run 13
#define custom_start 100
namespace Name
{
    json name_json;
    void begin()
    {
        ifstream file(string(getenv("appdata"))+"\\Orita\\name\\name.json");
        file>>name_json;
        file.close();
    }
    void end()
    {
        ofstream file(string(getenv("appdata"))+"\\Orita\\name\\name.json");
        file<<setw(4)<<name_json;
        file.close();
    }
    void add_name(int num,string name)
    {
        name_json["name"+to_string(num)]=name;
    }
    void add_name(int num,string name,string name_suf)
    {
        int length_name=name.size(),length_name_suf=name_suf.size();
        if(!(length_name>=length_name_suf&&name.substr(length_name-length_name_suf,length_name_suf)==name_suf)) name+=name_suf;
        name_json["name"+to_string(num)]=name;
    };
    string get_name(int num)
    {
        return name_json["name"+to_string(num)];
    }
    string get_name_pre(int num)
    {
        string name=name_json["name"+to_string(num)];
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
        string name=name_json["name"+to_string(num)];
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
        name_json["address"+to_string(num)]=address;
    }
    void add_running_address(int num)
    {
        char address[1001];
        getcwd(address,1000);
        name_json["address"+to_string(num)]=address;
    }
    string get_address(int num)
    {
        return name_json["address"+to_string(num)];
    }
    int get_custom_num(string name)
    {
        return stoi(name.substr(1,name.size()-1))+custom_start;
    }
    void add_file(int num,string name)
    {
        if(name[0]!=':')
        {
            add_name(num,name);
            add_running_address(num);
        }
        else
        {
            int name_num=get_custom_num(name);
            add_name(num,get_name(name_num));
            add_address(num,get_address(name_num));
        }
    }
    void add_file(int num,string name,string name_suf)
    {
        if(name[0]!=':')
        {
            add_name(num,name,name_suf);
            add_running_address(num);
        }
        else
        {
            int name_num=get_custom_num(name);
            add_name(num,get_name(name_num),name_suf);
            add_address(num,get_address(name_num));
        }
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
void add_file(int num,string name) {Name::add_file(num,name);}
void add_file(int num,string name,string name_suf) {Name::add_file(num,name,name_suf);}
int get_custom_num(string name) {return Name::get_custom_num(name);}
#endif