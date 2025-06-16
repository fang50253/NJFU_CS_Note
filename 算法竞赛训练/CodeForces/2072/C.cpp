#include<stdio.h>
#include<string.h>
typedef long long LL;
void fun()
{
    LL n,tgt,idx=0,num[40],cnt=0;
    scanf("%lld%lld",&n,&tgt);
    //将tgt转换为二进制数组
    bool bit[40],bitcpy[40];
    memset(bit,0,sizeof bit);
    memset(bitcpy,0,sizeof bitcpy);
    for(int i=0;tgt;++i,tgt>>=1)
    {
        bit[i]=tgt&1;
        if(tgt&1) num[idx++]=i;
    }//printf("ok");
    for(LL i=(1<<idx)-1;n--;--i)
    {
        LL val=0;
        for(int j=idx-1;j>=0;--j) bitcpy[num[j]]=i>>j&1;
        for(int j=num[idx-1];j>=0;--j)
        {
            val<<=1;
            val+=bitcpy[j]*bit[j];
        }
        printf("%lld ",val);
        if(i==0) i=(1<<idx)-1;
    }
    printf("\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}