#ifndef DATA_MAKER
#define DATA_MAKER DATA_MAKER
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#define _NEQ1 1
#define _NEQ2 -1
#define _LES1 2
#define _LES2 -2
#define _GRE1 3
#define _GRE2 -3
#define _LOE1 4
#define _LOE2 -4
#define _GOE1 5
#define _GOE2 -5
namespace Data_maker
{
    typedef long long ll;
    typedef unsigned long long ull;
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
    ull rnd()
    {
        return ((ull)rd()<<32)+rd();
    }
    ll rnd(ll lim)
    {
        return rnd()%lim;
    }
    ll rnd(ll llim,ll ulim)
    {
        return rnd(ulim-llim+1)+llim;
    }
    void rnd_pair(ll &s1,ll &s2,ll llim1,ll ulim1,ll llim2,ll ulim2,int opra)
    {
        auto checker=[&](ll s1,ll s2)
        {
            if(opra==_NEQ1||opra==_NEQ2) return s1!=s2;
            if(opra==_LES1||opra==_LES2) return s1<s2;
            if(opra==_GRE1||opra==_GRE2) return s1>s2;
            if(opra==_LOE1||opra==_LOE2) return s1<=s2;
            if(opra==_GOE1||opra==_GOE2) return s1>=s2;
            return false;
        };
        s1=rnd(llim1,ulim1),s2=rnd(llim2,ulim2);
        while(!checker(s1,s2)) s1=rnd(llim1,ulim1),s2=rnd(llim2,ulim2);
    }
    bool if_pair;
    ll pair_second;
    ll rnd_pair(ll llim1,ll ulim1,ll llim2,ll ulim2,int opra)
    {
        if(if_pair==true)
        {
            if_pair=false;
            return pair_second;
        }
        auto checker=[&](ll s1,ll s2)
        {
            if(opra==_NEQ1||opra==_NEQ2) return s1!=s2;
            if(opra==_LES1||opra==_LES2) return s1<s2;
            if(opra==_GRE1||opra==_GRE2) return s1>s2;
            if(opra==_LOE1||opra==_LOE2) return s1<=s2;
            if(opra==_GOE1||opra==_GOE2) return s1>=s2;
            return false;
        };
        ll s1=rnd(llim1,ulim1),s2=rnd(llim2,ulim2);
        while(!checker(s1,s2)) s1=rnd(llim1,ulim1),s2=rnd(llim2,ulim2);
        if_pair=true;
        if(opra<0) swap(s1,s2);
        pair_second=s2;
        return s1;
    }
}
long long rnd() {return Data_maker::rnd();}
long long rnd(long long lim) {return Data_maker::rnd(lim);}
long long rnd(long long llim,long long ulim) {return Data_maker::rnd(llim,ulim);}
void rnd_pair(long long &s1,long long &s2,long long llim1,long long ulim1,long long llim2,long long ulim2,int opra) {Data_maker::rnd_pair(s1,s2,llim1,ulim1,llim2,ulim2,opra);}
long long rnd_pair(long long llim1,long long ulim1,long long llim2,long long ulim2,int opra) {return Data_maker::rnd_pair(llim1,ulim1,llim2,ulim2,opra);}
#endif