#include <iostream>
#include <queue>
#include <unordered_map>
#include <stack>

using namespace std;

priority_queue<int, vector<int>, less<int> > maxHeap;   // 大根堆（存较小的一半）
priority_queue<int, vector<int>, greater<int> > minHeap; // 小根堆（存较大的一半）
unordered_map<int, int> countMap; // 记录堆中元素的个数
stack<int> stackData; // 模拟栈

void balanceHeaps() {
    while (!maxHeap.empty() && countMap[maxHeap.top()] == 0) maxHeap.pop(); // 清理无效数据
    while (!minHeap.empty() && countMap[minHeap.top()] == 0) minHeap.pop();

    if (maxHeap.size() > minHeap.size() + 1) {
        minHeap.push(maxHeap.top());
        countMap[maxHeap.top()]--;
        maxHeap.pop();
    } else if (maxHeap.size() < minHeap.size()) {
        maxHeap.push(minHeap.top());
        countMap[minHeap.top()]--;
        minHeap.pop();
    }
}

void push(int key) {
    stackData.push(key);
    if (maxHeap.empty() || key <= maxHeap.top()) {
        maxHeap.push(key);
    } else {
        minHeap.push(key);
    }
    countMap[key]++;
    balanceHeaps();
}

void pop() {
    if (stackData.empty()) {
        cout << "Invalid" << endl;
        return;
    }
    int key = stackData.top();
    stackData.pop();
    countMap[key]--;
    balanceHeaps();
    cout << key << endl;
}

void peekMedian() {
    if (stackData.empty()) {
        cout << "Invalid" << endl;
        return;
    }
    cout << maxHeap.top() << endl;
}

int main() {
    int N;
    cin >> N;
    while (N--) {
        string op;
        cin >> op;
        if (op == "Push") {
            int key;
            cin >> key;
            push(key);
        } else if (op == "Pop") {
            pop();
        } else if (op == "PeekMedian") {
            peekMedian();
        }
    }
    return 0;
}