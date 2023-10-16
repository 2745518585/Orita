#include<string>
#include<fstream>
#include<regex>
#include<vector>
#include<cstdlib>
#include<iostream>

#ifdef _WIN32
#include<windows.h>
#endif

std::string add_quo(const std::string &str)
{
    return "\""+str+"\"";
}

int ssystem(const std::string &command)
{
    #ifdef _WIN32
    return system(("cmd /C "+add_quo(command)).c_str());
    #endif
    #ifdef __linux__
    return system(command.c_str());
    #endif
}

#ifdef _WIN32
char PS='\\';
#endif
#ifdef __linux__
char PS='/';
#endif
std::string makepath(const std::string &path) {return path;}
template<typename ...others_type> std::string makepath(const std::string &path,const others_type ...others) {if(path=="") return makepath(others...); return path+PS+makepath(others...);}

std::string get_appdata_path()
{
    #ifdef _WIN32
    return makepath(getenv("appdata"),"Orita");
    #endif
    #ifdef __linux__
    return makepath(getenv("HOME"),".Orita");
    #endif
}

std::string get_filedir(std::string file)
{
    #ifdef _WIN32
    file=std::regex_replace(file,std::regex("/"),"\\");
    #endif
    if(file.find_last_of(PS)==std::string::npos) return "";
    return file.substr(0,file.find_last_of(PS));
}

std::vector<std::string> init_file(int argc,char **argv)
{
    std::vector<std::string> args;
    for(int i=1;i<argc;++i)
    {
        #ifdef _WIN32
        WIN32_FIND_DATA file;
        HANDLE hFind=FindFirstFile(argv[i],&file);
        std::string dir=get_filedir(argv[i]);
        if(hFind==INVALID_HANDLE_VALUE)
        {
            args.push_back(argv[i]);
            continue;
        }
        do
        {
            args.push_back(makepath(dir,file.cFileName));
        }while(FindNextFile(hFind,&file)!=0);
        FindClose(hFind);
        #endif
        #ifdef __linux__
        args.push_back(argv[i]);
        #endif
    }
    return args;
}

int main(int argc,char **argv)
{
    std::string path;
    (std::ifstream)(makepath(get_appdata_path(),"path.txt"))>>path;
    std::vector<std::string> args=init_file(argc,argv);
    #ifdef _WIN32
    path=makepath(path,"main.exe");
    #endif
    #ifdef __linux__
    path=makepath(path,"main");
    #endif
    std::string command=add_quo(path);
    auto ssetenv=[&](const std::string &key,const std::string &value)
    {
        #ifdef _WIN32
        SetEnvironmentVariable(key.c_str(),value.c_str());
        #endif
        #ifdef __linux__
        command="export "+key+"="+value+" && "+command;
        #endif
    };
    ssetenv("ORITA_ARGS",std::to_string(args.size()));
    for(int i=0;i<args.size();++i)
    {
        ssetenv("ORITA_ARGS_"+std::to_string(i),args[i]);
    }
    return ssystem(command);
}