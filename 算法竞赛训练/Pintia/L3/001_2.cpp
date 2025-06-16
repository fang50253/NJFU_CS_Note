#include<stdio.h>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=1e4+10;
LL n,m,a[N];
vector<queue<int>>que(N);
bool st[N];
struct Node
{
    int x;//待更新的索引号
    int t;//第几个数字
};
queue<Node>wa;
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    wa.push({0,1});
    while(wa.size())
    {
        auto x=wa.front();
        wa.pop();
        int x0=x.x+a[x.t];
        if(x0<=m&&st[x0])
        {
            st[x0]=1;
            queue<int>tmp;
            while(que[x].size())
            {
                auto out=que[x].front();
                que[x].pop();
                tmp.push(out.x);
            }
            while(tmp.size())
            {
                auto out=tmp.front();
                tmp.pop();
                que[x].push(out);
                que[x0].push(out);
            }
            que[x0].push(a[x.t]);
            wa.push({x0,x.t+1});
        }
    }
    if(st[m]==0) printf("No solution\n");
    else
    {
        while(que[m].size())
        {
            printf("%d ",que[m].front());
            que[m].pop();
        }
        printf("\n");
    }
    return 0;
}