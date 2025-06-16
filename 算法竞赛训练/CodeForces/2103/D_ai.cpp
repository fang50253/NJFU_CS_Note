#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int max_k = 0;
    for (int i = 0; i < n; ++i)
        if (a[i] != -1)
            max_k = max(max_k, a[i]);
    for (int i = 0; i < n; ++i)
        if (a[i] == -1)
            a[i] = max_k + 1;
    vector<vector<int>> groups(max_k + 2);
    for (int i = 0; i < n; ++i) groups[a[i]].push_back(i);
    vector<int> res(n);
    int low = 1, high = n;
    for (int k = 1; k <= max_k + 1; ++k) 
    {
        if (k % 2 == 1) 
        {
            for (int idx : groups[k]) res[idx] = high--;
        } else {
            for (int idx : groups[k]) res[idx] = low++;
        }
    }
    for (int i = 0; i < n; ++i) cout << res[i] << " ";
    cout << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}