#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll arr[N];
void fun()
{
    int n,k;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    scanf("%d",&k);
    ll ans=0;
    for(int i=1;i<=n-k+1;++i) ans=max(ans,arr[i]);
    for(int i=n-k+2;i<=n;++i) ans+=arr[i];
    printf("%lld\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}