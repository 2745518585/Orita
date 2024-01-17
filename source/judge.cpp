#pragma once
#ifndef _COMMAND_JUDGE
#define _COMMAND_JUDGE
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
        options.addOption(Poco::Util::Option("multithread","mul","turn on multithreading").noArgument());
        options.addOption(Poco::Util::Option("dorecompile","dore","force recompile").noArgument());
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
        INFO("args",add_squo(args));

        
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
        // init config
        if(check_option("time")) change_time_limit((tim)std::stoi(get_option("time")));
        if(check_option("dorecompile")) if_skip_compiled=false;
        // init data
        if(args.size()==0)
        {
            print_result(res::type::SS);
            return EXIT_OK;
        }
        // save config
        save_config();
        // find file
        if(ans==fil()||!ans.exists()) {print_result(_ans_name,res::type::NF);return EXIT_NOINPUT;}
        if(chk==fil()||!chk.exists()) {print_result(_chk_name,res::type::NF);return EXIT_NOINPUT;}
        if(show_file_info) scout<<termcolor::bright_grey<<print_type({"","","\n"},{{_ans_name+": ",ans},{_chk_name+": ",chk}},true)<<ANSI::move_up*2<<termcolor::reset;
        // compile file
        printer *print=new printer({"Compiling.","Compiling..","Compiling..."},(tim)150);print->start();
        th_compiler *run_compiler=new th_compiler();
        run_compiler->add({{_ans_name,ans},{_chk_name,chk}},data_compile_argu);
        run_compiler->wait_all();
        {
            std::string name=run_compiler->get_all();
            if(name!="")
            {
                delete print;
                scerr<<run_compiler->list[name]->err;
                print_result(name,res::type::CE);
                return EXIT_OK;
            }
        }
        delete run_compiler;
        delete print;
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
        print=new printer({"Deleting.","Deleting..","Deleting..."},(tim)150);print->start();
        try
        {
            if(default_data_dir.exists()) default_data_dir.remove(true);
            default_data_dir.createDirectory();
            (default_data_dir/"datas").createDirectory();
            (default_data_dir/"tmp_data").createDirectory();
            INFO("make data dir",add_squo(default_data_dir.path()));
        }
        catch(exception &error)
        {
            ERROR("make data dir - fail",add_squo(default_data_dir.path()),add_squo(error.displayText()));
            throw exception("fail make data dir",add_squo(error.displayText()));
        }
        delete print;
        // judge
        if(check_option("multithread"))
        {
            ssetenv(".data.chk_outputs","\"off\"");
            unsigned ac_sum=0,runned_sum=0,add_sum=0,output_sum=0;
            th_judger run_judger;
            std::vector<std::string> judge_list;
            std::map<std::string,unsigned> num_list;
            for(auto i:datas.items()) judge_list.push_back(i.key()),num_list[i.key()]=judge_list.size();
            auto add=[&](const std::string &name)
            {
                if(datas[name]["in"].is_null()&&datas[name]["out"].is_null()) return;
                fil run_dir=default_data_dir/"tmp_data"/std::to_string(num_list[name]);
                run_dir.createDirectory();
                fil in_file=system_nul,out_file=system_nul,ans_file=run_dir/"data.ans",chk_file=run_dir/"data.txt";
                if(!datas[name]["in"].is_null()) ((fil)(std::string)datas[name]["in"]).copyTo((in_file=run_dir/"data.in").path());
                if(!datas[name]["out"].is_null()) ((fil)(std::string)datas[name]["out"]).copyTo((out_file=run_dir/"data.out").path());
                run_judger.add(name,(new judger(ans,chk,in_file,out_file,ans_file,chk_file)));
            };
            while(add_sum<max_thread_num&&add_sum<judge_list.size()) add(judge_list[add_sum++]);
            std::string name;
            while((name=run_judger.get_one())!="")
            {
                const std::string data_name=[&]()
                {
                    std::string tmp=pat(name).getFileName();
                    if(!data_sum[data_name].is_null())
                    {
                        data_sum[data_name]=(unsigned)data_sum[data_name]+1;
                        tmp+="("+std::to_string((unsigned)data_sum[data_name])+")";
                    }
                    else data_sum[data_name]=0;
                    return tmp;
                }();
                scout<<std::string("-")*50<<"\r#"<<data_name<<"\n";
                ++runned_sum;
                fil run_dir=default_data_dir/"datas"/data_name;
                (default_data_dir/"tmp_data"/std::to_string(num_list[name])).copyTo(run_dir.path());
                judger *target=run_judger.list[name];
                target->print_result("",_chk_name);
                sofstream output_chk_file(run_dir/"data.txt",std::ios::app);
                output_chk_file<<"\n"<<std::string("*")*50<<"\n";
                output_chk_file
                <<"    infile: "<<add_squo(get_file(!datas[name]["in"].is_null()?(std::string)datas[name]["in"]:system_nul))
                <<", outfile: "<<add_squo(get_file(!datas[name]["out"].is_null()?(std::string)datas[name]["out"]:system_nul))<<"\n";
                output_chk_file<<"    result: "<<target->result<<"\n";
                output_chk_file<<print_type({"    "," time: "," exit_code: ","\n"},{
                    {_ans_name+":",target->time,target->exit_code},
                    {_chk_name+":",target->chk_runner->time,target->chk_runner->exit_code}});
                output_chk_file<<std::string("*")*50;
                output_chk_file.close();
                if(target->result.istrue()) ++ac_sum;
                if(target->result.isfalse())
                {
                    ++output_sum;
                    pat target_dir=get_file(replace_env(data_file_str,running_path,env_args::data(data_name,target->result,runned_sum,output_sum))).path();
                    ((fil)target_dir.parent()).createDirectories();
                    if((run_dir/"data.in").exists()) (run_dir/"data.in").copyTo(replace_extension(target_dir,"in").toString());
                    if((run_dir/"data.out").exists()) (run_dir/"data.out").copyTo(replace_extension(target_dir,"out").toString());
                    if((run_dir/"data.ans").exists()) (run_dir/"data.ans").copyTo(replace_extension(target_dir,"ans").toString());
                    if((run_dir/"data.txt").exists()) (run_dir/"data.txt").copyTo(replace_extension(target_dir,"txt").toString());
                }
                #undef run_dir
            }
            scout<<"\n"<<ac_sum<<" / "<<runned_sum<<"\n\n";
        }
        else
        {
            unsigned runned_sum=0,ac_sum=0,output_sum=0;
            for(auto i:datas.items())
            {
                ssetenv("runned_sum",std::to_string(runned_sum));
                ssetenv("outputed_sum",std::to_string(output_sum));
                // init file
                if(i.value()["in"].is_null()&&i.value()["out"].is_null()) continue;
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
                scout<<std::string("-")*50<<"\r#"<<data_name<<"\n";
                ++runned_sum;
                fil run_dir=default_data_dir/"datas"/data_name;
                run_dir.createDirectory();
                fil in_file=system_nul,out_file=system_nul,ans_file=run_dir/"data.ans",chk_file=run_dir/"data.txt";
                if(!i.value()["in"].is_null()) ((fil)(std::string)i.value()["in"]).copyTo((in_file=run_dir/"data.in").path());
                if(!i.value()["out"].is_null()) ((fil)(std::string)i.value()["out"]).copyTo((out_file=run_dir/"data.out").path());
                // judge
                judger run_judger(ans,chk,in_file,out_file,ans_file,chk_file);(&run_judger)->set_name(data_name);
                run_judger.judge();
                run_judger.print_result("",_chk_name);
                // print result
                sofstream output_chk_file(chk_file,std::ios::app);
                output_chk_file<<"\n"<<std::string("*")*50<<"\n";
                output_chk_file
                <<"    infile: "<<add_squo(get_file(!i.value()["in"].is_null()?(std::string)i.value()["in"]:system_nul))
                <<", outfile: "<<add_squo(get_file(!i.value()["out"].is_null()?(std::string)i.value()["out"]:system_nul))<<"\n";
                output_chk_file<<"    result: "<<run_judger.result<<"\n";
                output_chk_file<<print_type({"    "," time: "," exit_code: ","\n"},{
                    {_ans_name+":",run_judger.time,run_judger.exit_code},
                    {_chk_name+":",run_judger.chk_runner->time,run_judger.chk_runner->exit_code}});
                output_chk_file<<std::string("*")*50;
                output_chk_file.close();
                // copy result
                if(run_judger.result.istrue()) ++ac_sum;
                if(run_judger.result.isfalse())
                {
                    ++output_sum;
                    pat target_dir=get_file(replace_env(data_file_str,running_path,env_args::data(data_name,run_judger.result,runned_sum,output_sum))).path();
                    ((fil)target_dir.parent()).createDirectories();
                    if((run_dir/"data.in").exists()) (run_dir/"data.in").copyTo(replace_extension(target_dir,"in").toString());
                    if((run_dir/"data.out").exists()) (run_dir/"data.out").copyTo(replace_extension(target_dir,"out").toString());
                    if((run_dir/"data.ans").exists()) (run_dir/"data.ans").copyTo(replace_extension(target_dir,"ans").toString());
                    if((run_dir/"data.txt").exists()) (run_dir/"data.txt").copyTo(replace_extension(target_dir,"txt").toString());
                }
                ssetenv("runned_sum","");
                ssetenv("outputed_sum","");
            }
            scout<<ac_sum<<" / "<<runned_sum;
        }
        return EXIT_OK;
    }
};
#endif