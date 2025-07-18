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
ll a[N],p[N],s[N],n;
ll gp[N],gs[N];
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
    for(int i=1;i<=n;++i) scanf("%lld",&p[i]);
    for(int i=1;i<=n;++i) scanf("%lld",&s[i]);
    for(int i=1;i<=n;++i)
    {
        a[i]=gcd(p[i],s[i]);
    }
    gp[1]=a[1];
    for(int i=1;i<=n;++i)
    {
        if(lcm(p[i],s[i])>a[i])
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