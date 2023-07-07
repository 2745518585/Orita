#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{arguer::ND,2}},
        {"if",{arguer::ND,1}},
        {"of",{arguer::ND,1}},
        {"s",{arguer::ND,0,1}},
        {"t",{arguer::ND,1}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
int chdata_main()
{
    std::string in_file=check_file(argus["f"].get(1),argus["if"].get(1));
    std::string out_file=check_file(argus["f"].get(2),argus["of"].get(1));
    if(in_file!=""&&find_file(in_file)) {print_result(res::type::NF);return 0;}
    if(out_file!=""&&find_file(out_file)) {print_result(res::type::NF);return 0;}
    if(in_file!="") copy_file(in_file,makepath(appdata_path,"data","data.in"));
    if(out_file!="") copy_file(out_file,makepath(appdata_path,"data","data.out"));
    if(argus["s"].appear())
    {
        char str;
        FILE *file=fopen((makepath(appdata_path,"data","data.in")).c_str(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
        file=fopen((makepath(appdata_path,"data","data.out")).c_str(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
    }
    if(argus["t"].size()>=1) change_time_limit((tim)stoi(argus["t"][1]));
    print_result(res::type::SS);
    return 0;
}
int main(int argc,char **argv)
{
    if(argus.init_argu(argc,argv)) {print_result(res::type::II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(res::type::II);return 0;}
    int exit_code=chdata_main();
    return exit_code;
}