#include<stdio.h>
#include<vector>
using namespace std;
const int N=2e5+10;
int max(int a,int b)
{
    return a>b?a:b;
}
void fun()
{
    int n,maxn=0,vect=0;//maxn表示一个节点连接的没有孩子节点的节点数最大值，vect表示
    scanf("%d",&n);
    vector<int>vec[n+10];
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    if(n==2)
    {
        printf("0\n");
        return;
    }
    for(int i=1;i<=n;++i)
    {
        if(vec[i].size()==1)
        {
            ++vect;
            continue;
        }
        int t=0;
        for(auto x:vec[i]) t+=(vec[x].size()==1);
        maxn=max(maxn,t);
    }
    printf("%d\n",vect-maxn);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}