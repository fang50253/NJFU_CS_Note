#include<stdio.h>
#include<math.h>
#include<algorithm>
const int N=20;
int a[N],b[N],n;
int max(int a,int b)
{
    return a>b?a:b;
}
void fun()
{
    int ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i) scanf("%d",&b[i]);
    for(int i=1;i<=n;++i) ans+=max(a[i]-b[i],0);
    printf("%d\n",ans+1);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}