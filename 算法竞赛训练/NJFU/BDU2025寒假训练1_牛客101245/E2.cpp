#include<stdio.h>
using namespace std;
typedef long long LL;
LL exgcd(LL a, LL b, LL &x, LL &y) 
{
    if(!b) 
    {
        x=1,y=0;
        return a;
    }
    LL x1,y1;
    LL g=exgcd(b,a%b,x1,y1);
    x=y1;
    y=(a/b)*y1;
    y=x1-y;
    return g;
}
int main() 
{
    LL a,b,c;
    scanf("%lld%lld%lld",&a,&b,&c);
    LL x,y;
    LL gcdab=exgcd(a,b,x,y);
    // 无解情况
    if (c%gcdab!=0) 
    {
        printf("no\n");
        return 0;
    }
    x*=c/gcdab;
    y*=c/gcdab;
    printf("%lld %lld\n", x, y);
    return 0;
}