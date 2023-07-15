#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{arguer::ND,1}},
        {"c",{arguer::ND,0,1}},
        {"t",{arguer::ND,1}},
        {"d",{arguer::NL}},
        {"is",{arguer::ND,1}},
        {"os",{arguer::ND,1}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
const std::string _ans_name="ans";
const std::string _chk_name="checker";
int judge_main()
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
    else chk=add_namesuf(get_file("%1"),".cpp");
    // init time
    if(argus["t"].size()==1) change_time_limit((tim)stoi(argus["t"][1]));
    // init data
    if(argus["d"].not_appear())
    {
        print_result(res::type::SS);
        return 0;
    }
    // find file
    if(find_file(ans)) {print_result(_ans_name,res::type::NF);return 0;}
    if(find_file(chk)) {print_result(_chk_name,res::type::NF);return 0;}
    // compile file
    printer loading_printer({"Compiling.","Compiling..","Compiling..."},(tim)150);
    loading_printer.start();
    compiler *run_compiler=new compiler(2);
    run_compiler->add({{_ans_name,ans},{_chk_name,chk}},get_compile_argu()+" -D JUDGING");
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
    // find data
    const std::string in_file_suf=argus["is"].size()==1?argus["is"][1]:".in",out_file_suf=argus["os"].size()==1?argus["os"][1]:".out";
    json datas;
    for(auto i:argus["d"])
    {
        if(i.is_null()) continue;
        std::string file=i;
        if(get_filenamesuf(file)==in_file_suf)
        {
            datas[get_filepre(file)]["in"]=file;
        }
        if(get_filenamesuf(file)==out_file_suf)
        {
            datas[get_filepre(file)]["out"]=file;
        }
    }
    // judge
    remove_dir("data");
    make_dir("data");
    make_dir(makepath("data","datas"));
    int runned_sum=0,ac_sum=0;
    for(auto i:datas.items())
    {
        // init file
        if(i.value()["in"].is_null()&&i.value()["out"].is_null()) continue;
        for(int j=1;j<=50;++j) std::cout<<"-";
        std::cout<<"\r"<<"#"<<(std::string)i.key()<<"\n";
        ++runned_sum;
        #define run_dir "data","datas",std::to_string(runned_sum)
        std::string in_file=system_nul,out_file=system_nul,ans_file=makepath(run_dir,"data.ans"),chk_file=makepath(run_dir,"data.txt");
        make_dir(makepath(run_dir));
        if(!i.value()["in"].is_null()) copy_file((std::string)i.value()["in"],in_file=makepath(run_dir,"data.in"));
        if(!i.value()["out"].is_null()) copy_file((std::string)i.value()["out"],out_file=makepath(run_dir,"data.out"));
        // judge
        judger run_judger(ans,chk,in_file,out_file,ans_file,chk_file);
        run_judger.judge();
        run_judger.print_result();
        // print result
        std::ofstream output_chk_file(chk_file,std::ios::app);
        output_chk_file<<"\n";
        for(int j=1;j<=50;++j) output_chk_file<<"*";
        output_chk_file<<"\n";
        output_chk_file<<"    infile: "<<add_quo(i.value()["in"].is_null()?"nul":(std::string)i.value()["in"])<<", outfile: "<<add_quo(i.value()["out"].is_null()?"nul":(std::string)i.value()["out"])<<"\n";
        output_chk_file<<"    result: "<<get_resultname(run_judger.result)<<"\n";
        output_chk_file<<"    "<<_ans_name<<":  "<<"time: "<<run_judger.time<<", exit_code: "<<run_judger.exit_code<<"\n";
        output_chk_file<<"    "<<_chk_name<<":  "<<"time: "<<run_judger.chk_time<<", exit_code: "<<run_judger.chk_exit_code<<"\n";
        for(int j=1;j<=50;++j) output_chk_file<<"*";
        output_chk_file.close();
        // copy result
        if(run_judger.result.istrue()) ++ac_sum;
        if(run_judger.result.isfalse())
        {
            move_file(makepath(run_dir),makepath("data",std::to_string(runned_sum)+" - "+get_short_resultname(run_judger.result)));
        }
        #undef run_dir
    }
    std::cout<<ac_sum<<" / "<<runned_sum;
    return 0;
}
int main(int argc,char **argv)
{
    if(argus.init_argu(argc,argv)) {print_result(res::type::II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(res::type::II);return 0;}
    int exit_code=judge_main();
    return exit_code;
}