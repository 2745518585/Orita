#include"run.hpp"
json make_cor_argu()
{
    json cor_argu;
    for(int i=0;i<=_max_file_num;++i) cor_argu[std::to_string(i)]={_not_define,1};
    return cor_argu;
}
json cor_argu=make_cor_argu();
int setfile_main()
{
    for(int i=0;i<=_max_file_num;++i)
    {
        if(argus[std::to_string(i)].sum()>=1)
        {
            add_file(i,argus[std::to_string(i)][1]);
        }
    }
    print_result(res::type::SS);
    return 0;
}
int main(int argc,char **argv)
{
    if(argus.init_argu(argc,argv)) {print_result(res::type::II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(res::type::II);return 0;}
    int exit_code=setfile_main();
    return exit_code;
}