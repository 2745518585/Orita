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
    int compare()
    {
        ifstream infile1(UTF8toGB(get_complete_address(__NAME__judge_out))),infile2(UTF8toGB(get_complete_address(__NAME__judge_ans)));
        string str1,str2;
        bool empty1=0,empty2=0;
        while(true)
        {
            bool end1=bool(!getline(infile1,str1)),end2=bool(!getline(infile2,str2));
            if(end1&&end2) break;
            while(str1[str1.size()-1]==' ') str1=str1.substr(0,str1.size()-1);
            while(str2[str2.size()-1]==' ') str2=str2.substr(0,str2.size()-1);
            if(end1||str1.size()==0) empty1=true;
            else empty1=false;
            if(end2||str2.size()==0) empty2=true;
            else empty2=false;
            if(empty1^empty2) return 1;
            if(strcmp(str1.c_str(),str2.c_str())!=0) return 1;
        }
        return 0;
    }
    int judge(int ans_num,int chk_num)
    {
        string run_inst="\""+get_address(ans_num)+"\\"+get_name_pre(ans_num)+".exe\" < \""+get_complete_address(__NAME__judge_in)+"\" > \""+get_complete_address(__NAME__judge_ans)+"\"";
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
        if(chk_num!=0) check_inst="\""+get_address(chk_num)+"\\"+get_name_pre(chk_num)+".exe\" \""+get_complete_address(__NAME__judge_in)+"\" \""+get_complete_address(__NAME__judge_ans)+"\" \""+get_complete_address(__NAME__judge_out)+"\"";
        if(chk_num!=0?system(check_inst):compare())
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
int compare() {return Judge::compare();}
int judge(int name_num,int chk_num) {return Judge::judge(name_num,chk_num);}
int print_judge_monitor(int name_num,int chk_num) {return Judge::print_judge_monitor(name_num,chk_num);}
int run_monitor(int run_num,string parameter) {return Judge::run_monitor(run_num,parameter);}
#endif