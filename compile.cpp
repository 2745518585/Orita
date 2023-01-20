#include<bits/stdc++.h>
#include<windows.h>
#include "run.hpp"
using namespace std;
string compile_parameter="-std=c++14 -O2 -Wl,--stack=2147483647";
int main(int argc,char **argv)
{
    system((string("taskkill /f /pid ")+argv[1]+".exe 2>&1").c_str());
    string instruct=string("g++ ")+argv[1]+".cpp -o "+argv[1]+".exe "+compile_parameter;
    if(!system("dir include > \"%appdata%\\Orita\\rubbish\\rubbish.txt\" 2>&1")) instruct+=" -I include";
    if(system(instruct.c_str())==0)
    {
        change_color(1,0,1,0);
        cout<<"\nSuccess\n\n";
        change_color(1,1,1,1);
    }
    else print_result(Compile_Error);
    return 0;
}