#pragma once
#ifndef _COMMAND_CHECK
#define _COMMAND_CHECK
#include"orita.hpp"
class Command_check: public App
{
  protected:
    void defineOptions(Poco::Util::OptionSet &options)
    {
        options.addOption(Poco::Util::Option("help","h","display help information").noArgument());
        options.addOption(Poco::Util::Option("ifile","if","specify data maker").argument("file",true));
        options.addOption(Poco::Util::Option("ofile","of","specify std").argument("file",true));
        options.addOption(Poco::Util::Option("afile","af","specify ans").argument("file",true));
        options.addOption(Poco::Util::Option("checker","c","specify checker").argument("file",true));
        options.addOption(Poco::Util::Option("num","n","specify check num").argument("num",true));
        options.addOption(Poco::Util::Option("time","t","change time limit").argument("time",true));
        options.addOption(Poco::Util::Option("multithread","mul","turn on multithreading").noArgument());
        options.addOption(Poco::Util::Option("dorecompile","dore","force recompile").noArgument());
        App::defineOptions(options);
    }
    void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        helpFormatter->setHeader("Orita - Check");
        helpFormatter->setCommand("orita check");
        helpFormatter->setUsage("[options]\n");
        helpFormatter->setFooter(" ");
        helpFormatter->format(std::cout);
    }
    int main(const std::vector<std::string>& args)
    {
        loadConfiguration();
        if(check_option("error options")) return EXIT_USAGE;
        if(check_option("help")) return EXIT_OK;
        INFO("args",add_squo(args));


        const std::string _in_name="data_maker";
        const std::string _out_name="std";
        const std::string _ans_name="ans";
        const std::string _chk_name="checker";
        // init name
        fil in=[&]()
        {
            pat in_str=check_file(get_option("ifile"),_check_in);
            add_file(_check_in,in_str);
            return add_namesuf(get_file(in_str),"cpp");
        }();
        fil out=[&]()
        {
            pat out_str=check_file(get_option("ofile"),_check_out);
            add_file(_check_out,out_str);
            return add_namesuf(get_file(out_str),"cpp");
        }();
        fil ans=[&]()
        {
            pat ans_str=check_file(get_option("afile"),_check_ans);
            add_file(_check_ans,ans_str);
            return add_namesuf(get_file(ans_str),"cpp");
        }();
        fil chk=[&]()
        {
            pat chk_str=check_file(get_option("checker"),_check_chk);
            add_file(_check_chk,chk_str);
            return add_namesuf(get_file(chk_str),"cpp");
        }();
        // init config
        if(check_option("time")) change_time_limit((tim)std::stoi(get_option("time")));
        if(check_option("fcompile")) if_skip_compiled=false;
        // init total sum
        if(!check_option("num"))
        {
            print_result(res::type::SS);
            return EXIT_OK;
        }
        unsigned total_sum=std::stoi(get_option("num"));
        // save config
        save_config();
        // find file
        if(in==fil()||!in.exists()) {print_result(_in_name,res::type::NF);return EXIT_NOINPUT;}
        if(out==fil()||!out.exists()) {print_result(_out_name,res::type::NF);return EXIT_NOINPUT;}
        if(ans==fil()||!ans.exists()) {print_result(_ans_name,res::type::NF);return EXIT_NOINPUT;}
        if(chk==fil()||!chk.exists()) {print_result(_chk_name,res::type::NF);return EXIT_NOINPUT;}
        if(show_file_info) scout<<termcolor::bright_grey<<print_type({"","","\n"},{{_in_name+": ",in},{_out_name+": ",out},{_ans_name+": ",ans},{_chk_name+": ",chk}},true)<<ANSI::move_up*4<<termcolor::reset;
        // compile file
        printer *print=new printer({"Compiling.","Compiling..","Compiling..."},(tim)150);print->start();
        th_compiler *run_compiler=new th_compiler();
        run_compiler->add({{_in_name,in},{_out_name,out},{_ans_name,ans},{_chk_name,chk}},data_compile_argu);
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
            throw exception("fail make data dir",error.displayText());
        }
        delete print;
        // check
        if(check_option("multithread"))
        {
            ssetenv(".data.chk_outputs","\"off\"");
            unsigned ac_sum=0,runned_sum=0,add_sum=0,get_sum=0,output_sum=0;
            th_judger run_judger;
            auto add=[&](unsigned i)
            {
                fil run_dir=default_data_dir/"tmp_data"/std::to_string(i);
                run_dir.createDirectory();
                fil in_file=run_dir/"data.in",out_file=run_dir/"data.out",ans_file=run_dir/"data.ans",chk_file=run_dir/"data.txt";
                run_judger.add(std::to_string(i),(new judger(ans,chk,in_file,out_file,ans_file,chk_file))->set_in(in)->set_out(out));
            };
            while(add_sum<max_thread_num&&add_sum<total_sum) add(++add_sum);
            std::string name;
            while((name=run_judger.get_one())!="")
            {
                ++get_sum;
                scout<<std::string("-")*50<<"\r#"<<get_sum;
                if(runned_sum!=ac_sum)
                {
                    scout<<std::string("-")*(30-std::to_string(get_sum).size())<<termcolor::bright_grey<<" Unaccepted "<<termcolor::bright_red<<runned_sum-ac_sum<<" "<<termcolor::reset;
                }
                scout<<"\n";
                fil run_dir=default_data_dir/"datas"/std::to_string(get_sum);
                (default_data_dir/"tmp_data"/name).copyTo(run_dir.path());
                judger *target=run_judger.list[name];
                target->print_result(_in_name,_out_name,"",_chk_name);
                sofstream output_chk_file(run_dir/"data.txt",std::ios::app);
                output_chk_file<<"\n"<<std::string("*")*50<<"\n";
                output_chk_file<<"    result: "<<target->result<<"\n";
                output_chk_file<<"    seed: "<<target->seed<<"\n";
                output_chk_file<<print_type({"    "," time: "," exit_code: ","\n"},{
                    {_in_name+":",target->in_runner->time,target->in_runner->exit_code},
                    {_out_name+":",target->out_runner->time,target->out_runner->exit_code},
                    {_ans_name+":",target->time,target->exit_code},
                    {_chk_name+":",target->chk_runner->time,target->chk_runner->exit_code}});
                output_chk_file<<std::string("*")*50;
                output_chk_file.close();
                if(!target->result.isnull()) ++runned_sum;
                if(target->result.istrue()) ++ac_sum;
                if(target->result.isfalse())
                {
                    ++output_sum;
                    pat target_dir=get_file(replace_env(data_file_str,running_path,env_args::data(std::to_string(get_sum),target->result,runned_sum,output_sum))).path();
                    ((fil)target_dir.parent()).createDirectories();
                    if((run_dir/"data.in").exists()) (run_dir/"data.in").copyTo(replace_extension(target_dir,"in").toString());
                    if((run_dir/"data.out").exists()) (run_dir/"data.out").copyTo(replace_extension(target_dir,"out").toString());
                    if((run_dir/"data.ans").exists()) (run_dir/"data.ans").copyTo(replace_extension(target_dir,"ans").toString());
                    if((run_dir/"data.txt").exists()) (run_dir/"data.txt").copyTo(replace_extension(target_dir,"txt").toString());
                }
                run_judger.remove(name);
                if(add_sum<total_sum) add(++add_sum);
            }
            scout<<"\n"<<ac_sum<<" / "<<runned_sum<<"\n\n";
        }
        else
        {
            unsigned ac_sum=0,runned_sum=0,output_sum=0;
            for(unsigned i=1;i<=total_sum;++i)
            {
                ssetenv("runned_sum",std::to_string(runned_sum));
                ssetenv("outputed_sum",std::to_string(output_sum));
                scout<<std::string("-")*50<<"\r#"<<i;
                if(runned_sum!=ac_sum)
                {
                    scout<<std::string("-")*(30-std::to_string(i).size())<<termcolor::bright_grey<<" Unaccepted "<<termcolor::bright_red<<runned_sum-ac_sum<<" "<<termcolor::reset;
                }
                scout<<"\n";
                fil run_dir=default_data_dir/"datas"/std::to_string(i);
                run_dir.createDirectory();
                fil in_file=run_dir/"data.in",out_file=run_dir/"data.out",ans_file=run_dir/"data.ans",chk_file=run_dir/"data.txt";
                judger run_judger(ans,chk,in_file,out_file,ans_file,chk_file);(&run_judger)->set_in(in)->set_out(out)->set_name(std::to_string(i));
                run_judger.judge();
                run_judger.print_result(_in_name,_out_name,"",_chk_name);
                sofstream output_chk_file(chk_file,std::ios::app);
                output_chk_file<<"\n"<<std::string("*")*50<<"\n";
                output_chk_file<<"    result: "<<run_judger.result<<"\n";
                output_chk_file<<"    seed: "<<run_judger.seed<<"\n";
                output_chk_file<<print_type({"    "," time: "," exit_code: ","\n"},{
                    {_in_name+":",run_judger.in_runner->time,run_judger.in_runner->exit_code},
                    {_out_name+":",run_judger.out_runner->time,run_judger.out_runner->exit_code},
                    {_ans_name+":",run_judger.time,run_judger.exit_code},
                    {_chk_name+":",run_judger.chk_runner->time,run_judger.chk_runner->exit_code}});
                output_chk_file<<std::string("*")*50;
                output_chk_file.close();
                if(!run_judger.result.isnull()) ++runned_sum;
                if(run_judger.result.istrue()) ++ac_sum;
                if(run_judger.result.isfalse())
                {
                    ++output_sum;
                    pat target_dir=get_file(replace_env(data_file_str,running_path,env_args::data(std::to_string(i),run_judger.result,runned_sum,output_sum))).path();
                    ((fil)target_dir.parent()).createDirectories();
                    if((run_dir/"data.in").exists()) (run_dir/"data.in").copyTo(replace_extension(target_dir,"in").toString());
                    if((run_dir/"data.out").exists()) (run_dir/"data.out").copyTo(replace_extension(target_dir,"out").toString());
                    if((run_dir/"data.ans").exists()) (run_dir/"data.ans").copyTo(replace_extension(target_dir,"ans").toString());
                    if((run_dir/"data.txt").exists()) (run_dir/"data.txt").copyTo(replace_extension(target_dir,"txt").toString());
                }
                ssetenv("runned_sum","");
                ssetenv("outputed_sum","");
            }
            scout<<"\n"<<ac_sum<<" / "<<runned_sum<<"\n\n";
        }
        return EXIT_OK;
    }
};
#endif