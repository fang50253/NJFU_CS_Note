#include<stdio.h>
#include<math.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll arr[N];
ll min(ll a,ll b)
{
    return a>b?b:a;
}
ll min(ll a,ll b,ll c)
{
    ll ans=0x3f3f3f3f3f3f3f3f;
    ans=min(ans,a);
    ans=min(ans,b);
    ans=min(ans,c);
    return ans;
}
void fun()
{
    int n,k,sum=0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i]);
        sum+=arr[i];
    }
    printf("%lld\n",min(sum,k*(n-1)));

}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}