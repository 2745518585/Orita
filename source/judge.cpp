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
    if(argus["f"].sum()==1)
    {
        if(find_file(add_namesuf(get_file(argus["f"][1]),".cpp"))) {print_result(_ans_name,_NF);return 0;}
        add_file(_run_ans,argus["f"][1]);
    }
    bool use_checker=false;
    if(argus["c"].sum()!=-1)
    {
        if(argus["c"].sum()==1)
        {
            if(find_file(add_namesuf(get_file(argus["c"][1]),".cpp"))) {print_result(_chk_name,_NF);return 0;}
            add_file(_run_chk,argus["c"][1]);
        }
        use_checker=true;
    }
    // init time
    if(argus["t"].sum()==1) change_time_limit(stoi(argus["t"][1]));
    // init data
    if(argus["d"].sum()==-1)
    {
        print_result(_SS);
        return 0;
    }
    // find file
    if(find_filestr(_run_ans)) {print_result(_ans_name,_NF);return 0;}
    if(use_checker&&find_filestr(_run_chk)) {print_result(_chk_name,_NF);return 0;}
    std::string ans,chk;
    ans=add_namesuf(get_file(_run_ans),".cpp");
    if(use_checker) chk=add_namesuf(get_file(_run_chk),".cpp");
    else chk=get_file("%1");
    if(find_file(ans)) {print_result(_ans_name,_NF);return 0;}
    if(find_file(chk)) {print_result(_chk_name,_NF);return 0;}
    // compile file
    printer loading_printer({"Compiling.","Compiling..","Compiling..."},150);
    loading_printer.start();
    compiler *run_compiler=new compiler(2);
    run_compiler->add({{_ans_name,ans},{_chk_name,chk}},get_compile_argu()+" -D JUDGING");
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
    // judge
    std::string name_pre=argus["d"][1];
    std::ofstream file("result.txt");
    int total_sum=stoi(argus["d"][2]),ac_sum=0;
    for(int i=1;i<=total_sum;++i)
    {
        for(int j=1;j<=50;++j) std::cout<<"-";
        for(int j=1;j<=50;++j) std::cout<<"\b";
        std::cout<<"#"<<i<<"\n";
        if(find_file(makepath(running_path,name_pre+std::to_string(i)+".in"))) {print_result(_NF);continue;}
        judger run_judger(ans,chk,makepath(running_path,name_pre+std::to_string(i)+".in"),makepath(running_path,name_pre+std::to_string(i)+".out"),makepath(running_path,name_pre+std::to_string(i)+".ans"),makepath(running_path,name_pre+std::to_string(i)+".txt"));
        run_judger.judge();
        run_judger.print_result();
        if(run_judger.result.istrue()) ++ac_sum;
        file<<i<<":\t"<<get_short_resultname(run_judger.result)<<"\n";
    }
    file.close();
    std::cout<<ac_sum<<" / "<<total_sum;
    return 0;
}
int main(int argc,char **argv)
{
    if(argus.init_argu(argc,argv)) {print_result(_II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(_II);return 0;}
    int exit_code=judge_main();
    return exit_code;
}