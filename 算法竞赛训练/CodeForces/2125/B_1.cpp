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
ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}
void fun()
{
    ll a,b,k;
    scanf("%lld%lld%lld",&a,&b,&k);
    if(a<b) swap(a,b);
    ll g=gcd(a,b);
    ll dx=a/g;
    ll dy=b/g;
    if(dx<=k&&dy<=k)printf("1\n");
    else printf("2\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}