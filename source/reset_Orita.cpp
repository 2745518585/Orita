#include"init.hpp"
std::string change_form(std::string str)
{
    int pos=str.find("\\");
    while(pos!=std::string::npos)
    {
        str=(pos>0?str.substr(0,pos):"")+"\\\\"+str.substr(pos+1,str.size()-(pos+1));
        pos=str.find("\\",pos+2);
    }
    return GBtoUTF8(str);
}
int main()
{
    system("rmdir /s /Q \"%appdata%\\Orita\" > nul 2>&1");
    system("mkdir \"%appdata%\\Orita\" > nul 2>&1");
    system("mkdir \"%appdata%\\Orita\\data\" > nul 2>&1");
    system("echo 0 > \"%appdata%\\Orita\\data\\data.in\"");
    system("echo 0 > \"%appdata%\\Orita\\data\\data.out\"");
    system("mkdir \"%appdata%\\Orita\\source\" > nul 2>&1");
    system("mkdir \"%appdata%\\Orita\\temp\" > nul 2>&1");
    system("mkdir \"%appdata%\\Orita\\random\" > nul 2>&1");
    ssystem("copy \""+file_address+"\\files\\*\" \"%appdata%\\Orita\" > nul 2>&1");
    ssystem("echo "+change_form("{\"name100\":\""+appdata_address+"\\Orita\\0.cpp\",\"name101\":\""+appdata_address+"\\Orita\\1.cpp\"}")+" > \"%appdata%\\Orita\\name.json\"");
    return 0;
}