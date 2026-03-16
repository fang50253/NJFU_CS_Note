#include <bits/stdc++.h>
using namespace std;

int xa, ya, xb, yb;

int iabs(int x) {
    return x >= 0 ? x : -x;
}

// 你的“解法函数”，返回是否有解，并通过 x_out 给出 x
bool solve(long double &x_out) {
    if (xa == xb) {
        if (ya == yb) return false;
        x_out = xa + 4.0 / iabs(ya - yb);
        return true;
    }
    else if (ya == yb) {
        if (iabs(xa - xb) * iabs(ya) == 4) {
            x_out = 0;
            return true;
        }
        else return false;
    }
    long double k=1.0*(yb-ya)/(xb-xa);
    long double x0=(k*xa-ya)/k;
    long double py=4.0/iabs(ya-yb);
    x_out = py + x0;
    return true;
}

long double area2(long double x1, long double y1,
                  long double x2, long double y2,
                  long double x3, long double y3) {
    // 计算三边长度
    long double a = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    long double b = sqrt((x3 - x2)*(x3 - x2) + (y3 - y2)*(y3 - y2));
    long double c = sqrt((x1 - x3)*(x1 - x3) + (y1 - y3)*(y1 - y3));

    // 海伦公式
    long double s = (a + b + c) / 2.0;
    long double area = sqrt(std::max((long double)0.0, s * (s - a) * (s - b) * (s - c)));

    return area;
}

int main() {
    srand(time(0));

    for (int t = 1; t >= -10000000; t++) {
        // 随机生成整数点（范围可自行调）
        xa = rand() % 20001 - 10000;
        ya = rand() % 20001 - 10000;
        xb = rand() % 20001 - 10000;
        yb = rand() % 20001 - 10000;

        long double x;
        bool ok = solve(x);

        if (!ok) continue; // 无解就跳过（题目允许）

        long double S2 = area2(x, 0, xa, ya, xb, yb);

        if (fabs(S2 - 2) > 1e-3) {
            cout << "❌ WRONG ANSWER FOUND\n";
            cout << "A = (" << xa << ", " << ya << ")\n";
            cout << "B = (" << xb << ", " << yb << ")\n";
            cout << "X = (" << x << ", 0)\n";
            cout << "2 * Area = " << S2 << "\n";
            return 0;
        }
        else printf("pass,area=%lf\n",S2);
    }

    cout << "✅ No mismatch found after massive testing\n";
    return 0;
}