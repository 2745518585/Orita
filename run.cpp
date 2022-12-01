#include<bits/stdc++.h>
#include<windows.h>
#include "run.h"
using namespace std;
const int N=1001;
char instruct[N];
int main(int argc,char **argv)
{
    init_parameter(argc,argv);
    input_name(1,parameter['f'][1]);
    if(num_parameter['t']>=1) change_time_limit(atoi(parameter['t'][1]));
    print_judge2(1,1);
    sprintf(instruct,"copy %s\\run\\data\\data.in ..\\data\\ > %s\\run\\rubbish\\rubbish.txt",getenv("appdata"),getenv("appdata"));
    system(instruct);
    sprintf(instruct,"copy %s\\run\\data\\data.out ..\\data\\ > %s\\run\\rubbish\\rubbish.txt",getenv("appdata"),getenv("appdata"));
    system(instruct);
    sprintf(instruct,"copy %s\\run\\data\\run.out ..\\data\\ > %s\\run\\rubbish\\rubbish.txt",getenv("appdata"),getenv("appdata"));
    system(instruct);
    return 0;
}