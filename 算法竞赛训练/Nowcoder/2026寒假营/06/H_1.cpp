//dp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3010;
ll dp[N][2],a[N],b[N];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    for(int i=1;i<=n;++i) scanf("%lld",&b[i]);
    for(int i=1;i<=n;++i){
        dp[i][0]=max(dp[i-1][0]^b[i],dp[i-1][1]^b[i]);
        dp[i][1]=max(max((ll)0,dp[i][0]-a[i]),dp[i][1]-a[i]);
    }
    printf("%lld\n",max(dp[n][0],dp[n][1]));
    return 0;
}