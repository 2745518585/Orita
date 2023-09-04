#pragma once
#ifndef _FILE_ARGU
#define _FILE_ARGU _FILE_ARGU
#include"init.hpp"
#include"log.hpp"
class arguer
{
  public:
    static const size_t ND=-1,NL=-2;
    json argus,sum_argus;
    bool check_if_argu(const std::string &argu)
    {
        return std::regex_match(argu,std::regex("/([a-z]|[A-Z]|[0-9])+"));
    }
    int init_argu(int argc,char **argv)
    {
        std::string argu_str;
        for(int i=1;i<=argc-1;++i) argu_str+=std::string(argv[i])+" ";
        INFO("argu",add_squo(systoUTF8(argu_str)));
        for(int i=1;i<=argc-1;++i)
        {
            if(check_if_argu(argv[i]))
            {
                std::string argu=argv[i]+1;
                int j=1;
                for(;i+j<=argc-1&&!check_if_argu(argv[i+j]);++j)
                {
                    argus[argu][j]=systoUTF8(argv[i+j]);
                }
                sum_argus[argu]=j-1;
                i+=j-1;
            }
            else return 1;
        }
        return 0;
    }
    int check_argu(json cor_argu)
    {
        for(auto argu:sum_argus.items())
        {
            if(cor_argu[argu.key()].is_null()) return 1;
        }
        for(auto argu:cor_argu.items())
        {
            size_t sum=get_sum_argu(argu.key());
            bool if_cor=false;
            for(auto cor_sum:argu.value())
            {
                if(sum==cor_sum||cor_sum==arguer::NL)
                {
                    if_cor=true;
                    break;
                }
            }
            if(!if_cor) return 1;
        }
        return 0;
    }
    std::string get_argu(const std::string &name,const size_t num)
    {
        if(argus[name].is_null()||argus[name][num].is_null()) return "";
        return argus[name][num];
    }
    size_t get_sum_argu(const std::string &name)
    {
        if(argus[name].is_null()) return ND;
        return sum_argus[name];
    }
    class parameter
    {
      public:
        json para,sum;
        parameter(json _para,json _sum):para(_para),sum(_sum) {}
        auto begin() {return para.begin();}
        auto end() {return para.end();}
        std::string operator[](const size_t num)
        {
            if(para.is_null()||para[num].is_null()) return "";
            return para[num];
        }
        size_t size()
        {
            if(sum.is_null()) return ND;
            return (size_t)sum;
        }
        bool appear() {return !sum.is_null();}
        bool not_appear() {return sum.is_null();}
    };
    parameter operator[](const std::string &name)
    {
        return parameter(argus[name],sum_argus[name]);
    }
}argus;
#endif