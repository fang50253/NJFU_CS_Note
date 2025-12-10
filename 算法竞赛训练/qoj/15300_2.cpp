#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M=1e9+7;
const ll MOD=998244353;
const ll t=1e8;
const ll a0=0;
const int N=1e5+10;
ll cal[N];
ll fun(ll x)
{
    cal[0]=311;
    int cnt=0,i;
    for(i=0;cnt<t;i=(i+1)%(N-10))
    {
        ++cnt;
        cal[(i+1)%(N-10)]=((cal[i]*1234567+7654321)%M)^MOD;
    }
    return cal[i];
}
int main()
{
    printf("%lld\n",fun(t));
    return 0;
}