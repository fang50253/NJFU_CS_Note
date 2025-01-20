#include<stdio.h>
int factorial(int x)
{
    if(x==1) return 1;
    return x*factorial(x-1);
}
int main()
{
    int x;
    scanf("%d",&x);
    printf("factorial(%d)==%d",x,factorial(x));
    return 0;
}