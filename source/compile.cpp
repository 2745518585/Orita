#include "run.hpp"
json make_cor_parameter()
{
    json cor_parameter = {
        {"f", {_no_limit}},
        {"r", {_not_define, 1}},
        {"t", {_not_define, 1}},
        {"o", {_no_limit}}};
    return cor_parameter;
}
json cor_parameter = make_cor_parameter();
int compile_main()
{
    std::string compile_parameter;
    if (get_sum_parameter("o") != -1)
    {
        for (int i = 1; i <= get_sum_parameter("o"); ++i)
            compile_parameter = compile_parameter + " " + get_parameter("o", i);
    }
    if (get_sum_parameter("r") != -1)
    {
        std::string file;
        file = get_file(add_namesuf(get_parameter("r", 1), ".cpp"));
        if (!compile(file, compile_parameter))
        {
            stime run_time;
            run_time.init();
            int exit_code = ssystem(get_path(file) + sPATH_SE + get_namepre(file) + ".exe");
            change_color("grey");
            std::cout << "\n===== time: ";
            change_color("blue");
            std::cout << run_time.get_time();
            change_color("grey");
            std::cout << " ms, exit code: ";
            if (exit_code == 0)
                change_color("green");
            else
                change_color("purple");
            std::cout << exit_code;
            change_color("grey");
            std::cout << " =====\n";
            change_color("white");
        }
    }
    else if (get_sum_parameter("t") != -1)
    {
        std::string file;
        file = get_file(add_namesuf(get_parameter("t", 1), ".exe"));
        stime run_time;
        run_time.init();
        int exit_code = ssystem(file);
        change_color("grey");
        std::cout << "\n===== time: ";
        change_color("blue");
        std::cout << run_time.get_time();
        change_color("grey");
        std::cout << " ms, exit code: ";
        if (exit_code == 0)
            change_color("green");
        else
            change_color("purple");
        std::cout << exit_code;
        change_color("grey");
        std::cout << " =====\n";
        change_color("white");
    }
    else
    {
        for (int i = 1; i <= get_sum_parameter("f"); ++i)
        {
            std::string file = get_file(add_namesuf(get_parameter("f", i), ".cpp"));
            std::cout << get_filename(file) << "\n";
            if (compile(file, compile_parameter) == 0)
                print_result(_Success);
            else
                print_result(_CE);
        }
    }
    return 0;
}
int main(int argc, char **argv)
{
    Begin();
    if (init_parameter(argc, argv))
    {
        print_result(_II);
        return 0;
    }
    if (check_parameter(cor_parameter))
    {
        print_result(_II);
        return 0;
    }
    int exit_code = compile_main();
    End();
    return exit_code;
}