#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll a[N];
void fun(){
    int n;
    scanf("%d",&n);
    ll findmax=0,anti=0;
    for(int i=0;i<n;++i){
        scanf("%lld",&a[i]);
        findmax=max(findmax,a[i]);
    }
    sort(a,a+n);
    for(int i=0;i<n;++i){
        if(a[i]==anti) swap(a[i],a[anti++]);
    }
    //1.先选最大的数字
    ll ans1;
    if(findmax==0) ans1=n;
    else ans1=n*findmax+anti*(anti+1)/2+(anti+findmax)*max(0ll,n-anti-1);
    //ll ans2=anti*(anti+1)/2+(anti+findmax)*(n-anti);
    printf("%lld\n",ans1);//max(ans1,ans2));
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}