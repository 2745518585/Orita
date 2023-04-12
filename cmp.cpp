#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
json make_cor_parameter()
{
    json cor_parameter={
        {"f",{_not_define,2}}
    };
    return cor_parameter;
}
json cor_parameter=make_cor_parameter();
int cmp_main()
{
    if(get_sum_parameter("f")<2) return 0;
    string file1=get_file(get_parameter("f",1));
    string file2=get_file(get_parameter("f",2));
    if(find_file(file1)||find_file(file2))
    {
        print_result(_NF);
        return 1;
    }
    if(compare(file1,file2))
    {
        print_result(_DA);
        return 1;
    }
    else
    {
        print_result(_SA);
        return 0;
    }
}
int main(int argc,char **argv)
{
    Begin();
    if(init_parameter(argc,argv)) {print_result(_II);return 0;}
    if(check_parameter(cor_parameter)) {print_result(_II);return 0;}
    int exit_code=cmp_main();
    End();
    return exit_code;
}