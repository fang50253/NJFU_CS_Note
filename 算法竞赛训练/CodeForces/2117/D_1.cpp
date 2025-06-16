#include<stdio.h>
#include<string.h>
using namespace std;
const int N=2e5+10;
int arr[N],arr2[N],n;
void fun()
{
    scanf("%d",&n);
    memset(arr2,0,sizeof(arr2));
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    if((arr[1]+arr[n])%(n+1))
    {
        printf("NO\n");
        return;
    }
    int t=(arr[1]+arr[n])/(n+1);
    int y=(arr[1]-t)/(n-1);
    int x=t-y;
    if(x<0||y<0)
    {
        printf("NO\n");
        return;
    }
    for(int i=1;i<=n;++i)
    {
        if(arr[i]!=i*x+(n-i+1)*y)
        {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}