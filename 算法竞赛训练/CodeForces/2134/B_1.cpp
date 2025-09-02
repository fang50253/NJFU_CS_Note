#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<utility>
#include<unordered_map>
#include<queue>
#include<stack>
#include<cstdlib>
#include<string.h>
#include<stdlib.h>
#include<unordered_set>
#define PII pair<int,int>
using namespace std;
typedef long long ll;
const int N=1e5+10;
ll arr[N];
ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}
void fun()
{
    ll n,k;
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    ll g=arr[1];
    for(int i=2;i<=n;++i) g=gcd(g,arr[i]);
    if(g>1)
    {
        for(int i=1;i<=n;++i) printf("%lld ",arr[i]);
        printf("\n");
        return;
    }
    ll x=k+1;
    ll d=0;
    if(x%2==0) d=2;
    else
    {
        for(ll p=3;p*p<=x;p+=2)
        {
            if(x%p==0)
            {
                d=p;
                break;
            }
        }
        if(d==0) d=x;
    }
    ll aa=k%d;if(aa<0)aa+=d;
    ll bb=d;
    ll u=1,v=0;
    while(bb)
    {
        ll t=aa/bb;
        aa-=t*bb;
        swap(aa,bb);
        u-=t*v;
        swap(u,v);
    }
    ll invk=u%d;
    if(invk<0) invk+=d;
    for(int i=1;i<=n;++i)
    {
        ll r=arr[i]%d;
        if(r<0) r+=d;
        ll need=((d-r)%d)*invk%d;
        printf("%lld ",arr[i]+need*k);
    }
    printf("\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}