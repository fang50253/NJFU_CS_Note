#include<stdio.h>
#include<queue>
#include<algorithm>
#include<string.h>
using std::min;
using std::queue;
const int N=410;
bool st[N][N];
const int INF=0x3f3f3f3f;
struct Node
{
    int x,y,step;
};
queue<Node>que;
int n,m,x,y,dist[N][N];
const int dx[]={1,1,-1,-1,2,2,-2,-2};
const int dy[]={2,-2,2,-2,1,-1,1,-1};
int main()
{
    scanf("%d%d%d%d",&n,&m,&x,&y);
    st[x][y]=1;
    que.push({x,y,0});
    memset(dist,0x3f,sizeof dist);
    while(que.size())
    {
        auto v=que.front();
        dist[v.x][v.y]=min(dist[v.x][v.y],v.step);
        que.pop();
        for(int i=0;i<8;++i)
        {
            int x0=v.x+dx[i];
            int y0=v.y+dy[i];
            if(x0>n||x0<=0) continue;
            if(y0>m||y0<=0) continue;
            if(!st[x0][y0])
            {
                st[x0][y0]=1;
                que.push({x0,y0,v.step+1});
                //st[x0][y0]=0;
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(dist[i][j]==INF) printf("-1 ");
            else printf("%d ",dist[i][j]);
        }
        printf("\n");
    }
    return 0;
}