#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> b(n);
    for (int i = 0; i < n; ++i) cin >> b[i];

    long long pref = 0;
    for (int i = 0; i < n; ++i) {
        long long diff = b[i] - pref;
        if (diff > pref) {
            cout << "NO\n";
            return;
        }
        pref = max(pref, b[i]);
    }

    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}