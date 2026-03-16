#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll a[N],b[N];
void fun(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=m;++i){
        scanf("%lld",&b[i]);
    }
    sort(a+1,a+1+n,greater<ll>());
    sort(b+1,b+1+m,greater<ll>());
    ll sum1=0,sum2=0;
    for(int i=1;i<=n;++i){
        sum1+=a[i];
    }
    for(int i=1;i<=m;++i){
        sum2+=b[i];
    }
    int ans=0;
    if(sum1==sum2){
        printf("1\n");
    }
    else if(sum1>sum2){
        int idx=1;
        while(sum1>sum2){
            sum1-=a[idx++];
            ++ans;
        }
        printf("%d\n",ans);
    }
    else{
        int idx=1;
        while(sum1<sum2){
            sum2-=b[idx++];
            ++ans;
        }
        printf("%d\n",ans);
    }
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}