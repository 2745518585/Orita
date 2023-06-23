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
    std::string ans,chk;
    {
        const std::string ans_str=check_file(argus["f"].get(1),_run_ans);
        add_file(_run_ans,ans_str);
        ans=add_namesuf(get_file(ans_str),".cpp");
    }
    if(argus["c"].sum()!=-1)
    {
        const std::string chk_str=check_file(argus["c"].get(1),_run_chk);
        add_file(_run_chk,chk_str);
        chk=add_namesuf(get_file(chk_str),".cpp");
    }
    else chk=add_namesuf(get_file("%1"),".cpp");
    // init time
    if(argus["t"].sum()==1) change_time_limit((tim)stoi(argus["t"][1]));
    // init data
    if(argus["d"].sum()==-1)
    {
        print_result(res::type::SS);
        return 0;
    }
    // find file
    if(find_file(ans)) {print_result(_ans_name,res::type::NF);return 0;}
    if(find_file(chk)) {print_result(_chk_name,res::type::NF);return 0;}
    // compile file
    printer loading_printer({"Compiling.","Compiling..","Compiling..."},(tim)150);
    loading_printer.start();
    compiler *run_compiler=new compiler(2);
    run_compiler->add({{_ans_name,ans},{_chk_name,chk}},get_compile_argu()+" -D JUDGING");
    run_compiler->wait({_ans_name,_chk_name});
    {
        auto compile_result=run_compiler->get({_ans_name,_chk_name});
        if(compile_result.first)
        {
            loading_printer.stop();
            print_result(compile_result.second,res::type::CE);
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
        if(find_file(makepath(running_path,name_pre+std::to_string(i)+".in"))) {print_result(res::type::NF);continue;}
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
    if(argus.init_argu(argc,argv)) {print_result(res::type::II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(res::type::II);return 0;}
    int exit_code=judge_main();
    return exit_code;
}