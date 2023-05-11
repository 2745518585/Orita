#include"init.hpp"
int main()
{
    #ifdef _WIN32
    ssystem("rmdir /s /Q \""+appdata_path+"\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+"\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+sPS+"data\""+system_to_nul);
    ssystem("echo 0 > \""+appdata_path+sPS+"data"+sPS+"data.in\"");
    ssystem("echo 0 > \""+appdata_path+sPS+"data"+sPS+"data.out\"");
    ssystem("mkdir \""+appdata_path+sPS+"random\""+system_to_nul);
    ssystem("copy \""+file_path+sPS+"files"+sPS+"windows"+sPS+"*\" \""+appdata_path+"\""+system_to_nul);
    #endif
    #ifdef __linux__
    ssystem("rm -r \""+appdata_path+"\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+"\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+sPS+"data\""+system_to_nul);
    ssystem("echo 0 > \""+appdata_path+sPS+"data"+sPS+"data.in\"");
    ssystem("echo 0 > \""+appdata_path+sPS+"data"+sPS+"data.out\"");
    ssystem("mkdir \""+appdata_path+sPS+"random\""+system_to_nul);
    ssystem("cp \""+file_path+sPS+"files"+sPS+"linux"+sPS+"\"* \""+appdata_path+"\""+system_to_nul);
    #endif
    return 0;
}