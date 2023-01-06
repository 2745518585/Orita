#ifndef COMPILE
#define COMPILE COMPILE
#include<bits/stdc++.h>
#include<windows.h>
#include "name.h"
#include "task.h"
#include "print.h"
using namespace std;
namespace Compile
{
    const int N=1001;
    char instruct[N],*name,compile_parameter[N]="-std=c++14 -O2 -Wl,--stack=2147483647";
    FILE *file=NULL;
    int compile(int name_num)
    {
        name=get_name_suf(name_num);
        if(!(name[0]=='.'&&name[1]=='c'&&name[2]=='p'&&name[3]=='p'&&name[4]=='\0'))
        {
            change_color(1,0,1,1);
            printf("\nFile format not recognized\n\n");
            change_color(1,1,1,1);
            return 1;
        }
        name=get_name_pre(name_num);
        if(find_task(name_num))
        {
            sprintf(instruct,"taskkill /f /pid %s.exe > %%appdata%%\\run\\rubbish\\rubbish.txt",name);
            system(instruct);
        }
        sprintf(instruct,"g++ %%appdata%%\\run\\source\\%s.cpp -o %%appdata%%\\run\\source\\%s.exe %s",name,name,compile_parameter);
        return system(instruct)!=0;
    }
}
int compile(int name_num) {return Compile::compile(name_num);}
#endif