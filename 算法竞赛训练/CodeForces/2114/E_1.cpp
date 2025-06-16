#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#define int long long 
using namespace std;
const int N=2e5+10;
const int INF=0x3f3f3f3f;
int e[N*2],ne[N*2],h[N],idx=1,color[N];//color[]=1表示正，color[]=-1表示负
int tr[N];//表示每个节点的价值
int dpmax[N];//dpmax[i]表示以i为根的子树的最大价值
int dpmin[N];
bool st[N];//访问标记
void add(int a,int b)
{
    e[idx]=b;
    ne[idx]=h[a];
    h[a]=idx++;
    //w[idx++]=c;
}
void fun()
{
    //memset(color,0,sizeof color);
    memset(st,0,sizeof st);
    memset(h,0,sizeof h);
    //memset(dpmax,0,sizeof dpmax);
    //memset(dpmin,0x3f,sizeof dpmin);
    //memset(dpmin,0,sizeof dpmin);
    int n;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&tr[i]);
    for(int i=1;i<=n-1;++i)
    {
        int a,b;
        scanf("%lld%lld",&a,&b);
        add(a,b);
        add(b,a);
    }
    //染色
    color[1]=-1;
    queue<int>q;
    /*
    q.push(1);
    while(q.size())
    {
        auto x=q.front();
        q.pop();
        for(int i=h[x];i;i=ne[i])
        {
            if(color[e[i]]!=0) continue;
            color[e[i]]=color[x]*(-1);
            q.push(e[i]);
        }
    }
        */
    q.push(1);
    dpmax[1]=tr[1];
    dpmin[1]=tr[1];
    while(q.size())
    {
        auto x=q.front();
        q.pop();
        st[x]=1;
        for(int i=h[x];i;i=ne[i])
        {
            if(st[e[i]]) continue;
            //dpmax[e[i]]=max(tr[e[i]]*color[e[i]],dpmax[x]+tr[e[i]]*color[e[i]]);
            dpmax[e[i]]=max({tr[e[i]],dpmax[x]*(-1)+tr[e[i]],dpmin[x]*(-1)+tr[e[i]]});
            dpmin[e[i]]=min({tr[e[i]],dpmax[x]*(-1)+tr[e[i]],dpmin[x]*(-1)+tr[e[i]]});
            q.push(e[i]);
        }
    }
    for(int i=1;i<=n;++i) printf("%lld ",dpmax[i]);
    printf("\n");
    //for(int i=1;i<=n;++i) printf("%lld ",color[i]);
    //printf("\n");
}
signed main()
{
    int t;
    scanf("%lld",&t);
    while(t--) fun();
    return 0;
}