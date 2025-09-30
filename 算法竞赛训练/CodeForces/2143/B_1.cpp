#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll a[N],b[N],n,k;
void fun()
{
    ll sum=0;
    scanf("%lld%lld",&n,&k);
    for(ll i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        sum+=a[i];
    }
    for(ll i=1;i<=k;++i) scanf("%lld",&b[i]);
    sort(a+1,a+1+n);
    sort(b+1,b+1+k);
    int px=n+1,idx=1;
    while(px>=1&&idx<=k)
    {
        px-=b[idx++];
        if(px>=1) sum-=a[px];//+b[idx--]-1;
    }
    printf("%lld\n",sum);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}