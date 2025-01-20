#include<stdio.h>
int main()
{
    int x,ans=1;
    scanf("%d",&x);
    for(int i=1;i<=x;++i) ans*=i;
    printf("%d",ans);
    return 0;
}