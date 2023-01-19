#ifndef PARAMETER
#define PARAMETER PARAMETER
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
namespace Parameter
{
    const int N=1001;
    const char *parameter[N][N],*name_parameter[N];
    int tot,sum_parameter[N];
    void init_parameter(int argc,const char **argv)
    {
        for(int i=0;i<=1000;++i) sum_parameter[i]=-1;
        for(int i=1;i<=argc-1;++i)
        {
            if(argv[i][0]=='/')
            {
                sum_parameter[++tot]=0;
                name_parameter[tot]=argv[i]+1;
                int j=1;
                for(;i+j<=argc-1&&argv[i+j][0]!='/';++j)
                {
                    parameter[tot][j]=argv[i+j];
                    ++sum_parameter[tot];
                }
                i+=j-1;
            }
        }
    }
    const char *get_parameter(const char *name,int next_num)
    {
        int num=0;
        for(int i=1;i<=tot;++i)
        {
            if(strcmp(name,name_parameter[i])==0)
            {
                num=i;
                break;
            }
        }
        if(num==0||next_num>sum_parameter[num]) return NULL;
        return parameter[num][next_num];
    }
    int get_sum_parameter(const char *name)
    {
        int num=0;
        for(int i=1;i<=tot;++i)
        {
            if(strcmp(name,name_parameter[i])==0)
            {
                num=i;
                break;
            }
        }
        if(num==0) return -1;
        return sum_parameter[num];
    }
}
void init_parameter(int argc,const char **argv) {Parameter::init_parameter(argc,argv);}
const char *get_parameter(const char *name,int next_num) {return Parameter::get_parameter(name,next_num);}
int get_sum_parameter(const char *name) {return Parameter::get_sum_parameter(name);}
#endif