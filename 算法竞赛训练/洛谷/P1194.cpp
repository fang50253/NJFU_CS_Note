#include<stdio.h>
#include<algorithm>
#include<set>
using namespace std;
const int N=510;
int idx=1,p[N],cnt,ans;
struct Node
{
    int a,b,w;
    bool operator < (const Node &W) const
    {
        return w<W.w;
    }
}edge[N*N];
int find(int x)
{
    if(x!=p[x]) p[x]=find(p[x]);
    return p[x];
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x;
            scanf("%d",&x);
            if(i<j) edge[idx++]={i,j,x};
        }
    }
    sort(edge+1,edge+idx);
    for(int i=1;i<=n;++i) p[i]=i;
    for(int i=1;i<idx&&cnt<n-1;++i)
    {
        int fa=find(edge[i].a),fb=find(edge[i].b);
        if(fa==fb) continue;
        if(edge[i].w>=m) break;
        p[fa]=fb;
        ++cnt;
        ans+=edge[i].w;
    }
    set<int>s;
    for(int i=1;i<=n;++i) s.insert(find(i));
    printf("%d\n",ans+m*s.size());
    return 0;
}