#include<stdio.h>
#include<string.h>
using namespace std;
const int N=2e5+10;
int cnt[N];
void fun()
{
    memset(cnt,0,sizeof cnt);
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++cnt[x];
    }
    for(int i=1;i<=2e5;++i)
    {
        if(cnt[i]>=i) ans+=(cnt[i]/i)*i;
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