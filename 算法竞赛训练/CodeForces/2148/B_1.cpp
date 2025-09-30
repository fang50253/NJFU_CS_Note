#include<stdio.h>
using namespace std;
const int N=2e5+10;
void fun()
{
    int n,m,x,y,ans=0;
    scanf("%d%d%d%d",&n,&m,&x,&y);
    for(int i=1;i<=n;++i)
    {
        int t;
        scanf("%d",&t);
        if(t<y) ++ans;
    }
    for(int i=1;i<=m;++i)
    {
        int t;
        scanf("%d",&t);
        if(t<x) ++ans;
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