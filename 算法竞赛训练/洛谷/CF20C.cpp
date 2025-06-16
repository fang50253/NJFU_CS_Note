#include<stdio.h>
#include<queue>
#include<algorithm>
#include<string.h>
#include<stack>
#define int long long
using namespace std;
const int N=1e5+10;
const int INF=0x3f3f3f3f3f3f3f3f;
struct Node
{
    int e,dist;
    bool operator < (const Node &W) const
    {
        return dist>W.dist;
    }
};
int h[N],e[2*N],ne[2*N],w[2*N],idx=1,n,m,dist[N];
bool st[N];
void add(int a,int b,int c)
{
    ne[idx]=h[a];
    h[a]=idx;
    w[idx]=c;
    e[idx++]=b;
}
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int a,b,c;
        scanf("%lld%lld%lld",&a,&b,&c);
        add(a,b,c);
        add(b,a,c);
    }
    priority_queue<Node>que;
    memset(dist,0x3f,sizeof dist);
    que.push({1,0});
    dist[1]=0;
    while(que.size())
    {
        auto it=que.top();
        que.pop();
        if(st[it.e]) continue;
        st[it.e]=1;
        for(int i=h[it.e];i;i=ne[i])
        {
            if(dist[e[i]]>dist[it.e]+w[i])
            {
                dist[e[i]]=dist[it.e]+w[i];
                que.push({e[i],dist[e[i]]});
            }
        }
    }
    if(dist[n]==INF)
    {
        printf("-1\n");
        return 0;
    }
    int out=n;
    stack<int>sta;
    while(out!=1)
    {
        for(int i=h[out];i;i=ne[i])
        {
            if(dist[e[i]]+w[i]==dist[out])
            {
                sta.push(out);
                out=e[i];
            }
        }
    }
    printf("1 ");
    while(sta.size())
    {
        auto x=sta.top();
        printf("%lld ",x);
        sta.pop();
    }
    return 0;
}