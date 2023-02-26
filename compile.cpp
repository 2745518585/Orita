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
    if(get_sum_parameter("r")!=-1)
    {
        add_file(_compile_file,add_namesuf(get_parameter("r",1),".cpp"));
        if(!compile(_compile_file,compile_parameter))
        {
            system(get_address(_compile_file)+"\\"+get_namepre(_compile_file)+".exe");
        }
    }
    else if(get_sum_parameter("f")==-1)
    {
        system("dir /b /s > files.txt");
        ifstream file(UTF8toGB("files.txt"));
        string files;
        while(file>>files)
        {
            files=GBtoUTF8(files);
            add_file(_compile_file,files);
            if(get_namesuf(_compile_file)==".cpp"&&get_filename(_compile_file)!="compile.cpp")
            {
                cout<<UTF8toGB(get_filename(_compile_file))<<":\n";
                if(!compile(_compile_file,compile_parameter)) print_result(_Success);
                else print_result(_CE);
            }
        }
        file.close();
        system("del /Q files.txt > nul 2>&1");
    }
    else
    {
        for(int i=1;i<=get_sum_parameter("f");++i)
        {
            add_file(_compile_file,add_namesuf(get_parameter("f",i),".cpp"));
            cout<<UTF8toGB(get_filename(_compile_file))<<"\n";
            if(compile(_compile_file,compile_parameter)==0) print_result(_Success);
            else print_result(_CE);
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