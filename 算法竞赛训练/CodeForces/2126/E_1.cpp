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
const int N=2e5+10;
typedef long long ll;
ll a[N],b[N],c[N],n,a0[N],b0[N];
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
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    for(int i=1;i<=n;++i) scanf("%lld",&b[i]);
    for(int i=1;i<=n;++i) c[i]=lcm(a[i],b[i]);
    for(int i=1;i<=n;++i)
    {
        if(i==1) a0[1]=a[1];
        else a0[i]=gcd(a0[i-1],a[i]);
        if(a[i]<a0[i])
        {
            printf("NO\n");
            return;
        }
    }
    for(int i=n;i>=1;--i)
    {
        if(i==n) b0[n]=b[n];
        else b0[i]=gcd(b0[i+1],b[i]);
        if(b[i]<b0[i])
        {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}