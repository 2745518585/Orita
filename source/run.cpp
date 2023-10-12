#pragma once
#ifndef _COMMAND_RUN
#define _COMMAND_RUN _COMMAND_RUN
#include"orita.hpp"
class Command_run: public App
{
  protected:
    void defineOptions(Poco::Util::OptionSet &options)
    {
        options.addOption(Poco::Util::Option("help","h","display help information").noArgument());
        options.addOption(Poco::Util::Option("file","f","specify ans").argument("file",true));
        options.addOption(Poco::Util::Option("checker","c","specify checker").argument("file",true));
        options.addOption(Poco::Util::Option("time","t","change time limit").argument("time",true));
        App::defineOptions(options);
    }
    void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        helpFormatter->setHeader("Orita - Run");
        helpFormatter->setCommand("orita run");
        helpFormatter->setUsage("[options]\n");
        helpFormatter->setFooter(" ");
        helpFormatter->format(std::cout);
    }
    int main(const std::vector<std::string>& args)
    {
        loadConfiguration();
        if(check_option("error options")) return EXIT_USAGE;
        if(check_option("help")) return EXIT_OK;
        INFO("args",vec_to_str(args,static_cast<std::string(*)(const std::string&)>(add_squo)));


        const std::string _ans_name="ans";
        const std::string _chk_name="checker";
        fil in_file=default_infile;
        fil out_file=default_outfile;
        fil ans_file=default_ansfile;
        fil chk_file=default_chkfile;
        // init name
        fil ans=[&]()
        {
            pat ans_str=check_file(get_option("file"),_run_ans);
            add_file(_run_ans,ans_str);
            return add_namesuf(get_file(ans_str),"cpp");
        }();
        fil chk=[&]()
        {
            pat chk_str=check_file(get_option("checker"),_run_chk);
            add_file(_run_chk,chk_str);
            return add_namesuf(get_file(chk_str),"cpp");
        }();
        // init time
        if(check_option("time")) change_time_limit((tim)std::stoi(get_option("time")));
        // find file
        if(ans==fil()||!ans.exists()) {print_result(_ans_name,res::type::NF);return EXIT_NOINPUT;}
        if(chk==fil()||!chk.exists()) {print_result(_chk_name,res::type::NF);return EXIT_NOINPUT;}
        if(show_file_info) scout<<termcolor::bright_grey<<print_type({"","","\n"},{{_ans_name+": ",ans},{_chk_name+": ",chk}},true)<<ANSI::move_up*2<<termcolor::reset;
        // compile file
        printer *print=new printer({"Compiling.","Compiling..","Compiling..."},(tim)150);
        print->start();
        compiler *run_compiler=new compiler(2);
        run_compiler->add({{_ans_name,ans},{_chk_name,chk}},data_compile_argu);
        run_compiler->wait({_ans_name,_chk_name});
        {
            auto compile_result=run_compiler->get({_ans_name,_chk_name});
            if(compile_result.first)
            {
                delete print;
                print_result(compile_result.second,res::type::CE);
                return EXIT_OK;
            }
        }
        delete run_compiler;
        delete print;
        // run
        judger run_judger(ans,chk,in_file,out_file,ans_file,chk_file);
        run_judger.judge();
        // print result
        run_judger.print_result();
        sofstream output_chk_file(chk_file,std::ios::app);
        output_chk_file<<"\n"<<std::string("*")*50<<"\n";
        output_chk_file<<"    result: "<<run_judger.result<<"\n";
        output_chk_file<<print_type({"    "," time: "," exit_code: ","\n"},{{_ans_name+":",run_judger.time,run_judger.exit_code},{_chk_name+":",run_judger.chk_time,run_judger.chk_exit_code}});
        output_chk_file<<std::string("*")*50;
        output_chk_file.close();
        // copy result
        print=new printer({"Copying.","Copying..","Copying..."},(tim)150);
        print->start();
        try
        {
            default_data_dir.createDirectory();
            in_file.copyTo((default_data_dir/"data.in").path());
            out_file.copyTo((default_data_dir/"data.out").path());
            ans_file.copyTo((default_data_dir/"data.ans").path());
            chk_file.copyTo((default_data_dir/"data.txt").path());
            INFO("copy result",add_squo(default_data_dir.path()));
        }
        catch(...) {WARN("copy result - fail",add_squo(default_data_dir.path()));}
        delete print;
        return EXIT_OK;
    }
};
#endif