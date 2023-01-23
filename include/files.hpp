#ifndef FILES
#define FILES FILES
#include"name.hpp"
namespace Files
{
    int copy_source(string file_address,string file_name,string copy_address,string copy_name)
    {
        return system("copy \""+file_address+"\\"+file_name+"\" \"%appdata%\\Orita\\"+copy_address+"\\"+copy_name+"\""+system_to_nul);
    }
    int copy_result(string file_address,string file_name,string copy_address,string copy_name)
    {
        return system("copy \"%appdata%\\Orita\\"+file_address+"\\"+file_name+"\" \""+copy_address+"\\"+copy_name+"\""+system_to_nul);
    }
    int find_file(int name_num)
    {
        return system("dir \""+get_address(name_num)+"\\"+get_name(name_num)+"\""+system_to_nul);
    }
    int find_file(string file_address,string file_name)
    {
        return system("dir \""+file_address+"\\"+file_name+"\""+system_to_nul);
    }
}
int copy_source(string file_address,string file_name,string copy_address,string copy_name) {return Files::copy_source(file_address,file_name,copy_address,copy_name);}
int copy_result(string file_address,string file_name,string copy_address,string copy_name) {return Files::copy_result(file_address,file_name,copy_address,copy_name);}
int find_file(int name_num) {return Files::find_file(name_num);}
int find_file(string file_address,string file_name) {return Files::find_file(file_address,file_name);}
#endif