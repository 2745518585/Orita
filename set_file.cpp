#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int set_file_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("c")!=-1)
    {
        for(int i=1;i<=custom_tot;++i) del_name(i+custom_start);
        return 0;
    }
    for(int i=1;i<=custom_tot;++i)
    {
        if(get_sum_parameter(to_string(i))>=1)
        {
            add_name(i+custom_start,get_parameter(to_string(i),1));
            add_running_address(i+custom_start);
        }
    }
    change_color(1,0,1,0);
    cout<<("\nSuccess\n\n");
    change_color(1,1,1,1);
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=set_file_main(argc,argv);
    End();
    return exit_code;
}