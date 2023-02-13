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
            if(result==_Success)
            {
                change_color(1,0,1,0);
                cout<<"\nSuccess\n\n";
                change_color(1,1,1,1);
            }
            if(result==_Fail)
            {
                change_color(1,1,0,0);
                cout<<"\nFail\n\n";
                change_color(1,1,1,1);
            }
            return;
        }
        if(result==_AC)
        {
            change_color(1,0,1,0);
            cout<<"\nAccepted\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        if(result==_WA)
        {
            change_color(1,1,0,0);
            cout<<"\nWrong Answer\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        if(result==_RE)
        {
            change_color(1,1,0,1);
            cout<<"\nRuntime Error\nexit with code "<<information<<"\n\n";
            change_color(1,1,1,1);
        }
        if(result==_TLE_CA)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nCorrect Answer\n\n";
            change_color(1,1,1,1);
        }
        if(result==_TLE_WA)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\n"<<information<<"ms\n\nWrong Answer\n\n";
            change_color(1,1,1,1);
        }
        if(result==_TLE_O)
        {
            change_color(1,0,0,1);
            cout<<"\nTime Limit Error\nover "<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        if(result==_CE)
        {
            change_color(1,1,1,0);
            cout<<"\nCompile Error\n\n";
            change_color(1,1,1,1);
        }
        if(result==_DS)
        {
            change_color(1,1,1,0);
            cout<<"\nDangerous syscalls\n\n";
            change_color(1,1,1,1);
        }
        if(result==_SR)
        {
            change_color(1,0,1,0);
            cout<<"\nSuccess run\n"<<information<<"ms\n\n";
            change_color(1,1,1,1);
        }
        if(result==_SA)
        {
            change_color(1,0,1,0);
            cout<<"\nSame Answer\n\n";
            change_color(1,1,1,1);
        }
        if(result==_DA)
        {
            change_color(1,1,0,0);
            cout<<"\nDifferent Answer\n\n";
            change_color(1,1,1,1);
        }
        if(result==_NF)
        {
            change_color(1,0,1,1);
            cout<<"\nNo such file\n\n";
            change_color(1,1,1,1);
        }
        if(result==_II)
        {
            change_color(1,0,1,1);
            cout<<"\nInvalid input\n\n";
            change_color(1,1,1,1);
        }
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
void change_color(int intensity,int red,int green,int blue) {Print::change_color(intensity,red,green,blue);}
void print_result(int result,int information) {Print::print_result(result,information);}
void print_result(int result) {Print::print_result(result,0);}
string get_short_result(int result) {return Print::get_short_result(result);}
#endif