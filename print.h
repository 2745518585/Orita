#ifndef PRINT
#define PRINT PRINT
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#define No_such_file -1
#define Accepted 0
#define Wrong_Answer 1
#define Runtime_Error 2
#define Time_Limit_Error_Correct_Answer 3
#define Time_Limit_Error_Wrong_Answer 4
#define Time_Limit_Error_over 5
#define Compile_Error 6
#define data_maker_Compile_Error 15
#define std_Compile_Error 25
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
            printf("\nNo such file\n\n");
            change_color(1,1,1,1);
        }
        if(result==Accepted)
        {
            change_color(1,0,1,0);
            printf("\nAccepted\n%dms\n\n",information);
            change_color(1,1,1,1);
        }
        else if(result==Wrong_Answer)
        {
            change_color(1,1,0,0);
            printf("\nWrong Answer\n%dms\n\n",information);
            change_color(1,1,1,1);
        }
        else if(result==Runtime_Error)
        {
            change_color(1,1,0,1);
            printf("\nRuntime Error\nexit with code %d\n\n",information);
            change_color(1,1,1,1);
        }
        else if(result==Time_Limit_Error_Correct_Answer)
        {
            change_color(1,0,0,1);
            printf("\nTime Limit Error\n%dms\n\nCorrect Answer\n\n",information);
            change_color(1,1,1,1);
        }
        else if(result==Time_Limit_Error_Wrong_Answer)
        {
            change_color(1,0,0,1);
            printf("\nTime Limit Error\n%dms\n\nWrong Answer\n\n",information);
            change_color(1,1,1,1);
        }
        else if(result==Time_Limit_Error_over)
        {
            change_color(1,0,0,1);
            printf("\nTime Limit Error\nover %dms\n\n",information);
            change_color(1,1,1,1);
        }
        else if(result==Compile_Error)
        {
            change_color(1,1,1,0);
            printf("\nCompile Error\n\n");
            change_color(1,1,1,1);
        }
        else if(result==data_maker_Compile_Error)
        {
            change_color(1,1,1,0);
            printf("\ndata_maker Compile Error\n\n");
            change_color(1,1,1,1);
        }
        else if(result==std_Compile_Error)
        {
            change_color(1,1,1,0);
            printf("\nstd Compile Error\n\n");
            change_color(1,1,1,1);
        }
    }
}
void change_color(int intensity,int red,int green,int blue) {Print::change_color(intensity,red,green,blue);}
void print_result(int result,int information) {Print::print_result(result,information);}
void print_result(int result) {Print::print_result(result,0);}
#endif