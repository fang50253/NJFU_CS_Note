#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll arr[N];
void fun()
{
    ll n,ans=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    sort(arr+1,arr+1+n);
    for(int i=2;i<=n;i+=2) ans=max(ans,arr[i]-arr[i-1]);
    printf("%lld\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}