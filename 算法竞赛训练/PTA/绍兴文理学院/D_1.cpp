//1.先手肯定拿最小的
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll arr[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&arr[i]);
    int t=1;//拿的指针
    //i是轮数
    ll a=0,b=0;
    sort(arr+1,arr+n+1);
    for(int i=1;t<=n;i++)
    {
        for(int j=1;j<=i&&t<=n;++j) a+=arr[t++];
        for(int j=1;j<=i&&t<=n;++j) b+=arr[t++];
    }
    printf("%lld %lld\n",a,b);
    return 0;
}