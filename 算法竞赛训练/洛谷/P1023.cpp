#include<stdio.h>
#include<math.h>
#include<algorithm>
using std::max;
using std::min;
const int N=1e5+10;
int price[N],xiaoliang[N],idx,x,p,ansa,ansb,ans;
int main()
{
    int exp,a,b;
    scanf("%d",&exp);
    while(scanf("%d%d",&a,&b),!(a==-1&&b==-1))
    {
        price[++idx]=a;
        xiaoliang[idx]=b;
        x=max(x,b);
        p=min(p,a);
        if(a*b>=ans)
        {
            ansa=a;
            ansb=b;
            ans=a*b;
        }
    }
    int dx;
    scanf("%d",&dx);
    while(x>=0)
    {
        ++p;
        x-=dx;
        if(x*p>=ans)
        {
            ansa=p;
            ansb=x;
            ans=x*p;
        }
    }
    printf("%d\n",ansa-exp);
    return 0;
}