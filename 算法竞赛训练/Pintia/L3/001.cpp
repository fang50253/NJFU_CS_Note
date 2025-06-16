#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1e4+10;
typedef long long LL;
LL dp[N],dpm[N],n,m,a[N];
//dpm中存放最后一个放入的数字
void printdp()
{
    for(int i=1;i<=m;++i) printf("%lld ",dp[i]);
    printf("\n");
}
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    for(LL i=1;i<=n;++i)//从大到小依次把东西放入背包
    {
        for(int j=m;i>=0;--j)
        {
            if(j<a[i]) break;
            if(dp[j-a[i]]+a[i]>=dp[j])
            {
                if(dp[j-a[i]]+a[i]>dp[j]) dpm[j]=a[i];
                dp[j]=dp[j-a[i]]+a[i];
            }
        }
    }
    //倒着输出
    queue<LL>que;
    LL last;
    for(int i=m;i>=0&&dpm[i]!=0;i-=dpm[i])
    {
        
        if(i==m) {last=i;continue;}
        else {que.push(last-dpm[i]);last=i;}
        if(dpm[i]==i)
        {
            while(que.size())
            {
                printf("%lld ",que.front());
                que.pop();
            }
            return 0;
        }
    }
    printdp();
    printf("No solution\n");
    return 0;
}