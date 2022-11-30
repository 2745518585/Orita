#include<bits/stdc++.h>
#include<windows.h>
#include "run.h"
using namespace std;
const int N=1001;
FILE *file=NULL;
char files[N];
int main()
{
    char x;
    sprintf(files,"%s\\run\\data\\data.in",getenv("appdata"));
    file=fopen(files,"w");
    x=getchar();
    while(x!=EOF) fputc(x,file),x=getchar();
    sprintf(files,"%s\\run\\data\\data.out",getenv("appdata"));
    file=fopen(files,"w");
    x=getchar();
    while(x!=EOF) fputc(x,file),x=getchar();
    return 0;
}