#pragma once
#ifndef _COMMAND_JUDGE
#define _COMMAND_JUDGE _COMMAND_JUDGE
#include"orita.hpp"
class Command_judge: public App
{
  protected:
    void defineOptions(Poco::Util::OptionSet &options)
    {
        options.addOption(Poco::Util::Option("help","h","display help information").noArgument());
        options.addOption(Poco::Util::Option("file","f","specify ans").argument("file",true));
        options.addOption(Poco::Util::Option("checker","c","specify checker").argument("file",true));
        options.addOption(Poco::Util::Option("time","t","change time limit").argument("time",true));
        options.addOption(Poco::Util::Option("isuf","is","specify input file suf").argument("suf",true));
        options.addOption(Poco::Util::Option("osuf","os","specify output file suf").argument("suf",true));
        App::defineOptions(options);
    }
    void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        helpFormatter->setHeader("Orita - Judge");
        helpFormatter->setCommand("orita judge");
        helpFormatter->setUsage("[data] [options]\n");
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
        // init data
        if(args.size()==0)
        {
            print_result(res::type::SS);
            return EXIT_OK;
        }
        // find file
        if(ans==fil()||!ans.exists()) {print_result(_ans_name,res::type::NF);return EXIT_NOINPUT;}
        if(chk==fil()||!chk.exists()) {print_result(_chk_name,res::type::NF);return EXIT_NOINPUT;}
        scout<<termcolor::bright_grey<<print_type({std::string(" ")*60,"","\n"},{{_ans_name+": ",ans},{_chk_name+": ",chk}})<<ANSI::move_up*2<<termcolor::reset;
        // compile file
        printer loading_printer({"Compiling.","Compiling..","Compiling..."},(tim)150);
        loading_printer.start();
        compiler *run_compiler=new compiler(2);
        run_compiler->add({{_ans_name,ans},{_chk_name,chk}},data_compile_argu);
        run_compiler->wait({_ans_name,_chk_name});
        {
            auto compile_result=run_compiler->get({_ans_name,_chk_name});
            if(compile_result.first)
            {
                loading_printer.stop();
                print_result(compile_result.second,res::type::CE);
                return EXIT_OK;
            }
        }
        delete run_compiler;
        loading_printer.stop();
        // find data
        const std::string in_file_suf=get_option("isuf","in"),out_file_suf=get_option("osuf","out");
        json datas,data_sum;
        for(auto i:args)
        {
            pat file=i;
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
            if(default_data_dir.exists()) default_data_dir.remove(true);
            default_data_dir.createDirectory();
            (default_data_dir/"datas").createDirectory();
            INFO("make data dir",add_squo(default_data_dir.path()));
        }
        catch(...)
        {
            ERROR("make data dir - fail",add_squo(default_data_dir.path()));
            throw Poco::Exception("fail make data dir");
        }
        // judge
        int runned_sum=0,ac_sum=0;
        for(auto i:datas.items())
        {
            // init file
            if(i.value()["in"].is_null()&&i.value()["out"].is_null()) continue;
            for(int j=1;j<=50;++j) scout<<"-";
            const std::string data_name=[&]()
            {
                std::string tmp=pat(i.key()).getFileName();
                if(!data_sum[data_name].is_null())
                {
                    data_sum[data_name]=(unsigned)data_sum[data_name]+1;
                    tmp+="("+std::to_string((unsigned)data_sum[data_name])+")";
                }
                else data_sum[data_name]=0;
                return tmp;
            }();
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
            output_chk_file<<"\n"<<std::string("*")*50<<"\n";
            output_chk_file<<"    infile: "<<add_quo(get_file(!i.value()["in"].is_null()?(std::string)i.value()["in"]:system_nul.toString()))<<", outfile: "<<add_quo(get_file(!i.value()["out"].is_null()?(std::string)i.value()["out"]:system_nul.toString()))<<"\n";
            output_chk_file<<"    result: "<<run_judger.result<<"\n";
            output_chk_file<<print_type({"    "," time: "," exit_code: ","\n"},{{_ans_name+":",run_judger.time,run_judger.exit_code},{_chk_name+":",run_judger.chk_time,run_judger.chk_exit_code}});
            output_chk_file<<std::string("*")*50;
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
        return EXIT_OK;
    }
};
#endif