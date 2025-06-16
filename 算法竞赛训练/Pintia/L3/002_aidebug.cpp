#include <stdio.h>
#include <queue>
#include <set>
#include <stack>
#include <string.h> // 需要引入字符串处理头文件
using namespace std;

multiset<int> small, big; // small 存较小的元素, big 存较大的元素
stack<int> st; // 栈结构，维护原始顺序

// 确保 big 的大小最多比 small 多 1
void adjust() {
    while (big.size() > small.size() + 1) { 
        small.insert(*big.begin()); // 将 big 中最小的元素移动到 small
        big.erase(big.begin());
    }
    while (big.size() < small.size()) { 
        auto x = small.end();
        --x; // small 中最大的元素
        big.insert(*x);
        small.erase(x);
    }
}

int main() {
    int T;
    char op[20]; // 存操作字符串

    scanf("%d", &T);
    while (T--) {
        scanf("%s", op);
        if (strcmp(op, "Pop") == 0) { // 出栈操作
            if (st.empty()) {
                printf("Invalid\n");
            } else {
                int top_val = st.top();
                printf("%d\n", top_val);
                st.pop(); // 先 pop 掉栈顶元素

                // 在 multiset 中删除对应的值（使用 `find` 获取确切的迭代器）
                if (big.find(top_val) != big.end()) {
                    big.erase(big.find(top_val));
                } else {
                    small.erase(small.find(top_val));
                }

                adjust(); // 重新调整堆
            }
        } else if (strcmp(op, "Push") == 0) { // 入栈操作
            int x;
            scanf("%d", &x);
            st.push(x);

            // 先尝试放入 big，如果不合适再调整
            if (big.empty() || x >= *big.begin()) {
                big.insert(x);
            } else {
                small.insert(x);
            }

            adjust(); // 调整堆结构
        } else if (strcmp(op, "PeekMedian") == 0) { // 查询中位数
            if (st.empty()) {
                printf("Invalid\n");
            } else {
                printf("%d\n", *big.begin()); // 中位数在 big 堆的最小值
            }
        }
    }
    return 0;
}