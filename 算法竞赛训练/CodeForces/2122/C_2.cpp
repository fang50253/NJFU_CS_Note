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
#define int long long
#define PII pair<int,int>
using namespace std;
const int N=2e5+10;
int n,ans;
struct Node
{
    int x,y,kind,index;
}node[N];
bool cmp1(Node x,Node y)
{
    return x.x<y.x;
}
bool cmp2(Node x,Node y)
{
    return x.y<y.y;
}
bool cmp3(Node x,Node y)
{
    return x.kind<y.kind;
}
void fun()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%lld%lld",&x,&y);
        node[i]={x,y,0,i};
    }
    sort(node+1,node+1+n,cmp1);
    for(int i=1;i<=n>>1;++i) node[i].kind=1;
    sort(node+1,node+1+n,cmp2);
    for(int i=1;i<=n>>1;++i)
    {
        if(node[i].kind==1) node[i].kind=3;
        else node[i].kind=2;
    }
    sort(node+1,node+1+n,cmp3);
    for(int i=1,j=n;i<=n>>1;++i,--j) printf("%lld %lld\n",node[i].index,node[j].index);
}
signed main()
{
    int t;
    scanf("%lld",&t);
    while(t--) fun();
    return 0;
}