#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
const int N=110;
const int INF=0x3f3f3f3f;
int a[N],ans[N];
void fun()
{
    int n,maxn=0,minn=INF;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        maxn=max(maxn,a[i]);
        minn=min(minn,a[i]);
    }
    for(int i=1;i<=n;++i) ans[i]=1;
    for(int i=1;i<=n;++i)
    {
        if(maxn==a[i])
        {
            ans[i]=2;
            break;
        }
    }
    if(maxn==minn)
    {
        printf("No\n");
        return;
    }
    else
    {
        printf("Yes\n");
        for(int i=1;i<=n;++i) printf("%d ",ans[i]);
        printf("\n");
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}