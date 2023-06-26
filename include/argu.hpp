#pragma once
#ifndef _FILE_ARGU
#define _FILE_ARGU _FILE_ARGU
#include"init.hpp"
#define _not_define -1
#define _no_limit -2
class arguer
{
  public:
    json argus,sum_argus;
    bool check_if_argu(const std::string argu)
    {
        return std::regex_match(argu,std::regex("/([a-z]|[A-Z]|[0-9])+"));
    }
    int init_argu(int argc,char **argv)
    {
        for(int i=1;i<=argc-1;++i)
        {
            if(check_if_argu(argv[i]))
            {
                std::string argu=argv[i]+1;
                int j=1;
                for(;i+j<=argc-1&&!check_if_argu(argv[i+j]);++j)
                {
                    argus[argu][j]=argv[i+j];
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
        for(auto argu:argus.items())
        {
            if(cor_argu[argu.key()].type()==json::value_t::null) return 1;
        }
        for(auto argu:cor_argu.items())
        {
            int sum=get_sum_argu(argu.key());
            bool if_cor=false;
            for(auto cor_sum:argu.value().items())
            {
                if(sum==cor_sum.value()||cor_sum.value()==_no_limit)
                {
                    if_cor=true;
                    break;
                }
            }
            if(!if_cor) return 1;
        }
        return 0;
    }
    std::string get_argu(const std::string name,const int num)
    {
        if(argus[name].type()==json::value_t::null||argus[name][num].type()==json::value_t::null) return "";
        return argus[name][num];
    }
    int get_sum_argu(const std::string name)
    {
        if(argus[name].type()==json::value_t::null) return -1;
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
            if(para.type()==json::value_t::null||para[num].type()==json::value_t::null) return "";
            return para[num];
        }
        json get(const size_t num)
        {
            return para[num];
        }
        int size()
        {
            if(sum.type()==json::value_t::null) return -1;
            return (int)sum;
        }
    };
    parameter operator[](const std::string name)
    {
        return parameter(argus[name],sum_argus[name]);
    }
}argus;
#endif