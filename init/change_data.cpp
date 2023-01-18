#include<bits/stdc++.h>
#include<windows.h>
#include "..\run.h"
using namespace std;
const int N=1001;
char files[N];
FILE *file=NULL;
int main(int argc,char **argv)
{
    init_parameter(argc,argv);
    if(num_parameter['f']>=2)
    {
        if(copy_data_in(parameter['f'][1]))
        {
            print_result(-1);
            return 0;
        }
        if(copy_data_out(parameter['f'][2]))
        {
            print_result(-1);
            return 0;
        }
    }
    else if(num_parameter['s']!=-1)
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
    if(num_parameter['t']>=1)
    {
        change_time_limit(atoi(parameter['t'][1]));
    }
    change_color(1,0,1,0);
    printf("\nSuccess\n\n");
    change_color(1,1,1,1);
    return 0;
}