#include<stdio.h>
#include<iostream>
using namespace std;
const int N=1e6+10;
typedef long long ll;
ll arr[N],ans[N],maxa[N],dp[N];
int main()
{
    int n,q;
    scanf(" %d %d",&n,&q);
    for(int i=1;i<=n;++i)scanf(" %lld",&arr[i]);
    //预处理每个货币金额用到的最大面值的货币
    for(int i=1,j=1;i<=arr[n];++i)
    {
        while(j<n&&arr[j+1]<=i) ++j;
        maxa[i]=arr[j];
    }
    //for(int i=1;i<=arr[n];++i) printf("%lld ",maxa[i]);
    for(int i=1;i<=arr[n];++i)
    {
        //统计特点张数i张货币可以组成的金额的数量
        dp[i]=dp[i-maxa[i]]+1;
        ++ans[dp[i]];
    }
    for(int i=2;i<=arr[n];++i) ans[i]+=ans[i-1];
    for(int i=0;i<q;++i)
    {
        int x;
        scanf(" %d",&x);
        if(x>arr[n]) printf("%lld ",arr[n]);
        else printf("%lld ",ans[x]);
    }
    return 0;
}