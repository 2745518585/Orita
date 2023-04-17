#ifndef _FILE_PRINT
#define _FILE_PRINT _FILE_PRINT
#include"init.hpp"
#define _Success -50
#define _AC 0
#define _WA 1
#define _RE 2
#define _TLE_CA 3
#define _TLE_WA 4
#define _TLE_O 5
#define _CE 6
#define _DS 7
#define _SA 9
#define _DA 10
#define _NF 50
#define _II 51
#define _Fail 52
namespace Print
{
    void change_color(int red,int green,int blue)
    {
        std::cout<<"\e[38;2;"<<red<<";"<<green<<";"<<blue<<"m";
    }
    void change_color(std::string color)
    {
        if((int)settings["colors"][color][0].type()==0||(int)settings["colors"][color][1].type()==0||(int)settings["colors"][color][2].type()==0) return;
        std::cout<<"\e[38;2;"<<settings["colors"][color][0]<<";"<<settings["colors"][color][1]<<";"<<settings["colors"][color][2]<<"m";
    }
    void print_result(int result,int information)
    {
        if(result==_Success)
        {
            change_color("green");
            std::cout<<"\nSuccess\n\n";
            change_color("white");
        }
        if(result==_Fail)
        {
            change_color("red");
            std::cout<<"\nFail\n\n";
            change_color("white");
        }
        if(result==_AC)
        {
            change_color("green");
            std::cout<<"\nAccepted\n"<<information<<"ms\n\n";
            change_color("white");
        }
        if(result==_WA)
        {
            change_color("red");
            std::cout<<"\nWrong Answer\n"<<information<<"ms\n\n";
            change_color("white");
        }
        if(result==_RE)
        {
            change_color("purple");
            std::cout<<"\nRuntime Error\nexit with code "<<information<<"\n\n";
            change_color("white");
        }
        if(result==_TLE_CA)
        {
            change_color("blue");
            std::cout<<"\nTime Limit Error\n"<<information<<"ms\n\nCorrect Answer\n\n";
            change_color("white");
        }
        if(result==_TLE_WA)
        {
            change_color("blue");
            std::cout<<"\nTime Limit Error\n"<<information<<"ms\n\nWrong Answer\n\n";
            change_color("white");
        }
        if(result==_TLE_O)
        {
            change_color("blue");
            std::cout<<"\nTime Limit Error\nover "<<information<<"ms\n\n";
            change_color("white");
        }
        if(result==_CE)
        {
            change_color("yellow");
            std::cout<<"\nCompile Error\n\n";
            change_color("white");
        }
        if(result==_DS)
        {
            change_color("yellow");
            std::cout<<"\nDangerous syscalls\n\n";
            change_color("white");
        }
        if(result==_SA)
        {
            change_color("green");
            std::cout<<"\nSame Answer\n\n";
            change_color("white");
        }
        if(result==_DA)
        {
            change_color("red");
            std::cout<<"\nDifferent Answer\n\n";
            change_color("white");
        }
        if(result==_NF)
        {
            change_color("orange");
            std::cout<<"\nNo such file\n\n";
            change_color("white");
        }
        if(result==_II)
        {
            change_color("orange");
            std::cout<<"\nInvalid input\n\n";
            change_color("white");
        }
    }
    void print_judge_result(int result,int time,int exit_code,int time_limit)
    {
        if(result==_RE) print_result(result,exit_code);
        else if(result==_TLE_O) print_result(result,time_limit*2);
        else print_result(result,time);
    }
    std::string get_short_result(int result)
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
        if(result==_SA) return "SA";
        if(result==_DA) return "DA";
        return "";
    }
}
void change_color(int red,int green,int blue) {Print::change_color(red,green,blue);}
void change_color(std::string color) {Print::change_color(color);}
void print_result(int result,int information) {Print::print_result(result,information);}
void print_result(int result) {Print::print_result(result,0);}
void print_judge_result(int result,int time,int exit_code,int time_limit) {Print::print_judge_result(result,time,exit_code,time_limit);}
std::string get_short_result(int result) {return Print::get_short_result(result);}
#endif