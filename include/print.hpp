#ifndef _FILE_PRINT
#define _FILE_PRINT _FILE_PRINT
#include"init.hpp"
#define _Success -1
#define _Fail -2
#define _AC 0
#define _WA 1
#define _RE 2
#define _TLE_CA 3
#define _TLE_WA 4
#define _TLE_O 5
#define _CE 6
#define _DS 7
#define _SR 8
#define _SA 9
#define _DA 10
#define _NF 50
#define _II 51
#define _color_white 255,255,255
#define _color_red 240,0,0
#define _color_orange 240,160,0
#define _color_yellow 240,240,0
#define _color_green 32,224,112
#define _color_blue 0,176,255
#define _color_purple 160,0,240
namespace Print
{
    void change_color(int red,int green,int blue)
    {
        cout<<"\e[38;2;"<<red<<";"<<green<<";"<<blue<<"m";
    }
    void print_result(int result,int information)
    {
        if(result<0)
        {
            if(result==_Success)
            {
                change_color(_color_green);
                cout<<"\nSuccess\n\n";
                change_color(_color_white);
            }
            if(result==_Fail)
            {
                change_color(_color_red);
                cout<<"\nFail\n\n";
                change_color(_color_white);
            }
            return;
        }
        if(result==_AC)
        {
            change_color(_color_green);
            cout<<"\nAccepted\n"<<information<<"ms\n\n";
            change_color(_color_white);
        }
        if(result==_WA)
        {
            change_color(_color_red);
            cout<<"\nWrong Answer\n"<<information<<"ms\n\n";
            change_color(_color_white);
        }
        if(result==_RE)
        {
            change_color(_color_purple);
            cout<<"\nRuntime Error\nexit with code "<<information<<"\n\n";
            change_color(_color_white);
        }
        if(result==_TLE_CA)
        {
            change_color(_color_blue);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nCorrect Answer\n\n";
            change_color(_color_white);
        }
        if(result==_TLE_WA)
        {
            change_color(_color_blue);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nWrong Answer\n\n";
            change_color(_color_white);
        }
        if(result==_TLE_O)
        {
            change_color(_color_blue);
            cout<<"\nTime Limit Error\nover "<<information<<"ms\n\n";
            change_color(_color_white);
        }
        if(result==_CE)
        {
            change_color(_color_yellow);
            cout<<"\nCompile Error\n\n";
            change_color(_color_white);
        }
        if(result==_DS)
        {
            change_color(_color_yellow);
            cout<<"\nDangerous syscalls\n\n";
            change_color(_color_white);
        }
        if(result==_SR)
        {
            change_color(_color_green);
            cout<<"\nSuccess run\n"<<information<<"ms\n\n";
            change_color(_color_white);
        }
        if(result==_SA)
        {
            change_color(_color_green);
            cout<<"\nSame Answer\n\n";
            change_color(_color_white);
        }
        if(result==_DA)
        {
            change_color(_color_red);
            cout<<"\nDifferent Answer\n\n";
            change_color(_color_white);
        }
        if(result==_NF)
        {
            change_color(_color_orange);
            cout<<"\nNo such file\n\n";
            change_color(_color_white);
        }
        if(result==_II)
        {
            change_color(_color_orange);
            cout<<"\nInvalid input\n\n";
            change_color(_color_white);
        }
    }
    void print_judge_result(int result,int time,int exit_code,int time_limit)
    {
        if(result==_RE) print_result(result,exit_code);
        else if(result==_TLE_O) print_result(result,time_limit*2);
        else print_result(result,time);
    }
    string get_short_result(int result)
    {
        if(result==_NF) return "NF";
        if(result==_AC) return "AC";
        if(result==_WA) return "WA";
        if(result==_RE) return "RE";
        if(result==_TLE_CA) return "TLE_CA";
        if(result==_TLE_WA) return "TLE_WA";
        if(result==_TLE_O) return "TLE_O";
        if(result==_CE) return "CE";
        if(result==_DS) return "DS";
        if(result==_SR) return "SR";
        if(result==_SA) return "SA";
        if(result==_DA) return "DA";
        return "";
    }
}
void change_color(int red,int green,int blue) {Print::change_color(red,green,blue);}
void print_result(int result,int information) {Print::print_result(result,information);}
void print_result(int result) {Print::print_result(result,0);}
void print_judge_result(int result,int time,int exit_code,int time_limit) {Print::print_judge_result(result,time,exit_code,time_limit);}
string get_short_result(int result) {return Print::get_short_result(result);}
#endif