#include<stdio.h>
using namespace std;
typedef long long LL;
bool isprime(LL x)
{
    if(x<2) return 0;
    for(LL i=2;i<=x/i;++i)
    {
        if(x%i==0) return 0;
    }
    return 1;
}
void fun()
{
    LL x,k;
    scanf("%lld%lld",&x,&k);
    if((isprime(x)&&k==1)||x==1&&k==2) printf("Yes\n");
    else printf("No\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}