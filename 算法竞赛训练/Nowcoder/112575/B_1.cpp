#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll count1(ll x) {
    int count=0;
    while (x) 
    {
        count+=x&1;
        x>>=1;
    }
    return count;
}
ll count0(ll x) {
    int count=0;
    while (x) 
    {
        count+=(~x)&1;
        x>>=1;
    }
    return count;
}
ll gf(ll x)
{
    return count0(count1(x))+1;
}
int main()
{
    ll n;
    scanf("%lld",&n);
    ll x=gf(x);
    while(x!=gf(x)) x=gf(x);
    printf("%lld\n",x);
    return 0;
}