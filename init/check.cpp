#include<bits/stdc++.h>
#include<windows.h>
#include "..\copy.h"
#include "..\name.h"
#include "..\parameter.h"
using namespace std;
const int N=1001;
char instruct[N];
int main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(num_parameter['n']==0)
    {
        printf("\nERROR: Invalid syntax. No /n specified.\n\n");
        return 0;
    }
    system("del /Q %appdata%\\run\\source\\* > %appdata%\\run\\rubbish\\rubbish.txt");
    if(copy_source(input_name(11,parameter['f'][1])))
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        printf("\nNo such file\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        return 0;
    }
    if(copy_source(input_name(12,parameter['f'][2])))
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        printf("\nNo such file\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        return 0;
    }
    if(copy_source(input_name(13,parameter['f'][3])))
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        printf("\nNo such file\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        return 0;
    }
    sprintf(instruct,"start /b /d E:\\1.C++\\code\\run /wait E:\\1.C++\\code\\run\\check.exe ");
    for(int i=1;i<=argc-1;++i)
    {
        sprintf(instruct,"%s %s",instruct,argv[i]);
    }
    system(instruct);
    return 0;
}