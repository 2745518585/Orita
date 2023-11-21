#pragma once
#ifndef ORITA
#define ORITA
#include<algorithm>
#include<string>
#include<random>
#include<vector>
#include<utility>
#include<map>
namespace orita
{
    namespace Data_maker
    {
        std::mt19937 rd(std::random_device{}());
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
        std::vector<unsigned> rnd_range(unsigned tot)
        {
            std::vector<unsigned> ans;
            for(unsigned i=1;i<=tot;++i) ans.push_back(i);
            shuffle(ans.begin(),ans.end(),rd);
            return ans;
        }
        std::vector<std::pair<unsigned,unsigned>> rnd_tree(unsigned tot)
        {
            std::vector<std::pair<unsigned,unsigned>> ans;
            for(int i=1;i<=tot-1;++i) ans.push_back(std::make_pair(rnd(1,i),i+1));
            auto pos=rnd_range(tot);
            for(auto &i:ans)
            {
                i.first=pos[i.first-1];
                i.second=pos[i.second-1];
                if(rnd(0,1)) std::swap(i.first,i.second);
            }
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
    using Data_maker::rd;
    using Data_maker::register_rnd;
    using Data_maker::rnd;
    using Data_maker::rnd_pair;
    using Data_maker::reg_pair;
    using Data_maker::_NEQ;
    using Data_maker::_LES;
    using Data_maker::_GRE;
    using Data_maker::_LOE;
    using Data_maker::_GOE;
    using Data_maker::rnd_range;
    using Data_maker::rnd_tree;
    using Data_maker::rnd_ucgraph;

    void auto_flush()
    {
        setvbuf(stdout,NULL,_IONBF,0);
        setvbuf(stderr,NULL,_IONBF,0);
    }
}
#endif