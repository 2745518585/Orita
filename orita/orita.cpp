#include<iostream>
#include<string>
#include<windows.h>
using namespace std;
int main(int argc,char **argv)
{
    string para=__FILE__;
    int len=para.size();
    while(para[len-1]!='/'&&para[len-1]!='\\') --len;
    --len;
    while(para[len-1]!='/'&&para[len-1]!='\\') --len;
    --len;
    para=para.substr(0,len);
    for(int i=0;i<len;++i)
    {
        if(para[i]=='/'||para[len-1]=='\\') para[i]='\\';
    }
    para+="\\build\\orita";
    for(int i=1;i<argc;++i) para+=" \""+string(argv[i])+"\" ";
    system(para.c_str());
    return 0;
}