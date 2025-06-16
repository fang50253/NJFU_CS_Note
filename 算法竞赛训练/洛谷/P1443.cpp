#include<stdio.h>
#include<string.h>
#include<algorithm>
using std::min;
const int N=410;
bool st[N][N];
int n,m,x,y,dis[N][N];
const int dx[]={1,1,-1,-1,2,2,-2,-2};
const int dy[]={2,-2,2,-2,1,-1,1,-1};
void dfs(int x0,int y0,int step)
{
    if(dis[x0][y0]<=step) return;
    dis[x0][y0]=min(step,dis[x0][y0]);
    for(int i=0;i<8;++i)
    {
        int x1=x0+dx[i];
        int y1=y0+dy[i];
        if(x1>n||x1<=0) continue;
        if(y1>m||y1<=0) continue;//printf("ok");
        if(st[x1][y1]==0)
        {
            st[x1][y1]=1;
            dfs(x1,y1,step+1);
            st[x1][y1]=0;
        }
    }
}
int main()
{
    memset(st,0,sizeof st);
    scanf("%d%d%d%d",&n,&m,&x,&y);
    memset(dis,0x3f,sizeof dis);
    st[x][y]=1;
    dfs(x,y,0);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(dis[i][j]==0x3f3f3f3f) printf("-1 ");
            else printf("%d ",dis[i][j]);
        }
        printf("\n");
    }
    return 0;
}