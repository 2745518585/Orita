#ifndef _FILE_PRINT
#define _FILE_PRINT _FILE_PRINT
#include"init.hpp"
#define __PRINT__Success -1
#define __PRINT__AC 0
#define __PRINT__WA 1
#define __PRINT__RE 2
#define __PRINT__TLE_CA 3
#define __PRINT__TLE_WA 4
#define __PRINT__TLE_O 5
#define __PRINT__CE 6
#define __PRINT__DS 7
#define __PRINT__NF 50
#define __PRINT__IN 100
#define __PRINT__OUT 200
#define __PRINT__ANS 300
#define __PRINT__CHK 400
namespace Print
{
    void change_color(int intensity,int red,int green,int blue)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(8*intensity)|(4*red)|(2*green)|(blue));
    }
    void print_result(int result,int information)
    {
        if(result<0)
        {
            if(result%100==__PRINT__Success)
            {
                change_color(1,0,1,0);
                cout<<"\nSuccess\n\n";
                change_color(1,1,1,1);
            }
            return;
        }
        if(result/100*100==__PRINT__IN) cout<<"\ndata_maker:";
        else if(result/100*100==__PRINT__OUT) cout<<"\nstd:";
        else if(result/100*100==__PRINT__ANS) cout<<"\nans:";
        else if(result/100*100==__PRINT__CHK) cout<<"\nchecker:";
        if(result%100==__PRINT__NF)
        {
            change_color(1,0,1,1);
            cout<<"\nNo such file\n\n";
            change_color(1,1,1,1);
        }
        else if(result%100==__PRINT__AC)
        {
            change_color(1,0,1,0);
            cout<<"\nAccepted\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        else if(result%100==__PRINT__WA)
        {
            change_color(1,1,0,0);
            cout<<"\nWrong Answer\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        else if(result%100==__PRINT__RE)
        {
            change_color(1,1,0,1);
            cout<<"\nRuntime Error\nexit with code "<<information<<"\n\n";
            change_color(1,1,1,1);
        }
        else if(result%100==__PRINT__TLE_CA)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nCorrect Answer\n\n";
            change_color(1,1,1,1);
        }
        else if(result%100==__PRINT__TLE_WA)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nWrong Answer\n\n";
            change_color(1,1,1,1);
        }
        else if(result%100==__PRINT__TLE_O)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\nover "<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        else if(result%100==__PRINT__CE)
        {
            change_color(1,1,1,0);
            cout<<"\nCompile Error\n\n";
            change_color(1,1,1,1);
        }
        else if(result%100==__PRINT__DS)
        {
            change_color(1,1,1,0);
            cout<<"\nDangerous syscalls\n\n";
            change_color(1,1,1,1);
        }
    }
}
void change_color(int intensity,int red,int green,int blue) {Print::change_color(intensity,red,green,blue);}
void print_result(int result,int information) {Print::print_result(result,information);}
void print_result(int result) {Print::print_result(result,0);}
#endif