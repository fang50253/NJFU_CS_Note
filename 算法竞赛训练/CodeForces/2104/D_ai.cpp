#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define int long long
using namespace std;

static long long get_size(int n)
{
    if (n < 6) return 15;
    double dn = n;
    double bound = dn * (log(dn) + log(log(dn)));
    return (long long)(bound + 10);
}

signed main()
{
    int t;
    if (!(cin >> t)) return 0;
    vector<int> ns(t);
    vector<vector<int>> tests(t);
    int max_n = 0;
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        ns[i] = n;
        max_n = max(max_n, n);
        tests[i].resize(n);
        for (int j = 0; j < n; j++)
        {
            cin >> tests[i][j];
        }
    }

    long long sieve_size = get_size(max_n);
    vector<bool> is_prime(sieve_size + 1, true);
    is_prime[0] = is_prime[1] = false;
    vector<int> primes;
    primes.reserve(max_n + 1);
    for (long long i = 2; i <= sieve_size; i++)
    {
        if (is_prime[i])
        {
            primes.push_back((int)i);
            if ((int)primes.size() >= max_n) break;
            if (i * i <= sieve_size)
            {
                for (long long j = i * i; j <= sieve_size; j += i)
                {
                    is_prime[j] = false;
                }
            }
        }
    }

    long long next_check = sieve_size + 1;
    while ((int)primes.size() < max_n)
    {
        bool ok = true;
        for (int p : primes)
        {
            if ((long long)p * p > next_check) break;
            if (next_check % p == 0)
            {
                ok = false;
                break;
            }
        }
        if (ok) primes.push_back((int)next_check);
        next_check++;
    }

    vector<long long> prime_sum(max_n + 1, 0);
    for (int i = 1; i <= max_n; i++)
    {
        prime_sum[i] = prime_sum[i - 1] + primes[i - 1];
    }

    for (int ti = 0; ti < t; ti++)
    {
        auto &a = tests[ti];
        int n = ns[ti];
        if (n == 0)
        {
            cout << 0 << "\n";
            continue;
        }
        sort(a.begin(), a.end(), greater<int>());
        vector<long long> asum(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            asum[i] = asum[i - 1] + a[i - 1];
        }
        int best_k = 0;
        for (int k = 1; k <= n; k++)
        {
            if (asum[k] >= prime_sum[k])
            {
                best_k = k;
            }
        }
        cout << (n - best_k) << "\n";
    }

    return 0;
}