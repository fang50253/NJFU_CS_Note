#include <iostream>
#include <vector>
#include <algorithm>

void solve() {
    int n, j, k;
    std::cin >> n >> j >> k;

    std::vector<int> a(n);
    for (int& x : a) {
        std::cin >> x;
    }

    // 判断是否满足条件
    bool result = (k > 1 || a[j - 1] == *std::max_element(a.begin(), a.end()));

    if (result) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}