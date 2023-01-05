#include<bits/stdc++.h>
#include<windows.h>
#include "run.h"
using namespace std;
const int N=1001;
char instruct[N];
int main(int argc,char **argv)
{
    init_parameter(argc,argv);
    input_name(run_run,parameter['f'][1],".cpp");
    if(num_parameter['t']>=1) change_time_limit(atoi(parameter['t'][1]));
    print_judge2(run_run,1);
    sprintf(instruct,"copy %%appdata%%\\run\\data\\data.in ..\\data\\ > %%appdata%%\\run\\rubbish\\rubbish.txt");
    system(instruct);
    sprintf(instruct,"copy %%appdata%%\\run\\data\\data.out ..\\data\\ > %%appdata%%\\run\\rubbish\\rubbish.txt");
    system(instruct);
    sprintf(instruct,"copy %%appdata%%\\run\\data\\run.out ..\\data\\ > %%appdata%%\\run\\rubbish\\rubbish.txt");
    system(instruct);
    return 0;
}