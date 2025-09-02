#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;
using int64 = long long;
using i128 = __int128_t;

void solve() {
    long long n;
    cin >> n;
    vector<long long> ans;

    i128 N = n;
    i128 pow10 = 10;
    for (int k = 1; k <= 18; ++k) {  // 10^18 最大，k<=18
        i128 d = pow10 + 1;         // 10^k + 1
        if (N % d == 0) {
            i128 x = N / d;
            if (x <= LLONG_MAX) ans.push_back((long long)x);
        }
        pow10 *= 10;
    }

    if (ans.empty()) {
        cout << 0 << "\n";
    } else {
        cout << ans.size() << "\n";
        sort(ans.begin(), ans.end());
        for (auto x : ans) cout << x << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}