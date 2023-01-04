#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
const int N=1001;
char files[N],instruct[N];
FILE *file=NULL;
int main()
{
    system("dir /b /s /d ..\\ > files.txt");
    file=fopen("files.txt","r");
    while(~fscanf(file,"%s",files))
    {
        char length=strlen(files);
        if(files[length-4]=='.'&&files[length-3]=='c'&&files[length-2]=='p'&&files[length-1]=='p')
        {
            files[length-4]='\0';
            sprintf(instruct,"g++ %s.cpp -o %s.exe -std=c++14 -O2 -Wl,--stack=2147483647",files,files);
            system(instruct);
        }
    }
    fclose(file);
    system("del /Q files.txt");
    return 0;
}