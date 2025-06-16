#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<set>
#include<map>
#include<algorithm>
#include<unordered_map>
#include<queue>
using namespace std;
const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};
const int N=110;
char t[N][N];
int n, m;
typedef pair<int,int> PII;
int dist[N][N];
bool inmap(int nx,int ny)
{
    return nx>=0&&nx<n&&ny>=0&&ny<m;
}
int fun() 
{
    PII st={-1,-1},ed={-1,-1};
    for (int i=0;i<n;++i) 
    {
        for (int j=0;j<m;++j) 
        {
            if(t[i][j]=='x') st={i, j};
            if(t[i][j]=='p') ed={i, j};
        }
    }
    if (st.first==-1||ed.first==-1) return -1;
    queue<PII>q;
    memset(dist, -1, sizeof dist);
    q.push(st);
    dist[st.first][st.second] = 0;
    while (!q.empty()) 
    {
        auto out=q.front();
        auto x=out.first;
        auto y=out.second;
        q.pop();
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (inmap(nx,ny)&& t[nx][ny]!='#'&&dist[nx][ny]==-1)
            {
                dist[nx][ny]=dist[x][y]+1;
                q.push({nx,ny});
                if(nx==ed.first&&ny==ed.second) return dist[nx][ny];
            }
        }
    }
    return -1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;++i) scanf("%s",t[i]);
    printf("%d",fun());
    return 0;
}