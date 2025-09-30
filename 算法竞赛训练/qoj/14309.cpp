//The 2025 ICPC Asia East Continent Online Contest (I).  Problem I
#include<stdio.h>
#include<queue>
#include<string.h>
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+10;
const int INF=0x3f3f3f3f3f3f3f3f;
int e[N],ne[N],h[N],w[N],n,m,v,t,idx=1,dist[N];
bool st[N];
struct Node
{
    int node;//结点的编号
    int bags;//丢弃的包的个数
    int item;//剩余的物品个数
    bool operator < (const Node &W) const
    {
        if(bags==W.bags) return item>W.item;
        else return bags>W.bags;
    }
};
void add(int a,int b,int c)
{
    ne[idx]=h[a];
    h[a]=idx;
    e[idx]=b;
    w[idx++]=c;
}
signed main()
{
    ios::sync_with_stdio(0);
    memset(dist,0x3f,sizeof dist);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>v>>t;
    for(int i=1;i<=m;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c);
        add(b,a,c);
    }
    priority_queue<Node>que;
    dist[t]=0;
    que.push({t,0,0});
    while(que.size())
    {
        auto x=que.top();
        que.pop();
        if(st[x.node]) continue;
        else st[x.node]=1;
        //cout<<"确定"<<x.node<<" "<<x.bags<<" "<<x.item<<endl;
        for(int i=h[x.node];i;i=ne[i])
        {
            if(x.item+w[i]>v)
            {
                //if(st[e[i]]) continue;
                que.push({e[i],dist[x.node]+1,w[i]});
                dist[e[i]]=min(dist[x.node]+1,dist[e[i]]);
            }
            else
            {
                //if(st[e[i]]) continue;
                que.push({e[i],dist[x.node],x.item+w[i]});
                dist[e[i]]=min(dist[x.node],dist[e[i]]);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(dist[i]==INF) cout<<"-1 ";
        else cout<<dist[i]+1<<" ";
    }
    cout<<endl;
    return 0;
}