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
const int N=2e5+10;
struct Node
{
    ll l,r,real;
    bool operator < (const Node &W) const{
        return real<W.real;
    }
}arr[N];
void fun()
{
    ll n,k;
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld%lld",&arr[i].l,&arr[i].r,&arr[i].real);
    }
    sort(arr+1,arr+1+n);
    for(int i=1;i<=n;++i)
    {
        // if(arr[i].real<k)
        // {
        //     printf("%lld\n",k);
        //     return;
        // }
        if(arr[i].l<=k&&k<=arr[i].r) k=max(k,arr[i].real); 
    }
    printf("%lld\n",k);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}