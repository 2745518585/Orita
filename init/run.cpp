#include<bits/stdc++.h>
#include<windows.h>
#include "..\run.h"
using namespace std;
const int N=1001;
char instruct[N];
int main(int argc,char **argv)
{
    system("del /Q %appdata%\\Orita\\source\\");
    init_parameter(argc,argv);
    if(num_parameter['f']>=1)
    {
        add_name(run_run,parameter['f'][1],".cpp");
        add_running_address(run_run);
    }
    if(copy_source(get_name(run_run)))
    {
        print_result(No_such_file);
        return 0;
    }
    sprintf(instruct,"start /b /d E:\\1.C++\\code\\Orita /wait E:\\1.C++\\code\\Orita\\run.exe ");
    for(int i=1;i<=argc-1;++i)
    {
        sprintf(instruct,"%s %s",instruct,argv[i]);
    }
    system(instruct);
    return 0;
}