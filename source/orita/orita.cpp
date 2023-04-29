#include<iostream>
#include<string>
#ifdef _WIN32
char PS='\\';
#endif
#ifdef __linux__
char PS='/';
#endif
std::string get_file_path()
{
    std::string path=__FILE__;
    int len=path.size();
    for(int i=0;i<len;++i)
    {
        if(path[i]=='/'||path[i]=='\\') path[i]=PS;
    }
    while(path[len-1]!=PS) --len;
    --len;
    while(path[len-1]!=PS) --len;
    --len;
    while(path[len-1]!=PS) --len;
    --len;
    path=path.substr(0,len);
    return path;
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