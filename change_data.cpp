#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int change_data(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("f")>=2)
    {
        if(copy_source(".\\",get_parameter("f",1),"data","data.in"))
        {
            print_result(No_such_file);
            return 0;
        }
        if(copy_source(".\\",get_parameter("f",1),"data","data.in"))
        {
            print_result(No_such_file);
            return 0;
        }
    }
    else if(get_sum_parameter("s")!=-1)
    {
        char x;
        FILE *file=fopen((string(getenv("appdata"))+"\\Orita\\data\\data.in").c_str(),"w");
        x=getchar();
        while(x!=EOF) fputc(x,file),x=getchar();
        file=fopen((string(getenv("appdata"))+"\\Orita\\data\\data.out").c_str(),"w");
        x=getchar();
        while(x!=EOF) fputc(x,file),x=getchar();
    }
    if(get_sum_parameter("t")>=1)
    {
        change_time_limit(stoi(get_parameter("t",1)));
    }
    change_color(1,0,1,0);
    cout<<"\nSuccess\n\n";
    change_color(1,1,1,1);
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=change_data(argc,argv);
    End();
    return exit_code;
}