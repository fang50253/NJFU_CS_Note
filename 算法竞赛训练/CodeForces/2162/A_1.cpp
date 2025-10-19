#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;
const int N=2e5+10;
void fun()
{
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ans=max(ans,x);
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