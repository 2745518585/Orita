#ifndef COPY
#define COPY COPY
#include<bits/stdc++.h>
#include<windows.h>
namespace Copy
{
    const int N=1001;
    char instruct[N];
    int copy_source(char *name)
    {
        sprintf(instruct,"copy %s %%appdata%%\\Orita\\source\\ > %%appdata%%\\Orita\\rubbish\\rubbish.txt",name);
        return system(instruct);
    }
    int copy_data_in(char *name)
    {
        sprintf(instruct,"copy %s %%appdata%%\\Orita\\data\\data.in > %%appdata%%\\Orita\\rubbish\\rubbish.txt",name);
        return system(instruct);
    }
    int copy_data_out(char *name)
    {
        sprintf(instruct,"copy %s %%appdata%%\\Orita\\data\\data.out > %%appdata%%\\Orita\\rubbish\\rubbish.txt",name);
        return system(instruct);
    }
}
int copy_source(char *name) {return Copy::copy_source(name);}
int copy_data_in(char *name) {return Copy::copy_data_in(name);}
int copy_data_out(char *name) {return Copy::copy_data_out(name);}
#endif