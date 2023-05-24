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
    if(get_sum_argu("f")>=2)
    {
        std::string in_file=get_file(get_argu("f",1)),out_file=get_file(get_argu("f",2));
        if(find_file(in_file)||find_file(out_file))
        {
            print_result(_NF);
            return 0;
        }
        copy_file(in_file,appdata_path+sPS+"data"+sPS+"data.in");
        copy_file(out_file,appdata_path+sPS+"data"+sPS+"data.out");
    }
    else if(get_sum_argu("if")>=1||get_sum_argu("of")>=1)
    {
        std::string in_file,out_file;
        if(get_sum_argu("if")>=1)
        {
            in_file=get_file(get_argu("if",1));
            if(find_file(in_file))
            {
                print_result(_NF);
                return 0;
            }
        }
        if(get_sum_argu("of")>=1)
        {
            out_file=get_file(get_argu("of",1));
            if(find_file(out_file))
            {
                print_result(_NF);
                return 0;
            }
        }
        if(get_sum_argu("if")>=1) copy_file(in_file,appdata_path+sPS+"data"+sPS+"data.in");
        if(get_sum_argu("of")>=1) copy_file(out_file,appdata_path+sPS+"data"+sPS+"data.out");
    }
    else if(get_sum_argu("s")!=-1)
    {
        char str;
        FILE *file=fopen((appdata_path+sPS+"data"+sPS+"data.in").c_str(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
        file=fopen((appdata_path+sPS+"data"+sPS+"data.out").c_str(),"w");
        str=getchar();
        while(str!=EOF) fputc(str,file),str=getchar();
    }
    if(get_sum_argu("t")>=1)
    {
        change_time_limit(stoi(get_argu("t",1)));
    }
    print_result(_SS);
    return 0;
}
int main(int argc,char **argv)
{
    if(init_argu(argc,argv)) {print_result(_II);return 0;}
    if(check_argu(cor_argu)) {print_result(_II);return 0;}
    int exit_code=chdata_main();
    return exit_code;
}