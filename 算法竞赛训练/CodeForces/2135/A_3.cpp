#include<stdio.h>
#include<deque>
#include<vector>
#include<functional>
#include<string.h>
using namespace std;
const int N=2e5+10;
vector<deque<int>>vec(N);
void fun()
{
    int n,ans=0;
    scanf("%d",&n);
    int dp[n+1];
    dp[0]=0;
    for(int i=1;i<=n;++i) vec[i].clear();
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        vec[x].push_back(i);
        if(vec[x].size()==x)
        {
            dp[i]=max(dp[i-1],dp[vec[x].front()-1]+x);
            //while(vec[x].size()) 
            vec[x].pop_front();
        }
        else dp[i]=dp[i-1];
        ans=max(dp[i],ans);
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