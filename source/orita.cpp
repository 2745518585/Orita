#include"orita.hpp"
#include"Oritaconfig.hpp"
#include"chdata.cpp"
#include"check.cpp"
#include"compile.cpp"
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
        options.addOption(Poco::Util::Option("reset","r","reset Configuration").noArgument());
        options.addOption(Poco::Util::Option("clear","c","clear Configuration").noArgument());
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
            ((fil)file_path/"files"/os_name).copyTo(appdata_path.toString());
            ssystem("echo "+(file_path/"build").toString()+" > "+add_quo(appdata_path/"path.txt"));
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
    if(argc>1&&(std::string)argv[1]=="chdata") {Command_chdata Chdata;Chdata.init(argc-1,argv+1);return Chdata.run();}
    if(argc>1&&(std::string)argv[1]=="check") {Command_check Check;Check.init(argc-1,argv+1);return Check.run();}
    if(argc>1&&(std::string)argv[1]=="compile") {Command_compile Compile;Compile.init(argc-1,argv+1);return Compile.run();}
    if(argc>1&&(std::string)argv[1]=="config") {Command_config Config;Config.init(argc-1,argv+1);return Config.run();}
    if(argc>1&&(std::string)argv[1]=="judge") {Command_judge Judge;Judge.init(argc-1,argv+1);return Judge.run();}
    if(argc>1&&(std::string)argv[1]=="run") {Command_run Run;Run.init(argc-1,argv+1);return Run.run();}
    Command_orita Orita;
    Orita.init(argc,argv);
    return Orita.run();
}