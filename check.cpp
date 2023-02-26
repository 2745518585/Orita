#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
json make_cor_parameter()
{
    json cor_parameter={
        {"f",{-1,3}},
        {"if",{-1,1}},
        {"of",{-1,1}},
        {"af",{-1,1}},
        {"c",{-1,0,1}},
        {"n",{-1,1}},
        {"e",{-1,0}},
        {"p",{-1,0}},
        {"t",{-1,1}}
    };
    return cor_parameter;
}
json cor_parameter=make_cor_parameter();
int check_main()
{
    // init name
    string in,out,ans,chk;
    if(get_sum_parameter("f")==3)
    {
        add_file(_check_in,get_parameter("f",1));
        add_file(_check_out,get_parameter("f",2));
        add_file(_check_ans,get_parameter("f",3));
    }
    else
    {
        if(get_sum_parameter("if")>=1) add_file(_check_in,get_parameter("if",1));
        if(get_sum_parameter("of")>=1) add_file(_check_out,get_parameter("of",1));
        if(get_sum_parameter("af")>=1) add_file(_check_ans,get_parameter("af",1));
    }
    if(find_name(_check_in)) {cout<<"\ndata_maker:";print_result(_NF);return 0;}
    if(find_name(_check_out)) {cout<<"\nstd:";print_result(_NF);return 0;}
    if(find_name(_check_ans)) {cout<<"\nans:";print_result(_NF);return 0;}
    in=add_namesuf(get_name(_check_in),".cpp");
    out=add_namesuf(get_name(_check_out),".cpp");
    ans=add_namesuf(get_name(_check_ans),".cpp");
    bool use_checker=false;
    if(get_sum_parameter("c")!=-1)
    {
        if(get_sum_parameter("c")==1) add_file(_check_chk,get_parameter("c",1));
        if(find_name(_check_chk)) {cout<<"\nchecker:";print_result(_NF);return 0;}
        chk=add_namesuf(get_name(_check_chk),".cpp");
        if(chk[0]!='<') use_checker=true;
    }
    else chk="<1>";
    if(find_file(in)) {cout<<"\ndata_maker:";print_result(_NF);return 0;}
    if(find_file(out)) {cout<<"\nstd:";print_result(_NF);return 0;}
    if(find_file(ans)) {cout<<"\nans:";print_result(_NF);return 0;}
    if(use_checker&&find_file(chk)) {print_result(_NF);return 0;}
    // init time
    if(get_sum_parameter("t")==1) change_time_limit(stoi(get_parameter("t",1)));
    // init total sum
    if(get_sum_parameter("n")==-1)
    {
        print_result(_Success);
        return 0;
    }
    int total_sum=stoi(get_parameter("n",1));
    // compile file
    if(compile(in)) {cout<<"\ndata_maker:";print_result(_CE);return 0;}
    if(compile(out)) {cout<<"\nstd:";print_result(_CE);return 0;}
    if(compile(ans)) {print_result(_CE);return 0;}
    if(use_checker&&compile(chk)) {cout<<"\nchecker:";print_result(_CE);return 0;}
    // find dangerous syscalls
    if(find_dangerous_syscalls(in)) {cout<<"\ndata_maker:";print_result(_DS);}
    if(find_dangerous_syscalls(out)) {cout<<"\nstd:";print_result(_DS);}
    if(find_dangerous_syscalls(ans)) {print_result(_DS);}
    // init monitor
    bool use_monitor=false;
    if(get_sum_parameter("e")!=-1) use_monitor=true;
    // init compare
    bool use_compare=false;
    if(get_sum_parameter("p")!=-1) use_compare=true;
    // init data dir
    system("mkdir data"+system_to_nul);
    system("del /Q data\\*"+system_to_nul);
    // check
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
        if(use_compare)
        {
            if(use_monitor)
            {
                if(run_monitor(in," > \""+appdata_address+"\\Orita\\data\\data.in\" "+to_string(i))) {cout<<"\ndata_maker:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(Judge::exit_code!=0) {cout<<"\ndata_maker:";print_result(_RE,Judge::exit_code);continue;}
            }
            else system(get_address(in)+"\\"+get_namepre(in)+".exe > \""+appdata_address+"\\Orita\\data\\data.in\" "+to_string(i));
            Judge::ans_file=appdata_address+"\\Orita\\data\\data.out";
            cout<<"\nans1:";
            judge_monitor(out,"<0>");
            print_judge_result(Judge::result,Judge::time,Judge::exit_code,Judge::time_limit);
            int result1=Judge::result;
            Judge::ans_file=appdata_address+"\\Orita\\data\\data.ans";
            cout<<"ans2:";
            judge_monitor(ans,"<0>");
            print_judge_result(Judge::result,Judge::time,Judge::exit_code,Judge::time_limit);
            int result2=Judge::result;
            ++runned_sum;
            if(result1==_SR&&result2==_SR)
            {
                if(check_ans(chk))
                {
                    print_result(_DA);
                    copy_result("data\\data.in","data\\"+to_string(i)+".in");
                    copy_result("data\\data.out","data\\"+to_string(i)+".out");
                    copy_result("data\\data.ans","data\\"+to_string(i)+".ans");
                }
                else print_result(_SA),++ac_sum;
            }
        }
        else
        {
            if(use_monitor)
            {
                if(run_monitor(in," > \""+appdata_address+"\\Orita\\data\\data.in\" "+to_string(i))) {cout<<"\ndata_maker:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(Judge::exit_code!=0) {cout<<"\ndata_maker:";print_result(_RE,Judge::exit_code);continue;}
                if(run_monitor(out," < \""+appdata_address+"\\Orita\\data\\data.in\" > \""+appdata_address+"\\Orita\\data\\data.out\"")) {cout<<"\nstd:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(Judge::exit_code!=0) {cout<<"\nstd:";print_result(_RE,Judge::exit_code);continue;}
                ++runned_sum;
            }
            else
            {
                system(get_address(in)+"\\"+get_namepre(in)+".exe > \""+appdata_address+"\\Orita\\data\\data.in\" "+to_string(i));
                system(get_address(out)+"\\"+get_namepre(out)+".exe < \""+appdata_address+"\\Orita\\data\\data.in\" > \""+appdata_address+"\\Orita\\data\\data.out\"");
                ++runned_sum;
            }
            judge_monitor(ans,chk);
            print_judge_result();
            int result=Judge::result;
            if(result!=_AC&&result!=_SR&&result!=_SA)
            {
                copy_result("data\\data.in","data\\"+to_string(i)+".in");
                copy_result("data\\data.out","data\\"+to_string(i)+".out");
                copy_result("data\\data.ans","data\\"+to_string(i)+".ans");
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
    int exit_code=check_main();
    End();
    return exit_code;
}