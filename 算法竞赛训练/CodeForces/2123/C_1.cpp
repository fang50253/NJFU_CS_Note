#include<stdio.h>
using namespace std;
const int N=2e5+10;
int arr[N];
void fun()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    //从前面扫描，寻找最长下降序列
    int front=1;
    for(int i=2;i<=n;++i)
    {
        if(arr[i]<arr[i-1]) ++front;
        else break;
    }
    int back=n;
    for(int i=n-1;i>=1;--i)
    {
        if(arr[i]>arr[i+1]) --back;
        else break;
    }
    if(front>=back)
    {
        for(int i=1;i<=n;++i) printf("1");
        printf("\n");
        return;
    }
    for(int i=1;i<=front;++i) printf("1");
    for(int i=front+1;i<back;++i) printf("0");
    for(int i=back;i<=n;++i) printf("1");
    printf("\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}