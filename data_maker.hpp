#pragma once
#ifndef DATA_MAKER
#define DATA_MAKER DATA_MAKER
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<random>
#include<ctime>
#define _NEQ 1
#define _LES 2
#define _GRE 3
#define _LOE 4
#define _GOE 5
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
    std::map<int,std::pair<ll,ll>> pairs;
    std::pair<ll,ll> rnd_pair(ll llim,ll ulim,int opra)
    {
        auto checker=[&](ll s1,ll s2)
        {
            if(opra==_NEQ) return s1!=s2;
            if(opra==_LES) return s1<s2;
            if(opra==_GRE) return s1>s2;
            if(opra==_LOE) return s1<=s2;
            if(opra==_GOE) return s1>=s2;
            return false;
        };
        ll s1=rnd(llim,ulim),s2=rnd(llim,ulim);
        while(!checker(s1,s2)) s1=rnd(llim,ulim),s2=rnd(llim,ulim);
        return std::make_pair(s1,s2);
    }
    std::pair<ll,ll> rnd_pair(ll llim1,ll ulim1,ll llim2,ll ulim2,int opra)
    {
        auto checker=[&](ll s1,ll s2)
        {
            if(opra==_NEQ) return s1!=s2;
            if(opra==_LES) return s1<s2;
            if(opra==_GRE) return s1>s2;
            if(opra==_LOE) return s1<=s2;
            if(opra==_GOE) return s1>=s2;
            return false;
        };
        ll s1=rnd(llim1,ulim1),s2=rnd(llim2,ulim2);
        while(!checker(s1,s2)) s1=rnd(llim1,ulim1),s2=rnd(llim2,ulim2);
        return std::make_pair(s1,s2);
    }
    std::pair<ll,ll> reg_pair(int num,ll llim,ll ulim,int opra)
    {
        if(pairs.count(num)) return pairs[num];
        pairs[num]=rnd_pair(llim,ulim,opra);
        return pairs[num];
    }
    std::pair<ll,ll> reg_pair(int num,ll llim1,ll ulim1,ll llim2,ll ulim2,int opra)
    {
        if(pairs.count(num)) return pairs[num];
        pairs[num]=rnd_pair(llim1,ulim1,llim2,ulim2,opra);
        return pairs[num];
    }
    std::pair<ll,ll> reg_pair(int num)
    {
        if(!pairs.count(num)) std::make_pair(0,0);
        return pairs[num];
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
            std::pair<int,int> pos=rnd_pair(1,tot,_LES);
            while(find(pos.first)==find(pos.second)) pos=rnd_pair(1,tot,_LES);
            ans.push_back(pos);
            fa[find(pos.first)]=find(pos.second);
        }
        delete[] fa;
        return ans;
    }
    std::vector<std::pair<int,int>> rnd_ucgraph(int totp,int tote)
    {
        std::vector<std::pair<int,int>> ans=rnd_tree(totp);
        tote-=totp-1;
        std::map<std::pair<int,int>,bool> edges;
        for(auto i:ans) edges[i]=true;
        for(int i=1;i<=tote;++i)
        {
            std::pair<int,int> pos=rnd_pair(1,totp,_LES);
            while(edges.count(pos)) pos=rnd_pair(1,totp,_LES);
            ans.push_back(pos);
            edges[pos]=true;
        }
        return ans;
    }
}
unsigned long long rnd(){return Data_maker::rnd();}
long long rnd(long long lim){return Data_maker::rnd(lim);}
long long rnd(long long llim,long long ulim){return Data_maker::rnd(llim,ulim);}
std::pair<long long,long long> rnd_pair(long long llim,long long ulim,int opra){return Data_maker::rnd_pair(llim,ulim,opra);}
std::pair<long long,long long> rnd_pair(long long llim1,long long ulim1,long long llim2,long long ulim2,int opra){return Data_maker::rnd_pair(llim1,ulim1,llim2,ulim2,opra);}
std::pair<long long,long long> reg_pair(int num,long long llim,long long ulim,int opra){return Data_maker::reg_pair(num,llim,ulim,opra);}
std::pair<long long,long long> reg_pair(int num,long long llim1,long long ulim1,long long llim2,long long ulim2,int opra){return Data_maker::reg_pair(num,llim1,ulim1,llim2,ulim2,opra);}
std::pair<long long,long long> reg_pair(int num){return Data_maker::reg_pair(num);}
std::vector<std::pair<int,int>> rnd_tree(int tot){return Data_maker::rnd_tree(tot);}
std::vector<std::pair<int,int>> rnd_ucgraph(int totp,int tote){return Data_maker::rnd_ucgraph(totp,tote);}
#endif