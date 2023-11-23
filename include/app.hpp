#pragma once
#ifndef _FILE_APP
#define _FILE_APP
#include"init.hpp"
class App: public Poco::Util::Application
{
  public:
    void init(int argc,char **argv)
    {
        try {Application::init(argc,argv);}
        catch(Poco::Util::OptionException& err)
        {
            scerr<<"error: "<<err.displayText()<<std::endl;
            config().setBool("error options",true);
            ERROR((std::string)"option - "+err.displayText());
        }
        stopOptionsProcessing();
    }
    void init(std::vector<std::string> args)
    {
        try {Application::init(args);}
        catch(Poco::Util::OptionException& err)
        {
            scerr<<"error: "<<err.displayText()<<std::endl;
            config().setBool("error options",true);
            ERROR((std::string)"option - "+err.displayText());
        }
        stopOptionsProcessing();
    }
  protected:
    void initialize(Application &self)
    {
        Application::initialize(self);
    }
    void uninitialize()
    {
        Application::uninitialize();
    }
    Poco::Util::HelpFormatter *helpFormatter;
    void defineOptions(Poco::Util::OptionSet &options)
    {
        helpFormatter=new Poco::Util::HelpFormatter(options);
        Application::defineOptions(options);
    }
    virtual void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        
    }
    void handleOption(const std::string &name,const std::string &value)
    {
        config().setString(name,value);
        Application::handleOption(name,value);
        INFO("option - "+add_squo(name),"value: "+add_squo(value));
        if(name=="help")
        {
            displayHelp(helpFormatter);
            stopOptionsProcessing();
        }
    }
    bool check_option(const std::string &name) const
    {
        return config().hasOption(name);
    }
    std::string get_option(const std::string &name) const
    {
        return config().getString(name,"");
    }
    std::string get_option(const std::string &name,const std::string &default_value) const
    {
        return config().getString(name,default_value);
    }
};
#endif