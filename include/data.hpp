#ifndef DATA
#define DATA DATA
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
namespace Data
{
    const int N=1001;
    int time;
    char files[N];
    FILE *file=NULL;
    void change_time_limit(int time)
    {
        sprintf(files,"%s\\Orita\\data\\time.txt",getenv("appdata"));
        file=fopen(files,"w");
        fprintf(file,"%d",time);
        fclose(file);
    }
    int get_time_limit()
    {
        sprintf(files,"%s\\Orita\\data\\time.txt",getenv("appdata"));
        file=fopen(files,"r");
        fscanf(file,"%d",&time);
        fclose(file);
        return time;
    }
}
void change_time_limit(int time) {Data::change_time_limit(time);}
int get_time_limit() {return Data::get_time_limit();}
#endif