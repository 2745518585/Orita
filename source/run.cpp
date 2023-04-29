#include"run.hpp"
json make_cor_parameter()
{
    json cor_parameter={
        {"f",{_not_define,1}},
        {"c",{_not_define,0,1}},
        {"t",{_not_define,1}}
    };
    return cor_parameter;
}
json cor_parameter=make_cor_parameter();
int run_main()
{
    // init name
    if(get_sum_parameter("f")==1)
    {
        add_file(_run_ans,get_parameter("f",1));
        if(find_file(add_namesuf(get_name(_run_ans),".cpp"))) {std::cout<<"\nans:";print_result(_NF);return 0;}
    }
    bool use_checker=false;
    if(get_sum_parameter("c")!=-1)
    {
        if(get_sum_parameter("c")==1)
        {
            add_file(_run_chk,get_parameter("c",1));
            if(find_file(add_namesuf(get_name(_run_chk),".cpp"))) {std::cout<<"\nchecker:";print_result(_NF);return 0;}
        }
        use_checker=true;
    }
    // find file
    if(find_name(_run_ans)) {std::cout<<"\nans:";print_result(_NF);return 0;}
    if(use_checker&&find_name(_run_chk)) {std::cout<<"\nchecker:";print_result(_NF);return 0;}
    std::string ans,chk;
    ans=add_namesuf(get_name(_run_ans),".cpp");
    if(use_checker) chk=add_namesuf(get_name(_run_chk),".cpp");
    else chk=get_file(":1");
    if(find_file(ans)) {std::cout<<"\nans:";print_result(_NF);return 0;}
    if(find_file(chk)) {std::cout<<"\nchecker:";print_result(_NF);return 0;}
    // init time
    if(get_sum_parameter("t")==1) change_time_limit(stoi(get_parameter("t",1)));
    // compile file
    if(print_compile(ans,"ans","-D JUDGING")) {print_result(_CE);return 0;}
    if(print_compile(chk,"checker","-D JUDGING")) {std::cout<<"\nchecker:";print_result(_CE);return 0;}
    // find dangerous syscalls
    if(find_dangerous_syscalls(ans,"-D JUDGING")) {print_result(_DS);}
    // run
    monitor_judger run_judger(ans,chk);
    run_judger.judge();
    // print result
    run_judger.print_result();
    // copy result
    ssystem("mkdir data"+system_to_nul);
    copy_result("data"+sPS+"data.in","data"+sPS+"data.in");
    copy_result("data"+sPS+"data.out","data"+sPS+"data.out");
    copy_result("data"+sPS+"data.ans","data"+sPS+"data.ans");
    return 0;
}
int main(int argc,char **argv)
{
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
    int exit_code=run_main();
    return exit_code;
}