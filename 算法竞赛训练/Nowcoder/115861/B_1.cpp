#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=30;
ll a[N],b[N],ans;
ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    for(int i=2;i<=n;++i) b[i-1]=a[i-1]^a[i];
    ans=b[1];
    for(int i=2;i<=n-1;++i) ans=gcd(ans,b[i]);
    printf("%lld\n",ans);
    return 0;
}