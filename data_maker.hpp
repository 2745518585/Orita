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
namespace Data_maker
{
    #ifdef _WIN32
    char PS='\\';
    #endif
    #ifdef __linux__
    char PS='/';
    #endif
    std::string makepath(const std::string &path) {return path;}
    template<typename ...others_type> std::string makepath(const std::string &path,const others_type ...others) {return path+PS+makepath(others...);}

    std::string get_appdata_path()
    {
        #ifdef _WIN32
        return makepath(getenv("appdata"),"Orita");
        #endif
        #ifdef __linux__
        return makepath(getenv("HOME"),".Orita");
        #endif
    }
    typedef long long ll;
    typedef unsigned long long ull;
    unsigned int init_rnd()
    {
        unsigned int seed;
        (std::ifstream)(makepath(get_appdata_path(),"random","seed.txt"))>>seed;
        seed=((std::mt19937)(seed))();
        (std::ofstream)(makepath(get_appdata_path(),"random","seed.txt"))<<seed;
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
    template<typename Type> std::pair<ll,ll> rnd_pair(ll llim,ll ulim,Type checker)
    {
        ll s1=rnd(llim,ulim),s2=rnd(llim,ulim);
        while(!checker(s1,s2)) s1=rnd(llim,ulim),s2=rnd(llim,ulim);
        return std::make_pair(s1,s2);
    }
    template<typename Type> std::pair<ll,ll> rnd_pair(ll llim1,ll ulim1,ll llim2,ll ulim2,Type checker)
    {
        ll s1=rnd(llim1,ulim1),s2=rnd(llim2,ulim2);
        while(!checker(s1,s2)) s1=rnd(llim1,ulim1),s2=rnd(llim2,ulim2);
        return std::make_pair(s1,s2);
    }
    template<typename Type> std::pair<ll,ll> reg_pair(int num,ll llim,ll ulim,Type checker)
    {
        pairs[num]=Data_maker::rnd_pair(llim,ulim,checker);
        return pairs[num];
    }
    template<typename Type> std::pair<ll,ll> reg_pair(int num,ll llim1,ll ulim1,ll llim2,ll ulim2,Type checker)
    {
        pairs[num]=Data_maker::rnd_pair(llim1,ulim1,llim2,ulim2,checker);
        return pairs[num];
    }
    std::pair<ll,ll> reg_pair(int num)
    {
        if(!pairs.count(num)) return std::make_pair(0,0);
        return pairs[num];
    }
    auto _NEQ=[](long long s1,long long s2) {return s1!=s2;};
    auto _LES=[](long long s1,long long s2) {return s1<s2;};
    auto _GRE=[](long long s1,long long s2) {return s1>s2;};
    auto _LOE=[](long long s1,long long s2) {return s1<=s2;};
    auto _GOE=[](long long s1,long long s2) {return s1>=s2;};
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
std::mt19937 rd=Data_maker::rd;
unsigned long long rnd(){return Data_maker::rnd();}
long long rnd(long long lim){return Data_maker::rnd(lim);}
long long rnd(long long llim,long long ulim){return Data_maker::rnd(llim,ulim);}
template<typename Type> std::pair<long long,long long> rnd_pair(long long llim,long long ulim,Type checker){return Data_maker::rnd_pair(llim,ulim,checker);}
template<typename Type> std::pair<long long,long long> rnd_pair(long long llim1,long long ulim1,long long llim2,long long ulim2,Type checker){return Data_maker::rnd_pair(llim1,ulim1,llim2,ulim2,checker);}
template<typename Type> std::pair<long long,long long> reg_pair(int num,long long llim,long long ulim,Type checker){return Data_maker::reg_pair(num,llim,ulim,checker);}
template<typename Type> std::pair<long long,long long> reg_pair(int num,long long llim1,long long ulim1,long long llim2,long long ulim2,Type checker){return Data_maker::reg_pair(num,llim1,ulim1,llim2,ulim2,checker);}
std::pair<long long,long long> reg_pair(int num){return Data_maker::reg_pair(num);}
auto _NEQ=[](long long s1,long long s2) {return s1!=s2;};
auto _LES=[](long long s1,long long s2) {return s1<s2;};
auto _GRE=[](long long s1,long long s2) {return s1>s2;};
auto _LOE=[](long long s1,long long s2) {return s1<=s2;};
auto _GOE=[](long long s1,long long s2) {return s1>=s2;};
std::vector<std::pair<int,int>> rnd_tree(int tot){return Data_maker::rnd_tree(tot);}
std::vector<std::pair<int,int>> rnd_ucgraph(int totp,int tote){return Data_maker::rnd_ucgraph(totp,tote);}
#endif