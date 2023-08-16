#include<string>
#include<fstream>

std::string add_quo(const std::string &str)
{
    return "\""+str+"\"";
}

#ifdef _WIN32
char PS='\\';
#endif
#ifdef __linux__
char PS='/';
#endif
std::string makepath(const std::string &path) {return path;}
template<typename ...others_type> std::string makepath(const std::string &path,const others_type ...others) {return path+PS+makepath(others...);}

std::string get_appdata_path()
{
    #ifdef _WIN32
    return makepath(getenv("appdata"),"Orita");
    #endif
    #ifdef __linux__
    return makepath(getenv("HOME"),".Orita");
    #endif
}
int main(int argc,char **argv)
{
    std::string path;
    (std::ifstream)(makepath(get_appdata_path(),"path.txt"))>>path;
    #ifdef _WIN32
    path=makepath(path,"orita.exe");
    #endif
    #ifdef __linux__
    path=makepath(path,"orita");
    #endif
    std::string command=add_quo(path);
    for(int i=1;i<argc;++i) command+=" \""+std::string(argv[i])+"\" ";
    #ifdef _WIN32
    system(("cmd /C "+add_quo(command)).c_str());
    #endif
    #ifdef __linux__
    system(command.c_str());
    #endif
    return 0;
}