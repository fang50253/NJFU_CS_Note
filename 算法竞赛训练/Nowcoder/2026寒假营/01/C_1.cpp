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
    if(n<=3) printf("%lld\n",sum[n]);
    for(int i=1;i<=n;++i)
    {
        if(arr[i]==arr[maxidx])
        {
            l=i;
            break;
        }
    }
    for(int i=n;i>=1;--i)
    {
        if(arr[i]==arr[maxidx])
        {
            r=i;
            break;
        }
    }
    ll ans=0;
    // for(int i=1;i<=n;++i) printf("%lld ",sum[i]);
    // cout<<endl;
    //printf("%d %d\n",l,r);
    ans=sum[n]-sum[r]+arr[1]+(r-1)*arr[maxidx];
    ans=max(ans,sum[l-1]+(n-l)*arr[maxidx]+arr[n]);
    printf("%lld\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}