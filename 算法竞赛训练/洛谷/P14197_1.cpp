#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
const int N=1e5+10;
int cnt[N];
void fun()
{
    int n,m,k,ans=-1;
    memset(cnt,0,sizeof cnt);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n*m;++i)
    {
        int x;
        scanf("%d",&x);
        if(ans!=-1) continue;
        ++cnt[(x+m-1)/m];
        if(cnt[(x+m-1)/m]+k>=m) ans=max(i,m);
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