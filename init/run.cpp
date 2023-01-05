#include<bits/stdc++.h>
#include<windows.h>
#include "..\run.h"
using namespace std;
const int N=1001;
char instruct[N];
int main(int argc,char **argv)
{
    system("del /Q %appdata%\\run\\source\\");
    init_parameter(argc,argv);
    input_name(run_run,parameter['f'][1],".cpp");
    if(copy_source(get_name(run_run)))
    {
        print_result(No_such_file);
        return 0;
    }
    sprintf(instruct,"start /b /d E:\\1.C++\\code\\run /wait E:\\1.C++\\code\\run\\run.exe ");
    for(int i=1;i<=argc-1;++i)
    {
        sprintf(instruct,"%s %s",instruct,argv[i]);
    }
    system(instruct);
    return 0;
}