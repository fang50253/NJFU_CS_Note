#include<stdio.h>
typedef long long LL;
void fun()
{
    LL n,k,ans=0;
    scanf("%lld%lld",&n,&k);
    if(n>=k) {n-=k;++ans;}
    ans+=(n+k-2)/(k-1);
    printf("%lld\n",ans);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}