#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int run_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("f")>=1) add_file(__NAME__run_ans,get_parameter("f",1),".cpp");
    if(get_sum_parameter("t")>=1) change_time_limit(stoi(get_parameter("t",1)));
    bool use_checker=false;
    if(get_sum_parameter("c")!=-1)
    {
        use_checker=true;
        if(get_sum_parameter("c")>=1) add_file(__NAME__run_chk,get_parameter("c",1),".cpp");
    }
    if(find_file(__NAME__run_ans)) {cout<<"\nans:";print_result(__PRINT__NF);return 0;}
    if(use_checker&&find_file(__NAME__run_chk)) {cout<<"\nchecker:";print_result(__PRINT__NF);return 0;}
    if(find_dangerous_syscalls(__NAME__run_ans)) {print_result(__PRINT__DS);return 0;}
    if(compile(__NAME__run_ans)) {print_result(__PRINT__CE);return 0;}
    if(use_checker&&compile(__NAME__run_chk)) {cout<<"\nchecker:";compile(__PRINT__CE);return 0;}
    add_address(__NAME__judge_in,"%appdata%\\Orita\\data");
    add_name(__NAME__judge_in,"data.in");
    add_address(__NAME__judge_out,"%appdata%\\Orita\\data");
    add_name(__NAME__judge_out,"data.out");
    add_address(__NAME__judge_ans,"%appdata%\\Orita\\data");
    add_name(__NAME__judge_ans,"data.ans");
    print_judge_monitor(__NAME__run_ans,use_checker?__NAME__run_chk:0);
    system("md data"+system_to_nul);
    copy_result("data","data.in","data","data.in");
    copy_result("data","data.out","data","data.out");
    copy_result("data","data.ans","data","data.ans");
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=run_main(argc,argv);
    End();
    return exit_code;
}