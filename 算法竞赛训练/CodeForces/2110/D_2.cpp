#include<stdio.h>
#include<algorithm>
#include<queue>
#include<math.h>
#include<iostream>
using namespace std;
const int N=2e5+10;
const int INF=0x3f3f3f3f;
int arr[N],e[2*N],ne[2*N],h[N],w[2*N],idx=1,ans[N];
bool st[N];
struct Node
{
    int node;//记录结点编号
    int battery;//记录电池最大值
    bool operator < (const Node &W) const
    {
        return battery>W.battery;
    }
};
void add(int a,int b,int c)
{
    ne[idx]=h[a];
    e[idx]=b;
    h[a]=idx;
    w[idx++]=c;
}
void fun()
{
    priority_queue<Node>que;
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    que.push({1,arr[1]});
    memset(st,0,sizeof st);
    memset(ans,0x3f,sizeof ans);
    memset(h,0,sizeof h);
    ans[1]=arr[1];
    st[1]=1;
    for(int i=1;i<=m;++i)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }
    while(que.size())
    {
        auto out=que.top();
        que.pop();
        cout<<"out"<<out.node<<endl;
        if(st[out.node]) continue;
        st[out.node]=1;
        for(int i=h[out.node];i;i=ne[i])
        {
            auto battcnt=out.battery;
            if(battcnt<w[i]) continue;
            que.push({e[i],arr[e[i]]+battcnt});
            ans[e[i]]=min(ans[e[i]],arr[e[i]]+battcnt);
        }
    }
    if(ans[n]==INF)printf("-1\n");
    else printf("%d\n",ans[n]);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}