#ifndef COMPILE
#define COMPILE COMPILE
#include"name.hpp"
#include"print.hpp"
namespace Compile
{
    string compile_parameter="-std=c++14 -O2 -Wl,--stack=2147483647";
    int compile(int name_num)
    {
        if(get_name_suf(name_num)!=".cpp")
        {
            change_color(1,0,1,1);
            cout<<"\nFile format not recognized\n\n";
            change_color(1,1,1,1);
            return 1;
        }
        string name=get_name_pre(name_num);
        system("taskkill /f /pid "+name+".exe"+system_to_nul);
        string str;
        ifstream infile(string(getenv("appdata"))+"\\Orita\\source\\"+name+".cpp");
        ofstream outfile(string(getenv("appdata"))+"\\Orita\\source\\"+name+"#.cpp");
        while(getline(infile,str))
        {
            if(str.substr(0,8)!="#include") outfile<<str<<"\n";
        }
        infile.close();
        outfile.close();
        system("g++ -E \"%appdata%\\Orita\\source\\"+name+"#.cpp\" > \"%appdata%\\Orita\\source\\"+name+".e\" "+compile_parameter);
        system("del /Q \"%appdata%\\Orita\\source\\"+name+"#.cpp\"");
        infile.open(string(getenv("appdata"))+"\\Orita\\source\\"+name+".e");
        while(getline(infile,str))
        {
            if(str.find("fopen(")!=string::npos) return -1;
            if(str.find("freopen(")!=string::npos) return -1;
            if(str.find("ifstream(")!=string::npos) return -1;
            if(str.find("ofstream(")!=string::npos) return -1;
            if(str.find("system(")!=string::npos) return -1;
        }
        return system("g++ \"%appdata%\\Orita\\source\\"+name+".cpp\" -o \"%appdata%\\Orita\\source\\"+name+".exe\" "+compile_parameter)!=0;
    }
}
int compile(int name_num) {return Compile::compile(name_num);}
#endif