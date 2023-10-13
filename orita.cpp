#include<string>
#include<fstream>
#include<regex>
#include<vector>
#include<cstdlib>

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
template<typename ...others_type> std::string makepath(const std::string &path,const others_type ...others) {return path+PS+makepath(others...);}

void ssetenv(std::string key,std::string value)
{
    #ifdef _WIN32
    SetEnvironmentVariable(key.c_str(),value.c_str());
    #endif
    #ifdef __linux__
    setenv(key.c_str(),value.c_str(),true);
    #endif
}

std::string get_appdata_path()
{
    #ifdef _WIN32
    return makepath(getenv("appdata"),"Orita");
    #endif
    #ifdef __linux__
    return makepath(getenv("HOME"),".Orita");
    #endif
}

std::vector<std::string> init_file(int argc,char **argv)
{
    std::vector<std::string> args;
    for(int i=1;i<argc;++i)
    {
        #ifdef _WIN32
        WIN32_FIND_DATA findFileData;
        HANDLE hFind=FindFirstFile(argv[i],&findFileData);
        if(hFind==INVALID_HANDLE_VALUE)
        {
            args.push_back(argv[i]);
            continue;
        }
        do
        {
            args.push_back(findFileData.cFileName);
        }while(FindNextFile(hFind,&findFileData)!=0);
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
    if(argc>1&&std::string(argv[1])=="recompile")
    {
        ssystem("cmake -B "+makepath(path,"build")+" -S "+path);
        ssystem("cmake --build "+makepath(path,"build")+" --config Release --target orita");
        return 0;
    }
    std::vector<std::string> args=init_file(argc,argv);
    #ifdef _WIN32
    path=makepath(path,"main.exe");
    #endif
    #ifdef __linux__
    path=makepath(path,"main");
    #endif
    std::string command=add_quo(path);
    ssetenv("ORITA ARGS",std::to_string(args.size()));
    for(int i=0;i<args.size();++i)
    {
        ssetenv("ORITA ARGS "+std::to_string(i),args[i]);
    }
    return ssystem(command);
}