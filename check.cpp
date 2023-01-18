#include<bits/stdc++.h>
#include<windows.h>
#include "run.h"
using namespace std;
const int N=1001,M=1000001;
int a[M];
char instruct[N],instruct1[N],instruct2[N],instruct3[N];
void copy(int num)
{
    sprintf(instruct,"copy %%appdata%%\\Orata\\data\\data.in ..\\data\\%d.in > %%appdata%%\\Orata\\rubbish\\rubbish.txt",num);
    system(instruct);
    sprintf(instruct,"copy %%appdata%%\\Orata\\data\\data.out ..\\data\\%d.out > %%appdata%%\\Orata\\rubbish\\rubbish.txt",num);
    system(instruct);
    sprintf(instruct,"copy %%appdata%%\\Orata\\data\\run.out ..\\data\\%d.ans > %%appdata%%\\Orata\\rubbish\\rubbish.txt",num);
    system(instruct);
}
int main(int argc,char **argv)
{
    srand(time(NULL));
    system("del /Q ..\\data\\*.in > %appdata%\\Orata\\rubbish\\rubbish.txt");
    system("del /Q ..\\data\\*.out > %appdata%\\Orata\\rubbish\\rubbish.txt");
    system("del /Q ..\\data\\*.ans > %appdata%\\Orata\\rubbish\\rubbish.txt");
    init_parameter(argc,argv);
    if(num_parameter['f']>=3)
    {
        add_name(check_data_maker,parameter['f'][1]);
        add_name(check_std,parameter['f'][2]);
        add_name(check_run,parameter['f'][3]);
    }
    if(num_parameter['n']<=0) return 0;
    if(compile(check_data_maker))
    {
        print_result(data_maker_Compile_Error,0);
        return 0;
    }
    if(compile(check_std))
    {
        print_result(std_Compile_Error,0);
        return 0;
    }
    if(compile(check_run))
    {
        print_result(Compile_Error,0);
        return 0;
    }
    int n=atoi(parameter['n'][1]);
    if(num_parameter['t']>=1) change_time_limit(atoi(parameter['t'][1]));
    sprintf(instruct1,"%%appdata%%\\Orata\\source\\%s.exe > %%appdata%%\\Orata\\data\\data.in",get_name_pre(check_data_maker));
    sprintf(instruct2,"%%appdata%%\\Orata\\source\\%s.exe < %%appdata%%\\Orata\\data\\data.in > %%appdata%%\\Orata\\data\\data.out",get_name_pre(check_std));
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
        sprintf(instruct1,"%%appdata%%\\Orata\\source\\%s.exe > %%appdata%%\\Orata\\data\\data.in %d",get_name_pre(check_data_maker),i);
        system(instruct1);
        system(instruct2);
        print_judge2(check_run,0);
        a[i]=Judge::result;
        if(a[i]!=0) copy(i);
        else ++s;
    }
    printf("\n%d/%d %.2lfpts\n\n",s,n,(double)s*100/n);
    return 0;
}