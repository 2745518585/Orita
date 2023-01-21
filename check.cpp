#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
const int N=1001;
void copy(int num)
{
    copy_result("data","data.in","data",to_string(num)+".in");
    copy_result("data","data.out","data",to_string(num)+".out");
    copy_result("data","data.ans","data",to_string(num)+".ans");
}
int check(int argc,char **argv)
{
    init_parameter(argc,argv);
    system("del /Q \"%appdata%\\Orita\\source\\*\" > \"%appdata%\\Orita\\rubbish\\rubbish.txt\" 2>&1");
    if(get_sum_parameter("f")>=3)
    {
        add_name(check_data_maker,get_parameter("f",1),".cpp");
        add_running_address(check_data_maker);
        add_name(check_std,get_parameter("f",2),".cpp");
        add_running_address(check_std);
        add_name(check_run,get_parameter("f",3),".cpp");
        add_running_address(check_run);
    }
    if(copy_source(get_address(check_data_maker),get_name(check_data_maker),"source",get_name(check_data_maker)))
    {
        print_result(No_such_file);
        return 0;
    }
    if(copy_source(get_address(check_std),get_name(check_std),"source",get_name(check_std)))
    {
        print_result(No_such_file);
        return 0;
    }
    if(copy_source(get_address(check_run),get_name(check_run),"source",get_name(check_run)))
    {
        print_result(No_such_file);
        return 0;
    }
    if(get_sum_parameter("n")<1) return 0;
    if(system("dir data > \"%appdata%\\Orita\\rubbish\\rubbish.txt\" 2>&1")) system("md data");
    system("del /Q data\\* > \"%appdata%\\Orita\\rubbish\\rubbish.txt\" 2>&1");
    if(compile(check_data_maker))
    {
        print_result(data_maker_Compile_Error);
        return 0;
    }
    if(compile(check_std))
    {
        print_result(std_Compile_Error);
        return 0;
    }
    if(compile(check_run))
    {
        print_result(Compile_Error);
        return 0;
    }
    int total_sum=stoi(get_parameter("n",1));
    if(get_sum_parameter("t")>=1) change_time_limit(stoi(get_parameter("t",1)));
    string instruct1="%appdata%\\Orita\\source\\"+get_name_pre(check_data_maker)+".exe > \"%appdata%\\Orita\\data\\data.in\"";
    string instruct2="%appdata%\\Orita\\source\\"+get_name_pre(check_std)+".exe < \"%appdata%\\Orita\\data\\data.in\" > \"%appdata%\\Orita\\data\\data.out\"";
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
        system(instruct1.c_str());
        system(instruct2.c_str());
        print_judge_complete(check_run,0);
        int result=Judge::result;
        if(result!=0) copy(i);
        else ++ac_sum;
    }
    printf("\n%d/%d %.2lfpts\n\n",ac_sum,total_sum,(double)ac_sum*100/total_sum);
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=check(argc,argv);
    End();
    return exit_code;
}