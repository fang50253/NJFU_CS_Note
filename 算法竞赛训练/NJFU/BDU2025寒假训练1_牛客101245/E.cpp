#include<stdio.h>
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int main()
{
    int a,b,c;
    int gcdab=gcd(a,b);
    int gcdabc=gcd(gcdab,c);
    if(c%gcdab==0)
    {
        printf("no\n");
        return 0;
    }
    a/=gcdabc;
    b/=gcdabc;
    c/=gcdabc;
    
    return 0;
}