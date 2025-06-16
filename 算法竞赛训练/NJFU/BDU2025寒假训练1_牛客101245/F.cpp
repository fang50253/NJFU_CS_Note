#include<stdio.h>
typedef long long LL;
LL arr[25],n,tgt,ans,res;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    scanf("%lld",&tgt);
    for(LL i=0;i<1<<n;++i)
    {
        ans=0;
        for(int j=0;j<n;++j) ans+=(i>>j&1?1:-1)*arr[j+1];
        if(ans==tgt) ++res;
    }
    printf("%lld\n",res);
    return 0;
}