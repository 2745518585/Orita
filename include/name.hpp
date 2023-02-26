#ifndef _FILE_NAME
#define _FILE_NAME _FILE_NAME
#include"init.hpp"
#define _run_ans 1
#define _run_chk 2
#define _judge_in 3
#define _judge_out 4
#define _judge_ans 5
#define _check_in 11
#define _check_out 12
#define _check_ans 13
#define _check_chk 14
#define _data_in 21
#define _data_out 22
#define _compile_file 31
const int _custom_start=100,_custom_tot=100;
namespace Name
{
    const int name_len=3;
    json name_json;
    void begin()
    {
        ifstream file(UTF8toGB(appdata_address+"\\Orita\\name.json"));
        file>>name_json;
        file.close();
    }
    void end()
    {
        ofstream file(UTF8toGB(appdata_address+"\\Orita\\name.json"));
        file<<setw(4)<<name_json;
        file.close();
    }
    int find_name(int num)
    {
        return (int)name_json["name"+to_string(num,name_len)].type()!=3;
    }
    void add_name(int num,string name)
    {
        name_json["name"+to_string(num,name_len)]=name;
    }
    string get_name(int num)
    {
        return name_json["name"+to_string(num,name_len)];
    }
    string get_filename(string name)
    {
        int len=name.size();
        for(int i=len-1;i>=0;--i) if(name[i]=='\\') return name.substr(i+1,len-(i+1));
        return name;
    }
    string get_filename(int num)
    {
        string name=get_name(num);
        int len=name.size();
        for(int i=len-1;i>=0;--i) if(name[i]=='\\') return name.substr(i+1,len-(i+1));
        return name;
    }
    string get_address(string name)
    {
        int len=name.size();
        for(int i=len-1;i>=0;--i) if(name[i]=='\\') return name.substr(0,i);
        return name;
    }
    string get_address(int num)
    {
        return get_address(get_name(num));
    }
    string get_namepre(string name)
    {
        name=get_filename(name);
        int len=name.size();
        for(int i=len-1;i>=0;--i) if(name[i]=='.') return name.substr(0,i);
        return name;
    }
    string get_namepre(int num)
    {
        return get_namepre(get_name(num));
    }
    string get_namesuf(string name)
    {
        name=get_filename(name);
        int len=name.size();
        for(int i=len-1;i>=0;--i) if(name[i]=='.') return name.substr(i,len-i);
        return "";
    }
    string get_namesuf(int num)
    {
        return get_namesuf(get_name(num));
    }
    int get_custom_num(string name)
    {
        return stoi(name.substr(1,name.size()-1))+_custom_start;
    }
    void add_file(int num,string name)
    {
        while(name[0]=='"'&&name[name.size()-1]=='"') name=name.substr(1,name.size()-2);
        if(name[0]==':')
        {
            add_name(num,get_name(get_custom_num(name)));
            return;
        }
        string complete_address;
        if(name[1]==':') complete_address=name;
        else complete_address=running_address+"\\"+name;
        add_name(num,complete_address);
    }
    string add_namesuf(string name,string namesuf)
    {
        if(name.size()<namesuf.size()||name.substr(name.size()-namesuf.size(),namesuf.size())!=namesuf) return name+namesuf;
        return name;
    }
}
int find_name(int num) {return Name::find_name(num);}
void add_name(int num,string name) {return Name::add_name(num,name);}
string get_name(int num) {return Name::get_name(num);}
string get_filename(string name) {return Name::get_filename(name);}
string get_filename(int num) {return Name::get_filename(num);}
string get_address(string name) {return Name::get_address(name);}
string get_address(int num) {return Name::get_address(num);}
string get_namepre(string name) {return Name::get_namepre(name);}
string get_namepre(int num) {return Name::get_namepre(num);}
string get_namesuf(string name) {return Name::get_namesuf(name);}
string get_namesuf(int num) {return Name::get_namesuf(num);}
int get_custom_num(string name) {return Name::get_custom_num(name);}
void add_file(int num,string name) {return Name::add_file(num,name);}
string add_namesuf(string name,string namesuf) {return Name::add_namesuf(name,namesuf);}
#endif