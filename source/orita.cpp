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
        std::cout<<"  Local Path: "<<file_path<<"\n";
        std::cout<<"--------------------------------------------------\n";
        return 0;
    }
    if(std::string(argv[1])=="reset")
    {
        #ifdef _WIN32
        ssystem("rmdir /s /Q "+add_quo(appdata_path)+system_to_nul);
        ssystem("mkdir "+add_quo(appdata_path)+system_to_nul);
        ssystem("echo "+makepath(file_path,"build")+" > "+add_quo(makepath(appdata_path,"path.txt")));
        ssystem("xcopy /s /e /i /h /y "+add_quo(makepath(file_path,"files","windows",""))+"* "+add_quo(appdata_path)+system_to_nul);
        #endif
        #ifdef __linux__
        ssystem("rm -r "+add_quo(appdata_path)+system_to_nul);
        ssystem("mkdir "+add_quo(appdata_path)+system_to_nul);
        ssystem("echo "+makepath(file_path,"build")+" > "+add_quo(makepath(appdata_path,"path.txt")));
        ssystem("cp -r "+add_quo(makepath(file_path,"files","linux",""))+"* "+add_quo(appdata_path)+system_to_nul);
        #endif
        return 0;
    }
    if(std::string(argv[1])=="clear")
    {
        #ifdef _WIN32
        ssystem("rmdir /s /Q "+add_quo(appdata_path)+system_to_nul);
        #endif
        #ifdef __linux__
        ssystem("rm -r "+add_quo(appdata_path)+system_to_nul);
        #endif
        return 0;
    }
    #ifdef _WIN32
    std::string command=add_quo(makepath(file_path,"build",std::string(argv[1])+".exe"));
    #endif
    #ifdef __linux__
    std::string command=add_quo(makepath(file_path,"build",argv[1]));
    #endif
    for(int i=2;i<argc;++i) command+=" "+add_quo(std::regex_replace(argv[i],std::regex("\""),"\\\""))+" ";
    ssystem(command);
    return 0;
}