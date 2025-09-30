#include<stdio.h>
using namespace std;
const int N=2e5+10;
int req[N][2];
void fun()
{
    int n,m,nst=0,ans=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&req[i][0],&req[i][1]);
    }
    for(int i=1;i<=n;++i)
    {
        if(nst==req[i][1]) ans+=req[i][0]-req[i-1][0]-(req[i][0]-req[i-1][0])%2;
        else ans+=req[i][0]-req[i-1][0]-(req[i][0]-req[i-1][0]+1)%2;
        nst=req[i][1];
    }
    ans+=m-req[n][0];
    printf("%d\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}