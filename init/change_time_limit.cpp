#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
const int N=1001;
FILE *file=NULL;
char files[N];
int main()
{
    int time;
    scanf("%d",&time);
    sprintf(files,"%s\\run\\data\\time.txt",getenv("appdata"));
    file=fopen(files,"w");
    fprintf(file,"%d",time);
    return 0;
}