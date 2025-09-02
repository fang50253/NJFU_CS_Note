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
int t[N],ti;
vector<int>edg[N];//表示一个顶点指向的边
struct Node
{
    int node,cen,up;
};
void fun()
{
    
    ++ti;
    queue<Node>que;
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) edg[i].clear();
    for(int i=1;i<=n-1;++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        edg[a].push_back(b);
        edg[b].push_back(a);
    }
    bool flag=0;
    for(int i=1;i<=n;++i)
    {
        if(edg[i].size()==1)
        {
            que.push({edg[i][0],1,i});
            t[i]=ti;
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
        if(t[x.node]==ti) continue;
        t[x.node]=ti;
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
                    printf("%d %d %d\n",edg[x.node][i],x.node,x.up);
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