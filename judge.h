#ifndef JUDGE
#define JUDGE JUDGE
#include<bits/stdc++.h>
#include<windows.h>
#include "name.h"
#include "compile.h"
#include "data.h"
#include "print.h"
#include "task.h"
using namespace std;
namespace Judge
{
    const int N=1001;
    char instruct[N];
    int result,time,time_limit;
    clock_t begin_time;
    FILE *file=NULL;
    int judge(int name_num,bool if_compile)
    {
        if(if_compile) if(compile(name_num)) return result=5;
        sprintf(instruct,"%s\\run\\source\\%s.exe < %s\\run\\data\\data.in > %s\\run\\data\\run.out",getenv("appdata"),get_name(name_num),getenv("appdata"),getenv("appdata"));
        begin_time=clock();
        if(system(instruct)) return result=2;
        time=(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000;
        if(time>get_time_limit()) result=3;
        else result=0;
        if(system("fc %appdata%\\run\\data\\data.out %appdata%\\run\\data\\run.out > %appdata%\\run\\rubbish\\rubbish.txt")) return ++result;
        return result;
    }
    void print_judge(int name_num,bool if_compile)
    {
        judge(name_num,if_compile);
        print_result(result,time);
    }
    void print_judge2(int name_num,bool if_compile)
    {
        if(if_compile)
        {
            if(compile(name_num))
            {
                print_result(5,0);
                return;
            }
        }
        sprintf(instruct,"start /b start_run.exe %d",name_num);
        system(instruct);
        time_limit=get_time_limit();
        Sleep(100);
        for(int i=1;i<=time_limit/50;++i)
        {
            Sleep(100);
            if(!find_task(name_num))
            {
                Sleep(50);
                return;
            }
        }
        if(!find_task(name_num)) return;
        system("taskkill /f /pid start_run.exe > %appdata%\\run\\rubbish\\rubbish.txt");
        sprintf(instruct,"taskkill /f /pid %s.exe > %s\\run\\rubbish\\rubbish.txt",get_name(name_num),getenv("appdata"));
        system(instruct);
        change_color(1,0,0,1);
        printf("\nTime Limit Error\nover %dms\n\n",time_limit*2);
        change_color(1,1,1,1);
    }
}
int judge(int name_num,bool if_compile) {return Judge::judge(name_num,if_compile);}
void print_judge(int name_num,bool if_compile) {Judge::print_judge(name_num,if_compile);}
void print_judge2(int name_num,bool if_compile) {Judge::print_judge2(name_num,if_compile);}
#endif