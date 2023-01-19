#ifndef COPY
#define COPY COPY
#include<bits/stdc++.h>
#include<windows.h>
#include "name.h"
namespace Copy
{
    const int N=1001;
    char instruct[N];
    int copy_source(int num)
    {
        sprintf(instruct,"copy \"%s\\%s\" \"%%appdata%%\\Orita\\source\\\" > \"%%appdata%%\\Orita\\rubbish\\rubbish.txt\"",get_address(num),get_name(num));
        return system(instruct);
    }
    int copy_data(const char *name,const char *copy_name)
    {
        sprintf(instruct,"copy \"%s\" \"%%appdata%%\\Orita\\data\\%s\" > \"%%appdata%%\\Orita\\rubbish\\rubbish.txt\"",name,copy_name);
        return system(instruct);
    }
    int copy_result(const char *name)
    {
        sprintf(instruct,"copy \"%%appdata%%\\Orita\\data\\%s\" \"data\\\" > \"%%appdata%%\\Orita\\rubbish\\rubbish.txt\"",name);
        return system(instruct);
    }
    int copy_result(const char *name,const char *copy_name)
    {
        sprintf(instruct,"copy \"%%appdata%%\\Orita\\data\\%s\" \"data\\%s\" > \"%%appdata%%\\Orita\\rubbish\\rubbish.txt\"",name,copy_name);
        return system(instruct);
    }
}
int copy_source(int num) {return Copy::copy_source(num);}
int copy_result(const char* name) {return Copy::copy_result(name);}
int copy_result(const char* name,const char *copy_name) {return Copy::copy_result(name,copy_name);}
int copy_data(const char *name,const char *copy_name) {return Copy::copy_data(name,copy_name);}
#endif