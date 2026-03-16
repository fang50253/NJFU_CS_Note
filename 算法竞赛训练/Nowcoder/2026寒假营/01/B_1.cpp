#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int MOD=998244353;
typedef long long ll;
ll a[N],b[N],ans=1;
void cal(ll x,ll y){
    while(y--){
        ans=ans*(x--)%MOD;
    }
}
void fun()
{
    int n,idxa=0,idxb=1;//idx已经扫描
    ans=1;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i) scanf("%lld",&b[i]);
    sort(b+1,b+n+1);
    //吐掉所有小于b中最小值的a
//     for(int i=1;i<=n;++i) cout<<a[i]<<" ";
//     cout<<endl;
    while(a[idxa+1]<b[idxb]&&idxa<n) ++idxa;
    ll tmp=0,tmp1=1;
    //cout<<idxa<<" "<<idxb<<endl;;
   while(idxa<n){
       if(a[idxa+1]==0) break;
       tmp=a[idxa+1]-a[idxa]+1;
       ++idxa;
       while(a[idxa]+1==a[idxa+1]) {++idxa;++tmp1;}
       cal(max(tmp,tmp1),min(tmp,tmp1));
   }
    printf("%lld\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}