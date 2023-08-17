#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"s",{arguer::ND,0,1,2}},
        {"f",{arguer::ND,0,1,2}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
int config_main()
{
    if(argus["s"].appear())
    {
        if(argus["s"].size()==0)
        {
            std::cout<<std::setw(4)<<settings;
        }
        else if(argus["s"].size()==1)
        {
            std::cout<<settings[(json::json_pointer)("/"+argus["s"][1])]<<"\n";
        }
        else
        {
            settings[(json::json_pointer)("/"+argus["s"][1])]=json::parse(argus["s"][2]);
        }
    }
    else if(argus["f"].appear())
    {
        if(argus["f"].size()==0)
        {
            std::cout<<std::setw(4)<<Files::files_json;
        }
        else if(argus["f"].size()==1)
        {
            std::cout<<get_filestr(stoi(argus["f"][1]))<<"\n";
        }
        else
        {
            add_filestr(stoi(argus["f"][1]),argus["f"][2]);
        }
    }
    return 0;
}
int main(int argc,char **argv)
{
    if(argus.init_argu(argc,argv)) {print_result(res::type::II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(res::type::II);return 0;}
    int exit_code=config_main();
    return exit_code;
}