#include"run.hpp"
json make_cor_argu()
{
    json cor_argu;
    for(int i=1;i<=_custom_tot;++i) cor_argu[std::to_string(i)]={_not_define,1};
    return cor_argu;
}
json cor_argu=make_cor_argu();
int setfile_main()
{
    for(int i=1;i<=_custom_tot;++i)
    {
        if(get_sum_argu(std::to_string(i))>=1)
        {
            add_file(i+_custom_start,get_argu(std::to_string(i),1));
        }
    }
    print_result(_SS);
    return 0;
}
int main(int argc,char **argv)
{
    if(init_argu(argc,argv)) {print_result(_II);return 0;}
    if(check_argu(cor_argu)) {print_result(_II);return 0;}
    int exit_code=setfile_main();
    return exit_code;
}