#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
json make_cor_parameter()
{
    json cor_parameter={
        {"f",{-2}},
        {"r",{-1,1}},
        {"o",{-2}}
    };
    return cor_parameter;
}
json cor_parameter=make_cor_parameter();
int compile_main()
{
    string compile_parameter="";
    if(get_sum_parameter("o")!=-1)
    {
        for(int i=1;i<=get_sum_parameter("o");++i) compile_parameter=compile_parameter+" "+get_parameter("o",i);
    }
    if(!system("dir include"+system_to_nul)) compile_parameter+=" -I include";
    if(get_sum_parameter("r")!=-1)
    {
        string file;
        file=get_file(add_namesuf(get_parameter("r",1),".cpp"));
        if(!compile(file,compile_parameter))
        {
            system(get_address(file)+"\\"+get_namepre(file)+".exe");
        }
    }
    else
    {
        for(int i=1;i<=get_sum_parameter("f");++i)
        {
            string file=get_file(add_namesuf(get_parameter("f",i),".cpp"));
            cout<<get_filename(file)<<"\n";
            if(compile(file,compile_parameter)==0) print_result(_Success);
            else print_result(_CE);
        }
    }
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    if(init_parameter(argc,argv)) {print_result(_II);return 0;}
    if(check_parameter(cor_parameter)) {print_result(_II);return 0;}
    int exit_code=compile_main();
    End();
    return exit_code;
}