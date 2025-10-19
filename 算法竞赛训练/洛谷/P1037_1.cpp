#include<stdio.h>
#include<set>
using namespace std;
typedef unsigned long long ll;
typedef pair<ll,ll> PII;
ll n,k,cnt[10],ans=1;
int main()
{
    scanf("%lld%lld",&n,&k);
    set<PII>s;
    for(int i=1;i<=k;++i)
    {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        if(s.count({a,b})) continue;
        else {++cnt[a];s.insert({a,b});}
    }
    while(n)
    {
        ll x=n%10;
        n/=10;
        ans*=cnt[x]+1;
    }
    printf("%lld\n",ans);
    return 0;
}