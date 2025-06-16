#include<stdio.h>
#include<queue>
#include<string.h>
using namespace std;
const int N=1e3+10;
int p[N],t[N];
priority_queue<int>que;
//p[x]维护并查集，t[N]维护根节点的对这个东西感兴趣的人数
int find(int x) {
    if (x != p[x]) {
        int root = find(p[x]);  // 找到根节点
        t[root] += t[x];        // 把当前节点的 `t[x]` 贡献给最终根节点
        t[x] = 0;               // 清空当前节点的 `t[x]`，因为它已经合并到 `root`
        p[x] = root;            // 路径压缩
    }
    return p[x];
}
void print_t()
{
    for(int i=1;i<=10;++i) printf("%d ",t[i]);
    puts("");
}
int main()
{
    int T;
    for(int i=1;i<N-1;++i) p[i]=i;
    memset(t,0,sizeof t);
    scanf("%d",&T);
    for(int i=1;i<=T;++i)
    {
        int n,st;
        scanf("%d: %d",&n,&st);
        int pa=find(st);
        ++t[pa];
        for(int j=2;j<=n;++j)
        {
            int x;
            scanf("%d",&x);
            int pb=find(x);
            p[pb]=pa;
            t[pa]+=t[pb];
            t[pb]=0;
        }
    }
    for(int i=1;i<N-1;++i)
    {
        if(i==p[i]&&t[i]!=0) 
        {
            que.push(t[i]);
            //printf("i:%d:%d ",i,t[i]);
        }
        //print_t();
    }
    printf("%d\n",que.size());
    while(que.size()>=2)
    {
        auto x=que.top();
        que.pop();
        printf("%d ",x);
    }
    printf("%d",que.top());
    return 0;
}