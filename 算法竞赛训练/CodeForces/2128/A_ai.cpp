#include <iostream>
#include <algorithm>
using namespace std;

const int N = 35;
int a[N];

void solve() {
    int n, c;
    cin >> n >> c;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n); // 从小到大

    int ans = n; // 最坏情况，全部都要花钱
    for (int x = 0; x <= n; ++x) {
        // 枚举最后花金币销毁 x 个垃圾袋
        bool ok = true;
        long long weight = 0;
        for (int i = 0; i < n - x; ++i) {
            // 要免费销毁这些重量，销毁前要 ≤ c
            if (a[i] > c) {
                ok = false;
                break;
            }
            if (weight > c) { // 销毁前所有袋子重量已超过 c，无法免费销毁
                ok = false;
                break;
            }
            weight = max(weight, 1LL * a[i]) * 2;
        }
        if (ok) {
            ans = x; // 最小金币数量
            break;
        }
    }

    cout << ans << '\n';
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}