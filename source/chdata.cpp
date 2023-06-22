#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{_not_define,2}},
        {"if",{_not_define,1}},
        {"of",{_not_define,1}},
        {"s",{_not_define,0,1}},
        {"t",{_not_define,1}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
int chdata_main()
{
    std::string in_file=check_file(argus["f"].get(1),argus["if"].get(1));
    std::string out_file=check_file(argus["f"].get(2),argus["of"].get(1));
    if(in_file!=""&&find_file(in_file)) {print_result(_NF);return 0;}
    if(out_file!=""&&find_file(out_file)) {print_result(_NF);return 0;}
    if(in_file!="") copy_file(in_file,makepath(appdata_path,"data","data.in"));
    if(out_file!="") copy_file(out_file,makepath(appdata_path,"data","data.out"));
    if(argus["s"].sum()!=-1)
    {
        char str;
        FILE *file=fopen((makepath(appdata_path,"data","data.in")).c_str(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
        file=fopen((makepath(appdata_path,"data","data.out")).c_str(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
    }
    if(argus["t"].sum()>=1) change_time_limit(stoi(argus["t"][1]));
    print_result(_SS);
    return 0;
}
int main(int argc,char **argv)
{
    if(argus.init_argu(argc,argv)) {print_result(_II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(_II);return 0;}
    int exit_code=chdata_main();
    return exit_code;
}