#include<stdio.h>
using namespace std;
typedef long long ll;
void fun()
{
    ll n,ans=0;
    scanf("%lld",&n);
    ans+=n%10;
    n/=10;
    ll tmp=1;
    while(n)
    {
        tmp<<=1;
        auto x=n%10;
        n/=10;
        ans+=x*tmp;
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