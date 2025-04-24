```
@Author: 方泽宇
@Date: 2025-04-20
@LastEditTime: 2025-04-20
@Description: 2025ACM资料
@Version: 1.0
@Tags: ICPC南昌 JSCPC
@Email: fzy1139950253@gmail.com
```

# 数据结构
## KMP

使用 KMP（Knuth-Morris-Pratt）字符串匹配算法，在长度为 m 的主串 s 中查找所有长度为 n 的模式串 p 的匹配位置，并输出每次匹配成功的位置（从 0 开始）

```c++
#include<bits/stdc++.h> 
using namespace std;
const int N=1e5+10,M=1e6+10;
int n,m,ne[N];//n代表短文本，m代表长文本的长度
char s[N],t[M];//s是短文本，t是长文本 
int main()
{
    cin>>n>>s+1>>m>>t+1;
    //初始化next指针,一定要记住next指针是对着短的字符串求 
    for(int i=2,j=0;i<=n;i++)
    {
        while(j&&s[i]!=s[j+1]) j=ne[j];
        if(s[i]==s[j+1]) j++;
        ne[i]=j;
    }
    //kmp
    for(int i=1,j=0;i<=m;i++)
    {
        while(j&&t[i]!=s[j+1]) j=ne[j];
        if(t[i]==s[j+1]) j++;
        if(j==n)
        {
            printf("%d ",i-n);
            j=ne[j];
        }
    }
    return 0;
}
```

## 基于Trie的字符串计数器

通过构建字典树（Trie），实现对小写字母组成的字符串集合的维护，支持两种操作：I 表示插入字符串，Q 表示查询某个字符串在集合中被插入过多少次。

```c++
#include<iostream>
using namespace std;
const int N=1e5+10;
int a[N][26],b[N],idx=1;
char x[N];
void I(char *x)
{
    int tmp,c=0;
    for(int i=0;x[i];i++)
    {
        tmp=x[i]-'a';
        if(!a[c][tmp]) a[c][tmp]=idx++;
        c=a[c][tmp];
    }
    b[c]++;
}
int Q(char *x)
{
    int tmp,c=0;
    for(int i=0;x[i];i++)
    {
        tmp=x[i]-'a';
        if(!a[c][tmp]) return 0;
        c=a[c][tmp];
    }
    return b[c];
}
int main()
{
    int n;
    char op;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>op>>x;
        if(op=='I') I(x);
        else if(op=='Q') cout<<Q(x)<<endl;
    }
    return 0;
 } 
```

## 基于Trie实现的AC自动机算法

本程序利用 Trie 构建字典树，并通过 BFS 构建失配指针（即 Aho-Corasick 自动机），高效处理多模式串在一个主串中出现的总次数，其中每个模式串匹配一次就记一次（重复匹配位置不再重复统计）。

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10010, S = 55, M = 1000010;
int n, tr[N * S][26], cnt[N * S], idx, q[N * S], ne[N * S];
char str[M];
void insert()
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++ idx;
        p = tr[p][t];
    }
    cnt[p] ++ ;
}
void build()
{
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i ++ )
        if (tr[0][i])
            q[ ++ tt] = tr[0][i];

    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = 0; i < 26; i ++ )
        {
            int p = tr[t][i];
            if (!p) tr[t][i] = tr[ne[t]][i];
            else
            {
                ne[p] = tr[ne[t]][i];
                q[ ++ tt] = p;
            }
        }
    }
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        memset(tr, 0, sizeof tr);
        memset(cnt, 0, sizeof cnt);
        memset(ne, 0, sizeof ne);
        idx = 0;

        scanf("%d", &n);
        for (int i = 0; i < n; i ++ )
        {
            scanf("%s", str);
            insert();
        }
        build();
        scanf("%s", str);
        int res = 0;
        for (int i = 0, j = 0; str[i]; i ++ )
        {
            int t = str[i] - 'a';
            j = tr[j][t];

            int p = j;
            while (p)
            {
                res += cnt[p];
                cnt[p] = 0;
                p = ne[p];
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
```

## 带路经压缩的并查集

```c++
int find(int x)
{
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}
```

## 栈的应用————表达式求值(2025PTA天梯赛题目，主播不会背没写出来！！！)

```c++
#include<iostream>
#include<stdio.h>
#include<stack>
#include<unordered_map>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
stack<int>num;
stack<char>op;
void eval()
{
	auto b=num.top();num.pop();
	auto a=num.top();num.pop();
	auto c=op.top();op.pop();
	//cout<<a<<" "<<b<<" "<<c<<endl;
	if(c=='+') num.push(a+b);
	else if(c=='-') num.push(a-b);
	else if(c=='*') num.push(a*b);
	else num.push(a/b);
}
int main()
{
	string str;
	cin>>str;
	unordered_map<char, int> pr{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
	for(int i=0;i<str.size();i++)
	{
	    auto c = str[i];
        if (isdigit(c))
        {
            int x = 0, j = i;
            while (j < str.size() && isdigit(str[j]))
                x = x * 10 + str[j ++ ] - '0';
            i = j - 1;
            num.push(x);
        }
		else if (c == '(') op.push(c);
        else if (c == ')')
        {
            while (op.top() != '(') eval();
            op.pop();
        }
		else
		{
			while(op.size() && op.top() != '(' && pr[op.top()] >= pr[c]) eval();
			op.push(c);
			//cout<<"3";
		}
	}
	while(op.size()) eval();
	cout<<num.top()<<endl;
	return 0;
}
```

## 树状数组

```c++
int lowbit(int x)
{
    return x&-x;
}
long long query(int x)
{
    long long sum=0;
    while(x>0)
    {
        sum+=arr[x];
        x-=lowbit(x);
    }
    return sum;
}
int add(int x,int k)
{
    while(x<=n)
    {
        arr[x]+=k;
        x+=lowbit(x);
    }
}
```

✅ query(int x)：查询下标 1 到 x 的前缀和。

✅ add(int x, int k)：在下标 x 的位置上增加一个值 k，并更新相关节点。

## 线段树
```c++
const int N=1e5+10;
int w[N];
struct Node
{
    LL l,r,sum,lazytag;
    //sum维护区间和，lazytag维护懒标记
}tr[4*N];
void pushup(LL u)//用于上传区间修改的答案
{
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}
void pushdown(LL u)//用于下传懒标记
{
    auto &l=tr[u<<1];
    auto &r=tr[u<<1|1];
    auto &root=tr[u];
    if(tr[u].lazytag)
    {
        l.lazytag+=root.lazytag;
        l.sum+=(l.r-l.l+1)*root.lazytag;
        r.sum+=(r.r-r.l+1)*root.lazytag;
        r.lazytag+=root.lazytag;
        root.lazytag=0;
    }
}
void build(LL u,LL l,LL r)
{
    if(l==r) tr[u]={l,r,w[r],0};
    else 
    {
        LL mid=l+r>>1;
        tr[u].l=l;
        tr[u].r=r;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u);
    }
}
void modify(LL u,LL l,LL r,LL add)
{
    if(l<=tr[u].l&&r>=tr[u].r)//完全被包含
    {
        tr[u].lazytag+=add;//更新懒标记
        tr[u].sum+=(tr[u].r-tr[u].l+1)*add;
    }
    else
    {
        pushdown(u);//先下传懒标记
        LL mid=tr[u].l+tr[u].r>>1;
        if(l<=mid) modify(u<<1,l,r,add);
        if(r>=mid+1) modify(u<<1|1,l,r,add);
        pushup(u);
    }
}
LL query(LL u,LL l,LL r)
{
    if(l<=tr[u].l&&r>=tr[u].r) return tr[u].sum;
    pushdown(u);
    LL mid=tr[u].l+tr[u].r>>1,sum=0;
    if(l<=mid) sum=query(u<<1,l,r);
    if(r>=mid+1) sum+=query(u<<1|1,l,r);
    return sum;
}
```

✅ build(u, l, r)：构建线段树，将区间 [l, r] 建为编号为 u 的结点。

✅ modify(u, l, r, add)：将区间 [l, r] 上的每个元素都加上 add。

✅ query(u, l, r)：查询区间 [l, r] 的元素和。

✅ pushup(u)：更新节点 u 的区间和为左右子树之和。

✅ pushdown(u)：将节点 u 的懒标记传递给左右子节点，并更新它们的区间和。

一般递归调用上面函数时，除非特别说明u均为1


## 主席树维护区间第k小

```c++
int n, m;
int a[N];
vector<int> nums;
struct Node
{
    int l, r;
    int cnt;
}tr[N * 4 + N * 17];
int root[N], idx;
int find(int x)
{
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}
int build(int l, int r)
{
    int p = ++ idx;
    if (l == r) return p;
    int mid = l + r >> 1;
    tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
    return p;
}
int insert(int p, int l, int r, int x)
{
    int q = ++ idx;
    tr[q] = tr[p];
    if (l == r)
    {
        tr[q].cnt ++ ;
        return q;
    }
    int mid = l + r >> 1;
    if (x <= mid) tr[q].l = insert(tr[p].l, l, mid, x);
    else tr[q].r = insert(tr[p].r, mid + 1, r, x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
    return q;
}
int query(int q, int p, int l, int r, int k)
{
    if (l == r) return r;
    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
    int mid = l + r >> 1;
    if (k <= cnt) return query(tr[q].l, tr[p].l, l, mid, k);
    else return query(tr[q].r, tr[p].r, mid + 1, r, k - cnt);
}
```

find(int x)：离散化函数

build(int l, int r)：构建初始的空线段树

insert(int p, int l, int r, int x)：在已有版本 p 的基础上插入一个元素 x，构造新版本树

query(int q, int p, int l, int r, int k)：查询区间第 k 小值：区间 [l, r] 在版本 q 和 p 之间的差分第 k 小值

区间第k小主程序示范：

```c++
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
        nums.push_back(a[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    root[0] = build(0, nums.size() - 1);

    for (int i = 1; i <= n; i ++ )
        root[i] = insert(root[i - 1], 0, nums.size() - 1, find(a[i]));

    while (m -- )
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", nums[query(root[r], root[l - 1], 0, nums.size() - 1, k)]);
    }

    return 0;
}
```

## 离线算法(莫队)

```c++
int n, m, len;
int a[N], cnt[N], res[N], answer = 0;
struct Query {
    int l, r, id;
    bool operator<(const Query &q) const {
        int block_a = l / len, block_b = q.l / len;
        if (block_a != block_b) return block_a < block_b;
        return (block_a & 1) ? r < q.r : r > q.r;  // 奇偶块优化
    }
} query[N];
void add(int x) {
    if (++cnt[x] == 1) answer++;
}
void remove(int x) {
    if (--cnt[x] == 0) answer--;
}
int main() {
    cin >> n >> m;
    len = sqrt(n);  // 分块大小
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        cin >> query[i].l >> query[i].r;
        query[i].id = i;
    }
    sort(query, query + m);
    int L = 1, R = 0;
    for (int i = 0; i < m; i++) {
        int l = query[i].l, r = query[i].r;

        while (L > l) add(a[--L]);
        while (R < r) add(a[++R]);
        while (L < l) remove(a[L++]);
        while (R > r) remove(a[R--]);

        res[query[i].id] = answer;
    }
    for (int i = 0; i < m; i++) cout << res[i] << '\n';
    return 0;
}
```

add(int x):将元素 x 加入当前区间，并更新答案

remove(int x):将元素 x 从当前区间移除，并更新答案

虽然莫队不适合做RMQ问题，但是仍提供一个维护区间最大值的模板

```c++
#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
const int N = 1e5 + 10;
int n, m, len;
int a[N];
int res[N];
struct Query {
    int l, r, id;
    bool operator<(const Query &q) const {
        int block_a = l / len, block_b = q.l / len;
        if (block_a != block_b) return block_a < block_b;
        return (block_a & 1) ? r < q.r : r > q.r;
    }
} query[N];
multiset<int> window;
void add(int x) {
    window.insert(x);
}
void remove(int x) {
    window.erase(window.find(x)); // 删除一个等于 x 的值
}
int get_max() {
    return *window.rbegin(); // multiset 自动排序，最大值是最后一个
}
int main() {
    cin >> n >> m;
    len = sqrt(n);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        cin >> query[i].l >> query[i].r;
        query[i].id = i;
    }
    sort(query, query + m);
    int L = 1, R = 0;
    for (int i = 0; i < m; i++) {
        int l = query[i].l, r = query[i].r;
        while (R < r) add(a[++R]);
        while (R > r) remove(a[R--]);
        while (L < l) remove(a[L++]);
        while (L > l) add(a[--L]);
        res[query[i].id] = get_max();
    }
    for (int i = 0; i < m; i++) cout << res[i] << '\n';
    return 0;
}
```

