#include<bits/stdc++.h>
#include<windows.h>
#include "run.hpp"
using namespace std;
const int N=1001,M=1000001;
int a[M];
char files[N],instruct1[N],instruct2[N],instruct3[N];
void copy(int num)
{
    sprintf(files,"%d.in",num);
    copy_result("data","data.in","data",files);
    sprintf(files,"%d.out",num);
    copy_result("data","data.out","data",files);
    sprintf(files,"%d.ans",num);
    copy_result("data","data.ans","data",files);
}
int main(int argc,const char **argv)
{
    srand(time(NULL));
    init_parameter(argc,argv);
    if(get_sum_parameter("f")>=3)
    {
        add_name(check_data_maker,get_parameter("f",1),".cpp");
        add_running_address(check_data_maker);
        add_name(check_std,get_parameter("f",2),".cpp");
        add_running_address(check_std);
        add_name(check_run,get_parameter("f",3),".cpp");
        add_running_address(check_run);
    }
    if(copy_source(get_address(check_data_maker),get_name(check_data_maker),"source",get_name(check_data_maker)))
    {
        print_result(No_such_file);
        return 0;
    }
    if(copy_source(get_address(check_std),get_name(check_std),"source",get_name(check_std)))
    {
        print_result(No_such_file);
        return 0;
    }
    if(copy_source(get_address(check_std),get_name(check_std),"source",get_name(check_std)))
    {
        print_result(No_such_file);
        return 0;
    }
    if(get_sum_parameter("n")<1) return 0;
    if(system("dir data > \"%appdata%\\Orita\\rubbish\\rubbish.txt\"")) system("md data");
    system("del /Q data\\* > %appdata%\\Orita\\rubbish\\rubbish.txt");
    if(compile(check_data_maker))
    {
        print_result(data_maker_Compile_Error);
        return 0;
    }
    if(compile(check_std))
    {
        print_result(std_Compile_Error);
        return 0;
    }
    if(compile(check_run))
    {
        print_result(Compile_Error);
        return 0;
    }
    int n=atoi(get_parameter("n",1));
    if(get_sum_parameter("t")>=1) change_time_limit(atoi(get_parameter("t",1)));
    sprintf(instruct1,"%%appdata%%\\Orita\\source\\%s.exe > %%appdata%%\\Orita\\data\\data.in",get_name_pre(check_data_maker));
    sprintf(instruct2,"%%appdata%%\\Orita\\source\\%s.exe < %%appdata%%\\Orita\\data\\data.in > %%appdata%%\\Orita\\data\\data.out",get_name_pre(check_std));
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
        sprintf(instruct1,"%%appdata%%\\Orita\\source\\%s.exe > %%appdata%%\\Orita\\data\\data.in %d",get_name_pre(check_data_maker),i);
        system(instruct1);
        system(instruct2);
        print_judge_complete(check_run,0);
        a[i]=Judge::result;
        if(a[i]!=0) copy(i);
        else ++s;
    }
    printf("\n%d/%d %.2lfpts\n\n",s,n,(double)s*100/n);
    return 0;
}