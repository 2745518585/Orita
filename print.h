#ifndef PRINT
#define PRINT PRINT
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
namespace Print
{
    void change_color(int intensity,int red,int green,int blue)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(8*intensity)|(4*red)|(2*green)|(blue));
    }
    void print_result(int result,int time)
    {
        if(result==0)
        {
            change_color(1,0,1,0);
            printf("\nAccepted\n%dms\n\n",time);
            change_color(1,1,1,1);
        }
        else if(result==1)
        {
            change_color(1,1,0,0);
            printf("\nWrong Answer\n%dms\n\n",time);
            change_color(1,1,1,1);
        }
        else if(result==2)
        {
            change_color(1,1,0,1);
            printf("\nRuntime Error\n\n");
            change_color(1,1,1,1);
        }
        else if(result==3)
        {
            change_color(1,0,0,1);
            printf("\nTime Limit Error\n%dms\n\nCorrect Answer\n\n",time);
            change_color(1,1,1,1);
        }
        else if(result==4)
        {
            change_color(1,0,0,1);
            printf("\nTime Limit Error\n%dms\n\nWrong Answer\n\n",time);
            change_color(1,1,1,1);
        }
        else if(result==5)
        {
            change_color(1,1,1,0);
            printf("\nCompile Error\n\n");
            change_color(1,1,1,1);
        }
        else if(result==15)
        {
            change_color(1,1,1,0);
            printf("\ndata_maker Compile Error\n\n");
            change_color(1,1,1,1);
        }
        else if(result==25)
        {
            change_color(1,1,1,0);
            printf("\nstd Compile Error\n\n");
            change_color(1,1,1,1);
        }
    }
}
void change_color(int intensity,int red,int green,int blue) {Print::change_color(intensity,red,green,blue);}
void print_result(int result,int time) {Print::print_result(result,time);}
#endif