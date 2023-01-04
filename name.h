#ifndef NAME
#define NAME NAME
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
namespace Name
{
    const int N=1001;
    char files[N],name[N][N],name_pre[N][N],name_suf[N][N];
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
    char *get_name_pre(int num)
    {
        sprintf(files,"%s\\run\\name\\name%d.txt",getenv("appdata"),num);
        file=fopen(files,"r");
        fscanf(file,"%s",name_pre[num]);
        fclose(file);
        int length=strlen(name_pre[num]);
        for(int i=length-1;i>=0;--i)
        {
            if(name_pre[num][i]=='.')
            {
                name_pre[num][i]='\0';
                break;
            }
        }
        return name_pre[num];
    }
    char *get_name_suf(int num)
    {
        sprintf(files,"%s\\run\\name\\name%d.txt",getenv("appdata"),num);
        file=fopen(files,"r");
        fscanf(file,"%s",name_suf[num]);
        fclose(file);
        int length=strlen(name_suf[num]);
        bool if_find=false;
        for(int i=length-1;i>=0;--i)
        {
            if(name_suf[num][i]=='.')
            {
                if_find=true;
                for(int j=0;j<length-i;++j) name_suf[num][j]=name_suf[num][i+j];
                name_suf[num][length-i]='\0';
                break;
            }
        }
        if(if_find==false) name_suf[num][0]='\0';
        return name_suf[num];
    }
    void input_name(int num,char *name)
    {
        if(name==NULL) return;
        add_name(num,name);
    };
    void input_name(int num,char *name,char *name_suf)
    {
        if(name==NULL) return;
        int length_name=strlen(name),length_name_suf=strlen(name_suf);
        bool if_name_suf=true;
        for(int i=0;i<length_name_suf;++i)
        {
            if(name[length_name-i-1]!=name_suf[length_name_suf-i-1])
            {
                if_name_suf=false;
                break;
            }
        }
        if(if_name_suf==false) sprintf(name,"%s%s",name,name_suf);
        add_name(num,name);
    };
}
void add_name(int num,char name[]) {Name::add_name(num,name);}
char *get_name(int num) {return Name::get_name(num);}
char *get_name_pre(int num) {return Name::get_name_pre(num);}
char *get_name_suf(int num) {return Name::get_name_suf(num);}
void input_name(int num,char *name) {Name::input_name(num,name);}
void input_name(int num,char *name,char *name_suf) {Name::input_name(num,name,name_suf);}
#endif