#include<stdio.h>
#include<string.h>
using namespace std;
const int N=60;
int n,m,a[N][N],b[N][N];
bool check(int x,int y)
{
    for(int i=x;i<x+m;++i)
    {
        for(int j=y;j<y+m;++j)
        {
            if(a[i][j]!=b[i-x+1][j-y+1])
            {
                //printf("break:%d %d\n",i,j);
                return 0;
            }
        }
    }
    return 1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            char x;
            scanf(" %c",&x);
            if(x=='.') a[i][j]=1;
            else a[i][j]=2;
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=m;++j)
        {
            char x;
            scanf(" %c",&x);
            if(x=='.') b[i][j]=1;
            else b[i][j]=2;
        }
    }
    /*
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=m;++j)
        {
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    */
    for(int i=1;i+m<=n+1;++i)
    {
        for(int j=1;j+m<=n+1;++j)
        {
            //printf("ckeck:%d %d\n",i,j);
            if(check(i,j))
            {
                printf("%d %d\n",i,j);
                return 0;
            }
        }
    }
    return 0;
}