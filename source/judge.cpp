#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{_not_define,1}},
        {"c",{_not_define,0,1}},
        {"t",{_not_define,1}},
        {"d",{_not_define,2}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
const std::string _ans_name="ans";
const std::string _chk_name="checker";
int judge_main()
{
    // init name
    if(get_sum_argu("f")==1)
    {
        add_file(_run_ans,get_argu("f",1));
        if(find_file(add_namesuf(get_name(_run_ans),".cpp"))) {std::cout<<"\n"+_ans_name+":";print_result(_NF);return 0;}
    }
    bool use_checker=false;
    if(get_sum_argu("c")!=-1)
    {
        if(get_sum_argu("c")==1)
        {
            add_file(_run_chk,get_argu("c",1));
            if(find_file(add_namesuf(get_name(_run_chk),".cpp"))) {std::cout<<"\n"+_chk_name+":";print_result(_NF);return 0;}
        }
        use_checker=true;
    }
    // init time
    if(get_sum_argu("t")==1) change_time_limit(stoi(get_argu("t",1)));
    // init data
    if(get_sum_argu("d")==-1)
    {
        print_result(_Success);
        return 0;
    }
    // find file
    if(find_name(_run_ans)) {std::cout<<"\n"+_ans_name+":";print_result(_NF);return 0;}
    if(use_checker&&find_name(_run_chk)) {std::cout<<"\n"+_chk_name+":";print_result(_NF);return 0;}
    std::string ans,chk;
    ans=add_namesuf(get_name(_run_ans),".cpp");
    if(use_checker) chk=add_namesuf(get_name(_run_chk),".cpp");
    else chk=get_file(":1");
    if(find_file(ans)) {std::cout<<"\n"+_ans_name+":";print_result(_NF);return 0;}
    if(find_file(chk)) {std::cout<<"\n"+_chk_name+":";print_result(_NF);return 0;}
    // compile file
    printer loading_printer({"Compiling.","Compiling..","Compiling..."},150);
    loading_printer.start();
    compiler *run_compiler=new compiler(2);
    run_compiler->add({{_ans_name,ans},{_chk_name,chk}},"-D JUDGEING");
    run_compiler->wait({_ans_name,_chk_name});
    {
        auto compile_result=run_compiler->get({_ans_name,_chk_name});
        if(compile_result.first)
        {
            loading_printer.stop();
            std::cout<<"\n"<<compile_result.second<<":";
            print_result(_CE);
            return 0;
        }
    }
    delete run_compiler;
    loading_printer.stop();
    // judge
    std::string name_pre=get_argu("d",1);
    std::ofstream file("result.txt");
    int total_sum=stoi(get_argu("d",2)),ac_sum=0;
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
    if(init_argu(argc,argv)) {print_result(_II);return 0;}
    if(check_argu(cor_argu)) {print_result(_II);return 0;}
    int exit_code=judge_main();
    return exit_code;
}