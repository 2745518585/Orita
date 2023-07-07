#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{arguer::NL}},
        {"r",{arguer::ND,1}},
        {"t",{arguer::ND,1}},
        {"o",{arguer::NL}},
        {"p",{arguer::NL}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
int compile_main()
{
    std::string compile_argu;
    if(argus["o"].appear())
    {
        for(int i=1;i<=argus["o"].size();++i) compile_argu=compile_argu+" "+argus["o"][i];
    }
    else compile_argu=get_compile_argu();
    std::string run_argu;
    if(argus["p"].appear())
    {
        for(int i=1;i<=argus["p"].size();++i) run_argu=run_argu+" "+argus["p"][i];
    }
    if(argus["r"].appear())
    {
        std::string file;
        file=get_file(add_namesuf(argus["r"][1],".cpp"));
        if(compile(file,compile_argu)) return 0;
        runner runs(get_exefile(file),"","",run_argu,(tim)1000000);
        runs.run();
        std::cout<<"\n"<<termcolor::bright_grey<<"===== time: "<<termcolor::bright_cyan<<runs.time<<termcolor::bright_grey<<", exit code: "<<(runs.exit_code?termcolor::magenta<char>:termcolor::bright_green<char>)<<runs.exit_code<<termcolor::bright_grey<<" ====="<<termcolor::reset<<"\n";
    }
    else if(argus["t"].appear())
    {
        std::string file=get_file(argus["t"][1]);
        runner runs(file,"","",run_argu,(tim)1000000);
        runs.run();
        std::cout<<"\n"<<termcolor::bright_grey<<"===== time: "<<termcolor::bright_cyan<<runs.time<<termcolor::bright_grey<<", exit code: "<<(runs.exit_code?termcolor::magenta<char>:termcolor::bright_green<char>)<<runs.exit_code<<termcolor::bright_grey<<" ====="<<termcolor::reset<<"\n";
    }
    else
    {
        for(int i=1;i<=argus["f"].size();++i)
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