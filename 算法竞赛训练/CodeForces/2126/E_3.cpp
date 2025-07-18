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
const int N=1e5+10;
typedef long long ll;
ll a[N],p[N],s[N],n,gcd1,gcd2;
ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}
ll lcm(ll a,ll b)
{
    return a/gcd(a,b)*b;
}
void fun()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&p[i]);
        if(i==1) gcd1=p[i];
        else gcd1=gcd(gcd1,p[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&s[i]);
        if(i==1) gcd2=s[i];
        else gcd2=gcd(gcd2,s[i]);
    }
    if(gcd1==1||gcd2==1||gcd1!=gcd2) printf("NO\n");
    else printf("YES\n");
    //printf("%lld %lld\n",gcd1,gcd2);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}