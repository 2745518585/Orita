#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int check_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    system("del /Q \""+appdata_address+"\\Orita\\source\\*.cpp\")"+system_to_nul);
    if(get_sum_parameter("f")>=3)
    {
        add_file(_check_in,add_namesuf(get_parameter("f",1),".cpp"));
        add_file(_check_out,add_namesuf(get_parameter("f",2),".cpp"));
        add_file(_check_ans,add_namesuf(get_parameter("f",3),".cpp"));
    }
    else
    {
        if(get_sum_parameter("if")>=1) add_file(_check_in,add_namesuf(get_parameter("if",1),".cpp"));
        if(get_sum_parameter("of")>=1) add_file(_check_out,add_namesuf(get_parameter("of",1),".cpp"));
        if(get_sum_parameter("af")>=1) add_file(_check_ans,add_namesuf(get_parameter("af",1),".cpp"));
    }
    if(find_name(_check_in)) {cout<<"\ndata_maker:";print_result(_NF);return 0;}
    if(find_name(_check_out)) {cout<<"\nstd:";print_result(_NF);return 0;}
    if(find_name(_check_ans)) {cout<<"\nans:";print_result(_NF);return 0;}
    bool use_checker=false;
    if(get_sum_parameter("c")!=-1)
    {
        use_checker=true;
        if(get_sum_parameter("c")>=1)
        {
            add_file(_check_chk,add_namesuf(get_parameter("c",1),".cpp"));
        }
        if(find_name(_run_chk)) {cout<<"\nchecker:";print_result(_NF);return 0;}
    }
    if(find_file(_check_in)) {cout<<"\ndata_maker:";print_result(_NF);return 0;}
    if(find_file(_check_out)) {cout<<"\nstd:";print_result(_NF);return 0;}
    if(find_file(_check_ans)) {cout<<"\nans:";print_result(_NF);return 0;}
    if(use_checker&&find_file(_check_chk)) {print_result(_NF);return 0;}
    if(get_sum_parameter("n")<1)
    {
        print_result(_Success);
        return 0;
    }
    system("md data"+system_to_nul);
    system("del /Q data\\*"+system_to_nul);
    if(find_dangerous_syscalls(_check_in)) {cout<<"\ndata_maker:";print_result(_DS);}
    if(find_dangerous_syscalls(_check_out)) {cout<<"\nstd:";print_result(_DS);}
    if(find_dangerous_syscalls(_check_ans)) {print_result(_DS);}
    if(compile(_check_in)) {cout<<"\ndata_maker:";print_result(_CE);return 0;}
    if(compile(_check_out)) {cout<<"\nstd:";print_result(_CE);return 0;}
    if(compile(_check_ans)) {print_result(_CE);return 0;}
    if(use_checker&&compile(_check_chk)) {cout<<"\nchecker:";print_result(_CE);return 0;}
    int total_sum=stoi(get_parameter("n",1));
    if(get_sum_parameter("t")>=1) change_time_limit(stoi(get_parameter("t",1)));
    bool use_monitor=false;
    if(get_sum_parameter("e")!=-1) use_monitor=true;
    add_file(_judge_in,appdata_address+"\\Orita\\data\\data.in");
    add_file(_judge_in,appdata_address+"\\Orita\\data\\data.out");
    add_file(_judge_in,appdata_address+"\\Orita\\data\\data.ans");
    bool use_compare=false;
    if(get_sum_parameter("p")!=-1) use_compare=true;
    int ac_sum=0,runned_sum=0;
    for(int i=1;i<=total_sum;++i)
    {
        cout<<"#"<<i<<"--------------------------------------------------";
        if(runned_sum-ac_sum!=0)
        {
            change_color(1,1,0,0);
            cout<<" Unaccepted "<<runned_sum-ac_sum;
            change_color(1,1,1,1);
        }
        cout<<"\n";
        if(use_compare==true)
        {
            if(use_monitor)
            {
                if(run_monitor(_check_in," > \""+appdata_address+"\\Orita\\data\\data.in\" "+to_string(i))) {cout<<"\ndata_maker:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(Judge::exit_code!=0) {cout<<"\ndata_maker:";print_result(_RE,Judge::exit_code);continue;}
            }
            else system(get_address(_check_in)+"\\"+get_namepre(_check_in)+".exe > \""+appdata_address+"\\Orita\\data\\data.in\" "+to_string(i));
            add_file(_judge_ans,appdata_address+"\\Orita\\data\\data.out");
            cout<<"\nans1:";
            print_judge_monitor(_check_out,-1);
            int result1=Judge::result;
            add_file(_judge_ans,appdata_address+"\\Orita\\data\\data.ans");
            cout<<"ans2:";
            print_judge_monitor(_check_ans,-1);
            int result2=Judge::result;
            ++runned_sum;
            if(result1==_SR&&result2==_SR)
            {
                if(system("fc "+appdata_address+"\\Orita\\data\\data.out "+appdata_address+"\\Orita\\data\\data.out"+system_to_nul)) print_result(_DA);
                else print_result(_SA),++ac_sum;
            }
        }
        else
        {
            if(use_monitor)
            {
                if(run_monitor(_check_in," > \""+appdata_address+"\\Orita\\data\\data.in\" "+to_string(i))) {cout<<"\ndata_maker:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(Judge::exit_code!=0) {cout<<"\ndata_maker:";print_result(_RE,Judge::exit_code);continue;}
                if(run_monitor(_check_out," < \""+appdata_address+"\\Orita\\data\\data.in\" > \""+appdata_address+"\\Orita\\data\\data.out\"")) {cout<<"\nstd:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(Judge::exit_code!=0) {cout<<"\nstd:";print_result(_RE,Judge::exit_code);continue;}
                ++runned_sum;
            }
            else
            {
                system(get_address(_check_in)+"\\"+get_namepre(_check_in)+".exe > \""+appdata_address+"\\Orita\\data\\data.in\" "+to_string(i));
                system(get_address(_check_out)+"\\"+get_namepre(_check_out)+".exe < \""+appdata_address+"\\Orita\\data\\data.in\" > \""+appdata_address+"\\Orita\\data\\data.out\"");
                ++runned_sum;
            }
            print_judge_monitor(_check_ans,use_checker?_check_chk:0);
            int result=Judge::result;
            if(result!=_AC)
            {
                copy_result("data","data.in","data",to_string(i)+".in");
                copy_result("data","data.out","data",to_string(i)+".out");
                copy_result("data","data.ans","data",to_string(i)+".ans");
            }
            else ++ac_sum;
        }
    }
    cout<<"\n"<<ac_sum<<" / "<<runned_sum<<"\n\n";
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=check_main(argc,argv);
    End();
    return exit_code;
}