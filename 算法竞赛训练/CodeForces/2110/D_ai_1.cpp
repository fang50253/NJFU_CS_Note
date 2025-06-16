#include <cstdio>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int MAXN = 200005;
const long long INF = 1LL << 60;

struct Edge {
    int to;
    long long weight;
};

int n, m;
long long b[MAXN];
vector<Edge> adj[MAXN];
long long dist[MAXN];

void solve() {
    // 初始化距离数组和邻接表
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
        adj[i].clear();
    }

    // 读取电池数量
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &b[i]);
    }

    // 读取边的信息
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        adj[u].push_back({v, w});
    }

    // 优先队列，存储当前节点和到达该节点所需的最小电池数量
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    // 初始状态：从节点1开始，携带0个电池
    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [curr_battery, u] = pq.top();
        pq.pop();

        // 如果当前状态不是最优的，跳过
        if (curr_battery > dist[u]) continue;

        // 遍历所有邻接边
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            long long w = edge.weight;

            // 计算到达下一个节点所需的最小电池数量
            long long required_battery = max(curr_battery, w);

            // 如果在当前节点可以获取更多电池，更新所需电池数量
            if (required_battery > curr_battery) {
                long long additional_battery = required_battery - curr_battery;
                if (b[u] >= additional_battery) {
                    required_battery = curr_battery + additional_battery;
                } else {
                    // 如果无法获取足够的电池，跳过该边
                    continue;
                }
            }

            // 如果找到更优的路径，更新距离并加入队列
            if (required_battery < dist[v]) {
                dist[v] = required_battery;
                pq.push({dist[v], v});
            }
        }
    }

    // 输出结果
    if (dist[n] == INF) {
        printf("-1\n");
    } else {
        printf("%lld\n", dist[n]);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        solve();
    }
    return 0;
}