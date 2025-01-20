#include<stdio.h>
bool prime(int x)
{
    for(int i=2;i<x;++i)
    {
        if(x%i==0) return 0;
    }
    return 1;
}
int main()
{
    int x;
    scanf("%d",&x);
    if(prime(x)) printf("%d是一个质数",x);
    else printf("%d是一个合数",x);
    return 0;
}