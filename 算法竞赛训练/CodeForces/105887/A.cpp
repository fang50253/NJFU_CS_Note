#include<stdio.h>
void fun()
{
    int n,ans;
    scanf("%d%d",&n,&ans);
    for(int i=1;i<n;++i)
    {
        int x;
        scanf("%d",&x);
        ans^=x;
    }
    printf("%d\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}