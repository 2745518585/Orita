#include<bits/stdc++.h>
#include<windows.h>
#include "run.h"
using namespace std;
const int N=1001;
char files[N];
FILE *file=NULL;
int main(int argc,const char **argv)
{
    init_parameter(argc,argv);
    if(get_sum_parameter("f")>=2)
    {
        if(copy_source(".\\",get_parameter("f",1),"data","data.in"))
        {
            print_result(No_such_file);
            return 0;
        }
        if(copy_source(".\\",get_parameter("f",1),"data","data.in"))
        {
            print_result(No_such_file);
            return 0;
        }
    }
    else if(get_sum_parameter("s")!=-1)
    {
        char x;
        sprintf(files,"%s\\Orita\\data\\data.in",getenv("appdata"));
        file=fopen(files,"w");
        x=getchar();
        while(x!=EOF) fputc(x,file),x=getchar();
        sprintf(files,"%s\\Orita\\data\\data.out",getenv("appdata"));
        file=fopen(files,"w");
        x=getchar();
        while(x!=EOF) fputc(x,file),x=getchar();
    }
    if(get_sum_parameter("t")>=1)
    {
        change_time_limit(atoi(get_parameter("t",1)));
    }
    change_color(1,0,1,0);
    printf("\nSuccess\n\n");
    change_color(1,1,1,1);
    return 0;
}