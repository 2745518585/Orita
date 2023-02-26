#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
json make_cor_parameter()
{
    json cor_parameter;
    for(int i=1;i<=_custom_tot;++i) cor_parameter[to_string(i)]={-1,1};
    return cor_parameter;
}
json cor_parameter=make_cor_parameter();
int setfile_main()
{
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
    if(init_parameter(argc,argv))
    {
        print_result(_II);
        return 0;
    }
    if(check_parameter(cor_parameter))
    {
        print_result(_II);
        return 0;
    }
    int exit_code=setfile_main();
    End();
    return exit_code;
}