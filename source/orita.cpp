#include"orita.hpp"
#include"Oritaconfig.hpp"
#include"chdata.cpp"
#include"check.cpp"
#include"compile.cpp"
#include"command.cpp"
#include"config.cpp"
#include"judge.cpp"
#include"run.cpp"
class Command_orita: public App
{
  protected:
    Poco::Util::HelpFormatter *helpFormatter;
    void defineOptions(Poco::Util::OptionSet &options)
    {
        options.addOption(Poco::Util::Option("help","h","display help information").noArgument());
        options.addOption(Poco::Util::Option("reset","r","reset configuration").noArgument());
        options.addOption(Poco::Util::Option("clear","c","clear configuration").noArgument());
        App::defineOptions(options);
    }
    void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        helpFormatter->setHeader("Orita - Useful OI Tools");
        helpFormatter->setCommand("orita");
        helpFormatter->setUsage("[options]\n");
        helpFormatter->setFooter("Turn to https://github.com/2745518585/Orita#readme to get more information!\n");
        helpFormatter->format(std::cout);
    }
    int main(const std::vector<std::string> &args)
    {
        loadConfiguration();
        if(check_option("error options")) return EXIT_USAGE;
        if(check_option("help")) return EXIT_OK;
        INFO("args",vec_to_str(args,static_cast<std::string(*)(const std::string&)>(add_squo)));


        if(check_option("reset"))
        {
            delete orita_log;
            ((fil)appdata_path).remove(true);
            ((fil)file_path/"files").copyTo(appdata_path.toString());
            ssystem("echo "+file_path.toString()+" > "+add_quo(appdata_path/"path.txt"));
            global_settings=default_settings;
            Files::files_json=Files::default_files_json;
            return EXIT_OK;
        }
        else if(check_option("clear"))
        {
            delete orita_log;
            ((fil)appdata_path).remove(true);
            return EXIT_OK;
        }
        scout<<"--------------------------------------------------\n";
        scout<<"  Orita - Useful OI Tools\n";
        scout<<"  Version: Dev "<<PROJECT_VERSION<<"\n";
        scout<<"  Repository: https://github.com/2745518585/Orita\n";
        scout<<"  Local Path: "<<file_path.toString()<<"\n";
        scout<<"--------------------------------------------------\n";
        return EXIT_OK;
    }
};
int main(int argc,char **argv)
{
    std::vector<std::string> args;
    unsigned args_sum=stoul(sgetenv("ORITA ARGS"));
    args.push_back(argv[0]);
    for(int i=0;i<args_sum;++i)
    {
        args.push_back(sgetenv("ORITA ARGS "+std::to_string(i)));
    }
    auto run_commands=[&](std::string commands){
        INFO("run commands","commands: "+commands);
        if(commands=="chdata"||commands=="check"||commands=="compile"||commands=="command"||commands=="config"||commands=="judge"||commands=="run") args.erase(args.begin());
        if(commands=="chdata") {Command_chdata Chdata;Chdata.init(args);return Chdata.run();}
        else if(commands=="check") {Command_check Check;Check.init(args);return Check.run();}
        else if(commands=="compile") {Command_compile Compile;Compile.init(args);return Compile.run();}
        else if(commands=="command") {Command_command Command;Command.init(args);return Command.run();}
        else if(commands=="config") {Command_config Config;Config.init(args);return Config.run();}
        else if(commands=="judge") {Command_judge Judge;Judge.init(args);return Judge.run();}
        else if(commands=="run") {Command_run Run;Run.init(args);return Run.run();}
        else {Command_orita Orita;Orita.init(args);return Orita.run();}
    };
    std::string commands;
    if(args.size()>1&&!std::regex_match(args[1],std::regex("^[/|-].*$")))
    {
        try
        {
            commands=get_settings<std::string>((std::string)"/commands/"+args[1]);
        }
        catch(...) {commands=args[1];}
    }
    return run_commands(commands);
}
