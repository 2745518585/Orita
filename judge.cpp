#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int judge_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    // init name
    string ans,chk;
    if(get_sum_parameter("f")>=1) add_file(_run_ans,get_parameter("f",1));
    if(find_name(_run_ans)) {cout<<"\nans:";print_result(_NF);return 0;}
    ans=add_namesuf(get_name(_run_ans),".cpp");
    bool use_checker=false;
    if(get_sum_parameter("c")!=-1)
    {
        if(get_sum_parameter("c")>=1) add_file(_run_chk,get_parameter("c",1));
        if(find_name(_run_chk)) {cout<<"\nchecker:";print_result(_NF);return 0;}
        chk=add_namesuf(get_name(_run_chk),".cpp");
        if(chk[0]!='<') use_checker=true;
    }
    else chk="<1>";
    // find file
    if(find_file(ans)) {cout<<"\nans:";print_result(_NF);return 0;}
    if(use_checker&&find_file(chk)) {cout<<"\nchecker:";print_result(_NF);return 0;}
    // init time
    if(get_sum_parameter("t")>=1) change_time_limit(stoi(get_parameter("t",1)));
    if(get_sum_parameter("d")<2)
    {
        print_result(_Success);
        return 0;
    }
    // compile file
    if(compile(ans)) {print_result(_CE);return 0;}
    if(use_checker&&compile(chk)) {cout<<"\nchecker:";print_result(_CE);return 0;}
    // find dangerous syscalls
    if(find_dangerous_syscalls(ans)) {print_result(_DS);}
    string name_pre=get_parameter("d",1);
    ofstream file(UTF8toGB("result.txt"));
    int total_sum=stoi(get_parameter("d",2)),ac_sum=0;
    for(int i=1;i<=total_sum;++i)
    {
        cout<<"#"<<i<<"--------------------------------------------------"<<"\n";
        Judge::in_file=running_address+"\\"+name_pre+to_string(i)+".in";
        Judge::out_file=running_address+"\\"+name_pre+to_string(i)+".out";
        Judge::ans_file=running_address+"\\"+name_pre+to_string(i)+".ans";
        if(find_file(Judge::in_file)) {print_result(_NF);file<<i<<":\t"<<get_short_result(_NF)<<"\n";continue;}
        if(chk!="<0>"&&find_file(Judge::out_file)) {print_result(_NF);file<<i<<":\t"<<get_short_result(_NF)<<"\n";continue;}
        judge_monitor(ans,chk);
        print_judge_result();
        if(Judge::result==0) ++ac_sum;
        file<<i<<":\t"<<get_short_result(Judge::result)<<"\n";
    }
    file.close();
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