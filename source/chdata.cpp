#pragma once
#ifndef _COMMAND_CHDATA
#define _COMMAND_CHDATA _COMMAND_CHDATA
#include"orita.hpp"
class Command_chdata: public App
{
  protected:
    void defineOptions(Poco::Util::OptionSet &options)
    {
        options.addOption(Poco::Util::Option("help","h","display help information").noArgument());
        options.addOption(Poco::Util::Option("ifile","if","specify input file").argument("file",false));
        options.addOption(Poco::Util::Option("ofile","of","specify output file").argument("file",false));
        options.addOption(Poco::Util::Option("time","t","change time limit").argument("time",true));
        App::defineOptions(options);
    }
    void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        helpFormatter->setHeader("Orita - Chdata");
        helpFormatter->setUsage("[options]\n");
        helpFormatter->setFooter(" ");
        helpFormatter->setCommand(commandName());
        helpFormatter->format(std::cout);
    }
    int main(const std::vector<std::string>& args)
    {
        loadConfiguration();
        if(check_option("error options")) return EXIT_USAGE;
        if(check_option("help")) return Application::EXIT_OK;


        fil in_file=get_option("ifile");
        fil out_file=get_option("ofile");
        if(in_file!=fil()&&!in_file.exists()) {print_result(res::type::NF);return EXIT_NOINPUT;}
        if(out_file!=fil()&&!out_file.exists()) {print_result(res::type::NF);return EXIT_NOINPUT;}
        if(in_file!=fil()) in_file.copyTo(default_infile.path());
        else if(check_option("ifile"))
        {
            show_cursor();
            char str;
            FILE *file=sfopen(default_infile.path(),"w");
            str=getchar();
            while(str!=EOF) fputc(str,file),str=getchar();
            sfclose(file);
            hide_cursor();
        }
        if(out_file!=fil()) out_file.copyTo(default_outfile.path());
        else if(check_option("ofile"))
        {
            show_cursor();
            char str;
            FILE *file=sfopen(default_outfile.path(),"w");
            str=getchar();
            while(str!=EOF) fputc(str,file),str=getchar();
            sfclose(file);
            hide_cursor();
        }
        if(check_option("time")) change_time_limit((tim)std::stoi(get_option("time")));
        print_result(res::type::SS);
        return 0;
    }
};
#endif