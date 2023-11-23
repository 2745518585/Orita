#pragma once
#ifndef _COMMAND_COMMAND
#define _COMMAND_COMMAND
#include"orita.hpp"
class Command_command: public App
{
  protected:
    void defineOptions(Poco::Util::OptionSet &options)
    {
        options.addOption(Poco::Util::Option("help","h","display help information").noArgument());
        App::defineOptions(options);
    }
    void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        helpFormatter->setHeader("Orita - Command");
        helpFormatter->setCommand("orita command");
        helpFormatter->setUsage("[commands] [options]\n");
        helpFormatter->setFooter(" ");
        helpFormatter->format(std::cout);
    }
    int main(const std::vector<std::string>& args)
    {
        loadConfiguration();
        if(check_option("error options")) return EXIT_USAGE;
        if(check_option("help")) return EXIT_OK;
        INFO("args",add_squo(args));


        std::string command;
        for(auto i:args) command+=replace_env(i)+" ";
        ssystem(command);
        return 0;
    }
};
#endif