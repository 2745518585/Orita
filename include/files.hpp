#ifndef _FILE_FILES
#define _FILE_FILES _FILE_FILES
#include"name.hpp"
namespace Files
{
    int copy_source(string file,string copy)
    {
        return system("copy \""+file+"\" \""+appdata_address+"\\Orita\\"+copy+"\""+system_to_nul);
    }
    int copy_result(string file,string copy)
    {
        return system("copy \""+appdata_address+"\\Orita\\"+file+"\" \""+copy+"\""+system_to_nul);
    }
    int find_file(string file)
    {
        return system("dir \""+file+"\""+system_to_nul);
    }
}
int copy_source(string file,string copy) {return Files::copy_source(file,copy);}
int copy_result(string file,string copy) {return Files::copy_result(file,copy);}
int find_file(string file) {return Files::find_file(file);}
#endif