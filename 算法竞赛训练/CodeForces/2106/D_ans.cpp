#include<iostream>
#include<cassert>
using namespace std;

int N, M;
int A[2<<17], B[2<<17];  // A 是花园中的花的美丽值，B 是要采摘的目标花美丽值要求
int L[2<<17], R[2<<17];  // L[i] 表示匹配 B[0~i-1] 所需的最左位置，R[i] 表示匹配 B[i~M-1] 的最右位置

int main()
{
    ios::sync_with_stdio(false); // 关闭同步，加快 cin/cout
    cin.tie(nullptr); // 解绑 cin 和 cout，提高输入效率

    int T; 
    cin >> T; // 读入测试组数

    while (T--) // 每组测试数据
    {
        cin >> N >> M; // 读入 A 数组和 B 数组的大小

        for (int i = 0; i < N; i++) cin >> A[i]; // 读入花园中的花的美丽值
        for (int i = 0; i < M; i++) cin >> B[i]; // 读入要采摘的花的最低美丽要求

        L[0] = -1; // 初始时前缀为空，设为 -1 方便后续加一
        for (int i = 0; i < M; i++)
        {
            // 从前一个位置开始尝试往后找
            L[i + 1] = L[i] + 1;
            // 找到第一个满足 A[pos] >= B[i] 的位置
            while (L[i + 1] < N && A[L[i + 1]] < B[i]) L[i + 1]++;
        }

        R[M] = N; // 从末尾往前处理，初始化为 N
        for (int i = M - 1; i >= 0; i--)
        {
            // 从后一个位置往前推
            R[i] = R[i + 1] - 1;
            // 找到第一个满足 A[pos] >= B[i] 的位置
            while (R[i] >= 0 && A[R[i]] < B[i]) R[i]--;
        }

        int ans = 2e9; // 初始答案设置为极大值
        if (L[M] < N) ans = 0; // 如果整个 B 都能完整匹配在 A 中，最优解为 0

        // 尝试分割点，是否可以将 B 拆成前后两段分别匹配
        for (int i = 0; i < M; i++)
        {
            if (L[i] + 1 <= R[i + 1])
            {
                // 如果满足分割条件，尝试更新答案为 B[i] 的最小值
                ans = min(ans, B[i]);
            }
        }

        // 如果没有任何合法方案，则输出 -1
        if (ans == (int)2e9) ans = -1;
        cout << ans << "\n"; // 输出答案
    }
}