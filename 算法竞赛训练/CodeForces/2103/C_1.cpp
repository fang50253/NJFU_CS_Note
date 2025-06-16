#include<stdio.h>
#include<queue>
#include<string.h>
using namespace std;
const int N=2e5+10;
int arr[N],cnt[N];
void fun()
{
    int n,k,ans=0,t=0;
    scanf("%d%d",&n,&k);
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&arr[i]);
        if(arr[i]<=k) cnt[i]=cnt[i-1]+1;
        else cnt[i]=cnt[i-1];
    }
    //尝试从左边开始找
    int i;
    for(i=1;i<=n;++i)
    {
        if(cnt[i]*2>=i)
        {
            ++t;//左边是可行
            break;
        }
    }
    for(;i<=n;++i)
    {
        if(cnt[i]*2>=i)
        {
            printf("Yes\n");
            return;
        }
    }
    //尝试从右边开始找
    memset(cnt,0,sizeof(cnt));
    for(int i=1,j=n;i<j;++i,--j) swap(arr[i],arr[j]);
    for(int i=1;i<=n;++i)
    {
        if(arr[i]<=k) cnt[i]=cnt[i-1]+1;
        else cnt[i]=cnt[i-1];
    }
    for(i=1;i<=n;++i)
    {
        if(cnt[i]*2>i)
        {
            ++t;//左边是可行
            break;
        }
    }
    for(;i<=n;++i)
    {
        if(cnt[i]*2>=i)
        {
            printf("Yes\n");
            return;
        }
    }
    printf("No\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}