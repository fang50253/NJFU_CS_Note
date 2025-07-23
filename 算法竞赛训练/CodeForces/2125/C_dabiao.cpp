#include <iostream>
#include <vector>

using namespace std;

const int N = 100; // 修改这里的 N 以调整打表上限

bool is_good(int x) {
    for (int i = 2; i * i <= x; ++i) {
        while (x % i == 0) {
            if (i < 10) return false; // 出现小质因子
            x /= i;
        }
    }
    if (x > 1 && x < 10) return false; // 最后剩下的一个质因子也不能是小的
    return true;
}

int main() {
    int cnt = 0;
    for (int i = 1; i <= N; ++i) {
        if (is_good(i))
        {
            ++cnt;
            cout<<i<<endl;
        }
        cout << i << ": " << cnt << endl; // 输出当前前缀 [1, i] 有多少个好整数
        //if(i==10||i==100||i==1000||i==10000||i==100000) cout << i << ": " << cnt << endl;
    }
    return 0;
}