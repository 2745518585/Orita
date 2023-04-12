#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
json make_cor_parameter()
{
    json cor_parameter={
        {"f",{_not_define,2}},
        {"if",{_not_define,1}},
        {"of",{_not_define,1}},
        {"s",{_not_define,0,1}},
        {"t",{_not_define,1}}
    };
    return cor_parameter;
}
json cor_parameter=make_cor_parameter();
int chdata_main()
{
    if(get_sum_parameter("f")>=2)
    {
        string in_file=get_file(get_parameter("f",1)),out_file=get_file(get_parameter("f",2));
        if(find_file(in_file)||find_file(out_file))
        {
            print_result(_NF);
            return 0;
        }
        copy_source(in_file,"data\\data.in");
        copy_source(out_file,"data\\data.out");
    }
    else if(get_sum_parameter("if")>=1||get_sum_parameter("of")>=1)
    {
        string in_file,out_file;
        if(get_sum_parameter("if")>=1)
        {
            in_file=get_file(get_parameter("if",1));
            if(find_file(in_file))
            {
                print_result(_NF);
                return 0;
            }
        }
        if(get_sum_parameter("of")>=1)
        {
            out_file=get_file(get_parameter("of",1));
            if(find_file(out_file))
            {
                print_result(_NF);
                return 0;
            }
        }
        if(get_sum_parameter("if")>=1) copy_source(in_file,"data\\data.in");
        if(get_sum_parameter("of")>=1) copy_source(out_file,"data\\data.out");
    }
    else if(get_sum_parameter("s")!=-1)
    {
        char str;
        FILE *file=fopen((appdata_address+"\\Orita\\data\\data.in").c_str(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
        file=fopen((appdata_address+"\\Orita\\data\\data.out").c_str(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
    }
    if(get_sum_parameter("t")>=1)
    {
        change_time_limit(stoi(get_parameter("t",1)));
    }
    print_result(_Success);
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    if(init_parameter(argc,argv)) {print_result(_II);return 0;}
    if(check_parameter(cor_parameter)) {print_result(_II);return 0;}
    int exit_code=chdata_main();
    End();
    return exit_code;
}