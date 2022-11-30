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
        sprintf(instruct,"copy %s.cpp \"E:\\1.C++\\code\\run\\source\\\" > \"E:\\1.C++\\code\\run\\rubbish\\rubbish.txt\"",name);
        return system(instruct);
    }
}
int copy(char name[]) {return Copy::copy(name);}
#endif