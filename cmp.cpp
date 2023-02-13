#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int cmp_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("f")<2) return 0;
    add_file(_judge_out,get_parameter("f",1));
    add_file(_judge_ans,get_parameter("f",2));
    if(find_file(_judge_out)||find_file(_judge_ans))
    {
        print_result(_NF);
        return 1;
    }
    if(compare())
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
    int exit_code=cmp_main(argc,argv);
    End();
    return exit_code;
}