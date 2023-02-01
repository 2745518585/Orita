#ifndef _FILE_PARAMETER
#define _FILE_PARAMETER _FILE_PARAMETER
#include"init.hpp"
namespace Parameter
{
    const int N=1001;
    string parameter[N][N],name_parameter[N];
    int tot,sum_parameter[N];
    void init_parameter(int argc,char **argv)
    {
        for(int i=0;i<=N-1;++i) sum_parameter[i]=-1;
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
    string get_parameter(string name,int num2)
    {
        int num=0;
        for(int i=1;i<=tot;++i)
        {
            if(name==name_parameter[i])
            {
                num=i;
                break;
            }
        }
        if(num==0||num2>sum_parameter[num]) return NULL;
        return parameter[num][num2];
    }
    int get_sum_parameter(string name)
    {
        int num=0;
        for(int i=1;i<=tot;++i)
        {
            if(name==name_parameter[i])
            {
                num=i;
                break;
            }
        }
        if(num==0) return -1;
        return sum_parameter[num];
    }
}
void init_parameter(int argc,char **argv) {Parameter::init_parameter(argc,argv);}
string get_parameter(string name,int num2) {return Parameter::get_parameter(name,num2);}
int get_sum_parameter(string name) {return Parameter::get_sum_parameter(name);}
#endif