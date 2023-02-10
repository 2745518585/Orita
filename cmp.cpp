#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
int cmp_main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("f")<2) return 0;
    add_file(__NAME__judge_out,get_parameter("f",1));
    add_file(__NAME__judge_ans,get_parameter("f",2));
    if(find_file(__NAME__judge_out)||find_file(__NAME__judge_ans))
    {
        print_result(__PRINT__NF);
        return 1;
    }
    if(compare())
    {
        print_result(__PRINT__DA);
        return 1;
    }
    else
    {
        print_result(__PRINT__SA);
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