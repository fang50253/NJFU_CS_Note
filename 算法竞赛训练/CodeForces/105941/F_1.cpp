#include<iostream>
#include<vector>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
const int INF=0x3f3f3f3f;
struct node
{
    int x,y;
};
void fun()
{
    int n,m,maxans=0,minans=INF;
    scanf("%d%d",&n,&m);
    vector<vector<bool>>vec(n+10);
    queue<node>que;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            char x;
            scanf(" %c",&x);
            if(x=='.') vec[i].push_back(true);
            else vec[i].push_back(false);
        }
    }
    que.push({0,0});
    vec[0][0]=false;
    while(que.size())
    {
        auto x=que.front();
        que.pop();
        maxans=max(maxans,x.x+x.y);
        for(int i=0;i<4;++i)
        {
            int nx=x.x+dx[i],ny=x.y+dy[i];
            if(nx<0||ny<0||nx>=n||ny>=m||!vec[nx][ny]) continue;
            vec[nx][ny]=false;
            que.push({nx,ny});
        }
    }
    que.push({n-1,n-1});
    vec[n-1][n-1]=false;
    while(que.size())
    {
        auto x=que.front();
        que.pop();
        maxans=max(maxans,x.x+x.y);
        for(int i=0;i<4;++i)
        {
            int nx=x.x+dx[i],ny=x.y+dy[i];
            if(nx<0||ny<0||nx>=n||ny>=m||!vec[nx][ny]) continue;
            vec[nx][ny]=false;
            que.push({nx,ny});
        }
    }
    printf("%d\n",minans-maxans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}