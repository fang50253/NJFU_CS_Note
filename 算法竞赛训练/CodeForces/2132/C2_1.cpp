#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
const int N=1e5+10;
typedef long long ll;
ll pow_[N],v[N];
ll value(ll a)
{
    if(a==0) return 3;
    return pow_[a+1]+a*pow_[a-1];
}
void fun()
{
    ll idx=0,n,k;
    scanf("%lld%lld",&n,&k);
    while(n)
    {
        v[idx++]=n%3;
        k-=n%3;
        n/=3;
    }
    if(k<0)
    {
		printf("-1\n");
		return;
	}
    ll ans=0;
	for(int i=idx-1;i>=0;i--)
    {
		if(i!=0)
        {
			ll p=min(v[i],(ll)k/2);
			v[i]-=p;
            v[i-1]+=3*p;
            k-=2*p;
		}
		ans+=v[i]*value(i);
	}
	printf("%lld\n",ans);
}
int main()
{
    pow_[0]=1;
    for(int i=1;pow_[i-1]<=1e9;++i) pow_[i]=pow_[i-1]*3;
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}