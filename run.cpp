#include<bits/stdc++.h>
#include<windows.h>
#include "run.h"
using namespace std;
int main(int argc,char **argv)
{
    init_parameter(argc,argv);
    input_name(1,parameter['f'][1]);
    if(num_parameter['t']>=1) change_time_limit(atoi(parameter['t'][1]));
    print_judge2(1,1);
    return 0;
}