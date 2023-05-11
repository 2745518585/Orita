#include"run.hpp"
const int SUM=9;
json make_cor_argu()
{
    json cor_argu={
        {"f",{1}}
    };
    for(int i=1;i<=SUM;++i) cor_argu[std::to_string(i)]={_not_define,2};
    return cor_argu;
}
json cor_argu=make_cor_argu();
int sum,value[1001],min_value[1001],max_value[1001];
std::string command;
int check_value(std::string str)
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
int check_name(std::string str)
{
    for(int i=0;i<str.size();++i)
    {
        if(str[i]==':')
        {
            int j=str.find(':',i+1);
            if(j==std::string::npos) return 1;
            if(check_value(str.substr(i+1,j-i-1))) return 1;
            i=j;
        }
    }
    return 0;
}
std::string solve_value(std::string str)
{
    static int sta1[1001],top1=0,top2=0;
    static char sta2[1001];
    top1=0,top2=0;
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
    static char buf[1001];
    if(len_begin==-1) sprintf(buf,"%d",sta1[1]);
    else sprintf(buf,str.substr(len_begin,str.size()-len_begin).c_str(),sta1[1]);
    return buf;
}
std::string solve_name(std::string str)
{
    std::string solved_str;
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
        std::string solved_command=solve_name(command);
        std::cout<<solved_command<<"\n";
        if(ssystem(system_to_nul+solved_command)==0)
        {
            print_result(_SS);
            ++sum;
        }
        else print_result(_FL);
        return;
    }
    for(value[num]=min_value[num];value[num]<=max_value[num];++value[num]) make_scheme(num+1);
}
int changna_main(int argc,char **argv)
{
    command=get_argu("f",1);
    if(check_name(get_argu("f",1)))
    {
        print_result(_II);
        return 1;
    }
    for(int i=1;i<=9;++i)
    {
        if(get_sum_argu(std::to_string(i))>=2)
        {
            min_value[i]=stoi(get_argu(std::to_string(i),1));
            max_value[i]=stoi(get_argu(std::to_string(i),2));
        }
    }
    make_scheme(1);
    return 0;
}
int main(int argc,char **argv)
{
    if(init_argu(argc,argv)) {print_result(_II);return 0;}
    if(check_argu(cor_argu)) {print_result(_II);return 0;}
    int exit_code=changna_main(argc,argv);
    return exit_code;
}