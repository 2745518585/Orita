#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
string get_path()
{
	char path[1001];
	GetModuleFileNameA(NULL,path,MAX_PATH);
	(strrchr(path,'\\'))[0]=0;
	return path;
}
int main(int argc,char **argv)
{
    if(argc==1)
    {
        cout<<"  Orita - Useful OI Tools\n";
        cout<<"  Version: Dev 0.0.11\n";
        cout<<"  Eepository: https://github.com/2745518585/Orita\n";
        return 0;
    }
    string inst=get_path()+"\\..\\"+argv[1]+".exe";
    for(int i=2;i<=argc-1;++i) inst+=" \""+string(argv[i])+"\" ";
    system(inst.c_str());
    return 0;
}