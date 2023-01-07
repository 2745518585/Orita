#include<bits/stdc++.h>
#include<windows.h>
#include "..\run.h"
using namespace std;
const int N=1001;
char instruct[N];
int main(int argc,char **argv)
{
    system("del /Q %appdata%\\run\\source\\* > %appdata%\\run\\rubbish\\rubbish.txt");
    init_parameter(argc,argv);
    if(num_parameter['n']<=0)
    {
        printf("\nERROR: Invalid syntax. No /n specified.\n\n");
        return 0;
    }
    if(num_parameter['f']>=3)
    {
        add_name(check_data_maker,parameter['f'][1],".cpp");
        add_name(check_std,parameter['f'][2],".cpp");
        add_name(check_run,parameter['f'][3],".cpp");
    }
    if(copy_source(get_name(check_data_maker)))
    {
        print_result(No_such_file);
        return 0;
    }
    if(copy_source(get_name(check_std)))
    {
        print_result(No_such_file);
        return 0;
    }
    if(copy_source(get_name(check_run)))
    {
        print_result(No_such_file);
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