#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int judge_main(int argc,char **argv)
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
    if(get_sum_parameter("d")<2)
    {
        print_result(_Success);
        return 0;
    }
    if(find_dangerous_syscalls(_run_ans)) {print_result(_DS);return 0;}
    if(compile(_run_ans)) {print_result(_CE);return 0;}
    if(use_checker&&compile(_run_chk)) {compile(_CE);return 0;}
    string name_pre=get_parameter("d",1);
    ofstream file(UTF8toGB("result.txt"));
    int total_sum=stoi(get_parameter("d",2)),ac_sum=0;
    for(int i=1;i<=total_sum;++i)
    {
        cout<<"#"<<i<<"--------------------------------------------------"<<"\n";
        add_address(_judge_in,running_address);
        add_name(_judge_in,name_pre+to_string(i)+".in");
        add_address(_judge_out,running_address);
        add_name(_judge_out,name_pre+to_string(i)+".out");
        add_address(_judge_ans,running_address);
        add_name(_judge_ans,name_pre+to_string(i)+".ans");
        if(find_file(_judge_in)) {print_result(_NF);file<<i<<":\t"<<get_short_result(_NF)<<"\n";continue;}
        if(find_file(_judge_out)) {print_result(_NF);file<<i<<":\t"<<get_short_result(_NF)<<"\n";continue;}
        print_judge_monitor(_run_ans,use_checker?_run_chk:0);
        if(Judge::result==0) ++ac_sum;
        file<<i<<":\t"<<get_short_result(Judge::result)<<"\n";
    }
    cout<<ac_sum<<" / "<<total_sum;
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=judge_main(argc,argv);
    End();
    return exit_code;
}