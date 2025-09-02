#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

const double EPS = 1e-6;
const int TARGET = 24;

struct Expr {
    double val;    // 数值
    string str;    // 表达式字符串
    int pri;       // 优先级：数字=3，* /=2，+ -=1
};

vector<string> results;

bool applyOp(const Expr &a, const Expr &b, char op, Expr &res) {
    res.str = "";
    res.val = 0;
    res.pri = 0;
    if (op == '+') {
        res.val = a.val + b.val;
        res.pri = 1;
    } else if (op == '-') {
        res.val = a.val - b.val;
        res.pri = 1;
    } else if (op == '*') {
        res.val = a.val * b.val;
        res.pri = 2;
    } else if (op == '/') {
        if (fabs(b.val) < EPS) return false;
        res.val = a.val / b.val;
        res.pri = 2;
    }

    // 左操作数是否需要括号
    string left = a.str;
    if (a.pri < res.pri) left = "(" + left + ")";
    // 右操作数是否需要括号
    string right = b.str;
    if (b.pri < res.pri || (op == '-' || op == '/') && b.pri == res.pri) {
        right = "(" + right + ")";
    }

    res.str = left + op + right;
    return true;
}

void generateExpressions(vector<Expr> exprs) {
    int n = exprs.size();
    if (n == 1) {
        if (fabs(exprs[0].val - TARGET) < EPS) {
            results.push_back(exprs[0].str);
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            vector<Expr> rest;
            for (int k = 0; k < n; k++) {
                if (k != i && k != j) rest.push_back(exprs[k]);
            }
            for (char op : {'+', '-', '*', '/'}) {
                Expr res;
                if (applyOp(exprs[i], exprs[j], op, res)) {
                    rest.push_back(res);
                    generateExpressions(rest);
                    rest.pop_back();
                }
                if (applyOp(exprs[j], exprs[i], op, res)) {
                    rest.push_back(res);
                    generateExpressions(rest);
                    rest.pop_back();
                }
            }
        }
    }
}

int main() {
    vector<double> nums(4);
    cout << "请输入4个数：";
    for (int i = 0; i < 4; i++) cin >> nums[i];

    vector<int> idx = {0, 1, 2, 3};
    set<string> uniqueResults;

    do {
        vector<Expr> exprs;
        for (int i : idx) {
            exprs.push_back({nums[i], to_string((int)nums[i]), 3});
        }
        results.clear();
        generateExpressions(exprs);
        for (auto &s : results) {
            uniqueResults.insert(s);
        }
    } while (next_permutation(idx.begin(), idx.end()));

    if (uniqueResults.empty()) {
        cout << "无解" << endl;
    } else {
        cout << "所有可能的结果：" << endl;
        for (auto &s : uniqueResults) {
            cout << s << endl;
        }
    }
    return 0;
}