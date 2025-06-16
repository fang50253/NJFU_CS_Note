#include<stdio.h>
#include<algorithm>
#include<set>
#include<queue>
#include<string.h>
using namespace std;
const int N=510;
int idx=1,p[N],cnt,ans;
struct Node
{
    int a,b,w;
    bool operator < (const Node &W) const
    {
        return w>W.w;
    }
};
int find(int x)
{
    if(x!=p[x]) p[x]=find(p[x]);
    return p[x];
}
int main()
{
    int n,m;
    priority_queue<Node>que;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x;
            scanf("%d",&x);
            if(i<j)
            {
                if(x<=m&&x!=0) que.push({i,j,x});
                else que.push({i,j,m});
            }
        }
    }
    for(int i=1;i<=n;++i) p[i]=i;
    for(int i=1;que.size()&&cnt<n-1;++i)
    {
        auto edge=que.top();
        que.pop();
        int fa=find(edge.a),fb=find(edge.b);
        if(fa==fb) continue;
        p[fa]=fb;
        ++cnt;
        ans+=edge.w;
    }
    printf("%d\n",ans+m);
    return 0;
}