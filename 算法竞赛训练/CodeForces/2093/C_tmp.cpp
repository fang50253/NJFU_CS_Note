#include<stdio.h>
#define int long long
bool checkprime(int x)
{
    for(int i=2;i<=x/i;++i)
    {
        if(x%i==0) return 0;
    }
    return 1;
}
int pow(int n,int x)
{
    int ans=1;
    for(int i=1;i<=x;++i) ans*=n;
    return ans;
}
void out_gcd(int x)
{
    for(int i=2;i<=x/i;++i)
    {
        if(x%i==0) printf("%d\n",i);
    }
}
signed main()
{
    int t=1;
    out_gcd(11111);
    for(int i=1;i<=6;++i)
    {
        t=t*100+1;
        if(checkprime(t)) 
        printf("%lld is a prime\n",t);
    }
    return 0;
}