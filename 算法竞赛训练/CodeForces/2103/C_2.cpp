#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);

        for (int i = 0; i < n; ++i) cin >> a[i];

        bool found = false;
        // 如果数组中没有任何一个值 ≤ k，肯定不行
        // 如果只有一个值 ≤ k，也不行，因为至少要两个相邻或中间有一个 ≤ k
        for (int i = 0; i < n; ++i) {
            if (a[i] <= k) {
                // 看看当前位置和之后的两位内是否有另一个 ≤ k 的数
                if ((i + 1 < n && a[i + 1] <= k) ||
                    (i + 2 < n && a[i + 2] <= k)) {
                    found = true;
                    break;
                }
            }
        }

        // 如果只有3个元素，特判
        if (n == 3) {
            vector<int> temp = a;
            sort(temp.begin(), temp.end());
            found = (temp[1] <= k);
        }

        cout << (found ? "YES" : "NO") << '\n';
    }

    return 0;
}