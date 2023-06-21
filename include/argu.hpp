#pragma once
#ifndef _FILE_ARGU
#define _FILE_ARGU _FILE_ARGU
#include"init.hpp"
#define _not_define -1
#define _no_limit -2
class arguer
{
  public:
    json argus;
    bool check_if_argu(const std::string argu)
    {
        if(argu.size()==0||argu[0]!='/') return false;
        for(int i=1;i<argu.size();++i)
        {
            if(!((argu[i]>='a'&&argu[i]<='z')||(argu[i]>='A'&&argu[i]<='Z')||(argu[i]>='0'&&argu[i]<='9'))) return false;
        }
        return true;
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
                argus[argu][0]=j-1;
                i+=j-1;
            }
            else return 1;
        }
        return 0;
    }
    int check_argu(const json cor_argu)
    {
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
        for(auto argu:argus.items())
        {
            if((int)cor_argu[argu.key()].type()==0) return 1;
        }
        return 0;
    }
    std::string get_argu(const std::string name,const int num)
    {
        if((int)argus[name].type()==0||(int)argus[name][num].type()==0) return "";
        return argus[name][num];
    }
    int get_sum_argu(const std::string name)
    {
        if((int)argus[name].type()==0) return -1;
        return argus[name][0];
    }
    class parameter
    {
      public:
        json para;
        parameter(json _para):para(_para) {}
        std::string operator[](const size_t num)
        {
            if((int)para.type()==0||(int)para[num].type()==0) return "";
            return para[num];
        }
        json get(const size_t num)
        {
            return para[num];
        }
        int sum()
        {
            if((int)para.type()==0) return -1;
            return para[0];
        }
    };
    parameter operator[](const std::string name)
    {
        return parameter(argus[name]);
    }
}argus;
#endif