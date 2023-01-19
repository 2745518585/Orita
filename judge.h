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
        if(if_compile) if(compile(name_num)) return if_end=true,result=Compile_Error;
        sprintf(instruct,"%%appdata%%\\Orita\\source\\%s.exe < %%appdata%%\\Orita\\data\\data.in > %%appdata%%\\Orita\\data\\data.ans",get_name_pre(name_num));
        begin_time=clock();
        if(system(instruct)) return if_end=true,result=Runtime_Error;
        if_end=true;
        time=(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000;
        if(system("fc %appdata%\\Orita\\data\\data.out %appdata%\\Orita\\data\\data.ans > %appdata%\\Orita\\rubbish\\rubbish.txt"))
        {
            if(time>get_time_limit()) result=Time_Limit_Error_Wrong_Answer;
            else result=Wrong_Answer;
        }
        else
        {
            if(time>get_time_limit()) result=Time_Limit_Error_Correct_Answer;
            else result=Accepted;
        }
        return result;
    }
    void print_judge(int name_num,bool if_compile)
    {
        judge(name_num,if_compile);
        print_result(result,time);
    }
    void print_judge_complete(int name_num,bool if_compile)
    {
        if(if_compile)
        {
            if(compile(name_num))
            {
                print_result(Compile_Error);
                return;
            }
        }
        if_end=false;
        result=-1;
        time_limit=get_time_limit();
        begin_time=-1;
        thread(judge,name_num,false).detach();
        while(begin_time==-1||(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000<time_limit*2)
        {
            if(if_end)
            {
                while(result==-1) Sleep(5);
                print_result(result,time);
                return;
            }
        }
        sprintf(instruct,"taskkill /f /pid %s.exe > %%appdata%%\\Orita\\rubbish\\rubbish2.txt",get_name_pre(name_num));
        system(instruct);
        result=Time_Limit_Error_over;
        print_result(result,time_limit*2);
    }
}
int judge(int name_num,bool if_compile) {return Judge::judge(name_num,if_compile);}
void print_judge(int name_num,bool if_compile) {Judge::print_judge(name_num,if_compile);}
void print_judge_complete(int name_num,bool if_compile) {Judge::print_judge_complete(name_num,if_compile);}
#endif