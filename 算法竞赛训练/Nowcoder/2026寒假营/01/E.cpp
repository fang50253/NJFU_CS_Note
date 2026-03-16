#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
const ll INF=0x3f3f3f3f3f3f3f3f;
ll arr[N];
void fun()
{
    ll n,k,ans=-INF;
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    arr[++n]=k;
    arr[0]=k;
    for(int i=0;i<=n-1;++i) ans=max(ans,arr[i]+arr[i+1]);
    printf("%lld\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}