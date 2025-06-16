#include<stdio.h>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
#define int long long
static int get_size(int n)
{
    if(n<6) return 15;
    double dn=n;
    double bound=dn*(log(dn)+log(log(dn)));
    return (int)(bound+10);
}
const int M=4e5+10;
int ns[M];
vector<int> tests[M];

signed main()
{
    int t;
    if(scanf("%lld",&t)!=1) return 0;
    int max_n=0;
    for(int i=0;i<t;++i)
    {
        int n;
        scanf("%lld",&n);
        ns[i]=n;
        max_n=max(max_n,n);
        tests[i].resize(n);
        for(int j=0;j<n;++j) scanf("%lld",&tests[i][j]);
    }

    int sieve_size=get_size(max_n);
    vector<bool> is_prime(sieve_size+1,1);
    is_prime[0]=is_prime[1]=0;
    vector<int> primes;
    primes.reserve(max_n+1);

    for(int i=2;i<=sieve_size;++i)
    {
        if(is_prime[i])
        {
            primes.push_back(i);
            if((int)primes.size()>=max_n) break;
            if(i*i<=sieve_size)
            {
                for(int j=i*i;j<=sieve_size;j+=i) is_prime[j]=0;
            }
        }
    }

    int next_check=sieve_size+1;
    while((int)primes.size()<max_n)
    {
        bool ok=1;
        for(int p:primes)
        {
            if((int)p*p>next_check) break;
            if(next_check%p==0)
            {
                ok=0;
                break;
            }
        }
        if(ok) primes.push_back(next_check);
        next_check++;
    }

    vector<int> prime_sum(max_n+1,0);
    for(int i=1;i<=max_n;++i) prime_sum[i]=prime_sum[i-1]+primes[i-1];

    for(int ti=0;ti<t;++ti)
    {
        auto &a=tests[ti];
        int n=ns[ti];
        if(n==0)
        {
            printf("0\n");
            continue;
        }
        sort(a.begin(),a.end(),greater<int>());
        vector<int> asum(n+1,0);
        for(int i=1;i<=n;++i) asum[i]=asum[i-1]+a[i-1];
        int best_k=0;
        for(int k=1;k<=n;++k)
        {
            if(asum[k]>=prime_sum[k]) best_k=k;
        }
        printf("%lld\n",n-best_k);
    }
    return 0;
}