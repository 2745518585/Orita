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
    if(find_dangerous_syscalls(in)) {std::cout<<"\ndata_maker:";print_result(_DS);}
    if(find_dangerous_syscalls(out)) {std::cout<<"\nstd:";print_result(_DS);}
    if(find_dangerous_syscalls(ans)) {print_result(_DS);}
    // init monitor
    bool use_monitor=false;
    if(get_sum_parameter("e")!=-1) use_monitor=true;
    // init compare
    bool use_compare=false;
    if(get_sum_parameter("p")!=-1) use_compare=true;
    // init data dir
    ssystem("mkdir data"+system_to_nul);
    ssystem("del /Q data"+sPATH_SE+"*"+system_to_nul);
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
                if(run_monitor(in," > \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.in\" "+std::to_string(i))) {std::cout<<"\ndata_maker:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(Judge::exit_code!=0) {std::cout<<"\ndata_maker:";print_result(_RE,Judge::exit_code);continue;}
            }
            else ssystem("\""+get_path(in)+sPATH_SE+get_namepre(in)+"\".exe > \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.in\" "+std::to_string(i));
            Judge::ans_file=appdata_path+sPATH_SE+"data"+sPATH_SE+"data.out";
            std::cout<<"\nans1:";
            judge_monitor(out,get_file(":0"));
            print_judge_result(Judge::result,Judge::time,Judge::exit_code,Judge::time_limit);
            int result1=Judge::result;
            Judge::ans_file=appdata_path+sPATH_SE+"data"+sPATH_SE+"data.ans";
            std::cout<<"ans2:";
            judge_monitor(ans,get_file(":0"));
            print_judge_result(Judge::result,Judge::time,Judge::exit_code,Judge::time_limit);
            int result2=Judge::result;
            ++runned_sum;
            if(result1==_AC&&result2==_AC)
            {
                if(check_ans(chk))
                {
                    print_result(_DA);
                    copy_result("data"+sPATH_SE+"data.in","data"+sPATH_SE+std::to_string(i)+".in");
                    copy_result("data"+sPATH_SE+"data.out","data"+sPATH_SE+std::to_string(i)+".out");
                    copy_result("data"+sPATH_SE+"data.ans","data"+sPATH_SE+std::to_string(i)+".ans");
                    copy_result("data"+sPATH_SE+"data.txt","data"+sPATH_SE+std::to_string(i)+".txt");
                }
                else print_result(_SA),++ac_sum;
            }
        }
        else
        {
            if(use_monitor)
            {
                if(run_monitor(in," > \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.in\" "+std::to_string(i))) {std::cout<<"\ndata_maker:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(Judge::exit_code!=0) {std::cout<<"\ndata_maker:";print_result(_RE,Judge::exit_code);continue;}
                if(run_monitor(out," < \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.in\" > \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.out\"")) {std::cout<<"\nstd:";print_result(_TLE_O,get_time_limit()*2);continue;}
                if(Judge::exit_code!=0) {std::cout<<"\nstd:";print_result(_RE,Judge::exit_code);continue;}
                ++runned_sum;
            }
            else
            {
                ssystem("\""+get_path(in)+sPATH_SE+get_namepre(in)+".exe\" > \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.in\" "+std::to_string(i));
                ssystem("\""+get_path(out)+sPATH_SE+get_namepre(out)+".exe\" < \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.in\" > \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.out\"");
                ++runned_sum;
            }
            judge_monitor(ans,chk);
            print_judge_result();
            int result=Judge::result;
            if(result>0)
            {
                copy_result("data"+sPATH_SE+"data.in","data"+sPATH_SE+std::to_string(i)+".in");
                copy_result("data"+sPATH_SE+"data.out","data"+sPATH_SE+std::to_string(i)+".out");
                copy_result("data"+sPATH_SE+"data.ans","data"+sPATH_SE+std::to_string(i)+".ans");
                copy_result("data"+sPATH_SE+"data.txt","data"+sPATH_SE+std::to_string(i)+".txt");
            }
            else ++ac_sum;
        }
    }
    std::cout<<"\n"<<ac_sum<<" / "<<runned_sum<<"\n\n";
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    if(init_parameter(argc,argv)) {print_result(_II);return 0;}
    if(check_parameter(cor_parameter)) {print_result(_II);return 0;}
    int exit_code=check_main();
    End();
    return exit_code;
}