#include<stdio.h>
#include<queue>
#include<algorithm>
using std::max;
using std::queue;
struct Node
{
    int x,y;
};
const int N=1e3+10;
bool mp[N][N],st[N][N],al;
int n,m,ans;
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
bool check2(int x,int y,struct Node big)
{
    bool flag=0;
    if(al) return 1;
    al=1;
    ++ans;
    for(int i=y;i<=big.y;++i)
    {
        if(mp[big.x][i]==1) flag=1;  
    }
    if(!flag) return 1;
    flag=0;
    for(int i=y;i<=big.y;++i)
    {
        if(mp[x][i]==1) flag=1;  
    }
    if(!flag) return 1;
    flag=0;
    for(int i=x;i<=big.x;++i)
    {
        if(mp[i][big.y]==1) flag=1;  
    }
    if(!flag) return 1;
    flag=0;
    for(int i=x;i<=big.x;++i)
    {
        if(mp[i][y]==1) flag=1;  
    }
    if(!flag) return 1;
    return 0;
}
bool check(int x,int y,struct Node big)
{
    //判断是不是里面有一个长方形区域全部是1
    
    for(int i=x;i<=big.x;++i)
    {
        for(int j=y;j<=big.y;++j)
        {
            if(mp[i][j]==0) 
                return check2(x,y,big);
        }
    }
    return 1;
}
bool in_map(int x,int y)
{
    return x>=1&&x<=n&&y>=1&&y<=m;
}
struct Node bfs(int x,int y)
{
    queue<Node>que;
    que.push({x,y});
    struct Node tmp={0,0};
    while(que.size())
    {
        auto out=que.front();
        st[out.x][out.y]=1;
        tmp.x=max(tmp.x,out.x);
        tmp.y=max(tmp.y,out.y);
        que.pop();
        for(int i=0;i<4;++i)
        {
            int x0=out.x+dx[i];
            int y0=out.y+dy[i];
            if(!in_map(x0,y0)) continue;
            if(st[x0][y0]==0) que.push({x0,y0});
            st[x0][y0]=1;
        }
    }
    return tmp;
}
int main()
{
    bool flag=1;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            char x;
            scanf(" %c",&x);
            if(x=='#') mp[i][j]=st[i][j]=0;
            else mp[i][j]=st[i][j]=1;
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(st[i][j]==0)
            {
                struct Node big=bfs(i,j);
                if(check(i,j,big))
                {
                    ++ans;
                }
                else
                {
                    flag=0;
                }
            }
        }
    }
    if(flag==0) printf("Bad placement.\n");
    else printf("There are %d ships.\n",ans);
    return 0;
}