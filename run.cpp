#include<bits/stdc++.h>
#include<windows.h>
#include "run.h"
using namespace std;
const int N=1001;
char instruct[N];
int main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(num_parameter['f']>=1)
    {
        add_name(run_run,parameter['f'][1],".cpp");
        add_running_address(run_run);
    }
    if(num_parameter['t']>=1) change_time_limit(atoi(parameter['t'][1]));
    if(copy_source(run_run))
    {
        print_result(No_such_file);
        return 0;
    }
    print_judge_complete(run_run,1);
    if(system("dir data > \"%appdata%\\Orita\\rubbish\\rubbish.txt\"")) system("md data");
    copy_result("data.in");
    copy_result("data.out");
    copy_result("run.out");
    return 0;
}