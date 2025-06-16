#include <stdio.h>
#include <stack>
#include <algorithm>
using namespace std;

const int N = 2e5 + 10;
int ori[N], l[N], h[N], n;
int dpl[N], dph[N], t[N];

void fun() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &ori[i]);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &l[i], &h[i]);

    dpl[0] = dph[0] = 0;
    for (int i = 1; i <= n; ++i) {
        if (ori[i] == 0) {
            dpl[i] = dpl[i - 1];
            dph[i] = dph[i - 1];
        } else if (ori[i] == 1) {
            dpl[i] = dpl[i - 1] + 1;
            dph[i] = dph[i - 1] + 1;
        } else if (ori[i] == -1) {
            dpl[i] = dpl[i - 1];
            dph[i] = dph[i - 1] + 1;
        }
        if (dph[i] < l[i] || dpl[i] > h[i]) {
            printf("-1\n");
            return;
        }
        dpl[i] = max(dpl[i], l[i]);
        dph[i] = min(dph[i], h[i]);
    }

    // 回溯构造 h 序列
    int hnow = dpl[n]; // 以最小合法高度为起点
    t[n] = hnow;
    for (int i = n; i >= 1; --i) {
        if (ori[i] == 1) {
            t[i - 1] = hnow - 1;
            hnow--;
        } else if (ori[i] == 0) {
            t[i - 1] = hnow;
        } else { // ori[i] == -1
            if (hnow - 1 >= dpl[i - 1]) {
                t[i - 1] = hnow - 1;
                hnow--;
            } else {
                t[i - 1] = hnow;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d ", t[i] - t[i - 1]);
    }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) fun();
    return 0;
}