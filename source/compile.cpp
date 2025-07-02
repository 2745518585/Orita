#pragma once
#ifndef _COMMAND_COMPILE
#define _COMMAND_COMPILE
#include"orita.hpp"
class Command_compile: public App
{
  protected:
    void defineOptions(Poco::Util::OptionSet &options)
    {
        options.addOption(Poco::Util::Option("help","h","display help information").noArgument());
        options.addOption(Poco::Util::Option("run","r","compile and run").noArgument());
        options.addOption(Poco::Util::Option("trun","t","only run").noArgument());
        options.addOption(Poco::Util::Option("carg","c","compile args").argument("args",true));
        options.addOption(Poco::Util::Option("arg","a","run args").argument("args",true));
        options.addOption(Poco::Util::Option("dorecompile","dore","force recompile").noArgument());
        App::defineOptions(options);
    }
    void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        helpFormatter->setHeader("Orita - Compile");
        helpFormatter->setCommand("orita compile");
        helpFormatter->setUsage("[file] [options]\n");
        helpFormatter->setFooter(" ");
        helpFormatter->format(std::cout);
    }
    int main(const std::vector<std::string>& args)
    {
        loadConfiguration();
        if(check_option("error options")) return EXIT_USAGE;
        if(check_option("help")) return EXIT_OK;
        INFO("args",add_squo(args));

        
        const arg compile_argu=get_arg(get_option("carg"));
        const arg run_argu=get_arg(get_option("arg"));
        if(check_option("dorecompile")) if_skip_compiled=false;
        if(args.size()==1&&check_option("run"))
        {
            fil file=get_file((pat)args[0]);
            compiler comp(file,compile_argu);
            DEBUG("0");
            if(comp())
            {
                scerr<<comp.err;
                return EXIT_OK;
            }
            show_cursor();
            timer run_timer;run_timer.init();
            int exit_code=ssystem(replace_env(get_language_settings(file).run_command_str,running_path,env_args::files(file))+" "+replace_env(get_language_settings(file).run_argu_str+run_argu,running_path,env_args::files(file)).dump())>>sys_exit_code;
            tim time=run_timer.get_time();
            hide_cursor();
            scout<<"\n"<<(std::string)replace_env(print_str[exit_code?"run_fail_info":"run_success_info"],running_path,env_args::result(time,exit_code))<<"\n";
        }
        else if(args.size()==1&&check_option("trun"))
        {
            fil file=get_file((pat)args[0]);
            show_cursor();
            timer run_timer;run_timer.init();
            int exit_code=ssystem(replace_env(get_language_settings(file).run_command_str,running_path,env_args::files(file))+" "+replace_env(get_language_settings(file).run_argu_str+run_argu,running_path,env_args::files(file)).dump())>>sys_exit_code;
            tim time=run_timer.get_time();
            hide_cursor();
            scout<<"\n"<<(std::string)replace_env(print_str[exit_code?"run_fail_info":"run_success_info"],running_path,env_args::result(time,exit_code))<<"\n";
        }
        else
        {
            unsigned add_sum=0;
            th_compiler comp;
            auto add=[&](unsigned i)
            {
                fil file=get_file((pat)args[i-1]);
                comp.add(file.path(),file,compile_argu);
            };
            while(add_sum<max_thread_num&&add_sum<args.size()) add(++add_sum);
            std::string name;
            while((name=comp.get_one())!="")
            {
                if(comp.list[name]->exit_code)
                {
                    scerr<<comp.list[name]->err;
                    print_result(name,res::type::CE,(tim)0,comp.list[name]->exit_code);
                }
                else print_result(name,res::type::SS,(tim)0,comp.list[name]->exit_code);
                comp.remove(name);
                if(add_sum<args.size()) add(++add_sum);
            }
        }
        return EXIT_OK;
    }
};
#endif