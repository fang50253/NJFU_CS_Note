#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll a[N];
void fun(){
    ll n,ans=0;
    scanf("%lld",&n);
    for(ll i=0;i<n;++i){
        scanf("%lld",&a[i]);
    }
    for(ll i=n-1;i>=0;--i){
        if(i==0){
            if(a[i]>0) ++ans;
        }
        else{
            if(a[i]>0){
                a[i-1]+=a[i];
                ++ans;
            }
        }
    }
    printf("%lld\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}