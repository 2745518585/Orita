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
#define _custom_start 100
#define _custom_tot 100
namespace Name
{
    const int name_length=3;
    json name_json;
    void begin()
    {
        ifstream file(UTF8toGB(appdata_address+"\\Orita\\name\\name.json"));
        file>>name_json;
        file.close();
    }
    void end()
    {
        ofstream file(UTF8toGB(appdata_address+"\\Orita\\name\\name.json"));
        file<<setw(4)<<name_json;
        file.close();
    }
    bool find_name(int num)
    {
        return (int)name_json["name"+string(name_length-to_string(num).size(),'0')+to_string(num)].type()!=3;
    }
    void add_name(int num,string name)
    {
        name_json["name"+string(name_length-to_string(num).size(),'0')+to_string(num)]=name;
    }
    void add_name(int num,string name,string name_suf)
    {
        int length_name=name.size(),length_name_suf=name_suf.size();
        if(!(length_name>=length_name_suf&&name.substr(length_name-length_name_suf,length_name_suf)==name_suf)) name+=name_suf;
        name_json["name"+string(name_length-to_string(num).size(),'0')+to_string(num)]=name;
    };
    string get_name(int num)
    {
        return name_json["name"+string(name_length-to_string(num).size(),'0')+to_string(num)];
    }
    string get_name_pre(int num)
    {
        string name=name_json["name"+string(name_length-to_string(num).size(),'0')+to_string(num)];
        int len=name.size();
        for(int i=len-1;i>=0;--i)
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
        string name=name_json["name"+string(name_length-to_string(num).size(),'0')+to_string(num)];
        int len=name.size();
        bool if_find=false;
        for(int i=len-1;i>=0;--i)
        {
            if(name[i]=='.')
            {
                name=name.substr(i,len-i);
                break;
            }
        }
        if(if_find==false) name.substr(0,0);
        return name;
    }
    void add_address(int num,string address)
    {
        name_json["address"+string(name_length-to_string(num).size(),'0')+to_string(num)]=address;
    }
    string get_address(int num)
    {
        return name_json["address"+string(name_length-to_string(num).size(),'0')+to_string(num)];
    }
    string get_complete_address(int num)
    {
        return get_address(num)+"\\"+get_name(num);
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
            int name_num=get_custom_num(name);
            add_name(num,get_name(name_num));
            add_address(num,get_address(name_num));
            return;
        }
        string complete_address;
        if(name[1]==':') complete_address=name;
        else complete_address=running_address+"\\"+name;
        int len=complete_address.size();
        for(int i=len-1;i>=0;--i)
        {
            if(complete_address[i]=='\\')
            {
                add_name(num,complete_address.substr(i+1,len-(i+1)));
                add_address(num,complete_address.substr(0,i));
                return;
            }
        }
        add_name(num,complete_address);
        add_address(num,"");
    }
    void add_file(int num,string name,string name_suf)
    {
        while(name[0]=='"'&&name[name.size()-1]=='"') name=name.substr(1,name.size()-2);
        if(name[0]==':')
        {
            int name_num=get_custom_num(name);
            add_name(num,get_name(name_num),name_suf);
            add_address(num,get_address(name_num));
            return;
        }
        string complete_address;
        if(name[1]==':') complete_address=name;
        else complete_address=running_address+"\\"+name;
        int len=complete_address.size();
        for(int i=len-1;i>=0;--i)
        {
            if(complete_address[i]=='\\')
            {
                add_name(num,complete_address.substr(i+1,len-(i+1)),name_suf);
                add_address(num,complete_address.substr(0,i));
                return;
            }
        }
        add_name(num,complete_address,name_suf);
        add_address(num,"");
    }
}
bool find_name(int num) {return Name::find_name(num);}
void add_name(int num,string name) {Name::add_name(num,name);}
void add_name(int num,string name,string name_suf) {Name::add_name(num,name,name_suf);}
string get_name(int num) {return Name::get_name(num);}
string get_name_pre(int num) {return Name::get_name_pre(num);}
string get_name_suf(int num) {return Name::get_name_suf(num);}
void add_address(int num,string address) {Name::add_address(num,address);}
string get_address(int num) {return Name::get_address(num);}
string get_complete_address(int num) {return Name::get_complete_address(num);}
int get_custom_num(string name) {return Name::get_custom_num(name);}
void add_file(int num,string name) {Name::add_file(num,name);}
void add_file(int num,string name,string name_suf) {Name::add_file(num,name,name_suf);}
#endif