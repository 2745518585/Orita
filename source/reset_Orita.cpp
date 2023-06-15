#include"init.hpp"
int main()
{
    #ifdef _WIN32
    ssystem("rmdir /s /Q "+add_quotation(appdata_path)+system_to_nul);
    ssystem("mkdir "+add_quotation(appdata_path)+system_to_nul);
    ssystem("mkdir "+add_quotation(makepath(appdata_path,"data"))+system_to_nul);
    ssystem("echo 0 > "+add_quotation(makepath(appdata_path,"data","data.in")));
    ssystem("echo 0 > "+add_quotation(makepath(appdata_path,"data","data.out")));
    ssystem("mkdir "+add_quotation(makepath(appdata_path,"random"))+system_to_nul);
    ssystem("copy "+add_quotation(makepath(file_path,"files","windows","*"))+" "+add_quotation(appdata_path)+system_to_nul);
    #endif
    #ifdef __linux__
    ssystem("rm -r "+add_quotation(appdata_path)+system_to_nul);
    ssystem("mkdir "+add_quotation(appdata_path)+system_to_nul);
    ssystem("mkdir "+add_quotation(makepath(appdata_path,"data"))+system_to_nul);
    ssystem("echo 0 > "+add_quotation(makepath(appdata_path,"data","data.in")));
    ssystem("echo 0 > "+add_quotation(makepath(appdata_path,"data","data.out")));
    ssystem("mkdir "+add_quotation(makepath(appdata_path,"random"))+system_to_nul);
    ssystem("cp "+add_quotation(makepath(file_path,"files","linux","*"))+" "+add_quotation(appdata_path)+system_to_nul);
    #endif
    return 0;
}