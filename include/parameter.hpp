#pragma once
#ifndef _FILE_PARAMETER
#define _FILE_PARAMETER _FILE_PARAMETER
#include"init.hpp"
#define _not_define -1
#define _no_limit -2
namespace Parameter
{
    json parameter;
    bool check_if_para(std::string para)
    {
        if(para.size()==0||para[0]!='/') return false;
        for(int i=1;i<para.size();++i)
        {
            if(!((para[i]>='a'&&para[i]<='z')||(para[i]>='A'&&para[i]<='Z'))) return false;
        }
        return true;
    }
    int init_parameter(int argc,char **argv)
    {
        for(int i=1;i<=argc-1;++i)
        {
            if(check_if_para(argv[i]))
            {
                std::string para=argv[i]+1;
                int j=1;
                for(;i+j<=argc-1&&!check_if_para(argv[i+j]);++j)
                {
                    parameter[para][j]=argv[i+j];
                }
                parameter[para][0]=j-1;
                i+=j-1;
            }
            else return 1;
        }
        return 0;
    }
    std::string get_parameter(std::string name,int num)
    {
        if((int)parameter[name].type()==0||(int)parameter[name][num].type()==0) return NULL;
        return parameter[name][num];
    }
    int get_sum_parameter(std::string name)
    {
        if((int)parameter[name].type()==0) return -1;
        return parameter[name][0];
    }
    int check_parameter(json cor_parameter)
    {
        for(auto para:cor_parameter.items())
        {
            int sum=get_sum_parameter(para.key());
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
        for(auto para:parameter.items())
        {
            if((int)cor_parameter[para.key()].type()==0) return 1;
        }
        return 0;
    }
}
int init_parameter(int argc,char **argv) {return Parameter::init_parameter(argc,argv);}
std::string get_parameter(std::string name,int num2) {return Parameter::get_parameter(name,num2);}
int get_sum_parameter(std::string name) {return Parameter::get_sum_parameter(name);}
int check_parameter(json check_parameter) {return Parameter::check_parameter(check_parameter);}
#endif