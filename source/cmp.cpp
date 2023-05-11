#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{_not_define,2}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
int cmp_main()
{
    if(get_sum_argu("f")<2) return 0;
    std::string file1=get_file(get_argu("f",1));
    std::string file2=get_file(get_argu("f",2));
    if(find_file(file1)||find_file(file2))
    {
        print_result(_NF);
        return 1;
    }
    if(compare(file1,file2))
    {
        print_result(_DA);
        return 1;
    }
    else
    {
        print_result(_SA);
        return 0;
    }
}
int main(int argc,char **argv)
{
    if(init_argu(argc,argv)) {print_result(_II);return 0;}
    if(check_argu(cor_argu)) {print_result(_II);return 0;}
    int exit_code=cmp_main();
    return exit_code;
}