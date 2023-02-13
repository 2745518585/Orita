#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int setfile_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    for(int i=1;i<=_custom_tot;++i)
    {
        if(get_sum_parameter(to_string(i))>=1)
        {
            add_file(i+_custom_start,get_parameter(to_string(i),1));
        }
    }
    print_result(_Success);
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=setfile_main(argc,argv);
    End();
    return exit_code;
}