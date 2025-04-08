#include<stdio.h>
int main()
{
    int x;
    scanf("%d",&x);
    for(int i=2;i<x;++i)
    {
        if(x%i==0)
        {
            printf("%d是一个合数",x);
            return 0;
        }
    }
    printf("%d是一个质数",x);
    return 0;
}