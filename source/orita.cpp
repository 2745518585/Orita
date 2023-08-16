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
        ssystem("mkdir "+add_quo(makepath(appdata_path,"data"))+system_to_nul);
        ssystem("echo 0 > "+add_quo(makepath(appdata_path,"data","data.in")));
        ssystem("echo 0 > "+add_quo(makepath(appdata_path,"data","data.out")));
        ssystem("mkdir "+add_quo(makepath(appdata_path,"random"))+system_to_nul);
        ssystem("copy "+add_quo(makepath(file_path,"files","windows",""))+"* "+add_quo(appdata_path)+system_to_nul);
        #endif
        #ifdef __linux__
        ssystem("rm -r "+add_quo(appdata_path)+system_to_nul);
        ssystem("mkdir "+add_quo(appdata_path)+system_to_nul);
        ssystem("mkdir "+add_quo(makepath(appdata_path,"data"))+system_to_nul);
        ssystem("echo 0 > "+add_quo(makepath(appdata_path,"data","data.in")));
        ssystem("echo 0 > "+add_quo(makepath(appdata_path,"data","data.out")));
        ssystem("mkdir "+add_quo(makepath(appdata_path,"random"))+system_to_nul);
        ssystem("cp "+add_quo(makepath(file_path,"files","linux",""))+"* "+add_quo(appdata_path)+system_to_nul);
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
    for(int i=2;i<argc;++i) command+=" "+add_quo(std::string(argv[i]))+" ";
    #ifdef _WIN32
    system(("cmd /C "+add_quo(command)).c_str());
    #endif
    #ifdef __linux__
    system(command.c_str());
    #endif
    return 0;
}