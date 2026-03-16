//dp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3010;
ll dp[N][N];
ll a[N],b[N];
//定义为，i次操作后能否得到j
int main(){
    dp[0][0]=1;
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    for(int i=1;i<=n;++i) scanf("%lld",&b[i]);
    for(int i=1;i<=n;++i){
        //jinxin第i次操作
        for(int j=0;j<=2047;++j){
            if(dp[i-1][j]){
                int rule1=max((ll)0,j-a[i]);
                dp[i][rule1]=1;
                int rule2=j^b[i];
                dp[i][rule2]=1;
            }
        }
    }
    int ans=0;
    for(int j=0;j<=2047;++j){
        if(dp[n][j]==1) ans=j;
    }
    printf("%d\n",ans);
    return 0;
}