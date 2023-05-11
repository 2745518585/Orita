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
        {"e",{_not_define,0}},
        {"p",{_not_define,0}},
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
    // init monitor
    bool use_monitor=false;
    if(get_sum_argu("e")!=-1) use_monitor=true;
    // init compare
    bool use_compare=false;
    if(get_sum_argu("p")!=-1) use_compare=true;
    // init data dir
    ssystem("mkdir data"+system_to_nul);
    ssystem("del /Q data"+sPS+"*"+system_to_nul);
    // find file
    if(find_filestr(_check_in)) {print_result(_in_name,_NF);return 0;}
    if(find_filestr(_check_out)) {print_result(_out_name,_NF);return 0;}
    if(find_filestr(_check_ans)) {print_result(_ans_name,_NF);return 0;}
    if(use_checker&&find_filestr(_check_chk)) {print_result(_chk_name,_NF);return 0;}
    std::string in,out,ans,chk;
    in=add_namesuf(get_file(_check_in),".cpp");
    out=add_namesuf(get_file(_check_out),".cpp");
    ans=add_namesuf(get_file(_check_ans),".cpp");
    if(use_compare) chk=get_file("%0");
    else if(use_checker) chk=add_namesuf(get_file(_check_chk),".cpp");
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
        for(int j=1;j<=50;++j) std::cout<<"=";
        for(int j=1;j<=50;++j) std::cout<<"\b";
        std::cout<<"#"<<i;
        if(runned_sum-ac_sum!=0)
        {
            for(int j=1;j<=30-std::to_string(i).size();++j) std::cout<<"=";
            change_color("grey");
            std::cout<<" Unaccepted ";
            change_color("red");
            std::cout<<runned_sum-ac_sum<<" ";
            change_color("white");
        }
        std::cout<<"\n";
        if(use_compare)
        {
            if(use_monitor)
            {
                monitor_runner run_runner(in," > \""+appdata_path+sPS+"data"+sPS+"data.in\" "+std::to_string(i));
                if(run_runner.run()) {print_result(_in_name,_TLE_O,get_time_limit()*2);continue;}
                if(run_runner.exit_code) {print_result(_in_name,_RE,0,run_runner.exit_code);continue;}
            }
            else ssystem("\""+get_exefile(in)+"\" > \""+appdata_path+sPS+"data"+sPS+"data.in\" "+std::to_string(i));
            monitor_judger run_judger1(out,get_file("%0"),"","",appdata_path+sPS+"data"+sPS+"data.out","");
            print_result(_ans_name+"1");
            run_judger1.judge();
            run_judger1.print_result();
            monitor_judger run_judger2(ans,get_file("%0"),"","",appdata_path+sPS+"data"+sPS+"data.ans","");
            print_result(_ans_name+"2");
            run_judger2.judge();
            run_judger2.print_result();
            ++runned_sum;
            if(run_judger1.result.istrue()&&run_judger2.result.istrue())
            {
                if(compare(appdata_path+sPS+"data"+sPS+"data.ans",appdata_path+sPS+"data"+sPS+"data.out"))
                {
                    print_result(_DA);
                    copy_result("data"+sPS+"data.in","data"+sPS+std::to_string(i)+".in");
                    copy_result("data"+sPS+"data.out","data"+sPS+std::to_string(i)+".out");
                    copy_result("data"+sPS+"data.ans","data"+sPS+std::to_string(i)+".ans");
                    copy_result("data"+sPS+"data.txt","data"+sPS+std::to_string(i)+".txt");
                }
                else print_result(_SA),++ac_sum;
            }
        }
        else
        {
            if(use_monitor)
            {
                monitor_runner run_runner1(in," > \""+appdata_path+sPS+"data"+sPS+"data.in\" "+std::to_string(i));
                if(run_runner1.run()) {print_result(_in_name,_TLE_O,get_time_limit()*2);continue;}
                if(run_runner1.exit_code) {print_result(_in_name,_RE,0,run_runner1.exit_code);continue;}
                monitor_runner run_runner2(out," < \""+appdata_path+sPS+"data"+sPS+"data.in\" > \""+appdata_path+sPS+"data"+sPS+"data.out\"");
                if(run_runner2.run()) {print_result(_out_name,_TLE_O,get_time_limit()*2);continue;}
                if(run_runner2.exit_code) {print_result(_out_name,_RE,0,run_runner2.exit_code);continue;}
                ++runned_sum;
            }
            else
            {
                ssystem("\""+get_exefile(in)+"\" > \""+appdata_path+sPS+"data"+sPS+"data.in\" "+std::to_string(i));
                ssystem("\""+get_exefile(out)+"\" < \""+appdata_path+sPS+"data"+sPS+"data.in\" > \""+appdata_path+sPS+"data"+sPS+"data.out\"");
                ++runned_sum;
            }
            monitor_judger run_judger(ans,chk);
            run_judger.judge();
            run_judger.print_result();
            if(run_judger.result.isfalse())
            {
                copy_result("data"+sPS+"data.in","data"+sPS+std::to_string(i)+".in");
                copy_result("data"+sPS+"data.out","data"+sPS+std::to_string(i)+".out");
                copy_result("data"+sPS+"data.ans","data"+sPS+std::to_string(i)+".ans");
                copy_result("data"+sPS+"data.txt","data"+sPS+std::to_string(i)+".txt");
            }
            else ++ac_sum;
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