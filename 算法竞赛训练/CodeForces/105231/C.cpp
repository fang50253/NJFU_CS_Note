#include<stdio.h>
const int N=1e5+10;
typedef long long ll;
int arr[N];
int main()
{
    int n;
    ll s,sum=0;
    scanf("%d%lld",&n,&s);
    for(int i=1;i<=n;++i)
    {
        ll x;
        scanf("%lld",&x);
        sum+=x;
    }
    if(sum==s) printf("%d\n",n);
    else printf("%d\n",n-1);
    return 0;
}