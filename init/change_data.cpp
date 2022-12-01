#include<bits/stdc++.h>
#include<windows.h>
#include "..\copy.h"
#include "..\parameter.h"
using namespace std;
int main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(num_parameter['f']>=2)
    {
        if(copy_data_in(parameter['f'][1]))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
            printf("\nNo such file\n\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            return 0;
        }
        if(copy_data_out(parameter['f'][2]))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
            printf("\nNo such file\n\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            return 0;
        }
        return 0;
    }
    system("start /b /d E:\\1.C++\\code\\run /wait E:\\1.C++\\code\\run\\change_data.exe");
    return 0;
}