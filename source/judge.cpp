#include"run.hpp"
const json make_cor_argu()
{
    json cor_argu={
        {"f",{arguer::ND,1}},
        {"c",{arguer::ND,1}},
        {"t",{arguer::ND,1}},
        {"d",{arguer::NL}},
        {"is",{arguer::ND,1}},
        {"os",{arguer::ND,1}}
    };
    return cor_argu;
}
const json cor_argu=make_cor_argu();
const std::string _ans_name="ans";
const std::string _chk_name="checker";
int judge_main()
{
    // init name
    fil ans=[]()
    {
        pat ans_str=check_file(argus["f"][1],_run_ans);
        add_file(_run_ans,ans_str);
        return add_namesuf(get_file(ans_str),"cpp");
    }();
    fil chk=[]()
    {
        pat chk_str=check_file(argus["c"][1],_run_chk);
        add_file(_run_chk,chk_str);
        return add_namesuf(get_file(chk_str),"cpp");
    }();
    // init time
    if(argus["t"].size()==1) change_time_limit((tim)stoi(argus["t"][1]));
    // init data
    if(argus["d"].not_appear())
    {
        print_result(res::type::SS);
        return 0;
    }
    // find name
    if(ans==fil()) {print_result(_ans_name,res::type::NF);return 0;}
    if(chk==fil()) {print_result(_chk_name,res::type::NF);return 0;}
    // find file
    if(!ans.exists()) {print_result(_ans_name,res::type::NF);return 0;}
    if(!chk.exists()) {print_result(_chk_name,res::type::NF);return 0;}
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
    // find data
    const std::string in_file_suf=check_file(argus["is"][1],".in").toString(),out_file_suf=check_file(argus["os"][1],".out").toString();
    json datas;
    for(auto i:argus["d"])
    {
        if(i.is_null()) continue;
        pat file=(std::string)i;
        if(file.getExtension()==in_file_suf)
        {
            datas[replace_extension(file).toString()]["in"]=file.toString();
        }
        if(file.getExtension()==out_file_suf)
        {
            datas[replace_extension(file).toString()]["out"]=file.toString();
        }
    }
    // init data dir
    try
    {
        default_data_dir.remove(true);
        default_data_dir.createDirectory();
        (default_data_dir/"datas").createDirectory();
        INFO("make data dir",add_squo(default_data_dir.path()));
    }
    catch(...)
    {
        ERROR("make data dir - fail",add_squo(default_data_dir.path()));
        class fail_make_data_dir {}error;
        throw error;
    }
    // judge
    int runned_sum=0,ac_sum=0;
    for(auto i:datas.items())
    {
        // init file
        if(i.value()["in"].is_null()&&i.value()["out"].is_null()) continue;
        for(int j=1;j<=50;++j) scout<<"-";
        const std::string data_name=i.key();
        scout<<"\r#"<<data_name<<"\n";
        ++runned_sum;
        fil run_dir=default_data_dir/"datas"/data_name;
        run_dir.createDirectory();
        fil in_file=system_nul,out_file=system_nul,ans_file=run_dir/"data.ans",chk_file=run_dir/"data.txt";
        if(!i.value()["in"].is_null()) ((fil)(std::string)i.value()["in"]).copyTo((in_file=run_dir/"data.in").path());
        if(!i.value()["out"].is_null()) ((fil)(std::string)i.value()["out"]).copyTo((out_file=run_dir/"data.out").path());
        // judge
        judger run_judger(ans,chk,in_file,out_file,ans_file,chk_file);
        run_judger.judge();
        run_judger.print_result();
        // print result
        sofstream output_chk_file(chk_file,std::ios::app);
        output_chk_file<<"\n";
        for(int j=1;j<=50;++j) output_chk_file<<"*";
        output_chk_file<<"\n";
        output_chk_file<<"    infile: "<<add_quo(get_file(!i.value()["in"].is_null()?(std::string)i.value()["in"]:system_nul.toString()))<<", outfile: "<<add_quo(get_file(!i.value()["out"].is_null()?(std::string)i.value()["out"]:system_nul.toString()))<<"\n";
        output_chk_file<<"    result: "<<get_resultname(run_judger.result)<<"\n";
        output_chk_file<<"    "<<_ans_name<<":  "<<"time: "<<run_judger.time<<", exit_code: "<<run_judger.exit_code<<"\n";
        output_chk_file<<"    "<<_chk_name<<":  "<<"time: "<<run_judger.chk_time<<", exit_code: "<<run_judger.chk_exit_code<<"\n";
        for(int j=1;j<=50;++j) output_chk_file<<"*";
        output_chk_file.close();
        // copy result
        if(run_judger.result.istrue()) ++ac_sum;
        if(run_judger.result.isfalse())
        {
            run_dir.copyTo((default_data_dir/(data_name+" - "+get_short_resultname(run_judger.result))).path());
        }
        #undef run_dir
    }
    scout<<ac_sum<<" / "<<runned_sum;
    return 0;
}
int main(int argc,char **argv)
{
    if(argus.init_argu(argc,argv)) {print_result(res::type::II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(res::type::II);return 0;}
    int exit_code=judge_main();
    return exit_code;
}