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
    string in_file,out_file,ans_file;
    void begin()
    {
        in_file=appdata_address+"\\Orita\\data\\data.in";
        out_file=appdata_address+"\\Orita\\data\\data.out";
        ans_file=appdata_address+"\\Orita\\data\\data.ans";
    }
    int compare(string file1,string file2)
    {
        ifstream infile1(file1),infile2(file2);
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
    int check_ans(string chk)
    {
        if(chk=="<1>") return compare(out_file,ans_file);
        else return system("\""+get_address(chk)+"\\"+get_namepre(chk)+".exe\" \""+in_file+"\" \""+ans_file+"\" \""+out_file+"\"");
    }
    int judge(string ans,string chk)
    {
        string run_inst="\""+get_address(ans)+"\\"+get_namepre(ans)+".exe\" < \""+in_file+"\" > \""+ans_file+"\"";
        begin_time=clock();
        if(exit_code=system(run_inst))
        {
            if_end=true;
            if(result!=-1) return result;
            return result=_RE;
        }
        if_end=true;
        if(result!=-1) return result;
        time=(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000;
        string check_inst;
        if(chk=="<0>") return result=_SR;
        if(check_ans(chk))
        {
            if(time>get_time_limit()) result=_TLE_WA;
            else result=_WA;
        }
        else
        {
            if(time>get_time_limit()) result=_TLE_CA;
            else result=_AC;
        }
        return result;
    }
    int judge_monitor(string ans,string chk)
    {
        if_end=false;
        result=-1;
        time_limit=get_time_limit();
        begin_time=-1;
        thread(judge,ans,chk).detach();
        while(begin_time==-1||(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000<time_limit*2)
        {
            Sleep(5);
            if(if_end)
            {
                while(result==-1) Sleep(5);
                return 0;
            }
        }
        result=_TLE_O;
        system("taskkill /f /pid "+get_namepre(ans)+".exe"+system_to_nul);
        while(if_end==false) Sleep(5);
        return 1;
    }
    void running(string ans,string parameter)
    {
        begin_time=clock();
        exit_code=system(get_address(ans)+"\\"+get_namepre(ans)+".exe "+parameter);
        if_end=true;
    }
    int run_monitor(string ans,string parameter)
    {
        if_end=false;
        time_limit=get_time_limit();
        begin_time=-1;
        thread(running,ans,parameter).detach();
        while(begin_time==-1||(double)(clock()-begin_time)/CLOCKS_PER_SEC*1000<time_limit*2)
        {
            if(if_end) return 0;
        }
        system("taskkill /f /pid "+get_namepre(ans)+".exe"+system_to_nul);
        return 1;
    }
}
int compare(string file1,string file2) {return Judge::compare(file1,file2);}
int check_ans(string chk) {return Judge::check_ans(chk);}
int judge(string ans,string chk) {return Judge::judge(ans,chk);}
int judge_monitor(string ans,string chk) {return Judge::judge_monitor(ans,chk);}
int run_monitor(string ans,string parameter) {return Judge::run_monitor(ans,parameter);}
void print_judge_result() {Print::print_judge_result(Judge::result,Judge::time,Judge::exit_code,Judge::time_limit);}
#endif