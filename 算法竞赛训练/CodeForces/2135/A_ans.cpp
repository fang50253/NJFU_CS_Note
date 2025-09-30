#include <iostream>
#include <deque>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        for (int i = 0; i < n; i++)
            cin >> a[i];

        deque<int> q[n + 1];
        int dp[n + 1];
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            int x = a[i];
            q[x].push_back(i);
            if ((int)q[a[i]].size() == a[i]) {
                dp[i + 1] = max(dp[i], a[i] + dp[q[a[i]].front()]);
                q[a[i]].pop_front();
            } else {
                dp[i + 1] = dp[i];
            }
        }
        cout << dp[n] << endl;
    }
    return 0;
}