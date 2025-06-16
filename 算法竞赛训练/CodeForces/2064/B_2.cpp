#include<stdio.h>
#include<string.h>
const int N=2e5+10;
int arr[N],cnt[N],n;
void fun()
{
    scanf("%d",&n);
    memset(cnt,0,sizeof cnt);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&arr[i]);
        ++cnt[arr[i]];
    }
    int l=0,len=0,r;
    for(int i=1;i<=n;++i)
    {
        if(cnt[arr[i]]>1) l=i;
        else
        {
            if(i-l>len)
            {
                len=i-l;
                r=i;
            }
        }
    }
    if(len) printf("%d %d\n",r-len+1,r);
    else printf("0\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}