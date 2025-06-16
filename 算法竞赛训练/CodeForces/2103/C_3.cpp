#include<stdio.h>
#include<queue>
#include<string.h>
using namespace std;
const int N=2e5+10;
int arr[N],cnt[N];
void fun()
{
    int n,k,l,r;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&arr[i]);
    for(l=1;l<=n&&arr[l]>k;++l);
    for(r=n;r>0&&arr[r]>k;--r);
    if(r-l>=n/2) printf("Yes\n");
    else printf("No\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}