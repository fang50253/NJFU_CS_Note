#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;
ll n,m,arr[N];
ll t1[N],t2[N];
int INF=0x3f3f3f3f;
//t1表示奇数位是奇数，t2反之
int min(int a,int b)
{
    return a>b?b:a;
}
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i]);
        if(arr[i]%2==i%2) ++t2[i];
        if(arr[i]%2!=i%2) ++t1[i];
    }
    for(int i=1;i<=n;++i)
    {
        t1[i]+=t1[i-1];
        t2[i]+=t2[i-1];
    }
    int ans=INF;
    for(int i=0;i+m<=n;++i)
    {
        ans=min(ans,t1[i+m]-t1[i]);
        ans=min(ans,t2[i+m]-t2[i]);
    }
    printf("%d\n",ans);
    return 0;
    
}