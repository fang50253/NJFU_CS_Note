#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        int maxAlice = 0, maxBob = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'A') {
                maxAlice = max(maxAlice, i + 1); // 牌号是i+1
            } else {
                maxBob = max(maxBob, i + 1);
            }
        }

        if (maxAlice > maxBob) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }
    return 0;
}