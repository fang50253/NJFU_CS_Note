#include<stdio.h>
#include<iostream>
using namespace std;
typedef unsigned long long LL;
const LL maxnum=1e3;
LL gcd(LL a,LL b)
{
    return b?gcd(b,a%b):a;
}
LL lcm(LL a,LL b)
{
    return a/gcd(a,b)*b;
}
LL C(LL a)
{
    LL sum=1;
    for(LL i=a;i>=a-1;--i) sum*=i;
    return sum/2;
}
bool check(LL a,LL b,LL x,LL y)
{
    LL g=gcd(a,b);
    if(a/g==x&&b/g==y) return 1;
    else return 0;
}
int main()
{
    for(LL a=1;a<=maxnum;++a)
    {
        for(LL b=1;b<=maxnum;++b)
        {
            for(LL c=1;c<=maxnum;++c)
            {
                if(check(a*b,C(a+b+c),517,2091))
                    if(check(b*c,C(a+b+c),2632,10455))
                        if(check(a*c,C(a+b+c),308,2091))
                            printf("%lld %lld %lld,sum=%lld\n",a,b,c,a+b+c);

            }
        }
        if(a%20==0) printf("checked:%lld\n",a);
    }
    return 0;
}