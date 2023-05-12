#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{_no_limit}},
        {"r",{_not_define,1}},
        {"t",{_not_define,1}},
        {"o",{_no_limit}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
int compile_main()
{
    std::string compile_argu;
    if(get_sum_argu("o")!=-1)
    {
        for(int i=1;i<=get_sum_argu("o");++i) compile_argu=compile_argu+" "+get_argu("o",i);
    }
    if(get_sum_argu("r")!=-1)
    {
        std::string file;
        file=get_file(add_namesuf(get_argu("r",1),".cpp"));
        if(!compile(file,compile_argu))
        {
            stime run_time;
            run_time.init();
            int exit_code=ssystem(get_exefile(file))/sys_exit_code;
            change_color("grey");
            std::cout<<"\n===== time: ";
            change_color("blue");
            std::cout<<run_time.get_time();
            change_color("grey");
            std::cout<<" ms, exit code: ";
            if(exit_code==0) change_color("green");
            else change_color("purple");
            std::cout<<exit_code;
            change_color("grey");
            std::cout<<" =====\n";
            change_color("default");
        }
    }
    else if(get_sum_argu("t")!=-1)
    {
        std::string file;
        stime run_time;
        run_time.init();
        int exit_code=ssystem(file)/sys_exit_code;
        change_color("grey");
        std::cout<<"\n===== time: ";
        change_color("blue");
        std::cout<<run_time.get_time();
        change_color("grey");
        std::cout<<" ms, exit code: ";
        if(exit_code==0) change_color("green");
        else change_color("purple");
        std::cout<<exit_code;
        change_color("grey");
        std::cout<<" =====\n";
        change_color("default");
    }
    else
    {
        for(int i=1;i<=get_sum_argu("f");++i)
        {
            std::string file=get_file(add_namesuf(get_argu("f",i),".cpp"));
            if(compile(file,compile_argu)) print_result(get_filename(file),_CE);
            else print_result(get_filename(file),_SS);
        }
    }
    return 0;
}
int main(int argc,char **argv)
{
    if(init_argu(argc,argv)) {print_result(_II);return 0;}
    if(check_argu(cor_argu)) {print_result(_II);return 0;}
    int exit_code=compile_main();
    return exit_code;
}