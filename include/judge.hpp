#ifndef _FILE_JUDGE
#define _FILE_JUDGE _FILE_JUDGE
#include"name.hpp"
#include"compile.hpp"
#include"data.hpp"
#include"print.hpp"
namespace Judge
{
    int result,time,time_limit,exit_code;
    clock_t begin_time;
    bool if_end;
    int judge(int name_num,bool if_compile)
    {
        if(if_compile)
        {
            if(find_dangerous_syscalls(name_num)) return if_end=true,result=__PRINT__Dangerous_syscalls;
            if(compile(name_num)) return if_end=true,result=__PRINT__Compile_Error;
        }
        string run_instruct=get_address(name_num)+"\\"+get_name_pre(name_num)+".exe < %appdata%\\Orita\\data\\data.in > %appdata%\\Orita\\data\\data.ans";
        begin_time=clock();
        if(exit_code=system(run_instruct)) return if_end=true,result=__PRINT__Runtime_Error;
        if_end=true;
        time=(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000;
        if(system("fc %appdata%\\Orita\\data\\data.out %appdata%\\Orita\\data\\data.ans"+system_to_nul))
        {
            if(time>get_time_limit()) result=__PRINT__Time_Limit_Error_Wrong_Answer;
            else result=__PRINT__Wrong_Answer;
        }
        else
        {
            if(time>get_time_limit()) result=__PRINT__Time_Limit_Error_Correct_Answer;
            else result=__PRINT__Accepted;
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
            if(find_dangerous_syscalls(name_num))
            {
                print_result(__PRINT__Dangerous_syscalls);
                return;
            }
            if(compile(name_num))
            {
                print_result(__PRINT__Compile_Error);
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
                if(result==__PRINT__Runtime_Error) print_result(result,exit_code);
                else print_result(result,time);
                return;
            }
        }
        system(("taskkill /f /pid "+get_name_pre(name_num)+".exe"+system_to_nul).c_str());
        result=__PRINT__Time_Limit_Error_over;
        print_result(result,time_limit*2);
    }
}
int judge(int name_num,bool if_compile) {return Judge::judge(name_num,if_compile);}
void print_judge(int name_num,bool if_compile) {Judge::print_judge(name_num,if_compile);}
void print_judge_complete(int name_num,bool if_compile) {Judge::print_judge_complete(name_num,if_compile);}
#endif