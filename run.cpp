#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
json make_cor_parameter()
{
    json cor_parameter={
        {"f",{-1,1}},
        {"c",{-1,0,1}},
        {"t",{-1,1}}
    };
    return cor_parameter;
}
json cor_parameter=make_cor_parameter();
int run_main()
{
    // init name
    string ans,chk;
    if(get_sum_parameter("f")==1) add_file(_run_ans,get_parameter("f",1));
    if(find_name(_run_ans)) {cout<<"\nans:";print_result(_NF);return 0;}
    ans=add_namesuf(get_name(_run_ans),".cpp");
    bool use_checker=false;
    if(get_sum_parameter("c")!=-1)
    {
        if(get_sum_parameter("c")==1) add_file(_run_chk,get_parameter("c",1));
        if(find_name(_run_chk)) {cout<<"\nchecker:";print_result(_NF);return 0;}
        chk=add_namesuf(get_name(_run_chk),".cpp");
        if(chk[0]!='<') use_checker=true;
    }
    else chk="<1>";
    // find file
    if(find_file(ans)) {cout<<"\nans:";print_result(_NF);return 0;}
    if(use_checker&&find_file(chk)) {cout<<"\nchecker:";print_result(_NF);return 0;}
    // init time
    if(get_sum_parameter("t")==1) change_time_limit(stoi(get_parameter("t",1)));
    // compile file
    if(compile(ans)) {print_result(_CE);return 0;}
    if(use_checker&&compile(chk)) {cout<<"\nchecker:";print_result(_CE);return 0;}
    // find dangerous syscalls
    if(find_dangerous_syscalls(ans)) {print_result(_DS);}
    // run
    judge_monitor(ans,chk);
    // print result
    print_judge_result();
    // copy result
    system("md data"+system_to_nul);
    copy_result("data\\data.in","data\\data.in");
    copy_result("data\\data.out","data\\data.out");
    copy_result("data\\data.ans","data\\data.ans");
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    if(init_parameter(argc,argv))
    {
        print_result(_II);
        return 0;
    }
    if(check_parameter(cor_parameter))
    {
        print_result(_II);
        return 0;
    }
    int exit_code=run_main();
    End();
    return exit_code;
}