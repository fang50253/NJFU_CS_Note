#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool is_increasing(const vector<int>& p, int l, int r) {
    for (int i = l; i < r; ++i)
        if (p[i] > p[i+1]) return false;
    return true;
}

bool is_decreasing(const vector<int>& p, int l, int r) {
    for (int i = l; i < r; ++i)
        if (p[i] < p[i+1]) return false;
    return true;
}

string solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i)
        cin >> p[i];
    
    string res;
    int l = 0, r = n - 1;
    
    while (l <= r) {
        if (is_increasing(p, l, r)) {
            res += 'R';
            r--;
        }
        else if (is_decreasing(p, l, r)) {
            res += 'L';
            l++;
        }
        else if (p[l] < p[r]) {
            res += 'L';
            l++;
        }
        else {
            res += 'R';
            r--;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        cout << solve() << '\n';
    return 0;
}