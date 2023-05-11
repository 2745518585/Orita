#include<fstream>
#include<string>
int main(int argc,char **argv)
{
    std::ifstream infile1(argv[2]),infile2(argv[3]);
    std::string str1,str2;
    bool empty1=0,empty2=0;
    while(true)
    {
        bool end1=bool(!getline(infile1,str1)),end2=bool(!getline(infile2,str2));
        if(end1&&end2) break;
        while(str1[str1.size()-1]==' ') str1=str1.substr(0,str1.size()-1);
        while(str2[str2.size()-1]==' ') str2=str2.substr(0,str2.size()-1);
        if(end1||str1.size()==0) empty1=true;
        else empty1=false;
        if(end2||str2.size()==0) empty2=true;
        else empty2=false;
        if(empty1^empty2) return 1;
        if(str1!=str2) return 1;
    }
    return 0;
}