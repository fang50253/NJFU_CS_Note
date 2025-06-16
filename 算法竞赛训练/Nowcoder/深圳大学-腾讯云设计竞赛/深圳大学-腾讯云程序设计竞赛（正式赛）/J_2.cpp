#include<stdio.h>
const int N=1e6+10;
typedef long long LL;
LL arr[N];
void fun()
{
    int n,sum=0;
    bool flag=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i]);
        sum^=arr[i];
        if(arr[i]!=1) flag=1;
    }
    if(flag==1)
    {
        if(sum) printf("Akie\n");
        else printf("Jiuhui\n");
    }
    else
    {
        if(n%2) printf("Jiuhui\n");
        else printf("Akie\n");
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}