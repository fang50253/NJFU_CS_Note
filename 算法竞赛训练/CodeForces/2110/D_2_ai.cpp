#include <stdio.h>
#include <algorithm>
#include <queue>
#include <iostream>
#include <string.h>
using namespace std;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int arr[N];               // 每个节点电池容量
int e[2 * N], ne[2 * N], h[N], w[2 * N], idx = 1;
int min_batt[N], max_batt[N];

struct Node {
    int node;     // 结点编号
    int battery;  // 当前电池数（用于路径更新）
    bool operator < (const Node &W) const {
        return battery > W.battery; // 小电池优先（最小堆）
    }
};

void add(int a, int b, int c) {
    ne[idx] = h[a];
    e[idx] = b;
    w[idx] = c;
    h[a] = idx++;
}

void fun() {
    int n, m;
    scanf("%d%d", &n, &m);

    // 初始化
    for (int i = 1; i <= n; ++i) scanf("%d", &arr[i]);
    memset(h,0,sizeof h);
    idx = 1;

    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    // 初始化 battery 数组
    priority_queue<Node> que;
    fill(min_batt, min_batt + n + 1, INF);
    fill(max_batt, max_batt + n + 1, INF);

    que.push({1, arr[1]});
    min_batt[1] = max_batt[1] = arr[1];

    while (!que.empty()) {
        auto out = que.top(); que.pop();
        int u = out.node;
        int b = out.battery;

        if (b > max_batt[u]) continue;

        for (int i = h[u]; i; i = ne[i]) {
            int v = e[i], cost = w[i];
            if (b < cost) continue;

            int new_b = b + arr[v];
            if (new_b < max_batt[v]) {
                max_batt[v] = new_b;
                min_batt[v] = min({min_batt[v], new_b, cost});
                que.push({v, new_b});
            }
        }
    }

    if (min_batt[n] == INF) puts("-1");
    else printf("%d\n", min_batt[n]);
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}