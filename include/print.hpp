#ifndef _FILE_PRINT
#define _FILE_PRINT _FILE_PRINT
#include"init.hpp"
#define __PRINT__Success -1
#define __PRINT__Fail -2
#define __PRINT__AC 0
#define __PRINT__WA 1
#define __PRINT__RE 2
#define __PRINT__TLE_CA 3
#define __PRINT__TLE_WA 4
#define __PRINT__TLE_O 5
#define __PRINT__CE 6
#define __PRINT__DS 7
#define __PRINT__SR 8
#define __PRINT__SA 9
#define __PRINT__DA 10
#define __PRINT__NF 50
#define __PRINT__II 51
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
            if(result==__PRINT__Success)
            {
                change_color(1,0,1,0);
                cout<<"\nSuccess\n\n";
                change_color(1,1,1,1);
            }
            if(result==__PRINT__Fail)
            {
                change_color(1,1,0,0);
                cout<<"\nFail\n\n";
                change_color(1,1,1,1);
            }
            return;
        }
        if(result==__PRINT__AC)
        {
            change_color(1,0,1,0);
            cout<<"\nAccepted\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__WA)
        {
            change_color(1,1,0,0);
            cout<<"\nWrong Answer\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__RE)
        {
            change_color(1,1,0,1);
            cout<<"\nRuntime Error\nexit with code "<<information<<"\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__TLE_CA)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nCorrect Answer\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__TLE_WA)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nWrong Answer\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__TLE_O)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\nover "<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__CE)
        {
            change_color(1,1,1,0);
            cout<<"\nCompile Error\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__DS)
        {
            change_color(1,1,1,0);
            cout<<"\nDangerous syscalls\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__SR)
        {
            change_color(1,0,1,0);
            cout<<"\nSuccess run\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__SA)
        {
            change_color(1,0,1,0);
            cout<<"\nSame Answer\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__DA)
        {
            change_color(1,1,0,0);
            cout<<"\nDifferent Answer\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__NF)
        {
            change_color(1,0,1,1);
            cout<<"\nNo such file\n\n";
            change_color(1,1,1,1);
        }
        if(result==__PRINT__II)
        {
            change_color(1,0,1,1);
            cout<<"\nInvalid input\n\n";
            change_color(1,1,1,1);
        }
    }
    string get_short_result(int result)
    {
        if(result==__PRINT__NF) return "NF";
        if(result==__PRINT__AC) return "AC";
        if(result==__PRINT__WA) return "WA";
        if(result==__PRINT__RE) return "RE";
        if(result==__PRINT__TLE_CA) return "TLE_CA";
        if(result==__PRINT__TLE_WA) return "TLE_WA";
        if(result==__PRINT__TLE_O) return "TLE_O";
        if(result==__PRINT__CE) return "CE";
        if(result==__PRINT__DS) return "DS";
        if(result==__PRINT__SR) return "SR";
        if(result==__PRINT__SA) return "SA";
        if(result==__PRINT__DA) return "DA";
        return "";
    }
}
void change_color(int intensity,int red,int green,int blue) {Print::change_color(intensity,red,green,blue);}
void print_result(int result,int information) {Print::print_result(result,information);}
void print_result(int result) {Print::print_result(result,0);}
string get_short_result(int result) {return Print::get_short_result(result);}
#endif