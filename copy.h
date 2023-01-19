#ifndef COPY
#define COPY COPY
#include<bits/stdc++.h>
#include<windows.h>
#include "name.h"
namespace Copy
{
    const int N=1001;
    char instruct[N];
    int copy_source(const char* file_address,const char* file_name,const char* copy_address,const char* copy_name)
    {
        sprintf(instruct,"copy \"%s\\%s\" \"%%appdata%%\\Orita\\%s\\%s\" > \"%%appdata%%\\Orita\\rubbish\\rubbish.txt\"",file_address,file_name,copy_address,copy_name);
        return system(instruct);
    }
    int copy_result(const char* file_address,const char* file_name,const char* copy_address,const char* copy_name)
    {
        sprintf(instruct,"copy \"%%appdata%%\\Orita\\%s\\%s\" \"%s\\%s\" > \"%%appdata%%\\Orita\\rubbish\\rubbish.txt\"",file_address,file_name,copy_address,copy_name);
        return system(instruct);
    }
}
int copy_source(const char* file_address,const char* file_name,const char* copy_address,const char* copy_name) {return Copy::copy_source(file_address,file_name,copy_address,copy_name);}
int copy_result(const char* file_address,const char* file_name,const char* copy_address,const char* copy_name) {return Copy::copy_result(file_address,file_name,copy_address,copy_name);}
#endif