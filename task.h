#ifndef TASK
#define TASK TASK
#include<bits/stdc++.h>
#include<windows.h>
#include "name.h"
using namespace std;
namespace Task
{
    const int N=1001;
    char *name,task[N],instruct[N],files[N];
    FILE* file=NULL;
    bool check()
    {
        int length=strlen(name);
        for(int i=0;i<length;++i) if(name[i]!=task[i]) return false;
        if(task[length]=='.'&&task[length+1]=='e'&&task[length+2]=='x'&&task[length+3]=='e') return true;
        return false;
    }
    int find_task(int name_num)
    {
        name=get_name_pre(name_num);
        sprintf(instruct,"tasklist /NH /FI \"IMAGENAME eq %s.exe\" > %s\\Orita\\task\\task.txt",name,getenv("appdata"));
        system(instruct);
        sprintf(files,"%s\\Orita\\task\\task.txt",getenv("appdata"));
        file=fopen(files,"r");
        while(fgets(task,1000,file))
        {
            if(check())
            {
                fclose(file);
                return 1;
            }
        }
        fclose(file);
        return 0;
    }
}
int find_task(int name_num) {return Task::find_task(name_num);}
#endif