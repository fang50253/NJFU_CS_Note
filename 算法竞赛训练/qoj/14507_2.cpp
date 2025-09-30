#include<stdio.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll dp[N];
bool isprime(ll x)
{
    for(ll i=2;i<=x/i;++i)
    {
        if(x%i==0) return 0;
    }
    return 1;
}
void fun()
{
    ll x;
    scanf("%lld",&x);
    if(x%3==0) printf("%lld\n",x/3);
    else if(x<=2) printf("-1\n");
    else if(x==7) printf("1\n");
    else if(x%3==1&&x>=10) printf("%lld\n",(x-4)/3);
    else if(x%3==2) printf("%lld\n",x/3);
    else printf("-1\n");
}
int main()
{

    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}