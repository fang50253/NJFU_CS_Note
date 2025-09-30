#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=2e5+10;
int dp[N],cnt[N],st[N];
void fun() {
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;++i) cnt[i]=0;
    
    for (int i=0;i<n;++i) {
        int x; scanf("%d",&x);
        cnt[x]++;
    }

    int ans=0;
    for (int v=1;v<=n;++v) {
        ans += (cnt[v]/v)*v;  // 每 v 个 v 可以组成一个 block
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