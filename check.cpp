#include<bits/stdc++.h>
#include<windows.h>
#include "run.h"
using namespace std;
const int N=1001,M=1000001;
int a[M];
char instruct[N],instruct1[N],instruct2[N],instruct3[N];
void copy(int num)
{
    sprintf(instruct,"copy %%appdata%%\\run\\data\\data.in ..\\data\\%d.in > %%appdata%%\\run\\rubbish\\rubbish.txt",NUMA_NO_PREFERRED_NODE);
    system(instruct);
    sprintf(instruct,"copy %%appdata%%\\run\\data\\data.out ..\\data\\%d.out > %%appdata%%\\run\\rubbish\\rubbish.txt",NUMA_NO_PREFERRED_NODE);
    system(instruct);
    sprintf(instruct,"copy %%appdata%%\\run\\data\\run.out ..\\data\\%d.ans > %%appdata%%\\run\\rubbish\\rubbish.txt",NUMA_NO_PREFERRED_NODE);
    system(instruct);
}
int main(int argc,char **argv)
{
    srand(time(NULL));
    system("del /Q ..\\data\\*.in > %appdata%\\run\\rubbish\\rubbish.txt");
    system("del /Q ..\\data\\*.out > %appdata%\\run\\rubbish\\rubbish.txt");
    system("del /Q ..\\data\\*.ans > %appdata%\\run\\rubbish\\rubbish.txt");
    init_parameter(argc,argv);
    input_name(11,parameter['f'][1]);
    input_name(12,parameter['f'][2]);
    input_name(13,parameter['f'][3]);
    if(compile(11))
    {
        print_result(15,0);
        return 0;
    }
    if(compile(12))
    {
        print_result(25,0);
        return 0;
    }
    if(compile(13))
    {
        print_result(5,0);
        return 0;
    }
    int n=atoi(parameter['n'][1]);
    if(num_parameter['t']>=1) change_time_limit(atoi(parameter['t'][1]));
    sprintf(instruct1,"%%appdata%%\\run\\source\\%s.exe > %%appdata%%\\run\\data\\data.in",get_name_pre(11));
    sprintf(instruct2,"%%appdata%%\\run\\source\\%s.exe < %%appdata%%\\run\\data\\data.in > %%appdata%%\\run\\data\\data.out",get_name_pre(12));
    int s=0;
    for(int i=1;i<=n;++i)
    {
        printf("#%d--------------------------------------------------",i);
        if(i-s-1!=0)
        {
            change_color(1,1,0,0);
            printf(" Unaccepted %d",i-s-1);
            change_color(1,1,1,1);
        }
        printf("\n");
        sprintf(instruct1,"%%appdata%%\\run\\source\\%s.exe > %%appdata%%\\run\\data\\data.in %d",get_name_pre(11),i);
        system(instruct1);
        system(instruct2);
        print_judge(13,0);
        a[i]=Judge::result;
        if(a[i]!=0) copy(i);
        else ++s;
    }
    printf("\n%d/%d %.2lfpts\n\n",s,n,(double)s*100/n);
    return 0;
}