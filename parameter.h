#ifndef PARAMETER
#define PARAMETER PARAMETER
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
char *parameter[1001][101];
int num_parameter[1001];
namespace Parameter
{
    void init_parameter(int argc,char **argv)
    {
        for(int i=1;i<=argc-1;++i)
        {
            if(argv[i][0]=='/')
            {
                int j=1;
                for(;i+j<=argc-1&&argv[i+j][0]!='/';++j)
                {
                    parameter[argv[i][1]][j]=argv[i+j];
                    ++num_parameter[argv[i][1]];
                }
                i+=j-1;
            }
        }
    }
}
void init_parameter(int argc,char **argv) {Parameter::init_parameter(argc,argv);}
#endif