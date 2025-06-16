#include<stdio.h>
#include<string.h>
const int N=810;
int g[N][N],p[N*2];
bool t[N*2];
void fun()
{
    int n;
    scanf("%d",&n);
    memset(g,0,sizeof g);
    memset(t,0,sizeof t);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&g[i][j]);
            p[i+j]=g[i][j];
            t[g[i][j]]=1;
        }
    }
    for(int i=1;i<=2*n;++i)
    {
        if(t[i]==0)
        {
            p[1]=i;
        }
    }
    for(int i=1;i<=2*n;++i) printf("%d ",p[i]);
    printf("\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}