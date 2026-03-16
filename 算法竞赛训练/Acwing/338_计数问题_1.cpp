#include<stdio.h>
#include<string.h>
int cnt[10];
int count(int x,int num)
{
    int ans=0;
    //先分析个位这个数字出现的次数
    while(x>=10)
    {
        int tmp=x%10;
        if(tmp>=num) ans+=x/10;
        else ans+=x/10-1;
        x/=10;
    }
    if(x>num) ++ans;
    return ans;
}
int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    while(!(a==0&&b==0))
    {
        memset(cnt,0,sizeof cnt);
        for(int i=0;i<10;++i)
        {
            cnt[i]-=count(a-1,i);
            cnt[i]+=count(b,i);
        }
        for(int i=0;i<10;++i) printf("%d ",cnt[i]);
        printf("\n");
        scanf("%d%d",&a,&b);
    }
    return 0;
}