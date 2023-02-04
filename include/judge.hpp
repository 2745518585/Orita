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
    int judge(int ans_num,int chk_num)
    {
        string run_inst=get_address(ans_num)+"\\"+get_name_pre(ans_num)+".exe < "+get_complete_address(__NAME__judge_in)+" > "+get_complete_address(__NAME__judge_ans);
        begin_time=clock();
        if(exit_code=system(run_inst))
        {
            if_end=true;
            if(result!=-1) return result;
            return result=__PRINT__RE;
        }
        if_end=true;
        if(result!=-1) return result;
        time=(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000;
        string check_inst;
        if(chk_num==-1) return result=__PRINT__SR;
        if(chk_num!=0) check_inst=get_address(chk_num)+"\\"+get_name_pre(chk_num)+".exe "+get_complete_address(__NAME__judge_in)+" "+get_complete_address(__NAME__judge_ans)+" "+get_complete_address(__NAME__judge_out);
        else check_inst="fc "+get_complete_address(__NAME__judge_out)+" "+get_complete_address(__NAME__judge_ans)+system_to_nul;
        if(system(check_inst))
        {
            if(time>get_time_limit()) result=__PRINT__TLE_WA;
            else result=__PRINT__WA;
        }
        else
        {
            if(time>get_time_limit()) result=__PRINT__TLE_CA;
            else result=__PRINT__AC;
        }
        return result;
    }
    int print_judge_monitor(int ans_num,int chk_num)
    {
        if_end=false;
        result=-1;
        time_limit=get_time_limit();
        begin_time=-1;
        thread(judge,ans_num,chk_num).detach();
        while(begin_time==-1||(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000<time_limit*2)
        {
            Sleep(5);
            if(if_end)
            {
                while(result==-1) Sleep(5);
                if(result==__PRINT__RE) print_result(result,exit_code);
                else print_result(result,time);
                return 0;
            }
        }
        result=__PRINT__TLE_O;
        system("taskkill /f /pid "+get_name_pre(ans_num)+".exe"+system_to_nul);
        print_result(result,time_limit*2);
        while(if_end==false) Sleep(5);
        return 1;
    }
    void running(int run_num,string parameter)
    {
        begin_time=clock();
        exit_code=system(get_address(run_num)+"\\"+get_name_pre(run_num)+".exe "+parameter);
        if_end=true;
    }
    int run_monitor(int run_num,string parameter)
    {
        if_end=false;
        time_limit=get_time_limit();
        begin_time=-1;
        thread(running,run_num,parameter).detach();
        while(begin_time==-1||(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000<time_limit*2)
        {
            if(if_end) return 0;
        }
        system("taskkill /f /pid "+get_name_pre(run_num)+".exe"+system_to_nul);
        return 1;
    }
}
int judge(int name_num,int chk_num) {return Judge::judge(name_num,chk_num);}
int print_judge_monitor(int name_num,int chk_num) {return Judge::print_judge_monitor(name_num,chk_num);}
int run_monitor(int run_num,string parameter) {return Judge::run_monitor(run_num,parameter);}
#endif