#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{_no_limit}},
        {"r",{_not_define,1}},
        {"t",{_not_define,1}},
        {"o",{_no_limit}},
        {"p",{_no_limit}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
int compile_main()
{
    std::string compile_argu;
    if(argus["o"].sum()!=-1)
    {
        for(int i=1;i<=argus["o"].sum();++i) compile_argu=compile_argu+" "+argus["o"][i];
    }
    else compile_argu=get_compile_argu();
    std::string run_argu;
    if(argus["p"].sum()!=-1)
    {
        for(int i=1;i<=argus["p"].sum();++i) run_argu=run_argu+" "+argus["p"][i];
    }
    if(argus["r"].sum()!=-1)
    {
        std::string file;
        file=get_file(add_namesuf(argus["r"][1],".cpp"));
        if(compile(file,compile_argu)) return 0;
        runner runs(get_exefile(file),"","",run_argu,(tim)1000000);
        runs.run();
        std::cout<<"\n"<<color_str("grey")<<"===== time: "<<color_str("blue")<<runs.time<<color_str("grey")<<", exit code: "<<color_str(runs.exit_code?"purple":"green")<<runs.exit_code<<color_str("grey")<<" ====="<<color_str("default")<<"\n";
    }
    else if(argus["t"].sum()!=-1)
    {
        std::string file=get_file(argus["t"][1]);
        runner runs(file,"","",run_argu,(tim)1000000);
        runs.run();
        std::cout<<"\n"<<color_str("grey")<<"===== time: "<<color_str("blue")<<runs.time<<color_str("grey")<<", exit code: "<<color_str(runs.exit_code?"purple":"green")<<runs.exit_code<<color_str("grey")<<" ====="<<color_str("default")<<"\n";
    }
    else
    {
        for(int i=1;i<=argus["f"].sum();++i)
        {
            std::string file=get_file(add_namesuf(argus["f"][i],".cpp"));
            if(compile(file,compile_argu)) print_result(get_filename(file),res::type::CE);
            else print_result(get_filename(file),res::type::SS);
        }
    }
    return 0;
}
int main(int argc,char **argv)
{
    if(argus.init_argu(argc,argv)) {print_result(res::type::II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(res::type::II);return 0;}
    int exit_code=compile_main();
    return exit_code;
}