#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        int count = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (a[i] <= k) {
                count++;
            }
        }
        if (count == 0) {
            cout << "NO\n";
            continue;
        }
        if (n == 3) {
            int m1 = a[0];
            int m2 = a[1];
            int m3 = a[2];
            int median_of_medians = max(min(m1, m2), min(max(m1, m2), m3));
            if (median_of_medians <= k) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            continue;
        }
        bool possible = false;
        for (int i = 0; i < n; ++i) {
            if (a[i] <= k) {
                if (i > 0 && a[i-1] <= k) {
                    possible = true;
                    break;
                }
                if (i < n-1 && a[i+1] <= k) {
                    possible = true;
                    break;
                }
            }
        }
        if (possible || count >= 2) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    solve();
    return 0;
}