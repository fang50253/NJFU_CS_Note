#include<stdio.h>
const int N=1e7+10,M=1e8+10;
int prime[N],n,m,idx=1;
bool st[M];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;++i)
    {
        if(!st[i]) prime[idx++]=i;
        for(int j=1;j<idx&&prime[j]<=n/i;++j)
        {
            st[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
    while(m--)
    {
        int x;
        scanf("%d",&x);
        printf("%d\n",prime[x]);
    }
    return 0;
}