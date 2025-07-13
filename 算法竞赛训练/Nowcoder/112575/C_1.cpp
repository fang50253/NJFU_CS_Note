#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll arr[N],n,m;
ll leftlarge[N],rightlarge[N],leftsmall[N],rightsmall[N];
//上面均包含本数字
int main()
{
    scanf("%lld%lld",&n,&m);
    memset(leftsmall,0x3f,sizeof leftsmall);
    memset(rightsmall,0x3f,sizeof rightsmall);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i]);
        leftlarge[i]=max(arr[i],leftlarge[i-1]);
        leftsmall[i]=min(arr[i],leftlarge[i-1]);
    }
    for(int i=n;i>=1;--i)
    {
        scanf("%lld",&arr[i]);
        rightlarge[i]=max(arr[i],rightlarge[i+1]);
        rightsmall[i]=min(arr[i],rightlarge[i+1]);
    }
    ll l,r;
    for(int i=1;i<=n;++i)
    {
        if(rightsmall[i]==arr[i]) r=i;
        if(rightlarge<=arr[i]) l=i;
    }
    return 0;
}