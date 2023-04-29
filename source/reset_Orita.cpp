#include"init.hpp"
std::string change_form(std::string str)
{
    int pos=str.find(sPS);
    while(pos!=std::string::npos)
    {
        str=(pos>0?str.substr(0,pos):"")+sPS+""+sPS+str.substr(pos+1,str.size()-(pos+1));
        pos=str.find(sPS,pos+2);
    }
    return systoUTF8(str);
}
int main()
{
    #ifdef _WIN32
    ssystem("rmdir /s /Q \""+appdata_path+"\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+"\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+sPS+"data\""+system_to_nul);
    ssystem("echo 0 > \""+appdata_path+sPS+"data"+sPS+"data.in\"");
    ssystem("echo 0 > \""+appdata_path+sPS+"data"+sPS+"data.out\"");
    ssystem("mkdir \""+appdata_path+sPS+"source\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+sPS+"temp\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+sPS+"random\""+system_to_nul);
    ssystem("copy \""+file_path+sPS+"files"+sPS+"*\" \""+appdata_path+"\""+system_to_nul);
    ssystem("echo "+change_form("{\"name100\":\""+appdata_path+sPS+"0.cpp\",\"name101\":\""+appdata_path+sPS+"1.cpp\"}")+" > \""+appdata_path+sPS+"name.json\"");
    #endif
    #ifdef __linux__
    ssystem("rm -r \""+appdata_path+"\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+"\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+sPS+"data\""+system_to_nul);
    ssystem("echo 0 > \""+appdata_path+sPS+"data"+sPS+"data.in\"");
    ssystem("echo 0 > \""+appdata_path+sPS+"data"+sPS+"data.out\"");
    ssystem("mkdir \""+appdata_path+sPS+"source\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+sPS+"temp\""+system_to_nul);
    ssystem("mkdir \""+appdata_path+sPS+"random\""+system_to_nul);
    ssystem("cp \""+file_path+sPS+"files"+sPS+"\"* \""+appdata_path+"\""+system_to_nul);
    ssystem("echo \\{\\\"name100\\\":\\\""+appdata_path+"/0.cpp\\\",\\\"name101\\\":\\\""+appdata_path+"/1.cpp\\\"\\} > \""+appdata_path+sPS+"name.json\"");
    #endif
    return 0;
}