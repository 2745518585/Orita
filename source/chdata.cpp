#include"run.hpp"
const json make_cor_argu()
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
const json cor_argu=make_cor_argu();
int chdata_main()
{
    pat in_file=check_file(argus["f"].get(1),argus["if"].get(1));
    pat out_file=check_file(argus["f"].get(2),argus["of"].get(1));
    if(in_file!=""&&!std::filesystem::exists(in_file)) {print_result(res::type::NF);return 0;}
    if(out_file!=""&&!std::filesystem::exists(out_file)) {print_result(res::type::NF);return 0;}
    if(in_file!="") std::filesystem::copy_file(in_file,get_file(default_infile),std::filesystem::copy_options::overwrite_existing);
    if(out_file!="") std::filesystem::copy_file(out_file,get_file(default_outfile),std::filesystem::copy_options::overwrite_existing);
    if(argus["s"].appear())
    {
        show_cursor();
        char str;
        FILE *file=sfopen(get_file(default_infile).string(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
        sfclose(file);
        file=sfopen(get_file(default_outfile).string(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
        sfclose(file);
        hide_cursor();
    }
    if(argus["t"].size()==1) change_time_limit((tim)stoi(argus["t"][1]));
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