#include<stdio.h>
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int lcm(int a,int b)
{
    return a/gcd(a,b)*b;
}
int main()
{
    int x,y;
    scanf("%d%d",&x,&y);
    if(gcd(x,y)!=x||lcm(x,y)!=y) {printf("0\n");return 0;}
    int k=y/x,ans=0;
    for(int i=2;i<=k/i;++i)
    {
        if(k%i!=0) continue;
        int g=gcd(x*i,y/i);
        int l=lcm(x*i,y/i);
        if(g==x&&l==y) ++ans;
    }
    printf("%d\n",2*ans+2);
    return 0;
}