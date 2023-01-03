#ifndef COMPILE
#define COMPILE COMPILE
#include<bits/stdc++.h>
#include<windows.h>
#include "name.h"
#include "task.h"
using namespace std;
namespace Compile
{
    const int N=1001;
    char instruct[N],*name,parameter[N]="-std=c++14 -O2 -Wl,--stack=2147483647";
    FILE *file=NULL;
    int compile(int name_num)
    {
        name=get_name(name_num);
        if(find_task(name_num))
        {
            sprintf(instruct,"taskkill /f /pid %s.exe > %%appdata%%\\run\\rubbish\\rubbish.txt",name);
            system(instruct);
        }
        sprintf(instruct,"g++ %%appdata%%\\run\\source\\%s.cpp -o %%appdata%%\\run\\source\\%s.exe %s",name,name,parameter);
        return system(instruct)!=0;
    }
}
int compile(int name_num) {return Compile::compile(name_num);}
#endif