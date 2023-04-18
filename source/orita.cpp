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
        std::cout<<"  Local Address: "<<file_address<<"\n";
        std::cout<<"--------------------------------------------------\n";
        return 0;
    }
    std::string inst=file_address+"\\build\\"+argv[1]+".exe";
    for(int i=2;i<argc;++i) inst+=" \""+std::string(argv[i])+"\" ";
    system(inst.c_str());
    return 0;
}