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
    bool if_end;
    int judge(int name_num,bool if_compile)
    {
        if(if_compile) if(compile(name_num)) return if_end=true,result=5;
        sprintf(instruct,"%%appdata%%\\run\\source\\%s.exe < %%appdata%%\\run\\data\\data.in > %%appdata%%\\run\\data\\run.out",get_name_pre(name_num));
        begin_time=clock();
        if(system(instruct)) return if_end=true,result=2;
        if_end=true;
        time=(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000;
        int temp_result;
        if(time>get_time_limit()) temp_result=3;
        else temp_result=0;
        if(system("fc %appdata%\\run\\data\\data.out %appdata%\\run\\data\\run.out > %appdata%\\run\\rubbish\\rubbish.txt")) return result=temp_result+1;
        return result=temp_result;
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
        if_end=false;
        result=-1;
        time_limit=get_time_limit();
        thread(judge,name_num,false).detach();
        clock_t start_time=clock();
        while((double)(clock()-begin_time)/CLOCKS_PER_SEC*1000<time_limit*2)
        {
            if(if_end)
            {
                while(result==-1) Sleep(5);
                print_result(result,time);
                return;
            }
        }
        sprintf(instruct,"taskkill /f /pid %s.exe > %%appdata%%\\run\\rubbish\\rubbish2.txt",get_name_pre(name_num));
        system(instruct);
        result=4;
        change_color(1,0,0,1);
        printf("\nTime Limit Error\nover %dms\n\n",time_limit*2);
        change_color(1,1,1,1);
    }
}
int judge(int name_num,bool if_compile) {return Judge::judge(name_num,if_compile);}
void print_judge(int name_num,bool if_compile) {Judge::print_judge(name_num,if_compile);}
void print_judge2(int name_num,bool if_compile) {Judge::print_judge2(name_num,if_compile);}
#endif