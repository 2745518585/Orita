#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int chdata(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("f")>=2)
    {
        add_file(_data_in,get_parameter("f",1));
        add_file(_data_out,get_parameter("f",2));
        if(find_file(_data_in)||find_file(_data_out))
        {
            print_result(_NF);
            return 0;
        }
        copy_source(get_address(_data_in),get_name(_data_in),"data","data.in");
        copy_source(get_address(_data_out),get_name(_data_out),"data","data.out");
    }
    else if(get_sum_parameter("s")!=-1)
    {
        char str;
        FILE *file=fopen(UTF8toGB(appdata_address+"\\Orita\\data\\data.in").c_str(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
        file=fopen(UTF8toGB(appdata_address+"\\Orita\\data\\data.out").c_str(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
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
    int exit_code=chdata(argc,argv);
    End();
    return exit_code;
}