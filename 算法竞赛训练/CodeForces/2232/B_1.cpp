#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll ans[N];
void fun(){
    int n;
    scanf("%d",&n);
    ll sum=0,mx=0,mi=0x3f3f3f3f3f3f3f3f;
    for(int i=1;i<=n;++i){
        if(i==1) {
            scanf("%lld",&ans[i]);
            sum+=ans[i];
            mi=min(mi,ans[1]);
        }
        else{
            ll x;
            scanf("%lld",&x);
            if(ans[i-1]>x){
                ans[i]=min(mi,(sum+x)/i);
            }
            else{
                ans[i]=min(mi,ans[i-1]);
            }
            sum+=x;
            mi=min(mi,sum/i);
        }
        printf("%lld ",ans[i]);
    }
    printf("\n");
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}