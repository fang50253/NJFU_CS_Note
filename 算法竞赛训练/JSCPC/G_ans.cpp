#include<stdio.h>
#include<unordered_set>
using namespace std;
typedef long long ll;
const int N=1e6+10;
ll a[N],ans[N],maxa[N],dp[N];
int main()
{
    int n,q;
    scanf(" %d %d",&n,&q);
    for(int i=1;i<=n;++i) scanf(" %lld",&a[i]);
    for(int i=1,j=1;i<=a[n];++i) 
    {
        while(j<n&&a[j+1]<=i) ++j;
        maxa[i]=a[j];
    }
    for(int i=1;i<=a[n];++i)
    {
        dp[i]=dp[i-maxa[i]]+1;
        ans[dp[i]]++;
    }
    for(int i=2;i<=a[n];++i) ans[i]+=ans[i-1];
    for(int i=1;i<=q;++i) 
    {
        ll x;
        scanf("%lld",&x);
        printf("%lld ",ans[min(x,a[n])]);
    }
    return 0;
}