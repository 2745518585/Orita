#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int run(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("f")>=1)
    {
        add_file(run_run,get_parameter("f",1),".cpp");
    }
    if(get_sum_parameter("t")>=1) change_time_limit(stoi(get_parameter("t",1)));
    system("del /Q %appdata%\\Orita\\source\\*"+system_to_nul);
    if(copy_source(get_address(run_run),get_name(run_run),"source",get_name(run_run)))
    {
        print_result(No_such_file);
        return 0;
    }
    print_judge_complete(run_run,1);
    system("md data"+system_to_nul);
    copy_result("data","data.in","data","data.in");
    copy_result("data","data.out","data","data.out");
    copy_result("data","data.ans","data","data.ans");
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=run(argc,argv);
    End();
    return exit_code;
}