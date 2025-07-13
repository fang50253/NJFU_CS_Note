#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll arr[N],n,m,t[N];
ll first0,back0,maxt;
//上面均包含本数字
ll max(ll a,ll b)
{
    return a>b?a:b;
}
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i]);
        if(arr[i]==0&&first0==0) first0=i;
        if(arr[i]==0) back0=i;
    }
    for(int i=back0-1;;i=(i+1)%n)
    {
        ++i;
        if(arr[i]-t[(i-1+n)%(n+1)]>1)
        {
            printf("%d\n",i);
            printf("0\n");
            return 0;
        }
        t[i]=max(t[(i+n-1)%(n+1)],arr[i]);
        if(arr[i]==m-1)
        {
            //printf("%d %d\n",first0,i);
            if(back0-max(first0,i+1)+1>0) printf("%lld\n",back0-max(first0,i+1)+1);
            else printf("%lld\n",back0);
            return 0;
        }
        --i;
    }
    
    return 0;
}