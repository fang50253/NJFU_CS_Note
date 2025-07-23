#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<utility>
#include<unordered_map>
#include<queue>
#include<stack>
#include<cstdlib>
#include<string.h>
#include<stdlib.h>
#include<unordered_set>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        // 统计每个字符出现次数
        int cnt[26] = {0};
        for (char c : s) {
            cnt[c - 'A']++;
        }

        string res;

        // 优先处理 FFT -> FTF
        while (cnt['F' - 'A'] >= 2 && cnt['T' - 'A'] >= 1) {
            res += "FTF";
            cnt['F' - 'A'] -= 2;
            cnt['T' - 'A'] -= 1;
        }

        // 然后处理 NTT -> TNT
        while (cnt['N' - 'A'] >= 1 && cnt['T' - 'A'] >= 2) {
            res += "TNT";
            cnt['N' - 'A'] -= 1;
            cnt['T' - 'A'] -= 2;
        }

        // 把剩余的字符按顺序拼上去（安全）
        for (int i = 0; i < 26; ++i) {
            res += string(cnt[i], 'A' + i);
        }

        cout << res << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}