#pragma once
#ifndef DATA_MAKER
#define DATA_MAKER DATA_MAKER
#include<fstream>
#include<algorithm>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<random>
namespace Data_maker
{
    std::mt19937 rd;
    void register_rnd(int argc,char **argv)
    {
        if(argc>=2) rd.seed(std::stoul(argv[1]));
    }
    void register_rnd(unsigned seed)
    {
        rd.seed(seed);
    }
    unsigned long long rnd()
    {
        return (std::uniform_int_distribution<unsigned long long>(0,-1))(rd);
    }
    long long rnd(long long lim)
    {
        return (std::uniform_int_distribution<long long>(0,lim-1))(rd);
    }
    long long rnd(long long llim,long long ulim)
    {
        return (std::uniform_int_distribution<long long>(llim,ulim))(rd);
    }
    std::map<int,std::pair<long long,long long>> pairs;
    template<typename Type> std::pair<long long,long long> rnd_pair(long long llim,long long ulim,Type checker)
    {
        long long s1=rnd(llim,ulim),s2=rnd(llim,ulim);
        while(!checker(s1,s2)) s1=rnd(llim,ulim),s2=rnd(llim,ulim);
        return std::make_pair(s1,s2);
    }
    template<typename Type> std::pair<long long,long long> rnd_pair(long long llim1,long long ulim1,long long llim2,long long ulim2,Type checker)
    {
        long long s1=rnd(llim1,ulim1),s2=rnd(llim2,ulim2);
        while(!checker(s1,s2)) s1=rnd(llim1,ulim1),s2=rnd(llim2,ulim2);
        return std::make_pair(s1,s2);
    }
    template<typename Type> std::pair<long long,long long> reg_pair(int num,long long llim,long long ulim,Type checker)
    {
        pairs[num]=Data_maker::rnd_pair(llim,ulim,checker);
        return pairs[num];
    }
    template<typename Type> std::pair<long long,long long> reg_pair(int num,long long llim1,long long ulim1,long long llim2,long long ulim2,Type checker)
    {
        pairs[num]=Data_maker::rnd_pair(llim1,ulim1,llim2,ulim2,checker);
        return pairs[num];
    }
    std::pair<long long,long long> reg_pair(int num)
    {
        if(!pairs.count(num)) return std::make_pair(0,0);
        return pairs[num];
    }
    auto _NEQ=[](long long s1,long long s2) {return s1!=s2;};
    auto _LES=[](long long s1,long long s2) {return s1<s2;};
    auto _GRE=[](long long s1,long long s2) {return s1>s2;};
    auto _LOE=[](long long s1,long long s2) {return s1<=s2;};
    auto _GOE=[](long long s1,long long s2) {return s1>=s2;};
    std::vector<std::pair<unsigned,unsigned>> rnd_tree(unsigned tot)
    {
        unsigned *fa=new unsigned[tot+1];
        auto find=[&](unsigned pos)
        {
            auto s=[&](auto self,unsigned pos)
            {
                if(fa[pos]==pos) return pos;
                return fa[pos]=self(self,fa[pos]);
            };
            return s(s,pos);
        };
        std::vector<std::pair<unsigned,unsigned>> ans;
        for(unsigned i=1;i<=tot;++i) fa[i]=i;
        for(unsigned i=1;i<=tot-1;++i)
        {
            std::pair<unsigned,unsigned> pos=rnd_pair(1,tot,_LES);
            while(find(pos.first)==find(pos.second)) pos=rnd_pair(1,tot,_LES);
            ans.push_back(pos);
            fa[find(pos.first)]=find(pos.second);
        }
        delete[] fa;
        return ans;
    }
    std::vector<std::pair<unsigned,unsigned>> rnd_ucgraph(unsigned totp,unsigned tote)
    {
        std::vector<std::pair<unsigned,unsigned>> ans=rnd_tree(totp);
        tote-=totp-1;
        std::map<std::pair<unsigned,unsigned>,bool> edges;
        for(auto i:ans) edges[i]=true;
        for(unsigned i=1;i<=tote;++i)
        {
            std::pair<unsigned,unsigned> pos=rnd_pair(1,totp,_LES);
            while(edges.count(pos)) pos=rnd_pair(1,totp,_LES);
            ans.push_back(pos);
            edges[pos]=true;
        }
        return ans;
    }
}
std::mt19937 rd=Data_maker::rd;
void register_rnd(int argc,char **argv) {return Data_maker::register_rnd(argc,argv);}
void register_rnd(unsigned seed) {return Data_maker::register_rnd(seed);}
unsigned long long rnd(){return Data_maker::rnd();}
long long rnd(long long lim){return Data_maker::rnd(lim);}
long long rnd(long long llim,long long ulim){return Data_maker::rnd(llim,ulim);}
template<typename Type> std::pair<long long,long long> rnd_pair(long long llim,long long ulim,Type checker){return Data_maker::rnd_pair(llim,ulim,checker);}
template<typename Type> std::pair<long long,long long> rnd_pair(long long llim1,long long ulim1,long long llim2,long long ulim2,Type checker){return Data_maker::rnd_pair(llim1,ulim1,llim2,ulim2,checker);}
template<typename Type> std::pair<long long,long long> reg_pair(int num,long long llim,long long ulim,Type checker){return Data_maker::reg_pair(num,llim,ulim,checker);}
template<typename Type> std::pair<long long,long long> reg_pair(int num,long long llim1,long long ulim1,long long llim2,long long ulim2,Type checker){return Data_maker::reg_pair(num,llim1,ulim1,llim2,ulim2,checker);}
std::pair<long long,long long> reg_pair(int num){return Data_maker::reg_pair(num);}
auto _NEQ=Data_maker::_NEQ;
auto _LES=Data_maker::_LES;
auto _GRE=Data_maker::_LOE;
auto _LOE=Data_maker::_LOE;
auto _GOE=Data_maker::_GOE;
std::vector<std::pair<unsigned,unsigned>> rnd_tree(unsigned tot){return Data_maker::rnd_tree(tot);}
std::vector<std::pair<unsigned,unsigned>> rnd_ucgraph(unsigned totp,unsigned tote){return Data_maker::rnd_ucgraph(totp,tote);}
#endif