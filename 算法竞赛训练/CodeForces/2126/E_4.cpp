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
        int n;
        scanf("%d", &n);
        ll p[n], s[n];
        for (int i = 0; i < n; ++i) scanf("%lld", &p[i]);
        for (int i = 0; i < n; ++i) scanf("%lld", &s[i]);
        bool ok = true;
        for (int i = 0; i < n - 1; ++i)
        {
            if (p[i] % p[i+1] != 0 || s[i+1] % s[i] != 0)
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
    scanf("%d", &t);
    while (t--) fun();
    return 0;
}