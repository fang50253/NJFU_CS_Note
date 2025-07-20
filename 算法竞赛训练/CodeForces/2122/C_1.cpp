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
#define int long long
#define PII pair<int,int>
using namespace std;
const int N=2e5+10;
int n,ans;
struct Node
{
    int x,y,xy,index;
    bool operator< (const Node &W) const{
        return xy<W.xy;
    }
}node[N];
void fun()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%lld%lld",&x,&y);
        node[i]={x,y,max({x+y,x-y,y-x}),i};
    }
    sort(node+1,node+1+n);
    for(int i=1,j=n;i<=n>>1;++i,--j) printf("%lld %lld\n",node[i].index,node[j].index);
}
signed main()
{
    int t;
    scanf("%lld",&t);
    while(t--) fun();
    return 0;
}