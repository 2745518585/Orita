#ifndef _FILE_PRINT
#define _FILE_PRINT _FILE_PRINT
#include"init.hpp"
#define __PRINT__No_such_file -1
#define __PRINT__Accepted 0
#define __PRINT__Wrong_Answer 1
#define __PRINT__Runtime_Error 2
#define __PRINT__Time_Limit_Error_Correct_Answer 3
#define __PRINT__Time_Limit_Error_Wrong_Answer 4
#define __PRINT__Time_Limit_Error_over 5
#define __PRINT__Compile_Error 6
#define __PRINT__Dangerous_syscalls 7
#define __PRINT__data_maker_Compile_Error 16
#define __PRINT__data_maker_Dangerous_syscalls 17
#define __PRINT__std_Compile_Error 26
#define __PRINT__std_Dangerous_syscalls 27
#define __PRINT__Success 50
namespace Print
{
    void change_color(int intensity,int red,int green,int blue)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(8*intensity)|(4*red)|(2*green)|(blue));
    }
    void print_result(int result,int information)
    {
        if(result==__PRINT__No_such_file)
        {
            change_color(1,0,1,1);
            cout<<"\nNo such file\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__Accepted)
        {
            change_color(1,0,1,0);
            cout<<"\nAccepted\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__Wrong_Answer)
        {
            change_color(1,1,0,0);
            cout<<"\nWrong Answer\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__Runtime_Error)
        {
            change_color(1,1,0,1);
            cout<<"\nRuntime Error\nexit with code "<<information<<"\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__Time_Limit_Error_Correct_Answer)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nCorrect Answer\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__Time_Limit_Error_Wrong_Answer)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nWrong Answer\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__Time_Limit_Error_over)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\nover "<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__Compile_Error)
        {
            change_color(1,1,1,0);
            cout<<"\nCompile Error\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__Dangerous_syscalls)
        {
            change_color(1,1,1,0);
            cout<<"\nDangerous syscalls\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__data_maker_Compile_Error)
        {
            change_color(1,1,1,0);
            cout<<"\ndata_maker Compile Error\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__data_maker_Dangerous_syscalls)
        {
            change_color(1,1,1,0);
            cout<<"\ndata_maker Dangerous syscalls\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__std_Compile_Error)
        {
            change_color(1,1,1,0);
            cout<<"\nstd Compile Error\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__std_Dangerous_syscalls)
        {
            change_color(1,1,1,0);
            cout<<"\nstd Dangerous syscalls\n\n";
            change_color(1,1,1,1);
        }
        else if(result==__PRINT__Success)
        {
            change_color(1,0,1,0);
            cout<<"\nSuccess\n\n";
            change_color(1,1,1,1);
        }
    }
}
void change_color(int intensity,int red,int green,int blue) {Print::change_color(intensity,red,green,blue);}
void print_result(int result,int information) {Print::print_result(result,information);}
void print_result(int result) {Print::print_result(result,0);}
#endif