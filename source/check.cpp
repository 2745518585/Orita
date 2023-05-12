#include"run.hpp"
json make_cor_argu()
{
    json cor_argu={
        {"f",{_not_define,3}},
        {"if",{_not_define,1}},
        {"of",{_not_define,1}},
        {"af",{_not_define,1}},
        {"c",{_not_define,0,1}},
        {"n",{_not_define,1}},
        {"t",{_not_define,1}}
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
    if(get_sum_argu("f")==3)
    {
        if(find_file(add_namesuf(get_file(get_argu("f",1)),".cpp"))) {print_result(_in_name,_NF);return 0;}
        if(find_file(add_namesuf(get_file(get_argu("f",2)),".cpp"))) {print_result(_out_name,_NF);return 0;}
        if(find_file(add_namesuf(get_file(get_argu("f",3)),".cpp"))) {print_result(_ans_name,_NF);return 0;}
        add_file(_check_in,get_argu("f",1));
        add_file(_check_out,get_argu("f",2));
        add_file(_check_ans,get_argu("f",3));
    }
    else
    {
        if(get_sum_argu("if")==1)
        {
            if(find_file(add_namesuf(get_file(get_argu("if",1)),".cpp"))) {print_result(_in_name,_NF);return 0;}
            add_file(_check_in,get_argu("if",1));
        }
        if(get_sum_argu("of")==1)
        {
            if(find_file(add_namesuf(get_file(get_argu("of",1)),".cpp"))) {print_result(_out_name,_NF);return 0;}
            add_file(_check_out,get_argu("of",1));
        }
        if(get_sum_argu("af")==1)
        {
            if(find_file(add_namesuf(get_file(get_argu("af",1)),".cpp"))) {print_result(_ans_name,_NF);return 0;}
            add_file(_check_ans,get_argu("af",1));
        }
    }
    bool use_checker=false;
    if(get_sum_argu("c")!=-1)
    {
        if(get_sum_argu("c")==1)
        {
            if(find_file(add_namesuf(get_file(get_argu("c",1)),".cpp"))) {print_result(_chk_name,_NF);return 0;}
            add_file(_check_chk,get_argu("c",1));
        }
        use_checker=true;
    }
    // init time
    if(get_sum_argu("t")==1) change_time_limit(stoi(get_argu("t",1)));
    // init total sum
    if(get_sum_argu("n")==-1)
    {
        print_result(_SS);
        return 0;
    }
    int total_sum=stoi(get_argu("n",1));
    // init data dir
    ssystem("rmdir /S /Q data"+system_to_nul);
    ssystem("mkdir data"+system_to_nul);
    ssystem("mkdir data"+sPS+"others"+system_to_nul);
    // find file
    if(find_filestr(_check_in)) {print_result(_in_name,_NF);return 0;}
    if(find_filestr(_check_out)) {print_result(_out_name,_NF);return 0;}
    if(find_filestr(_check_ans)) {print_result(_ans_name,_NF);return 0;}
    if(use_checker&&find_filestr(_check_chk)) {print_result(_chk_name,_NF);return 0;}
    std::string in,out,ans,chk;
    in=add_namesuf(get_file(_check_in),".cpp");
    out=add_namesuf(get_file(_check_out),".cpp");
    ans=add_namesuf(get_file(_check_ans),".cpp");
    if(use_checker) chk=add_namesuf(get_file(_check_chk),".cpp");
    else chk=get_file("%1");
    if(find_file(in)) {print_result(_in_name,_NF);return 0;}
    if(find_file(out)) {print_result(_out_name,_NF);return 0;}
    if(find_file(ans)) {print_result(_ans_name,_NF);return 0;}
    if(find_file(chk)) {print_result(_chk_name,_NF);return 0;}
    // compile file
    printer loading_printer({"Compiling.","Compiling..","Compiling..."},150);
    loading_printer.start();
    compiler *run_compiler=new compiler(4);
    run_compiler->add({{_in_name,in},{_out_name,out},{_ans_name,ans},{_chk_name,chk}},"-D JUDGING");
    run_compiler->wait({_in_name,_out_name,_ans_name,_chk_name});
    {
        auto compile_result=run_compiler->get({_in_name,_out_name,_ans_name,_chk_name});
        if(compile_result.first)
        {
            loading_printer.stop();
            print_result(compile_result.second,_CE);
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
            change_color("grey");
            std::cout<<" Unaccepted ";
            change_color("red");
            std::cout<<runned_sum-ac_sum<<" ";
            change_color("default");
        }
        std::cout<<"\n";
        ssystem("mkdir data"+sPS+"others"+sPS+std::to_string(i)+system_to_nul);
        std::string in_file="data"+sPS+"others"+sPS+std::to_string(i)+sPS+std::to_string(i)+".in",out_file="data"+sPS+"others"+sPS+std::to_string(i)+sPS+std::to_string(i)+".out",ans_file="data"+sPS+"others"+sPS+std::to_string(i)+sPS+std::to_string(i)+".ans",chk_file="data"+sPS+"others"+sPS+std::to_string(i)+sPS+std::to_string(i)+".txt";
        runner in_runner(in,"",in_file,std::to_string(i));
        if(in_runner.run()) {print_result(_in_name,_TO,in_runner.time);continue;}
        if(in_runner.exit_code) {print_result(_in_name,_RE,0,in_runner.exit_code);continue;}
        runner out_runner(out,in_file,out_file);
        if(out_runner.run()) {print_result(_out_name,_TO,out_runner.time);continue;}
        if(out_runner.exit_code) {print_result(_out_name,_RE,0,out_runner.exit_code);continue;}
        judger ans_judger(ans,chk,in_file,out_file,ans_file,chk_file);
        ans_judger.judge();
        ans_judger.print_result();
        std::ofstream output_chk_file(chk_file,std::ios::app);
        output_chk_file<<"\n";
        for(int j=1;j<=50;++j) output_chk_file<<"*";
        output_chk_file<<"\n";
        output_chk_file<<"    "<<_in_name<<":  "<<"time: "<<in_runner.time<<"ms, exit_code: "<<in_runner.exit_code<<"\n";
        output_chk_file<<"    "<<_out_name<<":  "<<"time: "<<out_runner.time<<"ms, exit_code: "<<out_runner.exit_code<<"\n";
        output_chk_file<<"    "<<_ans_name<<":  "<<"result: "<<get_resultname(ans_judger.result)<<", time: "<<ans_judger.time<<"ms, exit_code: "<<ans_judger.exit_code<<"\n";
        output_chk_file<<"    "<<_chk_name<<":  "<<"time: "<<ans_judger.chk_time<<"ms, exit_code: "<<ans_judger.chk_exit_code<<"\n";
        for(int j=1;j<=50;++j) output_chk_file<<"*";
        output_chk_file.close();
        if(!ans_judger.result.isnull()) ++runned_sum;
        if(ans_judger.result.istrue()) ++ac_sum;
        if(ans_judger.result.isfalse())
        {
            ssystem("move data"+sPS+"others"+sPS+std::to_string(i)+" data"+system_to_nul);
            ssystem("ren data"+sPS+std::to_string(i)+" \""+std::to_string(i)+" - "+get_short_resultname(ans_judger.result)+"\""+system_to_nul);
        }
    }
    std::cout<<"\n"<<ac_sum<<" / "<<runned_sum<<"\n\n";
    return 0;
}
int main(int argc,char **argv)
{
    if(init_argu(argc,argv)) {print_result(_II);return 0;}
    if(check_argu(cor_argu)) {print_result(_II);return 0;}
    int exit_code=check_main();
    return exit_code;
}