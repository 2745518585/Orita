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
        INFO("args",vec_to_str(args,static_cast<std::string(*)(const std::string&)>(add_squo)));

        
        std::string compile_argu=get_option("carg");
        std::string run_argu=get_option("arg");
        if(args.size()==1&&check_option("run"))
        {
            fil file=add_namesuf(get_file((pat)args[0]),"cpp");
            if(compile(file,compile_argu)) return EXIT_OK;
            runner runs(replace_extension(file,exe_suf),"","",run_argu,(tim)1000000);
            runs.run();
            scout<<"\n"<<termcolor::bright_grey<<"===== time: "<<termcolor::bright_cyan<<runs.time<<termcolor::bright_grey<<", exit code: "<<(runs.exit_code?termcolor::magenta<char>:termcolor::bright_green<char>)<<runs.exit_code<<termcolor::bright_grey<<" ====="<<termcolor::reset<<"\n";
        }
        else if(args.size()==1&&check_option("trun"))
        {
            fil file=get_file((pat)args[0]);
            runner runs(file,"","",run_argu,(tim)1000000);
            runs.run();
            scout<<"\n"<<termcolor::bright_grey<<"===== time: "<<termcolor::bright_cyan<<runs.time<<termcolor::bright_grey<<", exit code: "<<(runs.exit_code?termcolor::magenta<char>:termcolor::bright_green<char>)<<runs.exit_code<<termcolor::bright_grey<<" ====="<<termcolor::reset<<"\n";
        }
        else
        {
            for(auto i:args)
            {
                fil file=get_file(add_namesuf((pat)i,"cpp"));
                if(compile(file,compile_argu)) print_result(((pat)file.path()).getFileName(),res::type::CE);
                else print_result(((pat)file.path()).getFileName(),res::type::SS);
            }
        }
        return EXIT_OK;
    }
};
#endif