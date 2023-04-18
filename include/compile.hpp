#pragma once
#ifndef _FILE_COMPILE
#define _FILE_COMPILE _FILE_COMPILE
#include"name.hpp"
#include"data.hpp"
#include"print.hpp"
namespace Compile
{
    int if_end_compile;
    bool if_end_print;
    int compile(std::string ans,std::string compile_parameter,bool if_print)
    {
        if(get_namesuf(ans)!=".cpp") return -1;
        std::string name=get_namepre(ans),address=get_address(ans);
        return ssystem("g++ \""+address+"\\"+name+".cpp\" -o \""+address+"\\"+name+".exe\" "+get_compile_parameter()+" "+compile_parameter+" "+(if_print?"":system_to_nul))!=0;
    }
    void printing(std::string str)
    {
        static int SUM=3;
        int sum=0;
        std::cout<<"Compiling "<<str;
        while(!if_end_compile)
        {
            sum=sum%SUM+1;
            for(int i=1;i<=sum;++i) std::cout<<".";
            for(int i=sum+1;i<=SUM;++i) std::cout<<" ";
            for(int i=1;i<=10;++i)
            {
                Sleep(5);
                if(if_end_compile) break;
            }
            for(int i=1;i<=SUM;++i) std::cout<<"\b";
        }
        if(if_end_compile!=-1)
        {
            for(int i=1;i<=SUM;++i) std::cout<<" ";
            for(int i=1;i<=SUM;++i) std::cout<<"\b";
            std::cout<<" Success\n";
        }
        if_end_print=true;
    }
    int print_compile(std::string ans,std::string str,std::string compile_parameter)
    {
        if_end_compile=0;
        if_end_print=false;
        std::thread(printing,str).detach();
        int result=compile(ans,compile_parameter,false);
        if(result) if_end_compile=-1;
        else if_end_compile=1;
        while(!if_end_print) Sleep(5);
        return result;
    }
    int find_dangerous_syscalls(std::string ans,std::string compile_parameter)
    {
        if(get_namesuf(ans)!=".cpp") return -1;
        std::string namepre=get_namepre(ans);
        std::ifstream infile(ans);
        std::ofstream outfile(appdata_address+"\\Orita\\temp\\"+namepre+".cpp");
        std::string str;
        while(getline(infile,str))
        {
            if(str.substr(0,8)!="#include") outfile<<str<<"\n";
        }
        infile.close();
        outfile.close();
        ssystem("g++ -E \""+appdata_address+"\\Orita\\temp\\"+namepre+".cpp\" > \""+appdata_address+"\\Orita\\temp\\"+namepre+".e\" "+get_compile_parameter()+" "+compile_parameter);
        ssystem("del /Q \""+appdata_address+"\\Orita\\temp\\"+namepre+".cpp\"");
        infile.open(appdata_address+"\\Orita\\temp\\"+namepre+".e");
        while(getline(infile,str))
        {
            if(str.find("fopen")!=std::string::npos||str.find("freopen")!=std::string::npos||str.find("std::ifstream")!=std::string::npos||str.find("std::ofstream")!=std::string::npos||str.find("fstream")!=std::string::npos||str.find("system")!=std::string::npos)
            {
                infile.close();
                ssystem("del /Q \""+appdata_address+"\\Orita\\temp\\"+namepre+".e\"");
                return 1;
            }
        }
        infile.close();
        ssystem("del /Q \""+appdata_address+"\\Orita\\temp\\"+namepre+".e\"");
        return 0;
    }
}
int compile(std::string ans,std::string compile_parameter="",bool if_print=true) {return Compile::compile(ans,compile_parameter,if_print);}
int print_compile(std::string ans,std::string str,std::string compile_parameter="") {return Compile::print_compile(ans,str,compile_parameter);}
int find_dangerous_syscalls(std::string ans,std::string compile_parameter="") {return Compile::find_dangerous_syscalls(ans,compile_parameter);}
#endif