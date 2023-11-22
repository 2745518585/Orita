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
        using ll=long long;
        using ull=unsigned long long;
        void register_rnd(int argc,char **argv)
        {
            if(argc>=2) rd.seed(std::stoul(argv[1]));
        }
        void register_rnd(unsigned seed)
        {
            rd.seed(seed);
        }
        ull rnd()
        {
            return (std::uniform_int_distribution<ull>(0,-1))(rd);
        }
        template<typename Ty> std::enable_if_t<std::is_integral_v<Ty>,Ty> rnd(const Ty &lim)
        {
            return (std::uniform_int_distribution<Ty>(0,lim-1))(rd);
        }
        ll rnd(const ll &lim)
        {
            return (std::uniform_int_distribution<ll>(0,lim-1))(rd);
        }
        template<typename Ty> std::enable_if_t<std::is_integral_v<Ty>,Ty> rnd(const Ty &llim,const Ty &ulim)
        {
            return (std::uniform_int_distribution<Ty>(llim,ulim))(rd);
        }
        ll rnd(const ll &llim,const ll &ulim)
        {
            return (std::uniform_int_distribution<ll>(llim,ulim))(rd);
        }
        template<typename Ty1,typename Ty2> class pair: public std::pair<Ty1,Ty2>
        {
          public:
            std::string sep;
            pair(const Ty1 &first,const Ty2 &second,const std::string &_sep=" "):std::pair<Ty1,Ty2>(first,second),sep(_sep) {}
            pair(const std::pair<Ty1,Ty2> &_pair,const std::string &_sep=" "):std::pair<Ty1,Ty2>(_pair),sep(_sep) {}
        };
        template<typename Ty1,typename Ty2> std::ostream &operator<<(std::ostream &out,const pair<Ty1,Ty2> &str)
        {
            return out<<str.first<<str.sep<<str.second;
        }
        template<typename lTy,typename uTy,typename chk_Ty> auto rnd_pair(const lTy &llim,const uTy &ulim,const chk_Ty &checker,const std::string &sep=" ")
        {
            auto s1=rnd(llim,ulim),s2=rnd(llim,ulim);
            while(!checker(s1,s2)) s1=rnd(llim,ulim),s2=rnd(llim,ulim);
            return pair(s1,s2,sep);
        }
        auto _NEQ=[](auto s1,auto s2) {return s1!=s2;};
        auto _LES=[](auto s1,auto s2) {return s1<s2;};
        auto _GRE=[](auto s1,auto s2) {return s1>s2;};
        auto _LOE=[](auto s1,auto s2) {return s1<=s2;};
        auto _GOE=[](auto s1,auto s2) {return s1>=s2;};
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
            for(unsigned i=1;i<=tot-1;++i) ans.push_back(std::make_pair(rnd(1,i),i+1));
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