#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;
const int N=2e5+10;
int arr[N],minnum[N],maxnum[N];
void fun()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    minnum[1]=arr[1];
    maxnum[n]=arr[n];
    for(int i=2;i<=n;++i) minnum[i]=min(minnum[i-1],arr[i]);
    for(int i=n-1;i>=1;--i) maxnum[i]=max(maxnum[i+1],arr[i]);
    for(int i=1;i<=n;++i)
    {
        if(arr[i]==minnum[i]||arr[i]==maxnum[i]) printf("1");
        else printf("0");
    }
    printf("\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}