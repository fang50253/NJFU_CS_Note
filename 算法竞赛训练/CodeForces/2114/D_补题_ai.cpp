#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
    int t;
    scanf("%d",&t);
    while (t--) 
    {
        int n;
        cin >> n;
        vector<pair<int, int>> l, t;
        for (int i = 0; i < n; i++)
        {
            int a, b;
            cin >> a >> b;
            l.push_back({a, i});
            t.push_back({b, i});
        }
        sort(l.begin(), l.end());
        sort(t.begin(), t.end());
        long long p = 1e18;
        for (int i = 0; i < n; i++) {
            int a, b, x, y;
            if (l[0].second == i && n > 1) a = l[1].first;
            else a = l[0].first;
            if (t[0].second == i && n > 1) b = t[1].first;
            else b = t[0].first;
            if (l[n - 1].second == i && n > 1) x = l[n - 2].first;
            else x = l[n - 1].first;
            if (t[n - 1].second == i && n > 1) y = t[n - 2].first;
            else y = t[n - 1].first;
            int d = x - a + 1;
            int f = y - b + 1;
            long long s = 1LL * d * f;
            if (s < n) s += min(d, f);
            p = min(p, s);
        }
        cout << p << '\n';
    }
    return 0;
}