#include<init.hpp>
using namespace std;
int main(int argc,char **argv)
{
    if(argc==1)
    {
        cout<<"--------------------------------------------------\n";
        cout<<"  Orita - Useful OI Tools\n";
        cout<<"  Version: Dev 0.0.11\n";
        cout<<"  Repository: https://github.com/2745518585/Orita\n";
        cout<<"--------------------------------------------------\n";
        return 0;
    }
    string inst=file_address+"\\..\\"+argv[1]+".exe";
    for(int i=2;i<=argc-1;++i) inst+=" \""+string(argv[i])+"\" ";
    system(inst.c_str());
    return 0;
}