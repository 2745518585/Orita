#pragma once
#ifndef _COMMAND_CONFIG
#define _COMMAND_CONFIG _COMMAND_CONFIG
#include"orita.hpp"
class Command_config: public App
{
  protected:
    void defineOptions(Poco::Util::OptionSet &options)
    {
        options.addOption(Poco::Util::Option("help","h","display help information").noArgument());
        options.addOption(Poco::Util::Option("settings","s","settings").noArgument());
        options.addOption(Poco::Util::Option("files","f","files").noArgument());
        App::defineOptions(options);
    }
    void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        helpFormatter->setHeader("Orita - Config");
        helpFormatter->setUsage("[file]... [options]\n");
        helpFormatter->setFooter(" ");
        helpFormatter->setCommand(commandName());
        helpFormatter->format(std::cout);
    }
    int main(const std::vector<std::string>& args)
    {
        loadConfiguration();
        if(check_option("error options")) return EXIT_USAGE;
        if(check_option("help")) return Application::EXIT_OK;


        if(check_option("settings"))
        {
            if(args.size()==0)
            {
                scout<<std::setw(4)<<settings;
            }
            else if(args.size()==1)
            {
                scout<<settings[(json::json_pointer)("/"+args[0])]<<"\n";
            }
            else
            {
                if(args[1]=="%{RESET}%") settings[(json::json_pointer)("/"+args[0])]=default_settings[(json::json_pointer)("/"+args[0])];
                else settings[(json::json_pointer)("/"+args[0])]=json::parse(args[1]);
            }
        }
        else if(check_option("files"))
        {
            if(args.size()==0)
            {
                scout<<std::setw(4)<<Files::files_json;
            }
            else if(args.size()==1)
            {
                scout<<get_filestr(std::stoi(args[0]))<<"\n";
            }
            else
            {
                const unsigned num=std::stoul(args[0]);
                if(args[1]=="%{RESET}%") add_filestr(num,get_default_filestr(num));
                else add_filestr(num,args[1]);
            }
        }
        return EXIT_OK;
    }
};
#endif