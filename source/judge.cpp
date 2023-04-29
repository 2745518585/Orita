#include"run.hpp"
json make_cor_parameter()
{
    json cor_parameter={
        {"f",{_not_define,1}},
        {"c",{_not_define,0,1}},
        {"t",{_not_define,1}},
        {"d",{_not_define,2}}
    };
    return cor_parameter;
}
json cor_parameter=make_cor_parameter();
int judge_main()
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
    // init time
    if(get_sum_parameter("t")==1) change_time_limit(stoi(get_parameter("t",1)));
    // init data
    if(get_sum_parameter("d")==-1)
    {
        print_result(_Success);
        return 0;
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
    // compile file
    if(print_compile(ans,"ans","-D JUDGING")) {print_result(_CE);return 0;}
    if(print_compile(chk,"checker","-D JUDGING")) {std::cout<<"\nchecker:";print_result(_CE);return 0;}
    // find dangerous syscalls
    if(find_dangerous_syscalls(ans,"-D JUDGING")) {print_result(_DS);}
    std::string name_pre=get_parameter("d",1);
    std::ofstream file("result.txt");
    int total_sum=stoi(get_parameter("d",2)),ac_sum=0;
    for(int i=1;i<=total_sum;++i)
    {
        std::cout<<"#"<<i<<"--------------------------------------------------"<<"\n";
        if(find_file(running_path+sPS+name_pre+std::to_string(i)+".in")) {print_result(_NF);continue;}
        monitor_judger run_judger(ans,chk,running_path+sPS+name_pre+std::to_string(i)+".in",running_path+sPS+name_pre+std::to_string(i)+".out",running_path+sPS+name_pre+std::to_string(i)+".ans",running_path+sPS+name_pre+std::to_string(i)+".txt");
        run_judger.judge();
        run_judger.print_result();
        if(run_judger.result==0) ++ac_sum;
        file<<i<<":\t"<<get_short_result(run_judger.result)<<"\n";
    }
    file.close();
    std::cout<<ac_sum<<" / "<<total_sum;
    return 0;
}
int main(int argc,char **argv)
{
    if(init_parameter(argc,argv)) {print_result(_II);return 0;}
    if(check_parameter(cor_parameter)) {print_result(_II);return 0;}
    int exit_code=judge_main();
    return exit_code;
}