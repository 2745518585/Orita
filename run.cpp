#include<bits/stdc++.h>
#include<windows.h>
#include "run.hpp"
using namespace std;
const int N=1001;
char instruct[N];
int main(int argc,const char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("f")>=1)
    {
        add_name(run_run,get_parameter("f",1),".cpp");
        add_running_address(run_run);
    }
    if(get_sum_parameter("t")>=1) change_time_limit(atoi(get_parameter("t",1)));
    if(copy_source(get_address(run_run),get_name(run_run),"source",get_name(run_run)))
    {
        print_result(No_such_file);
        return 0;
    }
    print_judge_complete(run_run,1);
    if(system("dir data > \"%appdata%\\Orita\\rubbish\\rubbish.txt\"")) system("md data");
    copy_result("data","data.in","data","data.in");
    copy_result("data","data.out","data","data.out");
    copy_result("data","data.ans","data","data.ans");
    return 0;
}