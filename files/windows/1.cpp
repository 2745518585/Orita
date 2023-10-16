#include<iostream>
#include<fstream>
#include<string>
int main(int argc,char **argv)
{
    std::ios_base::sync_with_stdio(false);
    std::ifstream infile1(argv[2]),infile2(argv[3]);
    std::string str1,str2;
    bool empty1=0,empty2=0;
    unsigned lines=0;
    while(true)
    {
        ++lines;
        bool end1=bool(!std::getline(infile1,str1)),end2=bool(!std::getline(infile2,str2));
        if(end1&&end2) break;
        while(str1.back()==' ') str1.pop_back();
        while(str2.back()==' ') str2.pop_back();
        if(end1||str1.size()==0) empty1=true;
        else empty1=false;
        if(end2||str2.size()==0) empty2=true;
        else empty2=false;
        if(empty1^empty2||str1!=str2)
        {
            std::cout<<"on line "<<lines<<"\n*****\n"<<str1<<"\n*****\n"<<str2<<"\n*****\n";
            return 1;
        }
    }
    return 0;
}