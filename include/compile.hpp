#ifndef _FILE_COMPILE
#define _FILE_COMPILE _FILE_COMPILE
#include"name.hpp"
#include"print.hpp"
namespace Compile
{
    string default_compile_parameter="-std=c++14 -O2 -Wl,--stack=2147483647";
    int compile(int name_num,string compile_parameter)
    {
        if(get_name_suf(name_num)!=".cpp") return -1;
        string name=get_name_pre(name_num),address=get_address(name_num);
        system("taskkill /f /pid "+name+".exe"+system_to_nul);
        return system("g++ \""+address+"\\"+name+".cpp\" -o \""+address+"\\"+name+".exe\" "+default_compile_parameter+" "+compile_parameter)!=0;
    }
    int find_dangerous_syscalls(int name_num,string compile_parameter)
    {
        if(get_name_suf(name_num)!=".cpp") return -1;
        string name=get_name_pre(name_num),address=get_address(name_num);
        ifstream infile(UTF8toGB(address+"\\"+name+".cpp"));
        ofstream outfile(UTF8toGB(appdata_address+"\\Orita\\source\\"+name+".cpp"));
        string str;
        while(getline(infile,str))
        {
            if(str.substr(0,8)!="#include") outfile<<str<<"\n";
        }
        infile.close();
        outfile.close();
        system("g++ -E \""+appdata_address+"\\Orita\\source\\"+name+".cpp\" > \""+appdata_address+"\\Orita\\source\\"+name+".e\" "+default_compile_parameter+" "+compile_parameter);
        system("del /Q \""+appdata_address+"\\Orita\\source\\"+name+".cpp\"");
        infile.open(UTF8toGB(appdata_address+"\\Orita\\source\\"+name+".e"));
        while(getline(infile,str))
        {
            if(str.find("fopen")!=string::npos||str.find("freopen")!=string::npos||str.find("ifstream")!=string::npos||str.find("ofstream")!=string::npos||str.find("fstream")!=string::npos||str.find("system")!=string::npos)
            {
                infile.close();
                system("del /Q \""+appdata_address+"\\Orita\\source\\"+name+".e\"");
                return 1;
            }
        }
        infile.close();
        system("del /Q \""+appdata_address+"\\Orita\\source\\"+name+".e\"");
        return 0;
    }
}
int compile(int name_num,string compile_parameter="") {return Compile::compile(name_num,compile_parameter);}
int find_dangerous_syscalls(int name_num,string compile_parameter="") {return Compile::find_dangerous_syscalls(name_num,compile_parameter);}
#endif