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
        options.addOption(Poco::Util::Option("global","g","global settings").noArgument());
        options.addOption(Poco::Util::Option("local","l","local settings").noArgument());
        options.addOption(Poco::Util::Option("files","f","files").noArgument());
        App::defineOptions(options);
    }
    void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        helpFormatter->setHeader("Orita - Config");
        helpFormatter->setCommand("orita config");
        helpFormatter->setUsage("[key [value]] [options]\n");
        helpFormatter->setFooter(" ");
        helpFormatter->format(std::cout);
    }
    int main(const std::vector<std::string>& args)
    {
        loadConfiguration();
        if(check_option("error options")) return EXIT_USAGE;
        if(check_option("help")) return EXIT_OK;
        INFO("args",vec_to_str(args,static_cast<std::string(*)(const std::string&)>(add_squo)));


        if(check_option("settings"))
        {
            std::string key="";
            if(args.size()>0) key="/"+args[0];
            json *target=NULL;
            if(check_option("global")) target=&global_settings[(json::json_pointer)(key)];
            else if(check_option("local"))
            {
                target=&all_settings[running_path.toString()][(json::json_pointer)(key)];
                if_has_settings[running_path.toString()]=true;
            }
            else
            {
                if(key=="")
                {
                    target=new json(default_settings);
                    merge(*target,global_settings);
                    for(auto i:all_settings) merge(*target,i);
                }
                else target=get_settings_object(key);
            }
            if(args.size()==0)
            {
                scout<<target->dump(4,' ',true,json::error_handler_t::ignore)<<"\n";
            }
            else if(args.size()==1)
            {
                scout<<(*target)<<"\n";
            }
            else
            {
                if(args[1]=="%{RESET}%") (*target)=default_settings[(json::json_pointer)(key)];
                else (*target)=json::parse(args[1]);
            }
            if(!check_option("global")) scout<<termcolor::grey<<get_settings_path(key).toString()<<termcolor::reset<<"\n";
        }
        else if(check_option("files"))
        {
            if(args.size()==0)
            {
                scout<<Files::files_json.dump(4,' ',true,json::error_handler_t::ignore)<<"\n";
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