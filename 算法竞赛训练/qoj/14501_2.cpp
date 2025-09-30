#include<stdio.h>
#include<math.h>
#include<functional>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll arr[N];
ll min(ll a,ll b)
{
    return a>b?b:a;
}
ll min(ll a,ll b,ll c)
{
    ll ans=0x3f3f3f3f3f3f3f3f;
    ans=min(ans,a);
    ans=min(ans,b);
    ans=min(ans,c);
    return ans;
}
void fun()
{
    int n,k,sum=0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i]);
        sum+=arr[i];
    }
    sort(arr+1,arr+1+n,greater<ll>());
    ll ans1=sum;
    ll ans2=1+(n-1)*k;
    ll ans3=0;
    ll type=0;
    for(int i=1;i<=n;++i)
    {
        //假设把第i多多给删完了，获得arr[i]/k次随机选择的机会
        ans3+=min(arr[i],n*k-type*k);
        type+=1+min(arr[i],n*k-type*k)/k;
        arr[i+1]=min(arr[i],n*k-type*k)%k;
    }
    printf("%lld\n",min(ans1,ans2,ans3));
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}