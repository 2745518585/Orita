#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{_not_define,1}},
        {"c",{_not_define,0,1}},
        {"t",{_not_define,1}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
const std::string _ans_name="ans";
const std::string _chk_name="checker";
int run_main()
{
    // init name
    if(get_sum_argu("f")==1)
    {
        add_file(_run_ans,get_argu("f",1));
        if(find_file(add_namesuf(get_name(_run_ans),".cpp"))) {print_result(_ans_name,_NF);return 0;}
    }
    bool use_checker=false;
    if(get_sum_argu("c")!=-1)
    {
        if(get_sum_argu("c")==1)
        {
            add_file(_run_chk,get_argu("c",1));
            if(find_file(add_namesuf(get_name(_run_chk),".cpp"))) {print_result(_chk_name,_NF);return 0;}
        }
        use_checker=true;
    }
    // find file
    if(find_name(_run_ans)) {print_result(_ans_name,_NF);return 0;}
    if(use_checker&&find_name(_run_chk)) {print_result(_chk_name,_NF);return 0;}
    std::string ans,chk;
    ans=add_namesuf(get_name(_run_ans),".cpp");
    if(use_checker) chk=add_namesuf(get_name(_run_chk),".cpp");
    else chk=get_file(":1");
    if(find_file(ans)) {print_result(_ans_name,_NF);return 0;}
    if(find_file(chk)) {print_result(_chk_name,_NF);return 0;}
    // init time
    if(get_sum_argu("t")==1) change_time_limit(stoi(get_argu("t",1)));
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
            print_result(compile_result.second,_CE);
            return 0;
        }
    }
    delete run_compiler;
    loading_printer.stop();
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
    if(init_argu(argc,argv)) {print_result(_II);return 0;}
    if(check_argu(cor_argu)) {print_result(_II);return 0;}
    int exit_code=run_main();
    return exit_code;
}