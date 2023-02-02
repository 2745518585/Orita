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
        string run_instruct=get_address(ans_num)+"\\"+get_name_pre(ans_num)+".exe < %appdata%\\Orita\\data\\data.in > %appdata%\\Orita\\data\\data.ans";
        begin_time=clock();
        if(exit_code=system(run_instruct)) return if_end=true,result=__PRINT__RE;
        if_end=true;
        time=(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000;
        string check_instruct;
        if(chk_num!=0) check_instruct=get_address(chk_num)+"\\"+get_name_pre(chk_num)+".exe %appdata%\\Orita\\data\\data.in %appdata%\\Orita\\data\\data.ans %appdata%\\Orita\\data\\data.out";
        else check_instruct="fc %appdata%\\Orita\\data\\data.out %appdata%\\Orita\\data\\data.ans"+system_to_nul;
        if(system(check_instruct))
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
    void print_judge_complete(int ans_num,int chk_num)
    {
        if_end=false;
        result=-1;
        time_limit=get_time_limit();
        begin_time=-1;
        thread(judge,ans_num,chk_num).detach();
        while(begin_time==-1||(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000<time_limit*2)
        {
            if(if_end)
            {
                while(result==-1) Sleep(5);
                if(result==__PRINT__RE) print_result(result,exit_code);
                else print_result(result,time);
                return;
            }
        }
        system(("taskkill /f /pid "+get_name_pre(ans_num)+".exe"+system_to_nul).c_str());
        result=__PRINT__TLE_O;
        print_result(result,time_limit*2);
    }
}
int judge(int name_num,int chk_num) {return Judge::judge(name_num,chk_num);}
void print_judge_complete(int name_num,int chk_num) {Judge::print_judge_complete(name_num,chk_num);}
#endif