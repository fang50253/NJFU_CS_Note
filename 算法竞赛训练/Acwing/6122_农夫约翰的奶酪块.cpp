#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int xy[N][N],xz[N][N],yz[N][N],n,q,ans;
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            xy[i][j]=xz[i][j]=yz[i][j]=n;
    while(q--)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        --xy[a][b];
        --yz[b][c];
        --xz[a][c];
        if(xy[a][b]==0) ++ans;
        if(xz[a][c]==0) ++ans;
        if(yz[b][c]==0) ++ans;
        printf("%d\n",ans);
    }
    return 0;
}