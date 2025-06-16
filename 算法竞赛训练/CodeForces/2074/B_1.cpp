#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll n,arr[N];
void fun()
{
    ll s=0;
    scanf("%lld",&n);
    for(ll i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i]);
        s+=arr[i];
    }
    printf("%lld\n",s-n+1);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}