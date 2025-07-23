#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<utility>
#include<unordered_map>
#include<queue>
#include<stack>
#include<cstdlib>
#include<string.h>
#include<stdlib.h>
#include<unordered_set>
#define PII pair<int,int>
using namespace std;
using namespace std;

#define MOD 998244353
typedef long long ll;

const int N = 200010;

int n, m;

// 快速幂（用于求逆元）
ll qpow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 每个结点存两个值：p0 和 p1（分别表示被覆盖0次和1次的概率）
struct Node {
    ll p0, p1;
    ll lazy_a, lazy_b, lazy_c, lazy_d; // 表示一个变换矩阵：[a b; c d]
} tr[N << 2];

void pushup(int u) {
    tr[u].p0 = (tr[u << 1].p0 + tr[u << 1 | 1].p0) % MOD;
    tr[u].p1 = (tr[u << 1].p1 + tr[u << 1 | 1].p1) % MOD;
}

void apply(int u, ll a, ll b, ll c, ll d) {
    ll p0 = tr[u].p0, p1 = tr[u].p1;
    tr[u].p0 = (a * p0 + b * p1) % MOD;
    tr[u].p1 = (c * p0 + d * p1) % MOD;

    ll la = tr[u].lazy_a, lb = tr[u].lazy_b, lc = tr[u].lazy_c, ld = tr[u].lazy_d;
    tr[u].lazy_a = (a * la + b * lc) % MOD;
    tr[u].lazy_b = (a * lb + b * ld) % MOD;
    tr[u].lazy_c = (c * la + d * lc) % MOD;
    tr[u].lazy_d = (c * lb + d * ld) % MOD;
}

void pushdown(int u) {
    apply(u << 1, tr[u].lazy_a, tr[u].lazy_b, tr[u].lazy_c, tr[u].lazy_d);
    apply(u << 1 | 1, tr[u].lazy_a, tr[u].lazy_b, tr[u].lazy_c, tr[u].lazy_d);

    tr[u].lazy_a = 1;
    tr[u].lazy_b = 0;
    tr[u].lazy_c = 0;
    tr[u].lazy_d = 1;
}

void build(int u, int l, int r) {
    tr[u].lazy_a = tr[u].lazy_d = 1;
    tr[u].lazy_b = tr[u].lazy_c = 0;

    if (l == r) {
        tr[u].p0 = 1;
        tr[u].p1 = 0;
        return;
    }

    int mid = (l + r) / 2;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

// 矩阵形式更新区间
void update(int u, int l, int r, int L, int R, ll a, ll b, ll c, ll d) {
    if (L <= l && r <= R) {
        apply(u, a, b, c, d);
        return;
    }
    pushdown(u);
    int mid = (l + r) / 2;
    if (L <= mid) update(u << 1, l, mid, L, R, a, b, c, d);
    if (R > mid) update(u << 1 | 1, mid + 1, r, L, R, a, b, c, d);
    pushup(u);
}

ll query(int u, int l, int r, int pos) {
    if (l == r) return tr[u].p1;
    pushdown(u);
    int mid = (l + r) / 2;
    if (pos <= mid) return query(u << 1, l, mid, pos);
    else return query(u << 1 | 1, mid + 1, r, pos);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    build(1, 1, m);

    for (int i = 1; i <= n; ++i) {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        ll prob = p * qpow(q, MOD - 2) % MOD;
        ll iprob = (1 - prob + MOD) % MOD;

        // 转移矩阵:
        // [p0'] = [ip  0 ] * [p0]
        // [p1']   [p  ip]   [p1]
        update(1, 1, m, l, r,
               iprob, 0,
               prob, iprob);
    }

    ll ans = 1;
    for (int i = 1; i <= m; ++i) {
        ans = ans * query(1, 1, m, i) % MOD;
    }

    cout << ans << "\n";
    return 0;
}