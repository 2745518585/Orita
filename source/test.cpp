#include<algorithm>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Vector Point
#define Re register int
using namespace std;
const int N=1e5+3;
const LD eps=1e-8;
int n;
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}
inline LD Abs(LD a){return a*dcmp(a);}
struct Point{
    LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}
    inline void in(){scanf("%lf%lf",&x,&y);}
}M,P1,P2;
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
inline LD Len(Vector a){return sqrt(Dot(a,a));}
inline LD Angle(Vector a,Vector b){return acos(Dot(a,b)/Len(a)/Len(b));}
inline Point operator+(Point a,Vector b){return Point(a.x+b.x,a.y+b.y);}
inline Vector operator-(Point a,Point b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator*(Vector a,LD x){return Vector(a.x*x,a.y*x);}
inline bool operator==(Point a,Point b){return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y);}
struct ANS{Point a;LD dis;ANS(Point A,LD D=0){a=A,dis=D;}};
inline Point FootPoint(Point p,Point a,Point b){//点P到直线AB的垂足
    Vector x=p-a,y=p-b,z=b-a;
    LD len1=Dot(x,z)/Len(z),len2=-1.0*Dot(y,z)/Len(z);//分别计算AP,BP在AB,BA上的投影
    return a+z*(len1/(len1+len2));//点A加上向量AF
}
inline Point dis_PL(Point p,Point a,Point b){//点P到线段AB距离
    if(a==b)return a;//AB重合
    Vector x=p-a,y=p-b,z=b-a;
    if(dcmp(Dot(x,z))<0)return a;//P距离A更近
    if(dcmp(Dot(y,z))>0)return b;//P距离B更近
    return FootPoint(p,a,b);//返回垂足
}
int main(){
//  freopen("123.txt","r",stdin);
    while(~scanf("%lf%lf",&M.x,&M.y)){
        scanf("%d",&n),P1.in();
        Point ans=P1;
        while(n--){
            P2.in();Point tmp=dis_PL(M,P1,P2);
            if(dcmp(Len(M-tmp)-Len(M-ans))<0)ans=tmp;
            P1=P2;
        }
        printf("%.4lf\n%.4lf\n",ans.x,ans.y);
    }
}
