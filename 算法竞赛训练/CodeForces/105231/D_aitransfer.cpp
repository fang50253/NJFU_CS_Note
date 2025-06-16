#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e6 + 10;
const int MOD = 998244353;
int arr[N], n, prime[N], cnt;
bool st[N];

void getprimes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) {
            prime[cnt++] = i;
            for (int j = i + i; j <= n; j += i)
                st[j] = 1;
        }
    }
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int qmi(int m, int k, int p) {
    int res = 1 % p, t = m;
    while (k) {
        if (k & 1) res = 1LL * res * t % p;
        t = 1LL * t * t % p;
        k >>= 1;
    }
    return res;
}

int main() {
    scanf("%d", &n);
    getprimes(1e6);
    for (int i = 1; i <= n; ++i) scanf("%d", &arr[i]);

    // 每个质因子对应的指数列表
    vector<vector<int>> vec(N);

    for (int i = 1; i <= n; ++i) {
        int x = arr[i];
        for (int j = 0; prime[j] * prime[j] <= x; ++j) {
            int p = prime[j];
            if (x % p == 0) {
                int s = 0;
                while (x % p == 0) {
                    x /= p;
                    s++;
                }
                vec[p].push_back(s);
            }
        }
        if (x > 1) {
            vec[x].push_back(1);  // x 是一个大质因子
        }
    }

    int ans = 0;
    for (int i = 1; i < N; ++i) {
        sort(vec[i].begin(), vec[i].end(), greater<int>());
        int res = 0;
        for (int j = 0; j < vec[i].size(); ++j) {
            res = (res + 1LL * vec[i][j] * qmi(i, j, MOD)) % MOD;
        }
        ans = (ans + res) % MOD;
    }

    printf("%d\n", ans);
    return 0;
}