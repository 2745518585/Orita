#include<iostream>
#include<string>
#ifdef _WIN32
#include<windows.h>
char PS='\\';
#endif
#ifdef __linux__
char PS='/';
#endif
std::string get_file_path()
{
    char tmp[10001];
    #ifdef _WIN32
    GetModuleFileNameA(NULL,tmp,MAX_PATH);
    #endif
    #ifdef __linux__
    realpath("/proc/self/exe",tmp);
    #endif
    std::string path=tmp;
    return path.substr(0,path.find_last_of(PS,path.find_last_of(PS)-1));
}
int main(int argc,char **argv)
{
    std::string command=get_file_path();
    #ifdef _WIN32
    command="\""+command+PS+"build"+PS+"orita.exe"+"\"";
    #endif
    #ifdef __linux__
    command="\""+command+PS+"build"+PS+"orita"+"\"";
    #endif
    for(int i=1;i<argc;++i) command+=" \""+std::string(argv[i])+"\" ";
    #ifdef _WIN32
    system(("cmd /C \""+command+"\"").c_str());
    #endif
    #ifdef __linux__
    system(command.c_str());
    #endif
    return 0;
}