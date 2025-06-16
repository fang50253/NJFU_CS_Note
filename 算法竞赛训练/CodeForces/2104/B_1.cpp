#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<stack>
#include<string.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll arr[N],sum[N];
void fun()
{
    ll n;
    memset(sum,0,sizeof(sum));
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    for(int i=n;i>=1;--i) sum[i]=sum[i+1]+arr[i];
    ll ans=0,maxd=0;//maxd代表前i个数的最大值
    stack<ll>s;
    for(int i=1;i<=n;++i)
    {
        maxd=max(maxd,arr[i]);
        s.push(maxd+sum[i+1]);
    }
    while(s.size())
    {
        printf("%lld ",s.top());
        s.pop();
    }
    printf("\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}