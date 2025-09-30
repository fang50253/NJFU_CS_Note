#include <iostream>
#include <vector>
using namespace std;

// 矩阵链乘法动态规划
void matrixChainOrder(vector<int> &p, vector<vector<int>> &m, vector<vector<int>> &s) {
    int n = p.size() - 1; // 矩阵个数
    m.assign(n + 1, vector<int>(n + 1, 0));
    s.assign(n + 1, vector<int>(n + 1, 0));

    // m[i][i] = 0
    for (int i = 1; i <= n; i++) m[i][i] = 0;

    // r 表示链长
    for (int r = 2; r <= n; r++) {
        for (int i = 1; i <= n - r + 1; i++) {
            int j = i + r - 1;
            m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
            s[i][j] = i;
            for (int k = i + 1; k < j; k++) {
                int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (t < m[i][j]) {
                    m[i][j] = t;
                    s[i][j] = k;
                }
            }
        }
    }
}

// 回溯输出最优乘法顺序
void traceback(vector<vector<int>> &s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
        return;
    }
    cout << "(";
    traceback(s, i, s[i][j]);
    cout << " x ";
    traceback(s, s[i][j] + 1, j);
    cout << ")";
}

int main() {
    // 测试数据：矩阵维度
    // p = {30, 35, 15, 5, 10, 20, 25}
    // 对应 6 个矩阵: A1(30x35), A2(35x15), A3(15x5), A4(5x10), A5(10x20), A6(20x25)
    vector<int> p = {30, 35, 15, 5, 10, 20, 25};

    vector<vector<int>> m, s;
    matrixChainOrder(p, m, s);

    // cout << "最少乘法次数: " << m[1][p.size() - 1] << endl;
    // cout << "最优乘法顺序: ";

    cout << m[1][p.size() - 1] << endl;

    traceback(s, 1, p.size() - 1);
    cout << endl;

    return 0;
}