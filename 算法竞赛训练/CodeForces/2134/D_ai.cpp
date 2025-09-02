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
bool vis[N];
struct Node{ll u,p;};
vector<ll>edg[N];
void fun()
{
    memset(vis,0,sizeof vis);
    ll n;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) edg[i].clear();
    for(int i=1;i<n;++i)
    {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        edg[a].push_back(b);
        edg[b].push_back(a);
    }
    queue<Node>q;
    for(int i=1;i<=n;++i)
    {
        if(edg[i].size()==1)
        {
            q.push({i,-1});
            vis[i]=1;
        }
    }
    while(!q.empty())
    {
        auto [u,p]=q.front();q.pop();
        if(edg[u].size()>=3)
        {
            for(auto v:edg[u]) if(v!=p)
            {
                printf("%lld %lld %lld\n",v,u,p);
                return;
            }
        }
        for(auto v:edg[u]) if(!vis[v])
        {
            vis[v]=1;
            q.push({v,u});
        }
    }
    printf("-1\n");
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}