#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=2e5+10;
int dp[N],cnt[N],st[N];
void fun()
{
    memset(dp,0,sizeof dp);
    memset(cnt,0,sizeof cnt);
    memset(st,0,sizeof st);
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++cnt[x];
        if(x==1) dp[i]=dp[i-1]+1;
        else if(cnt[x]==1) st[x]=i;
        else if(cnt[x]==x)
        {
            dp[i]=max(dp[st[x]]+x,dp[i-1]);
            ans=max(ans,dp[i]);
            cnt[x]=0;
            printf("add%d\n",x);
        }
    }
    printf("%d\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}