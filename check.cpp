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
        add_file(check_data_maker,get_parameter("f",1),".cpp");
        add_file(check_std,get_parameter("f",2),".cpp");
        add_file(check_run,get_parameter("f",3),".cpp");
    }
    else
    {
        if(get_sum_parameter("if")>=1) add_file(check_data_maker,get_parameter("if",1),".cpp");
        if(get_sum_parameter("of")>=1) add_file(check_std,get_parameter("of",1),".cpp");
        if(get_sum_parameter("af")>=1) add_file(check_run,get_parameter("af",1),".cpp");
    }
    if(find_file(check_data_maker)) {print_result(No_such_file);return 0;}
    if(find_file(check_std)) {print_result(No_such_file);return 0;}
    if(find_file(check_run)) {print_result(No_such_file);return 0;}
    if(get_sum_parameter("n")<1) return 0;
    system("md data"+system_to_nul);
    system("del /Q data\\*"+system_to_nul);
    if(find_dangerous_syscalls(check_data_maker)) {print_result(data_maker_Dangerous_syscalls);return 0;}
    if(find_dangerous_syscalls(check_std)) {print_result(std_Dangerous_syscalls);return 0;}
    if(find_dangerous_syscalls(check_run)) {print_result(Dangerous_syscalls);return 0;}
    if(compile(check_data_maker)) {print_result(data_maker_Compile_Error);return 0;}
    if(compile(check_std)) {print_result(std_Compile_Error);return 0;}
    if(compile(check_run)) {print_result(Compile_Error);return 0;}
    int total_sum=stoi(get_parameter("n",1));
    if(get_sum_parameter("t")>=1) change_time_limit(stoi(get_parameter("t",1)));
    string instruct1=get_address(check_data_maker)+"\\"+get_name_pre(check_data_maker)+".exe > \"%appdata%\\Orita\\data\\data.in\"";
    string instruct2=get_address(check_data_maker)+"\\"+get_name_pre(check_std)+".exe < \"%appdata%\\Orita\\data\\data.in\" > \"%appdata%\\Orita\\data\\data.out\"";
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
        print_judge_complete(check_run,0);
        int result=Judge::result;
        if(result!=Accepted)
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