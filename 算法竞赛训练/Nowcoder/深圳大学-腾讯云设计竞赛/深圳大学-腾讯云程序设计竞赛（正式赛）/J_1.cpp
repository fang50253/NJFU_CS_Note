#include<stdio.h>
const int N=1e6+10;
typedef long long LL;
LL arr[N];
void fun()
{
    int n,cnt=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    int i=n;
    while(arr[i]!=1&&i>=1) --i;
    cnt=i;
    while(arr[i]==1&&i>=1) --i;
    cnt-=i;
    if(cnt%2==1) printf("Jiuhui\n");
    else printf("Akie\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}