#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{arguer::ND,1}},
        {"c",{arguer::ND,0,1}},
        {"t",{arguer::ND,1}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
const std::string _ans_name="ans";
const std::string _chk_name="checker";
std::string in_file=makepath(appdata_path,"data","data.in");
std::string out_file=makepath(appdata_path,"data","data.out");
std::string ans_file=makepath(appdata_path,"data","data.ans");
std::string chk_file=makepath(appdata_path,"data","data.txt");
int run_main()
{
    // init name
    std::string ans,chk;
    {
        const std::string ans_str=check_file(argus["f"].get(1),_run_ans);
        add_file(_run_ans,ans_str);
        ans=add_namesuf(get_file(ans_str),".cpp");
    }
    if(argus["c"].appear())
    {
        const std::string chk_str=check_file(argus["c"].get(1),_run_chk);
        add_file(_run_chk,chk_str);
        chk=add_namesuf(get_file(chk_str),".cpp");
    }
    else chk=add_namesuf(get_file(default_checker),".cpp");
    // init time
    if(argus.get_sum_argu("t")==1) change_time_limit((tim)stoi(argus["t"][1]));
    // find file
    if(find_file(ans)) {print_result(_ans_name,res::type::NF);return 0;}
    if(find_file(chk)) {print_result(_chk_name,res::type::NF);return 0;}
    // compile file
    printer loading_printer({"Compiling.","Compiling..","Compiling..."},(tim)150);
    loading_printer.start();
    compiler *run_compiler=new compiler(2);
    run_compiler->add({{_ans_name,ans},{_chk_name,chk}},compile_argu+" -D JUDGING");
    run_compiler->wait({_ans_name,_chk_name});
    {
        auto compile_result=run_compiler->get({_ans_name,_chk_name});
        if(compile_result.first)
        {
            loading_printer.stop();
            print_result(compile_result.second,res::type::CE);
            return 0;
        }
    }
    delete run_compiler;
    loading_printer.stop();
    // run
    judger run_judger(ans,chk,in_file,out_file,ans_file,chk_file);
    run_judger.judge();
    // print result
    run_judger.print_result();
    std::ofstream output_chk_file(chk_file,std::ios::app);
    output_chk_file<<"\n";
    for(int j=1;j<=50;++j) output_chk_file<<"*";
    output_chk_file<<"\n";
    output_chk_file<<"    result: "<<get_resultname(run_judger.result)<<"\n";
    output_chk_file<<"    "<<_ans_name<<":  "<<"time: "<<run_judger.time<<", exit_code: "<<run_judger.exit_code<<"\n";
    output_chk_file<<"    "<<_chk_name<<":  "<<"time: "<<run_judger.chk_time<<", exit_code: "<<run_judger.chk_exit_code<<"\n";
    for(int j=1;j<=50;++j) output_chk_file<<"*";
    output_chk_file.close();
    // copy result
    make_dir("data");
    copy_file(in_file,makepath("data","data.in"));
    copy_file(out_file,makepath("data","data.out"));
    copy_file(ans_file,makepath("data","data.ans"));
    copy_file(chk_file,makepath("data","data.txt"));
    return 0;
}
int main(int argc,char **argv)
{
    if(argus.init_argu(argc,argv)) {print_result(res::type::II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(res::type::II);return 0;}
    int exit_code=run_main();
    return exit_code;
}