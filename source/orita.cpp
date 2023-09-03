#include"init.hpp"
#include"Oritaconfig.hpp"
int main(int argc,char **argv)
{
    if(argc==1)
    {
        scout<<"--------------------------------------------------\n";
        scout<<"  Orita - Useful OI Tools\n";
        scout<<"  Version: Dev "<<PROJECT_VERSION<<"\n";
        scout<<"  Repository: https://github.com/2745518585/Orita\n";
        scout<<"  Local Path: "<<file_path.string()<<"\n";
        scout<<"--------------------------------------------------\n";
        return 0;
    }
    if(std::string(argv[1])=="reset")
    {
        std::filesystem::remove_all(appdata_path);
        #ifdef _WIN32
        std::filesystem::copy(file_path/"files"/"windows",appdata_path,std::filesystem::copy_options::recursive);
        #endif
        #ifdef __linux__
        std::filesystem::copy(file_path/"files"/"linux",appdata_path,std::filesystem::copy_options::recursive);
        #endif
        ssystem("echo "+(file_path/"build").string()+" > "+add_quo(appdata_path/"path.txt"));
        return 0;
    }
    if(std::string(argv[1])=="clear")
    {
        std::filesystem::remove_all(appdata_path);
        return 0;
    }
    #ifdef _WIN32
    std::string command=add_quo(file_path/"build"/(std::string(argv[1])+".exe"));
    #endif
    #ifdef __linux__
    std::string command=add_quo(file_path/"build"/argv[1]);
    #endif
    for(int i=2;i<argc;++i) command+=" "+add_quo(std::regex_replace(systoUTF8(argv[i]),std::regex("\""),"\\\""))+" ";
    ssystem(command);
    return 0;
}