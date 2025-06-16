#include <stdio.h>
#include <math.h>
#include <map>
using namespace std;

// 分解质因数
void factorize(int n, map<int, int>& m) {
    for (int i = 2; i*i <= n; ++i) {
        while (n % i == 0) {
            m[i]++;
            n /= i;
        }
    }
    if (n > 1) m[n]++;
}

bool can_convert(int x, int y, int k, int* op_count) {
    if (x == y) {
        *op_count = 0;
        return true;
    }

    map<int, int> yf, xf, kf;
    factorize(y, yf);
    factorize(x, xf);
    factorize(k, kf);

    int cnt = 0;

    for (auto& p : yf) {
        int prime = p.first;
        int y_cnt = p.second;
        int x_cnt = xf[prime];
        int k_cnt = kf[prime];

        int need = y_cnt - x_cnt;
        if (need < 0) {
            // 说明需要除
            if (kf[prime] == 0) return false; // k 不包含这个质因数，不能除
            cnt += -need;
        } else {
            // 需要乘
            if (kf[prime] == 0 && x_cnt == 0) return false;
            cnt += need;
        }
    }

    *op_count = cnt;
    return true;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        int ops;
        if (can_convert(x, y, k, &ops))
            printf("%d\n", ops);
        else
            printf("-1\n");
    }
    return 0;
}