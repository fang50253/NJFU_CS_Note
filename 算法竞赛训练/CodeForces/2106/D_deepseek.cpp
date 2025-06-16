#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(m);
        for (int &x : a) cin >> x;
        for (int &x : b) cin >> x;

        vector<int> pre(m + 1, -1);
        pre[0] = -1;
        int j = 0;
        for (int i = 0; i < n && j < m; ++i) {
            if (a[i] >= b[j]) {
                pre[j + 1] = i;
                j++;
            }
        }
        if (pre[m] != -1) {
            cout << "0\n";
            continue;
        }

        vector<int> suf(m + 1, n);
        j = 0;
        for (int i = n - 1; i >= 0 && j < m; --i) {
            if (a[i] >= b[m - j - 1]) {
                suf[j + 1] = i;
                j++;
            }
        }

        int min_k = INT_MAX;
        for (int x = 1; x <= m; ++x) {
            // Check left
            int pos_left;
            bool left_ok;
            if (x - 1 == 0) {
                left_ok = true;
                pos_left = -1;
            } else {
                if (pre[x - 1] == -1) {
                    left_ok = false;
                } else {
                    left_ok = true;
                    pos_left = pre[x - 1];
                }
            }
            if (!left_ok) continue;

            // Check right
            int need_right = m - x;
            int pos_right;
            bool right_ok;
            if (need_right == 0) {
                right_ok = true;
                pos_right = n;
            } else {
                if (suf[need_right] == -1) {
                    right_ok = false;
                } else {
                    right_ok = true;
                    pos_right = suf[need_right];
                }
            }
            if (!right_ok) continue;

            if (pos_left < pos_right) {
                min_k = min(min_k, b[x - 1]);
            }
        }

        if (min_k != INT_MAX) {
            cout << min_k << "\n";
        } else {
            cout << "-1\n";
        }
    }
    return 0;
}