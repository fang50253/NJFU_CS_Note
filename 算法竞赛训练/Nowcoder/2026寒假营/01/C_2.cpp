#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
typedef long long ll;
ll arr[N],sum[N];
void fun()
{
    int n,maxidx=0,l=1,r=n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i]);
        sum[i]=sum[i-1]+arr[i];
        if(arr[i]>arr[maxidx]) maxidx=i;
    }
    //if(n<=3) {printf("%lld\n",sum[n]);return;}
    ll ans=arr[1]+arr[n]+arr[maxidx]*(n-2);
    printf("%lld\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}