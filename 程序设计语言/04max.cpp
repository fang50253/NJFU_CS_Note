#include<stdio.h>
int max(int a,int b)
{
    return a>b?a:b;
}
int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d",max(a,b));
    return 0;
}