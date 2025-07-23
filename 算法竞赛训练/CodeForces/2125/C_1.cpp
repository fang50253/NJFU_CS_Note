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
ll getans(ll x)
{
    return x-x/2-x/3-x/5-x/7+x/6+x/15+x/35+x/10+x/21+x/14-x/30-x/105-x/70-x/42+x/210;
}
void fun()
{
    ll l,r;
    scanf("%lld%lld",&l,&r);
    printf("%lld\n",getans(r)-getans(l-1));
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}