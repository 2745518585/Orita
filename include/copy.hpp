#ifndef COPY
#define COPY COPY
#include<bits/stdc++.h>
#include<windows.h>
#include"name.hpp"
namespace Copy
{
    int copy_source(string file_address,string file_name,string copy_address,string copy_name)
    {
        return system(("copy \""+file_address+"\\"+file_name+"\" \"%appdata%\\Orita\\"+copy_address+"\\"+copy_name+"\" > \"%appdata%\\Orita\\rubbish\\rubbish.txt\" 2>&1").c_str());
    }
    int copy_result(string file_address,string file_name,string copy_address,string copy_name)
    {
        return system(("copy \"%appdata%\\Orita\\"+file_address+"\\"+file_name+"\" \""+copy_address+"\\"+copy_name+"\" > \"%appdata%\\Orita\\rubbish\\rubbish.txt\" 2>&1").c_str());
    }
}
int copy_source(string file_address,string file_name,string copy_address,string copy_name) {return Copy::copy_source(file_address,file_name,copy_address,copy_name);}
int copy_result(string file_address,string file_name,string copy_address,string copy_name) {return Copy::copy_result(file_address,file_name,copy_address,copy_name);}
#endif