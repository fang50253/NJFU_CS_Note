#include<stdio.h>
#include<unordered_set>
using namespace std;
const int N=1e6+10;
typedef long long ll;
ll arr[N],ans[N];
ll f(ll x,ll y)
{
    return y==1?x:(x/arr[y]+f(x%arr[y],y-1));
}
int main()
{
    int n,q;
    scanf(" %d %d",&n,&q);
    unordered_set<ll>s;
    for(int i=1;i<=n;i++)
    {
        scanf(" %d",&arr[i]);
        s.insert(arr[i]);
    }
    for(int i=1;i<=arr[n];++i)
    {
        ++ans[f(i,n)];
    }
    for(int i=2;i<=arr[n];++i) ans[i]+=ans[i-1];
    while(q--)
    {
        int x;
        scanf(" %d",&x);
        printf("%lld ",ans[x]);
    }
    return 0;
}