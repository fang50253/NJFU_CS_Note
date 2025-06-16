#include<stdio.h>
using namespace std;
const int N=2e5+10;
int arr[N];
void fun()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i+=2) arr[i+1>>1]=i;
    arr[(n>>1)+1]=n;
    for(int i=2,j=n;i<n;i+=2,--j) arr[j]=i;
    for(int i=1;i<=n;++i) printf("%d ",arr[i]);
    printf("\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while (t--) fun();
    return 0;
}