#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int set_file_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("c")!=-1)
    {
        for(int i=1;i<=__NAME__custom_tot;++i) del_name(i+__NAME__custom_start);
        return 0;
    }
    for(int i=1;i<=__NAME__custom_tot;++i)
    {
        if(get_sum_parameter(to_string(i))>=1)
        {
            add_name(i+__NAME__custom_start,get_parameter(to_string(i),1));
            add_running_address(i+__NAME__custom_start);
        }
    }
    print_result(__PRINT__Success);
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=set_file_main(argc,argv);
    End();
    return exit_code;
}