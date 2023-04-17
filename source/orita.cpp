#include"init.hpp"
#include"Oritaconfig.hpp"
using namespace std;
int main(int argc,char **argv)
{
    if(argc==1)
    {
        cout<<"--------------------------------------------------\n";
        cout<<"  Orita - Useful OI Tools\n";
        cout<<"  Version: Dev "<<PROJECT_VERSION<<"\n";
        cout<<"  Repository: https://github.com/2745518585/Orita\n";
        cout<<"  Local Address: "<<file_address<<"\n";
        cout<<"--------------------------------------------------\n";
        return 0;
    }
    string inst=file_address+"\\build\\"+argv[1]+".exe";
    for(int i=2;i<argc;++i) inst+=" \""+string(argv[i])+"\" ";
    system(inst.c_str());
    return 0;
}