#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100010; // 数组最大长度
int n, m; // n 表示数组大小，m 表示操作次数
int w[N]; // 存储原始数组
// 线段树节点
struct Node
{
    int l, r;   // 当前节点对应的区间 [l, r]
    LL sum, add; // sum 维护区间和，add 维护懒标记（区间加法）
} tr[N * 4]; // 线段树最多需要 4 倍的数组大小

// 更新当前节点的 sum，保证区间和正确
void pushup(int u)
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

// 将懒标记下推到子节点
void pushdown(int u)
{
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add) // 如果当前节点有未处理的懒标记
    {
        // 把当前节点的懒标记累加到左右子节点
        left.add += root.add;
        left.sum += (LL)(left.r - left.l + 1) * root.add;
        right.add += root.add;
        right.sum += (LL)(right.r - right.l + 1) * root.add;
        
        // 清除当前节点的懒标记
        root.add = 0;
    }
}

// 递归建树，初始化线段树
void build(int u, int l, int r)
{
    if (l == r) tr[u] = {l, r, w[r], 0}; // 叶子节点，存储原数组值
    else
    {
        tr[u] = {l, r}; // 记录当前节点的区间范围
        int mid = l + r >> 1; // 计算中点
        build(u << 1, l, mid); // 递归构建左子树
        build(u << 1 | 1, mid + 1, r); // 递归构建右子树
        pushup(u); // 更新当前节点的 sum
    }
}

// 处理区间 [l, r] 内所有元素加 d
void modify(int u, int l, int r, int d)
{
    if (tr[u].l >= l && tr[u].r <= r) // 如果当前区间被完全包含
    {
        tr[u].sum += (LL)(tr[u].r - tr[u].l + 1) * d; // 更新区间和
        tr[u].add += d; // 标记懒更新
    }
    else // 部分覆盖，需要下推懒标记并递归更新子区间
    {
        pushdown(u); // 先下推懒标记
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d); // 修改左子区间
        if (r > mid) modify(u << 1 | 1, l, r, d); // 修改右子区间
        pushup(u); // 回溯更新当前节点的 sum
    }
}

// 查询区间 [l, r] 的元素和
LL query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum; // 当前区间完全包含在查询范围内
    
    pushdown(u); // 先下推懒标记，确保 sum 正确
    int mid = tr[u].l + tr[u].r >> 1;
    LL sum = 0;
    if (l <= mid) sum = query(u << 1, l, r); // 查询左子区间
    if (r > mid) sum += query(u << 1 | 1, l, r); // 查询右子区间
    return sum;
}

int main()
{
    scanf("%d%d", &n, &m); // 读取数组大小和操作次数

    for (int i = 1; i <= n; i++) scanf("%d", &w[i]); // 读取原数组

    build(1, 1, n); // 递归建树

    char op[2];
    int l, r, d;

    while (m --)
    {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C') // 区间加法操作
        {
            scanf("%d", &d);
            modify(1, l, r, d);
        }
        else // 区间求和操作
            printf("%lld\n", query(1, l, r));
    }

    return 0;
}