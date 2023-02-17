#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int run_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("f")>=1) add_file(_run_ans,get_parameter("f",1),".cpp");
    if(get_sum_parameter("t")>=1) change_time_limit(stoi(get_parameter("t",1)));
    bool use_checker=false;
    if(get_sum_parameter("c")!=-1)
    {
        use_checker=true;
        if(get_sum_parameter("c")>=1) add_file(_run_chk,get_parameter("c",1),".cpp");
    }
    if(find_file(_run_ans)) {cout<<"\nans:";print_result(_NF);return 0;}
    if(use_checker&&find_file(_run_chk)) {cout<<"\nchecker:";print_result(_NF);return 0;}
    if(find_dangerous_syscalls(_run_ans)) {print_result(_DS);}
    if(compile(_run_ans)) {print_result(_CE);return 0;}
    if(use_checker&&compile(_run_chk)) {cout<<"\nchecker:";compile(_CE);return 0;}
    add_address(_judge_in,appdata_address+"\\Orita\\data");
    add_name(_judge_in,"data.in");
    add_address(_judge_out,appdata_address+"\\Orita\\data");
    add_name(_judge_out,"data.out");
    add_address(_judge_ans,appdata_address+"\\Orita\\data");
    add_name(_judge_ans,"data.ans");
    print_judge_monitor(_run_ans,use_checker?_run_chk:0);
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