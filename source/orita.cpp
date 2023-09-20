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
        scout<<"  Local Path: "<<file_path.toString()<<"\n";
        scout<<"--------------------------------------------------\n";
        return 0;
    }
    if(std::string(argv[1])=="reset")
    {
        ((fil)appdata_path).remove(true);
        ((fil)file_path/"files").copyTo(appdata_path.toString());
        ssystem("echo "+(file_path/"build").toString()+" > "+add_quo(appdata_path/"path.txt"));
        return 0;
    }
    if(std::string(argv[1])=="clear")
    {
        ((fil)appdata_path).remove(true);
        return 0;
    }
    #ifdef _WIN32
    std::string command=add_quo(file_path/"build"/"bin"/(std::string(argv[1])+".exe"));
    #endif
    #ifdef __linux__
    std::string command=add_quo(file_path/"build"/"bin"/argv[1]);
    #endif
    for(int i=2;i<argc;++i) command+=" "+add_quo(std::regex_replace(systoUTF8(argv[i]),std::regex("\""),"\\\""))+" ";
    return ssystem(command);
}