#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
const ll INF=0x3f3f3f3f3f3f3f3f;
ll e[N],ne[N],h[N],idx=1,w[N],n,m,tele[N][2],dp[N][2];
bool st[N];
void add(ll a,ll b,ll c)
{
    e[idx]=b;
    ne[idx]=h[a];
    h[a]=idx;
    w[idx++]=c;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n-1;++i)
    {
        ll a,b,c;
        cin>>a>>b>>c;
        add(a,b,c);
        add(b,a,c);
    }
    //读取传送门的位置
    for(int i=1;i<=m;++i)
        cin>>tele[i][0]>>tele[i][1];
    //第一遍扫描
    memset(dp,0x3f,sizeof dp);
    queue<ll>que;
    que.push(1);
    dp[1][0]=0;
    while(que.size())
    {
        auto x=que.front();
        que.pop();
        if(st[x]) continue;
        st[x]=1;
        for(int i=h[x];i;i=ne[i])
        {
            if(st[e[i]]) continue;
            que.push(e[i]);
            dp[e[i]][0]=dp[x][0]+w[i];
        }
    }
    for(int i=1;i<=n;++i) cout<<dp[i][0]<<" ";
    cout<<"\n";
    for(int i=1;i<=n;++i)
    {
        //进行一次松弛操作
        for(int j=1;j<=m;++j)
        {
            dp[tele[j][0]][i%2]=min(dp[tele[j][0]][(i+1)%2],dp[tele[j][1]][(i+1)%2]);
            dp[tele[j][1]][i%2]=min(dp[tele[j][0]][(i+1)%2],dp[tele[j][1]][(i+1)%2]);
        }
        for(int i=1;i<=n;++i) cout<<dp[i][i%2]<<" ";
        cout<<"\n";
    }
    return 0;
}