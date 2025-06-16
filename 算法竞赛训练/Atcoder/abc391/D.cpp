#include<stdio.h>
#include<vector>
#include<queue>
#include<math.h>
#include<algorithm>
using namespace std;
const int N=2e5+10;
const int INF=0x3f3f3f3f;
int n,w,q,p,ans[N];//p表示剩余的未删除的数量
struct Node
{
    int no,y;
    bool operator <(const Node &W) const
    {
        return y>W.y;
    }
};
int main()
{
    scanf("%d%d",&n,&w);
    vector<priority_queue<Node>>s(n+1);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        s[x].push({i,y});
    }
    p=n;
    for(int i=1;i<=n;++i) ans[i]=INF;
    while(p)
    {
        int t1=INF,t2=0;
        bool flag=0;
        for(int i=1;i<=w;++i)
        {
            if(s[i].size())
            {
                t1=min(t1,s[i].top().y);
                t2=max(t2,s[i].top().y); 
            }
            else
            {
                flag=1;
                break;
            }
        }//找出最小值
        if(flag) break;
        for(int i=1;i<=w;++i)
        {
            //if(s[i].size()&&s[i].top()<=t2)//如果小于等于最大值
            {
                auto tmp=s[i].top();
                s[i].pop();
                ans[tmp.no]=t2;
            }
        }
    }
    //for(int i=1;i<=n;++i)
    //{
    //    printf("Node%ddisappear%d\n",i,ans[i]);
    //}
    scanf("%d",&q);
    while(q--)
    {
        int t,a;
        scanf("%d%d",&t,&a);
        if(ans[a]>t) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}