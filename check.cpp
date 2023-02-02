#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
const int N=1001;
int check_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    system("del /Q \"%appdata%\\Orita\\source\\*.cpp\")"+system_to_nul);
    if(get_sum_parameter("f")>=3)
    {
        add_file(__NAME__check_in,get_parameter("f",1),".cpp");
        add_file(__NAME__check_out,get_parameter("f",2),".cpp");
        add_file(__NAME__check_ans,get_parameter("f",3),".cpp");
    }
    else
    {
        if(get_sum_parameter("if")>=1) add_file(__NAME__check_in,get_parameter("if",1),".cpp");
        if(get_sum_parameter("of")>=1) add_file(__NAME__check_out,get_parameter("of",1),".cpp");
        if(get_sum_parameter("af")>=1) add_file(__NAME__check_ans,get_parameter("af",1),".cpp");
    }
    bool use_checker=false;
    if(get_sum_parameter("c")!=-1)
    {
        use_checker=true;
        if(get_sum_parameter("c")>=1)
        {
            add_file(__NAME__check_chk,get_parameter("c",1),".cpp");
        }
    }
    if(find_file(__NAME__check_in)) {print_result(__PRINT__IN+__PRINT__NF);return 0;}
    if(find_file(__NAME__check_out)) {print_result(__PRINT__OUT+__PRINT__NF);return 0;}
    if(find_file(__NAME__check_ans)) {print_result(__PRINT__ANS+__PRINT__NF);return 0;}
    if(use_checker&&find_file(__NAME__check_chk)) {print_result(__PRINT__CHK+__PRINT__NF);return 0;}
    if(get_sum_parameter("n")<1)
    {
        print_result(__PRINT__Success);
        return 0;
    }
    system("md data"+system_to_nul);
    system("del /Q data\\*"+system_to_nul);
    if(find_dangerous_syscalls(__NAME__check_in)) {print_result(__PRINT__IN+__PRINT__DS);return 0;}
    if(find_dangerous_syscalls(__NAME__check_out)) {print_result(__PRINT__OUT+__PRINT__DS);return 0;}
    if(find_dangerous_syscalls(__NAME__check_ans)) {print_result(__PRINT__DS);return 0;}
    if(compile(__NAME__check_in)) {print_result(__PRINT__IN+__PRINT__CE);return 0;}
    if(compile(__NAME__check_out)) {print_result(__PRINT__OUT+__PRINT__CE);return 0;}
    if(compile(__NAME__check_ans)) {print_result(__PRINT__CE);return 0;}
    if(use_checker&&compile(__NAME__check_chk)) {print_result(__PRINT__CHK+__PRINT__CE);return 0;}
    int total_sum=stoi(get_parameter("n",1));
    if(get_sum_parameter("t")>=1) change_time_limit(stoi(get_parameter("t",1)));
    string instruct1=get_address(__NAME__check_in)+"\\"+get_name_pre(__NAME__check_in)+".exe > \"%appdata%\\Orita\\data\\data.in\"";
    string instruct2=get_address(__NAME__check_in)+"\\"+get_name_pre(__NAME__check_out)+".exe < \"%appdata%\\Orita\\data\\data.in\" > \"%appdata%\\Orita\\data\\data.out\"";
    int ac_sum=0;
    for(int i=1;i<=total_sum;++i)
    {
        cout<<"#"<<i<<"--------------------------------------------------";
        if(i-ac_sum-1!=0)
        {
            change_color(1,1,0,0);
            cout<<" Unaccepted "<<i-ac_sum-1;
            change_color(1,1,1,1);
        }
        cout<<"\n";
        system(instruct1+" "+to_string(i));
        system(instruct2);
        print_judge_complete(__NAME__check_ans,use_checker?__NAME__check_chk:0);
        int result=Judge::result;
        if(result!=__PRINT__AC)
        {
            copy_result("data","data.in","data",to_string(i)+".in");
            copy_result("data","data.out","data",to_string(i)+".out");
            copy_result("data","data.ans","data",to_string(i)+".ans");
        }
        else ++ac_sum;
    }
    cout<<"\n"<<ac_sum<<" / "<<total_sum<<"\n\n";
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=check_main(argc,argv);
    End();
    return exit_code;
}