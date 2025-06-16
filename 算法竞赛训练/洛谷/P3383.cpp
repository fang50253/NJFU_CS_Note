#include<stdio.h>
#define int long long
const int N=1e6+10,M=1e8+10;
int prime[N],n,cnt;
bool st[M];
signed main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;++i)
    {
        if(!st[i])
        {
            prime[++cnt]=i;
            
        }
        for(int j=1;j<=cnt&&prime[j]<=n/i;++j)
            {
                st[i*prime[j]]=1;
                if(i%prime[j]==0) break;
            } 
    }
    int m;
    scanf("%d",&m);
    while(m--)
    {
        int x;
        scanf("%lld",&x);
        printf("%lld\n",prime[x]);
    }
    return 0;
}