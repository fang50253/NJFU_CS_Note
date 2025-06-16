#include <stdio.h>
#include <queue>
#include <set>
#include <stack>
#include <string.h>

using namespace std;

multiset<int> small, big; // small 存较小的元素（包含中位数），big 存较大的元素
stack<int> st; // 维护原始顺序

// 调整对顶堆，使得 small 的大小最多比 big 多 1
void adjust() {
    while (small.size() > big.size() + 1) { 
        auto it = small.end();
        --it; // small 中最大的元素
        big.insert(*it);
        small.erase(it);
    }
    while (small.size() < big.size()) { 
        small.insert(*big.begin()); // 将 big 中最小的元素移动到 small
        big.erase(big.begin());
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
                if (small.find(top_val) != small.end()) {
                    small.erase(small.find(top_val));
                } else {
                    big.erase(big.find(top_val));
                }

                adjust(); // 重新调整堆
            }
        } 
        else if (strcmp(op, "Push") == 0) { // 入栈操作
            int x;
            scanf("%d", &x);
            st.push(x);

            // 先尝试放入 small，如果不合适再调整
            if (small.empty() || x <= *small.rbegin()) {
                small.insert(x);
            } else {
                big.insert(x);
            }

            adjust(); // 调整堆结构
        } 
        else if (strcmp(op, "PeekMedian") == 0) { // 查询中位数
            if (st.empty()) {
                printf("Invalid\n");
            } else {
                printf("%d\n", *small.rbegin()); // 中位数在 small 堆的最大值
            }
        }
    }
    return 0;
}