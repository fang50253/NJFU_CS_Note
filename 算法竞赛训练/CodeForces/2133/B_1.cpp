#include<stdio.h>
#include<algorithm>
#include<functional>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll a[N];
void fun()
{
    ll n,ans=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    sort(a+1,a+n+1,greater<ll>());
    for(int i=1;i<=n;i+=2) ans+=a[i];
    printf("%lld\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}