#include <iostream>
#include <string>
using namespace std;

// 检查数字是否包含7
bool containsSeven(long long n) {
    while (n > 0) {
        if (n % 10 == 7) return true;
        n /= 10;
    }
    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        if (containsSeven(n)) {
            cout << 0 << endl;
            continue;
        }
        int operations = 0;
        while (true) {
            operations++;
            // 构造一个只由9组成的数
            long long add = 9;
            while (true) {
                if (containsSeven(n + add)) {
                    n += add;
                    break;
                }
                add = add * 10 + 9; // 下一个只由9组成的数（如9 -> 99 -> 999）
            }
            if (containsSeven(n)) {
                cout << operations << endl;
                break;
            }
        }
    }
    return 0;
}