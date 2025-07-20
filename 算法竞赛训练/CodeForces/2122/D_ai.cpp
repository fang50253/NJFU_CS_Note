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
const int INF=0x3f3f3f3f3f3f3f3f;
const int N=5010;
int t,n,m,ans;
vector<int> g[N];
struct State {
    int time,wait,u;
    bool operator>(const State &W) const 
    {
        if(time!=W.time) return time>W.time;
        return wait>W.wait;
    }
};
void fun()
{
    cin>>n>>m;
    for(int i=1;i<=n;++i) g[i].clear();
    for(int i=0;i<m;++i){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> dist(n+1,INF);
    vector<int> waitTime(n+1,INF);
    priority_queue<State,vector<State>,greater<State>> pq;
    pq.push({0,0,1});
    dist[1]=0;
    waitTime[1]=0;
    while(!pq.empty())
    {
        auto [t,w,u]=pq.top();pq.pop();
        if(t>dist[u]) continue;
        if(t==dist[u]&&w>waitTime[u]) continue;
        int d=g[u].size();
        int k=t%d;
        int v=g[u][k];
        if(t+1<dist[v]||(t+1==dist[v]&&w<waitTime[v]))
        {
            dist[v]=t+1;
            waitTime[v]=w;
            pq.push({t+1,w,v});
        }
        if(t+1<dist[u]||(t+1==dist[u]&&w+1<waitTime[u]))
        {
            dist[u]=t+1;
            waitTime[u]=w+1;
            pq.push({t+1,w+1,u});
        }
    }
    printf("%lld %lld\n",dist[n],waitTime[n]);
}

signed main()
{
    scanf("%lld",&t);
    while(t--) fun();
    return 0;
}