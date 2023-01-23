#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
string compile_parameter="-std=c++14 -O2 -Wl,--stack=2147483647";
int compile_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("o")!=-1)
    {
        for(int i=1;i<=get_sum_parameter("o");++i) compile_parameter=compile_parameter+" "+get_parameter("o",i);
    }
    if(!system("dir include"+system_to_nul)) compile_parameter+=" -I include";
    if(get_sum_parameter("f")<1)
    {
        system("dir /b /s > files.txt");
        ifstream file("files.txt");
        string files;
        while(file>>files)
        {
            add_complete_address(compile_file,files);
            if(get_name_suf(compile_file)==".cpp"&&get_name(compile_file)!="compile.cpp")
            {
                cout<<get_name(compile_file)<<"\n";
                if(compile(compile_file,compile_parameter)==0) print_result(Success);
                else print_result(Compile_Error);
            }
        }
        file.close();
        system("del /Q files.txt > nul 2>&1");
    }
    else
    {
        for(int i=1;i<=get_sum_parameter("f");++i)
        {
            add_file(compile_file,get_parameter("f",i),".cpp");
            cout<<get_name(compile_file)<<"\n";
            if(compile(compile_file,compile_parameter)==0) print_result(Success);
            else print_result(Compile_Error);
        }
    }
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=compile_main(argc,argv);
    End();
    return exit_code;
}