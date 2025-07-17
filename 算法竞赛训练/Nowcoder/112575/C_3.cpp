#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;

int arr[N];
int pos[N];
int b[N * 2];
int first[N];
int n, m;
struct Node {
    int l, r;
    int maxv;
    int add;
} tr[N * 4];
void build(int u, int l, int r, int w[]) {
    tr[u] = {l, r};
    if (l == r) {
        tr[u].maxv = pos[l];
    } else {
        int mid = (l + r) >> 1;
        build(u << 1, l, mid, w);
        build(u << 1 | 1, mid + 1, r, w);
        tr[u].maxv = max(tr[u << 1].maxv, tr[u << 1 | 1].maxv);
    }
}
void pushdown(int u) {
    if (tr[u].add) {
        int add = tr[u].add;
        tr[u << 1].add += add;
        tr[u << 1 | 1].add += add;
        tr[u << 1].maxv += add;
        tr[u << 1 | 1].maxv += add;
        tr[u].add = 0;
    }
}
void modify(int u, int l, int r, int d) {
    if (l <= tr[u].l && tr[u].r <= r) {
        tr[u].maxv += d;
        tr[u].add += d;
    } else {
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        tr[u].maxv = max(tr[u << 1].maxv, tr[u << 1 | 1].maxv);
    }
}
int query(int u, int l, int r) {
    if (l <= tr[u].l && tr[u].r <= r) return tr[u].maxv;
    
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    int res = INT_MIN;
    if (l <= mid) res = max(res, query(u << 1, l, r));
    if (r > mid) res = max(res, query(u << 1 | 1, l, r));
    return res;
}
void max_pos() {
    std::stack<int> stk;
    for (int i = n - 1; i >= 0; --i)
    {
        while (!stk.empty() && arr[stk.top()] <= arr[i]) stk.pop();
        if (!stk.empty()) pos[i] = stk.top();
        else pos[i] = -1;
        stk.push(i);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%d", &arr[i]);
    for(int i = 1; i <= n; ++i) arr[i + n] = arr[i];
    for(int i = 1; i <= 2 * n; ++i) b[i] = arr[i]; 
    n = 2 * n;
    max_pos(); 
    build(1, 1, 2 * n, pos);

    int ans = 0;
    for(int k = 1; k <= n; ++k)
    {
        for(int i = 0; i < m; ++i) first[i] = 1e9;

        for(int i = k; i <= k + n - 1; ++i)
        {
            int v = b[i];
            if(first[v] == 1e9) first[v] = i - k; // 记录相对位置
        }
        bool ok = true;
        for(int i = 0; i < m; ++i)
        {
            if(first[i] == 1e9) { ok = false; break; } // 没出现
        }
        for(int i = 0; i < m - 1; ++i)
        {
            if(first[i] >= first[i + 1]) { ok = false; break; } // 非严格递增
        }
        if(ok) ++ans;
    }
    printf("%d\n", ans);
    return 0;
}