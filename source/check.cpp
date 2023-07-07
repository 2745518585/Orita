#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{arguer::ND,3}},
        {"if",{arguer::ND,1}},
        {"of",{arguer::ND,1}},
        {"af",{arguer::ND,1}},
        {"c",{arguer::ND,0,1}},
        {"n",{arguer::ND,1}},
        {"t",{arguer::ND,1}}
    };
    return cor_argu;
}
json cor_argu=make_cor_argu();
const std::string _in_name="data_maker";
const std::string _out_name="std";
const std::string _ans_name="ans";
const std::string _chk_name="checker";
int check_main()
{
    // init name
    std::string in,out,ans,chk;
    {
        const std::string in_str=check_file(argus["f"].get(1),argus["if"].get(1),_check_in);
        add_file(_check_in,in_str);
        in=add_namesuf(get_file(in_str),".cpp");
    }
    {
        const std::string out_str=check_file(argus["f"].get(2),argus["of"].get(1),_check_out);
        add_file(_check_out,out_str);
        out=add_namesuf(get_file(out_str),".cpp");
    }
    {
        const std::string ans_str=check_file(argus["f"].get(3),argus["af"].get(1),_check_ans);
        add_file(_check_ans,ans_str);
        ans=add_namesuf(get_file(ans_str),".cpp");
    }
    if(argus["c"].appear())
    {
        const std::string chk_str=check_file(argus["c"].get(1),_check_chk);
        add_file(_check_chk,chk_str);
        chk=add_namesuf(get_file(chk_str),".cpp");
    }
    else chk=add_namesuf(get_file("%1"),".cpp");
    // init time
    if(argus["t"].size()==1) change_time_limit((tim)stoi(argus["t"][1]));
    // init total sum
    if(argus["n"].not_appear())
    {
        print_result(res::type::SS);
        return 0;
    }
    int total_sum=stoi(argus["n"][1]);
    // init data dir
    remove_dir("data");
    make_dir("data");
    make_dir(makepath("data","datas"));
    // find file
    if(find_file(in)) {print_result(_in_name,res::type::NF);return 0;}
    if(find_file(out)) {print_result(_out_name,res::type::NF);return 0;}
    if(find_file(ans)) {print_result(_ans_name,res::type::NF);return 0;}
    if(find_file(chk)) {print_result(_chk_name,res::type::NF);return 0;}
    // compile file
    printer loading_printer({"Compiling.","Compiling..","Compiling..."},(tim)150);
    loading_printer.start();
    compiler *run_compiler=new compiler(4);
    run_compiler->add({{_in_name,in},{_out_name,out},{_ans_name,ans},{_chk_name,chk}},get_compile_argu()+" -D JUDGING");
    run_compiler->wait({_in_name,_out_name,_ans_name,_chk_name});
    {
        auto compile_result=run_compiler->get({_in_name,_out_name,_ans_name,_chk_name});
        if(compile_result.first)
        {
            loading_printer.stop();
            print_result(compile_result.second,res::type::CE);
            return 0;
        }
    }
    delete run_compiler;
    loading_printer.stop();
    // check
    int ac_sum=0,runned_sum=0;
    for(int i=1;i<=total_sum;++i)
    {
        for(int j=1;j<=50;++j) std::cout<<"-";
        for(int j=1;j<=50;++j) std::cout<<"\b";
        std::cout<<"#"<<i;
        if(runned_sum-ac_sum!=0)
        {
            for(int j=1;j<=30-std::to_string(i).size();++j) std::cout<<"-";
            std::cout<<termcolor::bright_grey<<" Unaccepted "<<termcolor::bright_red<<runned_sum-ac_sum<<" "<<termcolor::reset;
        }
        std::cout<<"\n";
        #define run_dir "data","datas",std::to_string(i)
        make_dir(makepath(run_dir));
        std::string in_file=makepath(run_dir,"data.in"),out_file=makepath(run_dir,"data.out"),ans_file=makepath(run_dir,"data.ans"),chk_file=makepath(run_dir,"data.txt");
        runner in_runner(in,system_nul,in_file,std::to_string(i));
        if(in_runner.run()) {print_result(_in_name,res::type::TO,in_runner.time);continue;}
        if(in_runner.exit_code) {print_result(_in_name,res::type::RE,(tim)0,in_runner.exit_code);continue;}
        runner out_runner(out,in_file,out_file);
        if(out_runner.run()) {print_result(_out_name,res::type::TO,out_runner.time);continue;}
        if(out_runner.exit_code) {print_result(_out_name,res::type::RE,(tim)0,out_runner.exit_code);continue;}
        judger ans_judger(ans,chk,in_file,out_file,ans_file,chk_file);
        ans_judger.judge();
        ans_judger.print_result();
        std::ofstream output_chk_file(chk_file,std::ios::app);
        output_chk_file<<"\n";
        for(int j=1;j<=50;++j) output_chk_file<<"*";
        output_chk_file<<"\n";
        output_chk_file<<"    result: "<<get_resultname(ans_judger.result)<<"\n";
        output_chk_file<<"    "<<_in_name<<":  "<<"time: "<<in_runner.time<<", exit_code: "<<in_runner.exit_code<<"\n";
        output_chk_file<<"    "<<_out_name<<":  "<<"time: "<<out_runner.time<<", exit_code: "<<out_runner.exit_code<<"\n";
        output_chk_file<<"    "<<_ans_name<<":  "<<"time: "<<ans_judger.time<<", exit_code: "<<ans_judger.exit_code<<"\n";
        output_chk_file<<"    "<<_chk_name<<":  "<<"time: "<<ans_judger.chk_time<<", exit_code: "<<ans_judger.chk_exit_code<<"\n";
        for(int j=1;j<=50;++j) output_chk_file<<"*";
        output_chk_file.close();
        if(!ans_judger.result.isnull()) ++runned_sum;
        if(ans_judger.result.istrue()) ++ac_sum;
        if(ans_judger.result.isfalse())
        {
            move_file(makepath(run_dir),makepath("data",std::to_string(i)+" - "+get_short_resultname(ans_judger.result)));
        }
    }
    std::cout<<"\n"<<ac_sum<<" / "<<runned_sum<<"\n\n";
    return 0;
}
int main(int argc,char **argv)
{
    if(argus.init_argu(argc,argv)) {print_result(res::type::II);return 0;}
    if(argus.check_argu(cor_argu)) {print_result(res::type::II);return 0;}
    int exit_code=check_main();
    return exit_code;
}