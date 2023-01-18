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
    int copy_result(const char *name)
    {
        sprintf(instruct,"copy \"%%appdata%%\\Orita\\data\\%s\" \"data\\\" > \"%%appdata%%\\Orita\\rubbish\\rubbish.txt\"",name);
        return system(instruct);
    }
    int copy_data_in(const char *name)
    {
        sprintf(instruct,"copy \"%s\" \"%%appdata%%\\Orita\\data\\data.in\" > \"%%appdata%%\\Orita\\rubbish\\rubbish.txt\"",name);
        return system(instruct);
    }
    int copy_data_out(const char *name)
    {
        sprintf(instruct,"copy \"%s\" \"%%appdata%%\\Orita\\data\\data.out\" > \"%%appdata%%\\Orita\\rubbish\\rubbish.txt\"",name);
        return system(instruct);
    }
}
int copy_source(int num) {return Copy::copy_source(num);}
int copy_result(const char* name) {return Copy::copy_result(name);}
int copy_data_in(const char *name) {return Copy::copy_data_in(name);}
int copy_data_out(const char *name) {return Copy::copy_data_out(name);}
#endif