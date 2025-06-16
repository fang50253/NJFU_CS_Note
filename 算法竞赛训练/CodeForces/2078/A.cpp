#include<stdio.h>
void fun()
{
    int n,x,sum=0;
    scanf("%d%d",&n,&x);
    for(int i=1;i<=n;++i) {int a;scanf("%d",&a);sum+=a;}
    if(sum==n*x) printf("YES\n");
    else printf("NO\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}