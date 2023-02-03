#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int judge_main(int argc,char **argv)
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
    if(find_file(__NAME__run_ans)) {print_result(__PRINT__ANS+__PRINT__NF);return 0;}
    if(use_checker&&find_file(__NAME__run_chk)) {print_result(__PRINT__CHK+__PRINT__NF);return 0;}
    if(get_sum_parameter("n")<1||get_sum_parameter("d")<1)
    {
        print_result(__PRINT__Success);
        return 0;
    }
    if(find_dangerous_syscalls(__NAME__run_ans)) {print_result(__PRINT__DS);return 0;}
    if(compile(__NAME__run_ans)) {print_result(__PRINT__CE);return 0;}
    if(use_checker&&compile(__NAME__run_chk)) {compile(__PRINT__CHK+__PRINT__CE);return 0;}
    string name_pre=get_parameter("d",1);
    ofstream file("result.txt");
    int total_sum=stoi(get_parameter("n",1)),ac_sum=0;
    for(int i=1;i<=total_sum;++i)
    {
        cout<<"#"<<i<<"--------------------------------------------------"<<"\n";
        add_address(__NAME__judge_in,get_running_address());
        add_name(__NAME__judge_in,name_pre+to_string(i)+".in");
        add_address(__NAME__judge_out,get_running_address());
        add_name(__NAME__judge_out,name_pre+to_string(i)+".out");
        add_address(__NAME__judge_ans,get_running_address());
        add_name(__NAME__judge_ans,name_pre+to_string(i)+".ans");
        if(find_file(__NAME__judge_in)) {print_result(__PRINT__NF);file<<i<<":\t"<<get_short_result(__PRINT__NF)<<"\n";continue;}
        if(find_file(__NAME__judge_out)) {print_result(__PRINT__NF);file<<i<<":\t"<<get_short_result(__PRINT__NF)<<"\n";continue;}
        print_judge_monitor(__NAME__run_ans,use_checker?__NAME__run_chk:0);
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