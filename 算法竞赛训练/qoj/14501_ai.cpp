#include<stdio.h>
#include<math.h>
#include<functional>
#include<iostream>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> a(n);
        ll total = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            total += a[i];
        }

        sort(a.rbegin(), a.rend()); // 降序
        vector<ll> pref(n+1, 0);
        for (int i = 1; i <= n; ++i) pref[i] = pref[i-1] + a[i-1];

        ll lo = 0, hi = total, ans = total;
        while (lo <= hi) {
            ll mid = (lo + hi) / 2; // 尝试抽 mid 次
            // 找最小 t 使 pref[t] >= mid
            int t = int(lower_bound(pref.begin(), pref.end(), mid) - pref.begin()); // t in [0..n]
            // 可用的多余扭蛋数（duplicates，不牺牲已有不同种类）
            ll spare = mid - t;
            ll vouchers = (spare >= 0 && k > 0) ? (spare / k) : 0;
            if (vouchers >= (ll)(n - t)) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        cout << ans << '\n';
    }
    return 0;
}