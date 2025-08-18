#include<stdio.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll a[N],b[N],n;
void fun()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    for(int i=1;i<=n;++i) scanf("%lld",&b[i]);
    if(a[n]!=b[n])
    {
        printf("No\n");
        return;
    }
    for(int i=n-1;i>=1;--i)
    {
        if((a[i]^a[i+1])==b[i]||a[i]==b[i]||(a[i]^b[i+1])==b[i]) continue;
        else
        {
            printf("No\n");
            return;
        }
    }
    printf("Yes\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}