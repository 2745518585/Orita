#include"init.hpp"
std::string change_form(std::string str)
{
    int pos=str.find(sPATH_SE);
    while(pos!=std::string::npos)
    {
        str=(pos>0?str.substr(0,pos):"")+sPATH_SE+""+sPATH_SE+str.substr(pos+1,str.size()-(pos+1));
        pos=str.find(sPATH_SE,pos+2);
    }
    return systoUTF8(str);
}
int main()
{
    #ifdef _WIN32
    ssystem("rmdir /s /Q \""+appdata_path+"\" > nul 2>&1");
    ssystem("mkdir \""+appdata_path+"\" > nul 2>&1");
    ssystem("mkdir \""+appdata_path+sPATH_SE+"data\" > nul 2>&1");
    ssystem("echo 0 > \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.in\"");
    ssystem("echo 0 > \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.out\"");
    ssystem("mkdir \""+appdata_path+sPATH_SE+"source\" > nul 2>&1");
    ssystem("mkdir \""+appdata_path+sPATH_SE+"temp\" > nul 2>&1");
    ssystem("mkdir \""+appdata_path+sPATH_SE+"random\" > nul 2>&1");
    ssystem("copy \""+file_path+sPATH_SE+"files"+sPATH_SE+"*\" \""+appdata_path+"\" > nul 2>&1");
    ssystem("echo "+change_form("{\"name100\":\""+appdata_path+sPATH_SE+"0.cpp\",\"name101\":\""+appdata_path+sPATH_SE+"1.cpp\"}")+" > \""+appdata_path+sPATH_SE+"name.json\"");
    #endif
    #ifdef __linux__
    ssystem("rm -r \""+appdata_path+"\" > nul 2>&1");
    ssystem("mkdir \""+appdata_path+"\" > nul 2>&1");
    ssystem("mkdir \""+appdata_path+sPATH_SE+"data\" > nul 2>&1");
    ssystem("echo 0 > \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.in\"");
    ssystem("echo 0 > \""+appdata_path+sPATH_SE+"data"+sPATH_SE+"data.out\"");
    ssystem("mkdir \""+appdata_path+sPATH_SE+"source\" > nul 2>&1");
    ssystem("mkdir \""+appdata_path+sPATH_SE+"temp\" > nul 2>&1");
    ssystem("mkdir \""+appdata_path+sPATH_SE+"random\" > nul 2>&1");
    ssystem("cp \""+file_path+sPATH_SE+"files"+sPATH_SE+"\"* \""+appdata_path+"\" > nul 2>&1");
    ssystem("echo \\{\\\"name100\\\":\\\""+appdata_path+"/0.cpp\\\",\\\"name101\\\":\\\""+appdata_path+"/1.cpp\\\"\\} > \""+appdata_path+sPATH_SE+"name.json\"");
    #endif
    return 0;
}