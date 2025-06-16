#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=2e5+10;
typedef long long LL;
void fun()
{
    LL n,maxji=0,maxou=0,sumji=0,sumou=0,jicnt=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i)
    {
        LL x;
        scanf("%lld",&x);
        if(x%2==1) maxji=max(maxji,x);
        else maxou=max(maxou,x);
        if(x%2==1) sumji+=x;
        else sumou+=x;
        if(x%2==1) ++jicnt;
    }
    if(sumji==0||sumou==0) printf("%lld\n",max(maxji,maxou));
    else printf("%lld\n",sumou+sumji-jicnt+1);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}