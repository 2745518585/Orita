#include<bits/stdc++.h>
using namespace std;
int main(int argc,char **argv)
{
    srand(time(NULL)*atoi(argv[1]));
    int T=rand()%10;
    while(T--)
    {
        printf("%d\n%d\n",rand()%100,rand()%100);
        int n=rand()%100+1;
        printf("%d\n",n);
        for(int i=1;i<=n+1;++i)
        {
            printf("%d\n%d\n",rand()%100,rand()%100);
        }
    }
    return 0;
}