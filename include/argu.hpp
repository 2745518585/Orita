#pragma once
#ifndef _FILE_ARGU
#define _FILE_ARGU _FILE_ARGU
#include"init.hpp"
#define _not_define -1
#define _no_limit -2
namespace Argu
{
    json argu;
    bool check_if_para(std::string para)
    {
        if(para.size()==0||para[0]!='/') return false;
        for(int i=1;i<para.size();++i)
        {
            if(!((para[i]>='a'&&para[i]<='z')||(para[i]>='A'&&para[i]<='Z')||(para[i]>='0'&&para[i]<='9'))) return false;
        }
        return true;
    }
    int init_argu(int argc,char **argv)
    {
        for(int i=1;i<=argc-1;++i)
        {
            if(check_if_para(argv[i]))
            {
                std::string para=argv[i]+1;
                int j=1;
                for(;i+j<=argc-1&&!check_if_para(argv[i+j]);++j)
                {
                    argu[para][j]=argv[i+j];
                }
                argu[para][0]=j-1;
                i+=j-1;
            }
            else return 1;
        }
        return 0;
    }
    std::string get_argu(std::string name,int num)
    {
        if((int)argu[name].type()==0||(int)argu[name][num].type()==0) return NULL;
        return argu[name][num];
    }
    int get_sum_argu(std::string name)
    {
        if((int)argu[name].type()==0) return -1;
        return argu[name][0];
    }
    int check_argu(json cor_argu)
    {
        for(auto para:cor_argu.items())
        {
            int sum=get_sum_argu(para.key());
            bool if_cor=false;
            for(auto cor_sum:para.value().items())
            {
                if(sum==cor_sum.value()||cor_sum.value()==_no_limit)
                {
                    if_cor=true;
                    break;
                }
            }
            if(!if_cor) return 1;
        }
        for(auto para:argu.items())
        {
            if((int)cor_argu[para.key()].type()==0) return 1;
        }
        return 0;
    }
}
int init_argu(int argc,char **argv) {return Argu::init_argu(argc,argv);}
std::string get_argu(std::string name,int num2) {return Argu::get_argu(name,num2);}
int get_sum_argu(std::string name) {return Argu::get_sum_argu(name);}
int check_argu(json check_argu) {return Argu::check_argu(check_argu);}
#endif