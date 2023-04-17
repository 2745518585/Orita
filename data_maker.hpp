#ifndef DATA_MAKER
#define DATA_MAKER DATA_MAKER
#include<bits/stdc++.h>
#include<windows.h>
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
        std::ifstream infile(std::string(getenv("appdata"))+"\\Orita\\random\\seed.txt");
        unsigned int seed;
        infile>>seed;
        infile.close();
        seed=seed+(seed<<7)+(seed>>11)+(seed<<13)+time(NULL);
        std::ofstream outfile(std::string(getenv("appdata"))+"\\Orita\\random\\seed.txt");
        outfile<<seed;
        outfile.close();
        return seed;
    }
    std::mt19937 rd(init_rnd());
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
    void grnd_pair(ll &s1,ll &s2,ll llim,ll ulim,int opra)
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
        s1=rnd(llim,ulim),s2=rnd(llim,ulim);
        while(!checker(s1,s2)) s1=rnd(llim,ulim),s2=rnd(llim,ulim);
    }
    void grnd_pair(ll &s1,ll &s2,ll llim1,ll ulim1,ll llim2,ll ulim2,int opra)
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
    ll rnd_pair(ll llim,ll ulim,int opra)
    {
        static bool if_pair;
        static ll pair_second;
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
        ll s1=rnd(llim,ulim),s2=rnd(llim,ulim);
        while(!checker(s1,s2)) s1=rnd(llim,ulim),s2=rnd(llim,ulim);
        if_pair=true;
        if(opra<0) std::swap(s1,s2);
        pair_second=s2;
        return s1;
    }
    ll rnd_pair(ll llim1,ll ulim1,ll llim2,ll ulim2,int opra)
    {
        static bool if_pair;
        static ll pair_second;
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
        if(opra<0) std::swap(s1,s2);
        pair_second=s2;
        return s1;
    }
    std::vector<std::pair<int,int>> rnd_tree(int tot)
    {
        int *fa=new int[tot+1];
        auto find=[&](int pos)
        {
            auto s=[&](auto self,int pos)
            {
                if(fa[pos]==pos) return pos;
                return fa[pos]=self(self,fa[pos]);
            };
            return s(s,pos);
        };
        std::vector<std::pair<int,int>> ans;
        for(int i=1;i<=tot;++i) fa[i]=i;
        for(int i=1;i<=tot-1;++i)
        {
            int pos1=rnd(1,tot),pos2=rnd(1,tot);
            while(find(pos1)==find(pos2)) pos1=rnd(1,tot),pos2=rnd(1,tot);
            ans.push_back(std::make_pair(pos1,pos2));
            fa[find(pos1)]=find(pos2);
        }
        delete[] fa;
        return ans;
    }
}
long long rnd(){return Data_maker::rnd();}
long long rnd(long long lim){return Data_maker::rnd(lim);}
long long rnd(long long llim,long long ulim){return Data_maker::rnd(llim,ulim);}
void grnd_pair(long long &s1,long long &s2,long long llim,long long ulim,int opra){Data_maker::grnd_pair(s1,s2,llim,ulim,opra);}
void grnd_pair(long long &s1,long long &s2,long long llim1,long long ulim1,long long llim2,long long ulim2,int opra){Data_maker::grnd_pair(s1,s2,llim1,ulim1,llim2,ulim2,opra);}
long long rnd_pair(long long llim,long long ulim,int opra){return Data_maker::rnd_pair(llim,ulim,opra);}
long long rnd_pair(long long llim1,long long ulim1,long long llim2,long long ulim2,int opra){return Data_maker::rnd_pair(llim1,ulim1,llim2,ulim2,opra);}
std::vector<std::pair<int,int>> rnd_tree(int tot){return Data_maker::rnd_tree(tot);}
#endif