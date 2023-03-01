#ifndef _FILE_COMPILE
#define _FILE_COMPILE _FILE_COMPILE
#include"name.hpp"
#include"data.hpp"
#include"print.hpp"
namespace Compile
{
    int compile(string ans,string compile_parameter)
    {
        if(get_namesuf(ans)!=".cpp") return -1;
        string name=get_namepre(ans),address=get_address(ans);
        system("taskkill /f /pid "+name+".exe"+system_to_nul);
        return system("g++ \""+address+"\\"+name+".cpp\" -o \""+address+"\\"+name+".exe\" "+get_compile_parameter()+" "+compile_parameter)!=0;
    }
    int find_dangerous_syscalls(string ans,string compile_parameter)
    {
        if(get_namesuf(ans)!=".cpp") return -1;
        string namepre=get_namepre(ans);
        ifstream infile(UTF8toGB(ans));
        ofstream outfile(UTF8toGB(appdata_address+"\\Orita\\temp\\"+namepre+".cpp"));
        string str;
        while(getline(infile,str))
        {
            if(str.substr(0,8)!="#include") outfile<<str<<"\n";
        }
        infile.close();
        outfile.close();
        system("g++ -E \""+appdata_address+"\\Orita\\temp\\"+namepre+".cpp\" > \""+appdata_address+"\\Orita\\temp\\"+namepre+".e\" "+get_compile_parameter()+" "+compile_parameter);
        system("del /Q \""+appdata_address+"\\Orita\\temp\\"+namepre+".cpp\"");
        infile.open(UTF8toGB(appdata_address+"\\Orita\\temp\\"+namepre+".e"));
        while(getline(infile,str))
        {
            if(str.find("fopen")!=string::npos||str.find("freopen")!=string::npos||str.find("ifstream")!=string::npos||str.find("ofstream")!=string::npos||str.find("fstream")!=string::npos||str.find("system")!=string::npos)
            {
                infile.close();
                system("del /Q \""+appdata_address+"\\Orita\\temp\\"+namepre+".e\"");
                return 1;
            }
        }
        infile.close();
        system("del /Q \""+appdata_address+"\\Orita\\temp\\"+namepre+".e\"");
        return 0;
    }
}
int compile(string ans,string compile_parameter="") {return Compile::compile(ans,compile_parameter);}
int find_dangerous_syscalls(string ans,string compile_parameter="") {return Compile::find_dangerous_syscalls(ans,compile_parameter);}
#endif