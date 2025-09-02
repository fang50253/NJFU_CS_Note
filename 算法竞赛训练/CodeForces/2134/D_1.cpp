#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<utility>
#include<unordered_map>
#include<queue>
#include<stack>
#include<cstdlib>
#include<string.h>
#include<stdlib.h>
#include<unordered_set>
#define PII pair<int,int>
using namespace std;
typedef long long ll;
const int N=2e5+10;
bool t[N];
struct Node
{
    ll node,cen,up;
};
void fun()
{
    memset(t,0,sizeof t);
    vector<ll>edg[N];//表示一个顶点指向的边
    queue<Node>que;
    ll n;
    scanf("%lld",&n);
    for(int i=1;i<=n-1;++i)
    {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        edg[a].push_back(b);
        edg[b].push_back(a);
    }
    bool flag=0;
    for(int i=1;i<=n;++i)
    {
        if(edg[i].size()==1)
        {
            que.push({edg[i][0],1,i});
            t[i]=1;
        }
        if(edg[i].size()>=3) flag=1;
    }
    if(!flag)
    {
        printf("-1\n");
        return ;
    }
    while(que.size())
    {
        auto x=que.front();
        que.pop();
        if(t[x.node]) continue;
        t[x.node]=1;
        if(edg[x.node].size()==2)
        {
            for(int i=0;i<=1;++i)
            {
                if(!t[edg[x.node][i]])
                {
                    que.push({edg[x.node][i],x.cen+1,x.node});
                }
            }
        }
        else
        {
            for(int i=0;i<edg[x.node].size();++i)
            {
                if(edg[x.node][i]!=x.up)
                {
                    printf("%lld %lld %lld\n",edg[x.node][i],x.node,x.up);
                    return;
                }
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}