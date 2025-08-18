#include<stdio.h>
#include<string.h>
using namespace std;
const int N=5e3+10;
int arr[2*N],tr[2*N],n,bigger[2*N];
//bigger[i]表示右侧大于arr[i]的数量
//树状数组处理函数
void init()
{
    memset(tr,0,sizeof tr);
}
//树状数组求和
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
//单点增
void add(int x,int val) 
{
    while(x<2*n)
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
    init();
    memset(bigger,0,sizeof bigger);
    //预处理右边有多少个大于这个数字的数
    for(int i=n;i>=1;--i)
    {
        bigger[i]=sum(arr[i]+1,n);
        add(arr[i],1);
    }
    init();
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        ans+=min(sum(arr[i]+1,2*n),bigger[i]);
        if(sum(arr[i]+1,n)<bigger[i]) add(2*n-arr[i],1);
        else add(arr[i],1);
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