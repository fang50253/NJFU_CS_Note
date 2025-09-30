#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// 节点结构，表示一个矩阵或一段矩阵乘积
struct Node {
    int left, right;   // 矩阵编号范围 [left, right]
    Node* lchild;
    Node* rchild;
    Node(int l, int r): left(l), right(r), lchild(nullptr), rchild(nullptr) {}
};

// 格式化输出括号形式
void printOrder(Node* root) {
    if (!root) return;
    if (root->left == root->right) {
        cout << "A" << root->left;
        return;
    }
    cout << "(";
    printOrder(root->lchild);
    cout << " x ";
    printOrder(root->rchild);
    cout << ")";
}

// 贪心矩阵链乘法
pair<int, Node*> greedyMatrixChain(vector<int> p) {
    int n = p.size() - 1;
    vector<Node*> nodes;
    for (int i = 1; i <= n; i++) {
        nodes.push_back(new Node(i, i));
    }

    int cost = 0;
    while (p.size() > 2) {
        // 找到最大元素的位置
        int idx = 1;
        for (int i = 1; i < (int)p.size() - 1; i++) {
            if (p[i] > p[idx]) idx = i;
        }

        // 代价
        int mulCost = p[idx - 1] * p[idx] * p[idx + 1];
        cost += mulCost;

        // 合并对应的矩阵节点
        Node* leftNode = nodes[idx - 1];
        Node* rightNode = nodes[idx];
        Node* newNode = new Node(leftNode->left, rightNode->right);
        newNode->lchild = leftNode;
        newNode->rchild = rightNode;

        // 更新 p：删除 p[idx]
        p.erase(p.begin() + idx);

        // 更新 nodes：替换 idx-1 和 idx 的两个节点为合并节点
        nodes.erase(nodes.begin() + idx);
        nodes[idx - 1] = newNode;
    }

    return {cost, nodes[0]};
}

int main() {
    // 测试数据
    vector<int> p = {30, 35, 15, 5, 10, 20, 25};

    auto [greedyCost, root] = greedyMatrixChain(p);

    // cout << "贪心算法计算的乘法次数: " << greedyCost << endl;
    // cout << "贪心算法的乘法顺序: ";
    cout << greedyCost << endl;
    printOrder(root);
    cout << endl;

    return 0;
}