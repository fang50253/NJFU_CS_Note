#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
ll arr[N],n;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    sort(arr+1,arr+1+n,greater<int>());
    ll sum=0;
    for(int i=1;i<=n;i+=2) sum+=arr[i];
    printf("%lld ",sum);
    sum=0;
    for(int i=2;i<=n;i+=2) sum+=arr[i];
    printf("%lld\n",sum);
    return 0;
}