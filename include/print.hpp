#ifndef PRINT
#define PRINT PRINT
#include"init.hpp"
#define No_such_file -1
#define Accepted 0
#define Wrong_Answer 1
#define Runtime_Error 2
#define Time_Limit_Error_Correct_Answer 3
#define Time_Limit_Error_Wrong_Answer 4
#define Time_Limit_Error_over 5
#define Compile_Error 6
#define Dangerous_syscalls 7
#define data_maker_Compile_Error 16
#define data_maker_Dangerous_syscalls 17
#define std_Compile_Error 26
#define std_Dangerous_syscalls 27
namespace Print
{
    void change_color(int intensity,int red,int green,int blue)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(8*intensity)|(4*red)|(2*green)|(blue));
    }
    void print_result(int result,int information)
    {
        if(result==No_such_file)
        {
            change_color(1,0,1,1);
            cout<<"\nNo such file\n\n";
            change_color(1,1,1,1);
        }
        if(result==Accepted)
        {
            change_color(1,0,1,0);
            cout<<"\nAccepted\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        else if(result==Wrong_Answer)
        {
            change_color(1,1,0,0);
            cout<<"\nWrong Answer\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        else if(result==Runtime_Error)
        {
            change_color(1,1,0,1);
            cout<<"\nRuntime Error\nexit with code "<<information<<"\n\n";
            change_color(1,1,1,1);
        }
        else if(result==Time_Limit_Error_Correct_Answer)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nCorrect Answer\n\n";
            change_color(1,1,1,1);
        }
        else if(result==Time_Limit_Error_Wrong_Answer)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nWrong Answer\n\n";
            change_color(1,1,1,1);
        }
        else if(result==Time_Limit_Error_over)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\nover %dms\n\n",information;
            change_color(1,1,1,1);
        }
        else if(result==Compile_Error)
        {
            change_color(1,1,1,0);
            cout<<"\nCompile Error\n\n";
            change_color(1,1,1,1);
        }
        else if(result==Dangerous_syscalls)
        {
            change_color(1,1,1,0);
            cout<<"\nDangerous syscalls\n\n";
            change_color(1,1,1,1);
        }
        else if(result==data_maker_Compile_Error)
        {
            change_color(1,1,1,0);
            cout<<"\ndata_maker Compile Error\n\n";
            change_color(1,1,1,1);
        }
        else if(result==data_maker_Dangerous_syscalls)
        {
            change_color(1,1,1,0);
            cout<<"\ndata_maker Dangerous syscallsn\n";
            change_color(1,1,1,1);
        }
        else if(result==std_Compile_Error)
        {
            change_color(1,1,1,0);
            cout<<"\nstd Compile Error\n\n";
            change_color(1,1,1,1);
        }
        else if(result==std_Dangerous_syscalls)
        {
            change_color(1,1,1,0);
            cout<<"\nstd Dangerous syscalls\n\n";
            change_color(1,1,1,1);
        }
    }
}
void change_color(int intensity,int red,int green,int blue) {Print::change_color(intensity,red,green,blue);}
void print_result(int result,int information) {Print::print_result(result,information);}
void print_result(int result) {Print::print_result(result,0);}
#endif