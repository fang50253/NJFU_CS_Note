#include<stdio.h>
#include<string.h>
using namespace std;
const int N=5e3+10;
int arr[2*N],tr[2*N],n,bigger[2*N],left_bigger[2*N];

void init()
{
    memset(tr,0,sizeof tr);
}

int sum(int l,int r)
{
    --l;
    int ans=0;
    while(r)
    {
        ans+=tr[r];
        r-=r&-r;
    }
    while(l)
    {
        ans-=tr[l];
        l-=l&-l;
    }
    return ans;
}

void add(int x,int val) 
{
    while(x<=n)  // 注意这里范围只要到 n 就够了
    {
        tr[x]+=val;
        x+=x&-x;
    }
}

int min(int a,int b)
{
    return a>b?b:a;
}

void fun()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);

    // 预处理右边大于它的数量
    init();
    memset(bigger,0,sizeof bigger);
    for(int i=n;i>=1;--i)
    {
        bigger[i]=sum(arr[i]+1,n);
        add(arr[i],1);
    }

    // 预处理左边大于它的数量
    init();
    memset(left_bigger,0,sizeof left_bigger);
    for(int i=1;i<=n;++i)
    {
        left_bigger[i]=sum(arr[i]+1,n);
        add(arr[i],1);
    }

    // 统计答案
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        ans+=min(left_bigger[i], bigger[i]);
    }

    printf("%d\n",ans);
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}