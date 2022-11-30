#ifndef COPY
#define COPY COPY
#include<bits/stdc++.h>
#include<windows.h>
namespace Copy
{
    const int N=1001;
    char instruct[N];
    int copy(char name[])
    {
        sprintf(instruct,"copy %s.cpp %s\\run\\source\\ > %s\\run\\rubbish\\rubbish.txt",name,getenv("appdata"),getenv("appdata"));
        return system(instruct);
    }
}
int copy(char name[]) {return Copy::copy(name);}
#endif