#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=5e5+10;
typedef long long ll;
ll a[N];
void fun()
{
    ll n,ans=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
    {
		if(i==n||a[i]>a[i+1]) ans+=i*(n-i+1);
		else ans+=i;
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