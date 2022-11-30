#include<bits/stdc++.h>
#include<windows.h>
#include "run.h"
using namespace std;
FILE *file=NULL;
int main()
{
    char x;
    file=fopen("data\\data.in","w");
    x=getchar();
    while(x!=EOF) fputc(x,file),x=getchar();
    file=fopen("data\\data.out","w");
    x=getchar();
    while(x!=EOF) fputc(x,file),x=getchar();
    return 0;
}