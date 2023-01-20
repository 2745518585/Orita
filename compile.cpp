#include<bits/stdc++.h>
#include<windows.h>
#include "run.hpp"
using namespace std;
const int N=1001;
char instruct[N],compile_parameter[N]="-std=c++14 -O2 -Wl,--stack=2147483647";
int main(int argc,const char **argv)
{
    sprintf(instruct,"taskkill /f /pid %s.exe",argv[1]);
    system(instruct);
    if(system("dir include > \"%appdata%\\Orita\\rubbish\\rubbish.txt\""))
    {
        sprintf(instruct,"g++ %s.cpp -o %s.exe %s",argv[1],argv[1],compile_parameter);
    }
    else
    {
        sprintf(instruct,"g++ %s.cpp -o %s.exe %s -I include",argv[1],argv[1],compile_parameter);
    }
    if(system(instruct)==0)
    {
        change_color(1,0,1,0);
        printf("\nSuccess\n\n");
        change_color(1,1,1,1);
    }
    else print_result(Compile_Error);
    return 0;
}