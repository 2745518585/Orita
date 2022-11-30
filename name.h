#ifndef NAME
#define NAME NAME
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
namespace Name
{
    const int N=1001;
    char files[N],name[N][N];
    FILE *file=NULL;
    void add_name(int num,char *name)
    {
        sprintf(files,"%s\\run\\name\\name%d.txt",getenv("appdata"),num);
        file=fopen(files,"w");
        fprintf(file,"%s",name);
        fclose(file);
    }
    char *get_name(int num)
    {
        sprintf(files,"%s\\run\\name\\name%d.txt",getenv("appdata"),num);
        file=fopen(files,"r");
        fscanf(file,"%s",name[num]);
        fclose(file);
        return name[num];
    }
    char *input_name(int num,char *name)
    {
        if(name==NULL) return get_name(num);
        add_name(num,name);
        return get_name(num);
    };
}
void add_name(int num,char name[]) {Name::add_name(num,name);}
char *get_name(int num) {return Name::get_name(num);}
char *input_name(int num,char *name) {return Name::input_name(num,name);}
#endif