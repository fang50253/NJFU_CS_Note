#include<stdio.h>
#include<math.h>
using namespace std;
typedef long long ll;
ll get_sum(ll x)
{
    ll ans=0;
    while(x)
    {
        ans+=x%10;
        x/=10;
    }
    return ans;
}
int main()
{
    ll x;
    scanf("%lld",&x);
    if((ll)sqrt(x)*(ll)sqrt(x)==(ll)x)
    {
        if((ll)sqrt(get_sum(x))*(ll)sqrt(get_sum(x))==(ll)get_sum(x))
        {
            printf("Yes\n");
            return 0;
        }
    }
    printf("No\n");
    return 0;
}