#ifndef DATA_MAKER
#define DATA_MAKER DATA_MAKER
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
namespace Data_maker
{
    unsigned int init_rnd()
    {
        ifstream infile(string(getenv("appdata"))+"\\Orita\\random\\seed.txt");
        unsigned int seed;
        infile>>seed;
        infile.close();
        seed=seed+(seed<<7)+(seed>>11)+(seed<<13)+time(NULL);
        ofstream outfile(string(getenv("appdata"))+"\\Orita\\random\\seed.txt");
        outfile<<seed;
        outfile.close();
        return seed;
    }
    mt19937 rd(init_rnd());
    bool if_pair;
    long long last_pair;
    unsigned long long rnd()
    {
        return ((unsigned long long)rd()<<32)+rd();
    }
    long long rnd(long long limit)
    {
        return rnd()%limit;
    }
    long long rnd(long long Llimit,long long Ulimit)
    {
        return rnd(Ulimit-Llimit+1)+Llimit;
    }
    long long rnd_neq(long long limit)
    {
        long long num;
        if(if_pair==true)
        {
            num=rnd(limit);
            while(!(num!=last_pair)) num=rnd(limit);
            if_pair=false;
        }
        else
        {
            num=rnd(limit);
            last_pair=num,if_pair=true;
        }
        return num;
    }
    long long rnd_gre(long long limit)
    {
        long long num;
        if(if_pair==true)
        {
            num=rnd(limit);
            while(!(num>last_pair)) num=rnd(limit);
            if_pair=false;
        }
        else
        {
            num=rnd(limit)+rnd(limit)+1;
            while(!(num<limit)) num=rnd(limit)+rnd(limit)+1;
            last_pair=num,if_pair=true;
        }
        return num;
    }
    long long rnd_les(long long limit)
    {
        long long num;
        if(if_pair==true)
        {
            num=rnd(limit);
            while(!(num<last_pair)) num=rnd(limit);
            if_pair=false;
        }
        else
        {
            num=rnd(limit)+rnd(limit)-(limit-1)+1;
            while(!(num>=0)) num=rnd(limit)+rnd(limit)-(limit-1)-1;
            last_pair=num,if_pair=true;
        }
        return num;
    }
    long long rnd_goe(long long limit)
    {
        long long num;
        if(if_pair==true)
        {
            num=rnd(limit);
            while(!(num>=last_pair)) num=rnd(limit);
            if_pair=false;
        }
        else
        {
            num=rnd(limit)+rnd(limit);
            while(!(num<limit)) num=rnd(limit)+rnd(limit);
            last_pair=num,if_pair=true;
        }
        return num;
    }
    long long rnd_loe(long long limit)
    {
        long long num;
        if(if_pair==true)
        {
            num=rnd(limit);
            while(!(num<=last_pair)) num=rnd(limit);
            if_pair=false;
        }
        else
        {
            num=rnd(limit)+rnd(limit)-(limit-1);
            while(!(num>=0)) num=rnd(limit)+rnd(limit)-(limit-1);
            last_pair=num,if_pair=true;
        }
        return num;
    }
    void print_rnd_neq(long long limit,string mid,string end)
    {
        long long num1=rnd_neq(limit),num2=rnd_neq(limit);
        cout<<num1<<mid<<num2<<end;
    }
    void print_rnd_gre(long long limit,string mid,string end)
    {
        long long num1=rnd_gre(limit),num2=rnd_les(limit);
        cout<<num1<<mid<<num2<<end;
    }
    void print_rnd_les(long long limit,string mid,string end)
    {
        long long num1=rnd_les(limit),num2=rnd_gre(limit);
        cout<<num1<<mid<<num2<<end;
    }
    void print_rnd_goe(long long limit,string mid,string end)
    {
        long long num1=rnd_goe(limit),num2=rnd_loe(limit);
        cout<<num1<<mid<<num2<<end;
    }
    void print_rnd_loe(long long limit,string mid,string end)
    {
        long long num1=rnd_loe(limit),num2=rnd_goe(limit);
        cout<<num1<<mid<<num2<<end;
    }
    long long rnd_neq(long long Llimit,long long Ulimit)
    {
        if(Llimit>Ulimit) swap(Llimit,Ulimit);
        return rnd_neq(Ulimit-Llimit+1)+Llimit;
    }
    long long rnd_gre(long long Llimit,long long Ulimit)
    {
        if(Llimit>Ulimit) swap(Llimit,Ulimit);
        return rnd_gre(Ulimit-Llimit+1)+Llimit;
    }
    long long rnd_les(long long Llimit,long long Ulimit)
    {
        if(Llimit>Ulimit) swap(Llimit,Ulimit);
        return rnd_les(Ulimit-Llimit+1)+Llimit;
    }
    long long rnd_goe(long long Llimit,long long Ulimit)
    {
        if(Llimit>Ulimit) swap(Llimit,Ulimit);
        return rnd_goe(Ulimit-Llimit+1)+Llimit;
    }
    long long rnd_loe(long long Llimit,long long Ulimit)
    {
        if(Llimit>Ulimit) swap(Llimit,Ulimit);
        return rnd_loe(Ulimit-Llimit+1)+Llimit;
    }
    void print_rnd_neq(long long Llimit,long long Ulimit,string mid,string end)
    {
        long long num1=rnd_neq(Llimit,Ulimit),num2=rnd_neq(Llimit,Ulimit);
        cout<<num1<<mid<<num2<<end;
    }
    void print_rnd_gre(long long Llimit,long long Ulimit,string mid,string end)
    {
        long long num1=rnd_gre(Llimit,Ulimit),num2=rnd_les(Llimit,Ulimit);
        cout<<num1<<mid<<num2<<end;
    }
    void print_rnd_les(long long Llimit,long long Ulimit,string mid,string end)
    {
        long long num1=rnd_les(Llimit,Ulimit),num2=rnd_gre(Llimit,Ulimit);
        cout<<num1<<mid<<num2<<end;
    }
    void print_rnd_goe(long long Llimit,long long Ulimit,string mid,string end)
    {
        long long num1=rnd_goe(Llimit,Ulimit),num2=rnd_loe(Llimit,Ulimit);
        cout<<num1<<mid<<num2<<end;
    }
    void print_rnd_loe(long long Llimit,long long Ulimit,string mid,string end)
    {
        long long num1=rnd_loe(Llimit,Ulimit),num2=rnd_goe(Llimit,Ulimit);
        cout<<num1<<mid<<num2<<end;
    }
}
long long rnd() {return Data_maker::rnd();}
long long rnd(long long limit) {return Data_maker::rnd(limit);}
long long rnd(long long Llimit,long long Ulimit) {return Data_maker::rnd(Llimit,Ulimit);}
long long rnd_neq(long long limit) {return Data_maker::rnd_neq(limit);}
long long rnd_gre(long long limit) {return Data_maker::rnd_gre(limit);}
long long rnd_les(long long limit) {return Data_maker::rnd_les(limit);}
long long rnd_goe(long long limit) {return Data_maker::rnd_goe(limit);}
long long rnd_loe(long long limit) {return Data_maker::rnd_loe(limit);}
void print_rnd_neq(long long limit,string mid,string end) {Data_maker::print_rnd_neq(limit,mid,end);}
void print_rnd_gre(long long limit,string mid,string end) {Data_maker::print_rnd_gre(limit,mid,end);}
void print_rnd_les(long long limit,string mid,string end) {Data_maker::print_rnd_les(limit,mid,end);}
void print_rnd_goe(long long limit,string mid,string end) {Data_maker::print_rnd_goe(limit,mid,end);}
void print_rnd_loe(long long limit,string mid,string end) {Data_maker::print_rnd_loe(limit,mid,end);}
long long rnd_neq(long long Llimit,long long Ulimit) {return Data_maker::rnd_neq(Llimit,Ulimit);}
long long rnd_gre(long long Llimit,long long Ulimit) {return Data_maker::rnd_gre(Llimit,Ulimit);}
long long rnd_les(long long Llimit,long long Ulimit) {return Data_maker::rnd_les(Llimit,Ulimit);}
long long rnd_goe(long long Llimit,long long Ulimit) {return Data_maker::rnd_goe(Llimit,Ulimit);}
long long rnd_loe(long long Llimit,long long Ulimit) {return Data_maker::rnd_loe(Llimit,Ulimit);}
void print_rnd_neq(long long Llimit,long long Ulimit,string mid,string end) {Data_maker::print_rnd_neq(Llimit,Ulimit,mid,end);}
void print_rnd_gre(long long Llimit,long long Ulimit,string mid,string end) {Data_maker::print_rnd_gre(Llimit,Ulimit,mid,end);}
void print_rnd_les(long long Llimit,long long Ulimit,string mid,string end) {Data_maker::print_rnd_les(Llimit,Ulimit,mid,end);}
void print_rnd_goe(long long Llimit,long long Ulimit,string mid,string end) {Data_maker::print_rnd_goe(Llimit,Ulimit,mid,end);}
void print_rnd_loe(long long Llimit,long long Ulimit,string mid,string end) {Data_maker::print_rnd_loe(Llimit,Ulimit,mid,end);}
#endif