#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M=1e9+7;
const ll MOD=998244353;
const ll t=1e8;
const ll a0=0;
ll fun(ll x)
{
    if(x==0) return a0;
    return ((fun(x-1)*1234567+7654321)%M)^MOD;
}
int main()
{
    printf("%lld\n",fun(t));
    return 0;
}