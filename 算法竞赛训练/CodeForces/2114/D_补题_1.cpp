#include<stdio.h>
#include<iostream>
#include<set>
#include<algorithm>
#include<unordered_set>
#include<math.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int INF=1e9;
struct Node
{
    int x,y;
};
void fun()
{
    int n;
    scanf("%lld",&n);
    unordered_set<Node>s;
    int xmax=0,xmin=INF+10,ymax=0,ymin=INF+10;
    int xmaxcnt=0,xmincnt=0,ymaxcnt=0,ymincnt=0;
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%lld%lld",&x,&y);
        Node node={x,y};
        s.insert(node);
        if(x==xmax) ++xmaxcnt;
        else xmaxcnt=1;
        if(x==xmin) ++xmincnt;
        else xmincnt=1;
        if(y==ymax) ++ymaxcnt;
        else ymaxcnt=1;
        if(y==ymin) ++ymincnt;
        else ymincnt=1;
        xmax=max(xmax,x);
        xmin=min(xmin,x);
        ymax=max(ymax,y);
        ymin=min(ymin,y);
    }
    if(xmaxcnt>=2&&xmincnt>=2&&ymaxcnt>=2&&ymincnt>=2)
    {
        printf("%lld\n",(xmax-xmin+1)*(ymax-ymin+1));
        return;
    }
    else
    {
        if(xmaxcnt<=1)
        {
            for(int i=ymin;i<=ymax;++i)
            {
                if(s.find({x,i})==s.end())
                {
                    printf("YES\n");
                    return;
                }
            }
        }
    }
}
signed main()
{
    int t;
    scanf("%lld",&t);
    while(t--) fun();
    return 0;
}