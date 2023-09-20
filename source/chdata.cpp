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
    fil in_file=check_file(argus["f"][1],argus["if"][1]);
    fil out_file=check_file(argus["f"][2],argus["of"][1]);
    if(in_file!=fil()&&!in_file.exists()) {print_result(res::type::NF);return 0;}
    if(out_file!=fil()&&!out_file.exists()) {print_result(res::type::NF);return 0;}
    if(in_file!=fil()) in_file.copyTo(default_infile.path());
    if(out_file!=fil()) out_file.copyTo(default_outfile.path());
    if(argus["s"].appear())
    {
        show_cursor();
        char str;
        FILE *file=sfopen(default_infile.path(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
        sfclose(file);
        file=sfopen(default_outfile.path(),"w");
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