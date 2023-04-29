#include"run.hpp"
json make_cor_parameter()
{
    json cor_parameter={
        {"f",{_not_define,3}},
        {"if",{_not_define,1}},
        {"of",{_not_define,1}},
        {"af",{_not_define,1}},
        {"c",{_not_define,0,1}},
        {"n",{_not_define,1}},
        {"e",{_not_define,0}},
        {"p",{_not_define,0}},
        {"t",{_not_define,1}}
    };
    return cor_parameter;
}
json cor_parameter=make_cor_parameter();
int check_main()
{
    // init name
    if(get_sum_parameter("f")==3)
    {
        add_file(_check_in,get_parameter("f",1));
        add_file(_check_out,get_parameter("f",2));
        add_file(_check_ans,get_parameter("f",3));
        if(find_file(add_namesuf(get_name(_check_in),".cpp"))) {std::cout<<"\ndata_maker:";print_result(_NF);return 0;}
        if(find_file(add_namesuf(get_name(_check_out),".cpp"))) {std::cout<<"\nstd:";print_result(_NF);return 0;}
        if(find_file(add_namesuf(get_name(_check_ans),".cpp"))) {std::cout<<"\nans:";print_result(_NF);return 0;}
    }
    else
    {
        if(get_sum_parameter("if")==1) add_file(_check_in,get_parameter("if",1));
        if(get_sum_parameter("of")==1) add_file(_check_out,get_parameter("of",1));
        if(get_sum_parameter("af")==1) add_file(_check_ans,get_parameter("af",1));
        if(get_sum_parameter("if")==1&&find_file(add_namesuf(get_name(_check_in),".cpp"))) {std::cout<<"\ndata_maker:";print_result(_NF);return 0;}
        if(get_sum_parameter("of")==1&&find_file(add_namesuf(get_name(_check_out),".cpp"))) {std::cout<<"\nstd:";print_result(_NF);return 0;}
        if(get_sum_parameter("af")==1&&find_file(add_namesuf(get_name(_check_ans),".cpp"))) {std::cout<<"\nans:";print_result(_NF);return 0;}
    }
    bool use_checker=false;
    if(get_sum_parameter("c")!=-1)
    {
        if(get_sum_parameter("c")==1)
        {
            add_file(_check_chk,get_parameter("c",1));
            if(find_file(add_namesuf(get_name(_check_chk),".cpp"))) {std::cout<<"\nchecker:";print_result(_NF);return 0;}
        }
        use_checker=true;
    }
    // init time
    if(get_sum_parameter("t")==1) change_time_limit(stoi(get_parameter("t",1)));
    // init total sum
    if(get_sum_parameter("n")==-1)
    {
        print_result(_Success);
        return 0;
    }
    int total_sum=stoi(get_parameter("n",1));
    // find file
    if(find_name(_check_in)) {std::cout<<"\ndata_maker:";print_result(_NF);return 0;}
    if(find_name(_check_out)) {std::cout<<"\nstd:";print_result(_NF);return 0;}
    if(find_name(_check_ans)) {std::cout<<"\nans:";print_result(_NF);return 0;}
    if(use_checker&&find_name(_check_chk)) {std::cout<<"\nchecker:";print_result(_NF);return 0;}
    std::string in,out,ans,chk;
    in=add_namesuf(get_name(_check_in),".cpp");
    out=add_namesuf(get_name(_check_out),".cpp");
    ans=add_namesuf(get_name(_check_ans),".cpp");
    if(use_checker) chk=add_namesuf(get_name(_check_chk),".cpp");
    else chk=get_file(":1");
    if(find_file(in)) {std::cout<<"\ndata_maker:";print_result(_NF);return 0;}
    if(find_file(out)) {std::cout<<"\nstd:";print_result(_NF);return 0;}
    if(find_file(ans)) {std::cout<<"\nans:";print_result(_NF);return 0;}
    if(find_file(chk)) {std::cout<<"\nchecker:";print_result(_NF);return 0;}
    // compile file
    if(print_compile(in,"data_maker","-D JUDGING")) {std::cout<<"\ndata_maker:";print_result(_CE);return 0;}
    if(print_compile(out,"std","-D JUDGING")) {std::cout<<"\nstd:";print_result(_CE);return 0;}
    if(print_compile(ans,"ans","-D JUDGING")) {print_result(_CE);return 0;}
    if(print_compile(chk,"checker","-D JUDGING")) {std::cout<<"\nchecker:";print_result(_CE);return 0;}
    // find dangerous syscalls
    if(find_dangerous_syscalls(in,"-D JUDGING")) {std::cout<<"\ndata_maker:";print_result(_DS);}
    if(find_dangerous_syscalls(out,"-D JUDGING")) {std::cout<<"\nstd:";print_result(_DS);}
    if(find_dangerous_syscalls(ans,"-D JUDGING")) {print_result(_DS);}
    // init monitor
    bool use_monitor=false;
    if(get_sum_parameter("e")!=-1) use_monitor=true;
    // init compare
    bool use_compare=false;
    if(get_sum_parameter("p")!=-1) use_compare=true;
    // init data dir
    ssystem("mkdir data"+system_to_nul);
    ssystem("del /Q data"+sPS+"*"+system_to_nul);
    // check
    int ac_sum=0,runned_sum=0;
    for(int i=1;i<=total_sum;++i)
    {
        std::cout<<"#"<<i<<"--------------------------------------------------";
        if(runned_sum-ac_sum!=0)
        {
            change_color("red");
            std::cout<<" Unaccepted "<<runned_sum-ac_sum;
            change_color("white");
        }
        std::cout<<"\n";
        if(use_compare)
        {
            if(use_monitor)
            {
                monitor_runner run_runner(in," > \""+appdata_path+sPS+"data"+sPS+"data.in\" "+std::to_string(i));
                if(run_runner.run()) {std::cout<<"\ndata_maker:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(run_runner.exit_code) {std::cout<<"\ndata_maker:";print_result(_RE,run_runner.exit_code);continue;}
            }
            else ssystem("\""+get_path(in)+sPS+get_namepre(in)+"\".exe > \""+appdata_path+sPS+"data"+sPS+"data.in\" "+std::to_string(i));
            monitor_judger run_judger1(out,get_file(":0"),"","",appdata_path+sPS+"data"+sPS+"data.out","");
            std::cout<<"\nans1:";
            run_judger1.judge();
            run_judger1.print_result();
            monitor_judger run_judger2(ans,get_file(":0"),"","",appdata_path+sPS+"data"+sPS+"data.ans","");
            std::cout<<"ans2:";
            run_judger2.judge();
            run_judger2.print_result();
            ++runned_sum;
            if(run_judger1.result==_AC&&run_judger2.result==_AC)
            {
                if(ssystem(get_exefile(chk)+" "+appdata_path+sPS+"data"+sPS+"data.in "+appdata_path+sPS+"data"+sPS+"data.out "+appdata_path+sPS+"data"+sPS+"data.ans"))
                {
                    print_result(_DA);
                    copy_result("data"+sPS+"data.in","data"+sPS+std::to_string(i)+".in");
                    copy_result("data"+sPS+"data.out","data"+sPS+std::to_string(i)+".out");
                    copy_result("data"+sPS+"data.ans","data"+sPS+std::to_string(i)+".ans");
                    copy_result("data"+sPS+"data.txt","data"+sPS+std::to_string(i)+".txt");
                }
                else print_result(_SA),++ac_sum;
            }
        }
        else
        {
            if(use_monitor)
            {
                monitor_runner run_runner1(in," > \""+appdata_path+sPS+"data"+sPS+"data.in\" "+std::to_string(i));
                if(run_runner1.run()) {std::cout<<"\ndata_maker:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(run_runner1.exit_code) {std::cout<<"\ndata_maker:";print_result(_RE,run_runner1.exit_code);continue;}
                monitor_runner run_runner2(out," < \""+appdata_path+sPS+"data"+sPS+"data.in\" > \""+appdata_path+sPS+"data"+sPS+"data.out\"");
                if(run_runner2.run()) {std::cout<<"\nstd:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(run_runner2.exit_code) {std::cout<<"\nstd:";print_result(_RE,run_runner2.exit_code);continue;}
                ++runned_sum;
            }
            else
            {
                ssystem("\""+get_path(in)+sPS+get_namepre(in)+".exe\" > \""+appdata_path+sPS+"data"+sPS+"data.in\" "+std::to_string(i));
                ssystem("\""+get_path(out)+sPS+get_namepre(out)+".exe\" < \""+appdata_path+sPS+"data"+sPS+"data.in\" > \""+appdata_path+sPS+"data"+sPS+"data.out\"");
                ++runned_sum;
            }
            monitor_judger run_judger(ans,chk);
            run_judger.judge();
            run_judger.print_result();
            if(run_judger.result>0)
            {
                copy_result("data"+sPS+"data.in","data"+sPS+std::to_string(i)+".in");
                copy_result("data"+sPS+"data.out","data"+sPS+std::to_string(i)+".out");
                copy_result("data"+sPS+"data.ans","data"+sPS+std::to_string(i)+".ans");
                copy_result("data"+sPS+"data.txt","data"+sPS+std::to_string(i)+".txt");
            }
            else ++ac_sum;
        }
    }
    std::cout<<"\n"<<ac_sum<<" / "<<runned_sum<<"\n\n";
    return 0;
}
int main(int argc,char **argv)
{
    if(init_parameter(argc,argv)) {print_result(_II);return 0;}
    if(check_parameter(cor_parameter)) {print_result(_II);return 0;}
    int exit_code=check_main();
    return exit_code;
}