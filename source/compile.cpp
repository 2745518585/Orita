#pragma once
#ifndef _COMMAND_COMPILE
#define _COMMAND_COMPILE _COMMAND_COMPILE
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

        
        arg compile_argu=get_arg(get_option("carg"));
        std::string run_argu=get_option("arg");
        if(args.size()==1&&check_option("run"))
        {
            fil file=add_namesuf(get_file((pat)args[0]),"cpp");
            compiler comp(file,compile_argu);
            if(comp())
            {
                scerr<<comp.err;
                return EXIT_OK;
            }
            show_cursor();
            timer run_timer;run_timer.init();
            int exit_code=ssystem(replace_extension(file,exe_suf).toString()+" "+run_argu);
            tim time=run_timer.get_time();
            hide_cursor();
            scout<<"\n"<<termcolor::bright_grey<<"===== time: "<<termcolor::bright_cyan<<time<<termcolor::bright_grey<<", exit code: "<<(exit_code?termcolor::magenta<char>:termcolor::bright_green<char>)<<exit_code<<termcolor::bright_grey<<" ====="<<termcolor::reset<<"\n";
        }
        else if(args.size()==1&&check_option("trun"))
        {
            fil file=get_file((pat)args[0]);
            show_cursor();
            timer run_timer;run_timer.init();
            int exit_code=ssystem(replace_extension(file,exe_suf).toString()+" "+run_argu);
            tim time=run_timer.get_time();
            hide_cursor();
            scout<<"\n"<<termcolor::bright_grey<<"===== time: "<<termcolor::bright_cyan<<time<<termcolor::bright_grey<<", exit code: "<<(exit_code?termcolor::magenta<char>:termcolor::bright_green<char>)<<exit_code<<termcolor::bright_grey<<" ====="<<termcolor::reset<<"\n";
        }
        else
        {
            th_compiler comp;
            for(auto i:args)
            {
                fil file=get_file(add_namesuf((pat)i,"cpp"));
                comp.add(file.path(),file,compile_argu);
            }
            comp.wait_all();
            {
                auto compile_result=comp.get_all();
                if(compile_result.first!="")
                {
                    scerr<<compile_result.second->err;
                    print_result(compile_result.first,res::type::CE);
                    return EXIT_OK;
                }
            }
            print_result(res::type::SS);
        }
        return EXIT_OK;
    }
};
#endif