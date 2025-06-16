#include<stdio.h>
#include<algorithm>
#define int long long
using namespace std;
const int N=6e7+10,M=4e5+10;
int primes[N],cnt,arr[M];
bool st[N];

void get_primes(int n)
{
    for(int i=2;i<=n;++i)
    {
        if(!st[i]) primes[cnt++]=i;
        for(int j=0;primes[j]<=n/i;++j)
        {
            st[primes[j]*i]=true;
            if(i%primes[j]==0) break;
        }
    }
}

void fun()
{
    int n,sum=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    sort(arr+1,arr+n+1,greater<int>());
    int i;
    for(i=1;i<=n;++i)
    {
        sum+=arr[i];
        if(sum<primes[i]) break;
    }
    printf("%lld\n",n-i+1);
}

signed main()
{
    int t;
    get_primes(6e7);
    for(int i=1;i<=cnt;++i) primes[i]=primes[i-1]+primes[i];
    scanf("%lld",&t);
    while(t--) fun();
    return 0;
}