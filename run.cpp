#include<bits/stdc++.h>
#include<windows.h>
#include "run.h"
using namespace std;
const int N=1001;
char instruct[N];
int main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(num_parameter['f']>=1) add_name(run_run,parameter['f'][1],".cpp");
    if(num_parameter['t']>=1) change_time_limit(atoi(parameter['t'][1]));
    print_judge2(run_run,1);
    sprintf(instruct,"copy %%appdata%%\\Orita\\data\\data.in ..\\data\\ > %%appdata%%\\Orita\\rubbish\\rubbish.txt");
    system(instruct);
    sprintf(instruct,"copy %%appdata%%\\Orita\\data\\data.out ..\\data\\ > %%appdata%%\\Orita\\rubbish\\rubbish.txt");
    system(instruct);
    sprintf(instruct,"copy %%appdata%%\\Orita\\data\\run.out ..\\data\\ > %%appdata%%\\Orita\\rubbish\\rubbish.txt");
    system(instruct);
    return 0;
}