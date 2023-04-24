#include"init.hpp"
#include"Oritaconfig.hpp"
int main(int argc,char **argv)
{
    if(argc==1)
    {
        std::cout<<"--------------------------------------------------\n";
        std::cout<<"  Orita - Useful OI Tools\n";
        std::cout<<"  Version: Dev "<<PROJECT_VERSION<<"\n";
        std::cout<<"  Repository: https://github.com/2745518585/Orita\n";
        std::cout<<"  Local Address: "<<file_path<<"\n";
        std::cout<<"--------------------------------------------------\n";
        return 0;
    }
    #ifdef _WIN32
    std::string command="\""+file_path+sPATH_SE+"build"+sPATH_SE+argv[1]+".exe\"";
    #endif
    #ifdef __linux__
    std::string command="\""+file_path+sPATH_SE+"build"+sPATH_SE+argv[1]+"\"";
    #endif
    for(int i=2;i<argc;++i) command+=" \""+std::string(argv[i])+"\" ";
    #ifdef _WIN32
    system(("cmd /C \""+command+"\"").c_str());
    #endif
    #ifdef __linux__
    system(command.c_str());
    #endif
    return 0;
}