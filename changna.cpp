#include<bits/stdc++.h>
#include<windows.h>
#include"run.hpp"
using namespace std;
const int SUM=9;
json make_cor_parameter()
{
    json cor_parameter={
        {"f",{-1,2}}
    };
    for(int i=1;i<=SUM;++i) cor_parameter[to_string(i)]={-1,2};
    return cor_parameter;
}
json cor_parameter=make_cor_parameter();
int sum,value[1001],min_value[1001],max_value[1001];
string old_name,new_name;
int check_value(string str)
{
    int sum_bracket=0;
    auto check_number=[&](int pos)
    {
        if(pos<0||pos>=str.size()) return false;
        return (str[pos]>='0'&&str[pos]<='9')||str[pos]=='s'||str[pos]=='x';
    };
    for(int i=0;i<str.size();++i)
    {
        if(str[i]>='0'&&str[i]<='9')
        {
            if(str[i+1]=='x'||str[i+1]=='s') return 1;
        }
        else if(str[i]=='x')
        {
            if(str[i+1]<'1'||str[i+1]>'9') return 1;
            if(check_number(i+2)) return 1;
            ++i;
        }
        else if(str[i]=='s')
        {
            if(check_number(i+1)) return 1;
        }
        else if(str[i]=='+'||str[i]=='*'||str[i]=='/')
        {
            if(!check_number(i-1)&&!check_number(i+1)) return 1;
        }
        else if(str[i]=='-')
        {
            if(!check_number(i+1)) return 1;
        }
        else if(str[i]=='(')
        {
            if(check_number(i-1)) return 1;
            ++sum_bracket;
        }
        else if(str[i]==')')
        {
            if(check_number(i+1)) return 1;
            --sum_bracket;
            if(sum_bracket<0) return 1;
        }
        else if(str[i]==',') break;
        else return 1;
    }
    return 0;
}
int check_name(string str)
{
    for(int i=0;i<str.size();++i)
    {
        if(str[i]==':')
        {
            int j=str.find(':',i+1);
            if(j==string::npos) return 1;
            if(check_value(str.substr(i+1,j-i-1))) return 1;
            i=j;
        }
    }
    return 0;
}
string solve_value(string str)
{
    int sta1[1001],top1=0,top2=0;
    char sta2[1001];
    auto check_number=[&](int pos)
    {
        if(pos<0||pos>=str.size()) return false;
        return (str[pos]>='0'&&str[pos]<='9')||str[pos]=='s'||str[pos]=='x';
    };
    auto compute=[&]()
    {
        if(sta2[top2]=='+') sta1[top1-1]+=sta1[top1];
        if(sta2[top2]=='-') sta1[top1-1]-=sta1[top1];
        if(sta2[top2]=='*') sta1[top1-1]*=sta1[top1];
        if(sta2[top2]=='/') sta1[top1-1]/=sta1[top1];
        --top1,--top2;
    };
    int len_begin=-1;
    for(int i=0;i<str.size();++i)
    {
        if(str[i]>='0'&&str[i]<='9')
        {
            if((i<1||(str[i-1]<'0'||str[i-1]>'9'))) sta1[++top1]=str[i]-'0';
            else sta1[top1]=sta1[top1]*10+str[i]-'0';
        }
        if(str[i]=='x')
        {
            sta1[++top1]=value[str[i+1]-'0'];
            ++i;
        }
        if(str[i]=='s') sta1[++top1]=sum+1;
        if(str[i]=='+')
        {
            while(sta2[top2]=='*'||sta2[top2]=='/') compute();
            sta2[++top2]='+';
        }
        if(str[i]=='-')
        {
            if(!check_number(i-1)) sta1[++top1]=0;
            while(sta2[top2]=='*'||sta2[top2]=='/') compute();
            sta2[++top2]='-';
        }
        if(str[i]=='*') sta2[++top2]='*';
        if(str[i]=='/') sta2[++top2]='/';
        if(str[i]=='(') sta2[++top2]='(';
        if(str[i]==')')
        {
            while(sta2[top2]!='(') compute();
            --top2;
        }
        if(str[i]==',') len_begin=i+1;
    }
    while(top2>0) compute();
    char buf[1001];
    if(len_begin==-1) sprintf(buf,"%d",sta1[1]);
    else sprintf(buf,str.substr(len_begin,str.size()-len_begin).c_str(),sta1[1]);
    return buf;
}
string solve_name(string str)
{
    string solved_str;
    for(int i=0;i<str.size();++i)
    {
        if(str[i]==':')
        {
            int j=str.find(':',i+1);
            solved_str+=solve_value(str.substr(i+1,j-i-1));
            i=j;
        }
        else solved_str+=str[i];
    }
    return solved_str;
}
void make_scheme(int num)
{
    if(num==SUM+1)
    {
        string solved_old_name=solve_name(old_name),solved_new_name=solve_name(new_name);
        cout<<solved_old_name<<" -> "<<solved_new_name<<endl;
        if(system("copy \""+solved_old_name+"\" \"renamed\\"+solved_new_name+"\""+system_to_nul)==0)
        {
            print_result(_Success);
            ++sum;
        }
        else print_result(_Fail);
        return;
    }
    for(value[num]=min_value[num];value[num]<=max_value[num];++value[num]) make_scheme(num+1);
}
int changna_main(int argc,char **argv)
{
    if(init_parameter(argc,argv)) {print_result(_II);return 0;}
    if(check_parameter(cor_parameter)) {print_result(_II);return 0;}
    if(get_sum_parameter("f")<2)
    {
        print_result(_II);
        return 1;
    }
    old_name=get_parameter("f",1);
    new_name=get_parameter("f",2);
    if(check_name(get_parameter("f",1))||check_name(get_parameter("f",2)))
    {
        print_result(_II);
        return 1;
    }
    for(int i=1;i<=9;++i)
    {
        if(get_sum_parameter(to_string(i))>=2)
        {
            min_value[i]=stoi(get_parameter(to_string(i),1));
            max_value[i]=stoi(get_parameter(to_string(i),2));
        }
    }
    system("mkdir renamed"+system_to_nul);
    make_scheme(1);
    return 0;
}
int main(int argc,char **argv)
{
    Begin();
    int exit_code=changna_main(argc,argv);
    End();
    return exit_code;
}