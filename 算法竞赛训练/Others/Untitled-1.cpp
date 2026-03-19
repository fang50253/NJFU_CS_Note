#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
const ll INF=0x3f3f3f3f3f3f3f3f;
void fun(){
    int n;
    scanf("%d",&n);
    vector<ll> a(n+1),b(n+1),c(n+1);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    for(int i=1;i<=n;++i) scanf("%lld",&b[i]);
    for(int i=1;i<=n;++i) scanf("%lld",&c[i]);
    vector<vector<ll>>dp(n+10,vector<ll>(3,INF));
    dp[1][0]=0;
    dp[1][1]=b[1];
    if(a[1]>1) dp[1][2]=c[1];
    else dp[1][2]=INF;
    for(int i=2;i<=n;++i){
        for(int j=0;j<3;++j){
            ll tmp;
            if(j==0) tmp=a[i];
            else if(j==1) tmp=a[i]+1;
            else{
                if(a[i]<=1) continue;
                tmp=a[i]-1;
            }
            for(int k=0;k<3;++k){
                ll t;
                if(k==0) t=a[i-1];
                else if(k==1) t=a[i-1]+1;
                else{
                    if(a[i-1]<=1) continue;
                    t=a[i-1]-1;
                }
                if(tmp!=t){
                    if(j==1) dp[i][j]=min(dp[i][j],dp[i-1][k]+b[i]);
                    else if(j==2) dp[i][j]=min(dp[i][j],dp[i-1][k]+c[i]);
                    else dp[i][j]=min(dp[i][j],dp[i-1][k]);
                }
            }
        }
    }
    ll ans=min({dp[n][0],dp[n][1],dp[n][2]});
    printf("%lld\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}