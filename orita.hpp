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
        template<typename Ty> std::enable_if_t<std::is_integral<Ty>::value,Ty> rnd(const Ty &lim)
        {
            return (std::uniform_int_distribution<Ty>(0,lim-1))(rd);
        }
        ll rnd(const ll &lim)
        {
            return (std::uniform_int_distribution<ll>(0,lim-1))(rd);
        }
        template<typename Ty> std::enable_if_t<std::is_integral<Ty>::value,Ty> rnd(const Ty &llim,const Ty &ulim)
        {
            return (std::uniform_int_distribution<Ty>(llim,ulim))(rd);
        }
        ll rnd(const ll &llim,const ll &ulim)
        {
            return (std::uniform_int_distribution<ll>(llim,ulim))(rd);
        }
        template<typename lTy,typename uTy> class rdl
        {
          public:
            lTy llim;
            uTy ulim;
            rdl() {}
            rdl(const uTy &lim):llim(0),ulim(lim-1) {}
            rdl(const lTy &llim,const uTy &ulim):llim(llim),ulim(ulim) {}
            auto operator()() const {return rnd(llim,ulim);}
        };
        template<typename Ty1,typename Ty2> class pair: public std::pair<Ty1,Ty2>
        {
          public:
            std::string sep;
            pair(const Ty1 &first,const Ty2 &second,const std::string &_sep=" "):std::pair<Ty1,Ty2>(first,second),sep(_sep) {}
            pair(const std::pair<Ty1,Ty2> &_pair,const std::string &_sep=" "):std::pair<Ty1,Ty2>(_pair),sep(_sep) {}
        };
        template<typename Ty1,typename Ty2> std::ostream &operator<<(std::ostream &out,const pair<Ty1,Ty2> &pr)
        {
            return out<<pr.first<<pr.sep<<pr.second;
        }

        namespace cmp
        {
            template<typename Ty1,typename Ty2> struct _NEQ {bool operator()(const Ty1 &s1,const Ty2 &s2) const {return s1!=s2;}};
            template<typename Ty1,typename Ty2> struct _LES {bool operator()(const Ty1 &s1,const Ty2 &s2) const {return s1<s2;}};
            template<typename Ty1,typename Ty2> struct _GRE {bool operator()(const Ty1 &s1,const Ty2 &s2) const {return s1>s2;}};
            template<typename Ty1,typename Ty2> struct _LOE {bool operator()(const Ty1 &s1,const Ty2 &s2) const {return s1<=s2;}};
            template<typename Ty1,typename Ty2> struct _GOE {bool operator()(const Ty1 &s1,const Ty2 &s2) const {return s1>=s2;}};
        }
        using namespace cmp;

        template<typename...> using void_t=void;

        template<typename Ty,typename=void>
        struct has_call_operator: std::false_type {};
        template<typename Ty>
        struct has_call_operator<Ty,void_t<decltype(&Ty::operator())>>: std::true_type {};

        template<typename chk_Ty,typename mk_Ty> auto rnd_pair(const mk_Ty &maker,const chk_Ty &checker,const std::string &sep=" ")
        {
            auto s1=maker(),s2=maker();
            while(!checker(s1,s2)) s1=maker(),s2=maker();
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }
        template<typename chk_Ty,typename mk_Ty> auto rnd_pair(const mk_Ty &maker,const std::string &sep=" ")
        {
            auto s1=maker(),s2=maker();
            while(!(*new chk_Ty)(s1,s2)) s1=maker(),s2=maker();
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }
        template<template<typename Ty> typename chk_Ty,typename mk_Ty> auto rnd_pair(const mk_Ty &maker,const std::string &sep=" ")
        {
            auto s1=maker(),s2=maker();
            while(!(*new chk_Ty<decltype(s1)>)(s1,s2)) s1=maker(),s2=maker();
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }
        template<template<typename Ty1,typename Ty2> typename chk_Ty,typename mk_Ty> auto rnd_pair(const mk_Ty &maker,const std::string &sep=" ")
        {
            auto s1=maker(),s2=maker();
            static_assert(std::is_same<decltype(s1),decltype(s2)>::value);
            while(!(*new chk_Ty<decltype(s1),decltype(s2)>)(s1,s2)) s1=maker(),s2=maker();
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }

        template<typename Ty1,typename Ty2> using chk_has_call_operator=std::enable_if_t<has_call_operator<Ty1>::value&&has_call_operator<Ty2>::value,pair<decltype((*new Ty1)()),decltype((*new Ty2)())>>;
        template<typename chk_Ty,typename mk_Ty1,typename mk_Ty2> chk_has_call_operator<mk_Ty1,mk_Ty2> rnd_pair(const mk_Ty1 &maker1,const mk_Ty2 &maker2,const chk_Ty &checker,const std::string &sep=" ")
        {
            auto s1=maker1(),s2=maker2();
            while(!checker(s1,s2)) s1=maker1(),s2=maker2();
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }
        template<typename chk_Ty,typename mk_Ty1,typename mk_Ty2> chk_has_call_operator<mk_Ty1,mk_Ty2> rnd_pair(const mk_Ty1 &maker1,const mk_Ty2 &maker2,const std::string &sep=" ")
        {
            auto s1=maker1(),s2=maker2();
            while(!(*new chk_Ty)(s1,s2)) s1=maker1(),s2=maker2();
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }
        template<template<typename Ty> typename chk_Ty,typename mk_Ty1,typename mk_Ty2> chk_has_call_operator<mk_Ty1,mk_Ty2> rnd_pair(const mk_Ty1 &maker1,const mk_Ty2 &maker2,const std::string &sep=" ")
        {
            auto s1=maker1(),s2=maker2();
            static_assert(std::is_same<decltype(s1),decltype(s2)>::value);
            while(!(*new chk_Ty<decltype(s1)>)(s1,s2)) s1=maker1(),s2=maker2();
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }
        template<template<typename Ty1,typename Ty2> typename chk_Ty,typename mk_Ty1,typename mk_Ty2> chk_has_call_operator<mk_Ty1,mk_Ty2> rnd_pair(const mk_Ty1 &maker1,const mk_Ty2 &maker2,const std::string &sep=" ")
        {
            auto s1=maker1(),s2=maker2();
            while(!(*new chk_Ty<decltype(s1),decltype(s2)>)(s1,s2)) s1=maker1(),s2=maker2();
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }

        template<typename Ty1,typename Ty2> using chk_without_call_operator=std::enable_if_t<!has_call_operator<Ty1>::value&&!has_call_operator<Ty2>::value,pair<decltype(rnd(Ty1(),Ty2())),decltype(rnd(Ty1(),Ty2()))>>;
        template<typename chk_Ty,typename lTy,typename uTy> chk_without_call_operator<lTy,uTy> rnd_pair(const lTy &llim,const uTy &ulim,const chk_Ty &checker,const std::string &sep=" ")
        {
            auto s1=rnd(llim,ulim),s2=rnd(llim,ulim);
            while(!checker(s1,s2)) s1=rnd(llim,ulim),s2=rnd(llim,ulim);
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }
        template<typename chk_Ty,typename lTy,typename uTy> chk_without_call_operator<lTy,uTy> rnd_pair(const lTy &llim,const uTy &ulim,const std::string &sep=" ")
        {
            auto s1=rnd(llim,ulim),s2=rnd(llim,ulim);
            while(!(*new chk_Ty)(s1,s2)) s1=rnd(llim,ulim),s2=rnd(llim,ulim);
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }
        template<template<typename Ty> typename chk_Ty,typename lTy,typename uTy> chk_without_call_operator<lTy,uTy> rnd_pair(const lTy &llim,const uTy &ulim,const std::string &sep=" ")
        {
            auto s1=rnd(llim,ulim),s2=rnd(llim,ulim);
            static_assert(std::is_same<decltype(s1),decltype(s2)>::value);
            while(!(*new chk_Ty<decltype(s1)>)(s1,s2)) s1=rnd(llim,ulim),s2=rnd(llim,ulim);
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }
        template<template<typename Ty1,typename Ty2> typename chk_Ty,typename lTy,typename uTy> chk_without_call_operator<lTy,uTy> rnd_pair(const lTy &llim,const uTy &ulim,const std::string &sep=" ")
        {
            auto s1=rnd(llim,ulim),s2=rnd(llim,ulim);
            while(!(*new chk_Ty<decltype(s1),decltype(s2)>)(s1,s2)) s1=rnd(llim,ulim),s2=rnd(llim,ulim);
            return pair<decltype(s1),decltype(s2)>(s1,s2,sep);
        }

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
                std::pair<unsigned,unsigned> pos=rnd_pair<_LES>(1,totp);
                while(edges.count(pos)) pos=rnd_pair<_LES>(1,totp);
                ans.push_back(pos);
                edges[pos]=true;
            }
            return ans;
        }
    }
    using Data_maker::rd;
    using Data_maker::register_rnd;
    using Data_maker::rnd;
    using Data_maker::rdl;
    using Data_maker::pair;
    using Data_maker::rnd_pair;
    using namespace Data_maker::cmp;
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