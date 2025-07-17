#include<stdio.h>
using namespace std;
typedef long long ll;
ll mp[1010][1010];
ll muti(ll x)
{
    ll ans=1;
    while(x)
    {
        ans*=x%10;
        x/=10;
    }
    return ans;
}
int main()
{
    ll n;
    scanf("%lld",&n);
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=n;++j)
        {
            ++mp[muti(i)][muti(j)];
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            printf("%lld ",mp[i][j]);
        }
        printf("\n");
    }
    return 0;
}