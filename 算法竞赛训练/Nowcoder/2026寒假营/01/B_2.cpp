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
    int x=0;
    for(int i=n;i>=1;--i)
    {
        if(a[i]>b[1]) ++x;
        else break;
    }
    cal(x,x);
    cal(n-x,n-x);
    printf("%lld\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}